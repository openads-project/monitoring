#!/usr/bin/env bash
set -euo pipefail

# Publish a dummy geometry_msgs/PolygonStamped in the map frame (by default)
# Usage:
#   ./scripts/publish_dummy_geofence.sh [<topic> [<frame_id> [<rate_hz>]]]
# Examples:
#   ./scripts/publish_dummy_geofence.sh               # /geofence, map, 1 Hz
#   ./scripts/publish_dummy_geofence.sh /geofence map 5

TOPIC="${1:-/geofence}"
FRAME_ID="${2:-map}"
RATE="${3:-1}"

echo "Publishing dummy polygon to ${TOPIC} in frame '${FRAME_ID}' at ${RATE} Hz..."

# A simple pentagon-like geofence footprint (meters)
read -r -d '' MSG << YAML || true
header:
  frame_id: ${FRAME_ID}
polygon:
  points:
  - {x: 0.0,  y: 0.0,  z: 0.0}
  - {x: 10.0, y: 0.0,  z: 0.0}
  - {x: 10.0, y: 6.0,  z: 0.0}
  - {x: 5.0,  y: 10.0, z: 0.0}
  - {x: 0.0,  y: 6.0,  z: 0.0}
YAML

ros2 topic pub -r "${RATE}" "${TOPIC}" geometry_msgs/msg/PolygonStamped "${MSG}"
