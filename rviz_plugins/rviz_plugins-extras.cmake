# Ensure Qt5::Widgets target is available for consumers of rviz_plugins.
find_package(Qt5 REQUIRED QUIET COMPONENTS Widgets)
