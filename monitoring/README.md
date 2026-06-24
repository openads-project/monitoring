# `monitoring`

Monitoring launch package

## Launch Files

### [`monitoring.launch.py`](launch/monitoring.launch.py)

| Argument | Default | Description |
| --- | --- | --- |
| `name` | `"monitoring"` | Node name |
| `namespace` | `""` | Node namespace |
| `config` | `os.path.join(get_package_share_directory("monitoring"), "config", "conf.rviz")` | Path to rviz config file |
| `log_level` | `"info"` | ROS logging level (debug, info, warn, error, fatal) |
| `use_sim_time` | `"false"` | Use simulation clock |
