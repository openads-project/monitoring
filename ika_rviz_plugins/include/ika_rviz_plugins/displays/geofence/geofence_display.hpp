/*
 * Geofence display for geometry_msgs::msg::PolygonStamped
 */

#ifndef IKA_RVIZ_PLUGINS__DISPLAYS__GEOFENCE__GEOFENCE_DISPLAY_HPP_
#define IKA_RVIZ_PLUGINS__DISPLAYS__GEOFENCE__GEOFENCE_DISPLAY_HPP_

#include "geometry_msgs/msg/polygon_stamped.hpp"

#include "rviz_common/message_filter_display.hpp"

#include "ika_rviz_plugins/visibility_control.hpp"

namespace Ogre {
class ManualObject;
}

namespace rviz_common {
namespace properties {
class ColorProperty;
class FloatProperty;
}  // namespace properties
}  // namespace rviz_common

namespace ika_rviz_plugins {
namespace displays {

class IKA_RVIZ_PLUGINS_PUBLIC GeofenceDisplay : public rviz_common::MessageFilterDisplay<geometry_msgs::msg::PolygonStamped> {
  Q_OBJECT

 public:
  GeofenceDisplay();
  ~GeofenceDisplay() override;

  void onInitialize() override;
  void reset() override;

 protected:
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
}  // namespace ika_rviz_plugins

#endif  // IKA_RVIZ_PLUGINS__DISPLAYS__GEOFENCE__GEOFENCE_DISPLAY_HPP_
