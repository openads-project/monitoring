// Copyright Institute for Automotive Engineering (ika), RWTH Aachen University
// SPDX-License-Identifier: Apache-2.0

/*
 * Geofence display for geometry_msgs::msg::PolygonStamped
 */

#ifndef RVIZ_PLUGINS__DISPLAYS__GEOFENCE__GEOFENCE_DISPLAY_HPP_
#define RVIZ_PLUGINS__DISPLAYS__GEOFENCE__GEOFENCE_DISPLAY_HPP_

#include "geometry_msgs/msg/polygon_stamped.hpp"

#include "rviz_common/message_filter_display.hpp"

#include "rviz_plugins/visibility_control.hpp"

namespace Ogre {
class ManualObject;
}

namespace rviz_common {
namespace properties {
class ColorProperty;
class FloatProperty;
}  // namespace properties
}  // namespace rviz_common

namespace rviz_plugins {
namespace displays {

class RVIZ_PLUGINS_PUBLIC GeofenceDisplay : public rviz_common::MessageFilterDisplay<geometry_msgs::msg::PolygonStamped> {
  Q_OBJECT

 public:
  /**
   * @brief Construct a new GeofenceDisplay.
   */
  GeofenceDisplay();

  /**
   * @brief Destroy the GeofenceDisplay.
   */
  ~GeofenceDisplay() override;

  /**
   * @brief Initialize display resources and properties.
   */
  void onInitialize() override;

  /**
   * @brief Reset the display and clear all rendered data.
   */
  void reset() override;

 protected:
  /**
   * @brief Process an incoming geofence polygon message.
   *
   * @param msg Incoming polygon-stamped geofence message.
   */
  void processMessage(geometry_msgs::msg::PolygonStamped::ConstSharedPtr msg) override;

 private:
  Ogre::ManualObject* manual_object_;
  Ogre::MaterialPtr material_;

  // Properties
  rviz_common::properties::ColorProperty* color_property_;
  rviz_common::properties::FloatProperty* bottom_alpha_property_;
  rviz_common::properties::FloatProperty* top_alpha_property_;
  rviz_common::properties::FloatProperty* height_property_;
  rviz_common::properties::FloatProperty* thickness_property_;
};

}  // namespace displays
}  // namespace rviz_plugins

#endif  // RVIZ_PLUGINS__DISPLAYS__GEOFENCE__GEOFENCE_DISPLAY_HPP_
