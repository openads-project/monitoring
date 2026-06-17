# `monitoring`

Monitoring launch package

## Launch Files

### [`monitoring.launch.py`](launch/monitoring.launch.py)

| Argument | Default | Description |
| --- | --- | --- |
| `name` | `"monitoring"` | node name |
| `namespace` | `""` | node namespace |
| `config` | `os.path.join(get_package_share_directory("monitoring"), "config", "conf.rviz")` | path to rviz config file |
| `log_level` | `"info"` | ROS logging level (debug, info, warn, error, fatal) |
| `use_sim_time` | `"false"` | use simulation clock |
