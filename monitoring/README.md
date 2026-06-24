# `monitoring`

Monitoring launch package

The default RViz config file can be overridden using the `config` launch argument.

## Launch Files

### [`monitoring.launch.py`](launch/monitoring.launch.py)

| Argument | Default | Description |
| --- | --- | --- |
| `name` | `"monitoring"` | Node name |
| `namespace` | `""` | Node namespace |
| `config` | `"/docker-ros/ws/install/monitoring/share/monitoring/config/conf.rviz"` | Path to rviz config file |
| `log_level` | `"info"` | ROS logging level (debug, info, warn, error, fatal) |
| `use_sim_time` | `"false"` | Use simulation clock |
