cmake_minimum_required(VERSION 3.8)
project(monitoring)

find_package(rosidl_default_generators REQUIRED)

ament_export_dependencies(rosidl_default_runtime)

ament_package()

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
  OPTIONAL
)

install(DIRECTORY config
  DESTINATION share/${PROJECT_NAME}
)
