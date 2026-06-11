# TODO: copy only necessary ROS components from carla/ros-bridge and remove the rest
# mkdir -p $WORKSPACE/src/upstream
# git clone --recurse-submodules https://${GIT_HTTPS_USER}:${GIT_HTTPS_PASSWORD}@gitlab.ika.rwth-aachen.de/fb-fi/simulation/carla/ros-bridge.git
# mv ros-bridge/rviz_carla_plugin $WORKSPACE/src/upstream
# mv ros-bridge/carla_ros_scenario_runner_types $WORKSPACE/src/upstream
# rm -rf ros-bridge

# re-run rosdep install after adding more packages
cd $WORKSPACE
apt-get update
rosdep update --rosdistro ${ROS_DISTRO}
OS="ubuntu:$(lsb_release -c | awk '{print $2}')"
if [[ "$ROS_DISTRO" = "rolling" && "$OS" = "ubuntu:focal" ]]; then OS="ubuntu:jammy"; fi
rosdep install --os $OS -y --from-paths src --ignore-src --skip-keys carla_msgs
rm -rf /var/lib/apt/lists/*

# download and set up alias for rviz dark mode
mkdir -p /opt/ros/jazzy/share/rviz2/style
curl -o /opt/ros/jazzy/share/rviz2/style/dark.qss https://raw.githubusercontent.com/davutcanakbas/rviz_dark_theme/refs/heads/main/rviz/dark.qss
echo "alias darkviz2='rviz2 --stylesheet /opt/ros/jazzy/share/rviz2/style/dark.qss'" >> /root/.bashrc
