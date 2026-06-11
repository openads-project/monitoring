cmake_minimum_required(VERSION 3.5)

project(ika_rviz_plugins)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Wnon-virtual-dtor -Woverloaded-virtual)
endif()

find_package(ament_cmake REQUIRED)
find_package(rviz_common REQUIRED)
find_package(rviz_rendering REQUIRED)
find_package(rviz_ogre_vendor REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(pluginlib REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

qt5_wrap_cpp(ika_rviz_plugins_moc_files
  include/ika_rviz_plugins/displays/geofence/geofence_display.hpp
)

add_library(ika_rviz_plugins SHARED
  ${ika_rviz_plugins_moc_files}
  src/ika_rviz_plugins/displays/geofence/geofence_display.cpp
)

target_include_directories(ika_rviz_plugins PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

ament_target_dependencies(ika_rviz_plugins
  geometry_msgs
  pluginlib
  rviz_common
  rviz_rendering
  rviz_ogre_vendor
)

target_link_libraries(ika_rviz_plugins Qt5::Widgets)

target_compile_definitions(ika_rviz_plugins PRIVATE "IKA_RVIZ_PLUGINS_BUILDING_LIBRARY")

pluginlib_export_plugin_description_file(rviz_common plugin_description.xml)

install(
  TARGETS ika_rviz_plugins
  EXPORT ika_rviz_plugins
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

ament_export_include_directories(include)
ament_export_targets(ika_rviz_plugins HAS_LIBRARY_TARGET)
ament_export_dependencies(
  geometry_msgs
  pluginlib
  rviz_common
  rviz_rendering
  rviz_ogre_vendor
)

ament_package()
