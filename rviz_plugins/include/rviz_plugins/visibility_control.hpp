/*
 * Export macros to control symbol visibility on different platforms.
 */

#ifndef RVIZ_PLUGINS__VISIBILITY_CONTROL_HPP_
#define RVIZ_PLUGINS__VISIBILITY_CONTROL_HPP_

// Borrowed from standard ROS 2 visibility control patterns.
#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define RVIZ_PLUGINS_EXPORT __attribute__((dllexport))
#define RVIZ_PLUGINS_IMPORT __attribute__((dllimport))
#else
#define RVIZ_PLUGINS_EXPORT __declspec(dllexport)
#define RVIZ_PLUGINS_IMPORT __declspec(dllimport)
#endif
#ifdef RVIZ_PLUGINS_BUILDING_LIBRARY
#define RVIZ_PLUGINS_PUBLIC RVIZ_PLUGINS_EXPORT
#else
#define RVIZ_PLUGINS_PUBLIC RVIZ_PLUGINS_IMPORT
#endif
#define RVIZ_PLUGINS_PUBLIC_TYPE RVIZ_PLUGINS_PUBLIC
#define RVIZ_PLUGINS_LOCAL
#else
#define RVIZ_PLUGINS_EXPORT __attribute__((visibility("default")))
#define RVIZ_PLUGINS_IMPORT
#if __GNUC__ >= 4
#define RVIZ_PLUGINS_PUBLIC __attribute__((visibility("default")))
#define RVIZ_PLUGINS_LOCAL __attribute__((visibility("hidden")))
#else
#define RVIZ_PLUGINS_PUBLIC
#define RVIZ_PLUGINS_LOCAL
#endif
#define RVIZ_PLUGINS_PUBLIC_TYPE
#endif

#endif  // RVIZ_PLUGINS__VISIBILITY_CONTROL_HPP_
