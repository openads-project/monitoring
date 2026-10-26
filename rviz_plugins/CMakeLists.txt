cmake_minimum_required(VERSION 3.5)

project(rviz_plugins)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Wnon-virtual-dtor -Woverloaded-virtual)
endif()

find_package(ament_cmake REQUIRED)
find_package(action_msgs REQUIRED)
find_package(ament_index_cpp REQUIRED)
find_package(rviz_common REQUIRED)
find_package(rviz_rendering REQUIRED)
find_package(rviz_ogre_vendor REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(pluginlib REQUIRED)
find_package(rcl_interfaces REQUIRED)
find_package(rclcpp REQUIRED)
find_package(route_planning_msgs REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

qt5_wrap_cpp(rviz_plugins_moc_files
  include/rviz_plugins/displays/geofence/geofence_display.hpp
  include/rviz_plugins/panels/plan_route/plan_route_panel.hpp
)

add_library(rviz_plugins SHARED
  ${rviz_plugins_moc_files}
  src/rviz_plugins/displays/geofence/geofence_display.cpp
  src/rviz_plugins/panels/plan_route/plan_route_panel.cpp
)

target_include_directories(rviz_plugins PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

ament_target_dependencies(rviz_plugins
  action_msgs
  ament_index_cpp
  geometry_msgs
  pluginlib
  rcl_interfaces
  rclcpp
  route_planning_msgs
  rviz_common
  rviz_rendering
  rviz_ogre_vendor
)

target_link_libraries(rviz_plugins Qt5::Widgets yaml-cpp)

target_compile_definitions(rviz_plugins PRIVATE "RVIZ_PLUGINS_BUILDING_LIBRARY")

pluginlib_export_plugin_description_file(rviz_common plugin_description.xml)

install(
  TARGETS rviz_plugins
  EXPORT rviz_plugins
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(
  DIRECTORY include/
  DESTINATION include
)

install(
  FILES plugin_description.xml
  DESTINATION share/${PROJECT_NAME}
)

install(
  DIRECTORY config/
  DESTINATION share/${PROJECT_NAME}/config
)

ament_export_include_directories(include)
ament_export_targets(rviz_plugins HAS_LIBRARY_TARGET)
ament_export_dependencies(
  action_msgs
  ament_index_cpp
  geometry_msgs
  pluginlib
  rcl_interfaces
  rclcpp
  route_planning_msgs
  rviz_common
  rviz_rendering
  rviz_ogre_vendor
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_clang_format_CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../.vscode/format/.clang-format)
  set(ament_cmake_clang_tidy_CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../.vscode/lint/.clang-tidy)
  set(ament_cmake_flake8_CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../.vscode/lint/ament_flake8.ini)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
