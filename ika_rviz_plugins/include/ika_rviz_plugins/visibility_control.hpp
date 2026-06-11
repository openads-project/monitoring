/*
 * Export macros to control symbol visibility on different platforms.
 */

#ifndef IKA_RVIZ_PLUGINS__VISIBILITY_CONTROL_HPP_
#define IKA_RVIZ_PLUGINS__VISIBILITY_CONTROL_HPP_

// Borrowed from standard ROS 2 visibility control patterns.
#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define IKA_RVIZ_PLUGINS_EXPORT __attribute__((dllexport))
#define IKA_RVIZ_PLUGINS_IMPORT __attribute__((dllimport))
#else
#define IKA_RVIZ_PLUGINS_EXPORT __declspec(dllexport)
#define IKA_RVIZ_PLUGINS_IMPORT __declspec(dllimport)
#endif
#ifdef IKA_RVIZ_PLUGINS_BUILDING_LIBRARY
#define IKA_RVIZ_PLUGINS_PUBLIC IKA_RVIZ_PLUGINS_EXPORT
#else
#define IKA_RVIZ_PLUGINS_PUBLIC IKA_RVIZ_PLUGINS_IMPORT
#endif
#define IKA_RVIZ_PLUGINS_PUBLIC_TYPE IKA_RVIZ_PLUGINS_PUBLIC
#define IKA_RVIZ_PLUGINS_LOCAL
#else
#define IKA_RVIZ_PLUGINS_EXPORT __attribute__((visibility("default")))
#define IKA_RVIZ_PLUGINS_IMPORT
#if __GNUC__ >= 4
#define IKA_RVIZ_PLUGINS_PUBLIC __attribute__((visibility("default")))
#define IKA_RVIZ_PLUGINS_LOCAL __attribute__((visibility("hidden")))
#else
#define IKA_RVIZ_PLUGINS_PUBLIC
#define IKA_RVIZ_PLUGINS_LOCAL
#endif
#define IKA_RVIZ_PLUGINS_PUBLIC_TYPE
#endif

#endif  // IKA_RVIZ_PLUGINS__VISIBILITY_CONTROL_HPP_
