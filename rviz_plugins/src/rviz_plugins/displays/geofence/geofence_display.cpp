/*
 * Geofence display - renders polygon edges as thin 3D quads with vertical fade.
 */

#include "rviz_plugins/displays/geofence/geofence_display.hpp"

#include <OgreManualObject.h>
#include <OgreMaterialManager.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTechnique.h>

#include <string>
#include <vector>

#include "rviz_common/display_context.hpp"
#include "rviz_common/frame_manager_iface.hpp"
#include "rviz_common/logging.hpp"
#include "rviz_common/properties/color_property.hpp"
#include "rviz_common/properties/float_property.hpp"
#include "rviz_common/validate_floats.hpp"
#include "rviz_rendering/material_manager.hpp"

namespace rviz_plugins {
namespace displays {

namespace {
bool validateFloats(const geometry_msgs::msg::PolygonStamped::ConstSharedPtr& msg) {
  return rviz_common::validateFloats(msg->polygon.points);
}
}  // namespace

GeofenceDisplay::GeofenceDisplay() {
  color_property_ = new rviz_common::properties::ColorProperty("Color", QColor(25, 255, 0), "Base color for geofence edges.",
                                                               this, SLOT(queueRender()));

  bottom_alpha_property_ = new rviz_common::properties::FloatProperty(
      "Bottom Alpha", 0.8f, "Alpha at the bottom of the edge (0..1).", this, SLOT(queueRender()));
  bottom_alpha_property_->setMin(0.0);
  bottom_alpha_property_->setMax(1.0);

  top_alpha_property_ = new rviz_common::properties::FloatProperty("Top Alpha", 0.05f, "Alpha at the top of the edge (0..1).",
                                                                   this, SLOT(queueRender()));
  top_alpha_property_->setMin(0.0);
  top_alpha_property_->setMax(1.0);

  height_property_ = new rviz_common::properties::FloatProperty("Height", 2.0f, "Extrusion height of the edges (meters).", this,
                                                                SLOT(queueRender()));
  height_property_->setMin(0.0);

  thickness_property_ = new rviz_common::properties::FloatProperty(
      "Thickness", 0.05f, "Visual thickness of the edge band (meters).", this, SLOT(queueRender()));
  thickness_property_->setMin(0.0);

  static int geofence_count = 0;
  std::string material_name = "GeofenceMaterial" + std::to_string(geofence_count++);
  material_ = rviz_rendering::MaterialManager::createMaterialWithNoLighting(material_name);
  material_->setCullingMode(Ogre::CULL_NONE);
}

GeofenceDisplay::~GeofenceDisplay() {
  if (initialized()) {
    scene_manager_->destroyManualObject(manual_object_);
  }
}

void GeofenceDisplay::onInitialize() {
  MFDClass::onInitialize();
  manual_object_ = scene_manager_->createManualObject();
  manual_object_->setDynamic(true);
  scene_node_->attachObject(manual_object_);
}

void GeofenceDisplay::reset() {
  MFDClass::reset();
  manual_object_->clear();
}

void GeofenceDisplay::processMessage(geometry_msgs::msg::PolygonStamped::ConstSharedPtr msg) {
  if (!validateFloats(msg)) {
    setStatus(rviz_common::properties::StatusProperty::Error, "Topic",
              "Message contained invalid floating point values (nans or infs)");
    return;
  }

  rclcpp::Time msg_time(msg->header.stamp, RCL_ROS_TIME);
  if (!updateFrame(msg->header.frame_id, msg_time)) {
    setMissingTransformToFixedFrame(msg->header.frame_id);
    return;
  }
  setTransformOk();

  manual_object_->clear();

  const auto base_color_qt = color_property_->getColor();
  Ogre::ColourValue base_color(static_cast<float>(base_color_qt.redF()), static_cast<float>(base_color_qt.greenF()),
                               static_cast<float>(base_color_qt.blueF()), 1.0f);

  const float alpha_bottom = std::max(0.0f, std::min(1.0f, bottom_alpha_property_->getFloat()));
  const float alpha_top = std::max(0.0f, std::min(1.0f, top_alpha_property_->getFloat()));
  const float height = std::max(0.0f, height_property_->getFloat());
  const float thickness = std::max(0.0f, thickness_property_->getFloat());

  // If any alpha < 1, enable alpha blending
  rviz_rendering::MaterialManager::enableAlphaBlending(material_, std::min(alpha_bottom, alpha_top));

  const size_t n = msg->polygon.points.size();
  if (n < 2 || height <= 0.0f) {
    return;
  }

  // Two quads per edge if thickness > 0, otherwise one quad centered on the edge normal.
  // We'll use OT_TRIANGLE_LIST and per-vertex colors for vertical fade.
  manual_object_->begin(material_->getName(), Ogre::RenderOperation::OT_TRIANGLE_LIST, "rviz_rendering");

  // Helper lambda to push a quad as two triangles with vertical fade.
  unsigned int vertex_index = 0;
  auto add_quad = [&](const Ogre::Vector3& b0, const Ogre::Vector3& b1, const Ogre::Vector3& t1, const Ogre::Vector3& t0) {
    // Vertex order: b0, b1, t1, t0
    const unsigned int start_index = vertex_index;

    Ogre::ColourValue bottom_color = base_color;
    bottom_color.a = alpha_bottom;
    Ogre::ColourValue top_color = base_color;
    top_color.a = alpha_top;

    manual_object_->position(b0);
    manual_object_->colour(bottom_color);
    manual_object_->position(b1);
    manual_object_->colour(bottom_color);
    manual_object_->position(t1);
    manual_object_->colour(top_color);
    manual_object_->position(t0);
    manual_object_->colour(top_color);

    // Two triangles: (0,1,2) and (0,2,3)
    manual_object_->triangle(start_index + 0, start_index + 1, start_index + 2);
    manual_object_->triangle(start_index + 0, start_index + 2, start_index + 3);
    vertex_index += 4;
  };

  const Ogre::Vector3 z_up(0.0f, 0.0f, 1.0f);

  for (size_t i = 0; i < n; ++i) {
    const auto& p0 = msg->polygon.points[i];
    const auto& p1 = msg->polygon.points[(i + 1) % n];

    Ogre::Vector3 P0(p0.x, p0.y, p0.z);
    Ogre::Vector3 P1(p1.x, p1.y, p1.z);

    Ogre::Vector3 edge = P1 - P0;
    Ogre::Vector3 edge_xy(edge.x, edge.y, 0.0f);
    if (edge_xy.squaredLength() < 1e-10f) {
      continue;  // skip degenerate edge
    }
    edge_xy.normalise();
    Ogre::Vector3 normal(-edge_xy.y, edge_xy.x, 0.0f);  // perpendicular in XY

    const float hw = thickness * 0.5f;

    // Base and top points for this edge
    Ogre::Vector3 B0 = P0;
    Ogre::Vector3 B1 = P1;
    Ogre::Vector3 T0 = P0 + height * z_up;
    Ogre::Vector3 T1 = P1 + height * z_up;

    if (thickness > 1e-6f) {
      // Left face (offset -normal)
      Ogre::Vector3 off = -normal * hw;
      add_quad(B0 + off, B1 + off, T1 + off, T0 + off);
      // Right face (offset +normal)
      off = normal * hw;
      add_quad(B0 + off, B1 + off, T1 + off, T0 + off);
    } else {
      // Single centered face: create a very thin band by offsetting half-width on each side
      Ogre::Vector3 off = normal * 1e-3f;  // virtually zero thickness
      add_quad(B0 - off, B1 - off, T1 - off, T0 - off);
      add_quad(B0 + off, B1 + off, T1 + off, T0 + off);
    }
  }

  manual_object_->end();
}

}  // namespace displays
}  // namespace rviz_plugins

#include <pluginlib/class_list_macros.hpp>  // NOLINT
PLUGINLIB_EXPORT_CLASS(rviz_plugins::displays::GeofenceDisplay, rviz_common::Display)
