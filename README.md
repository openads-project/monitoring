# monitoring

<p align="center">
  <a href="https://github.com/openads-project"><img src="https://img.shields.io/badge/OpenADS-f5ff01"/></a>
  <a href="https://www.ros.org"><img src="https://img.shields.io/badge/ROS 2-jazzy-22314e"/></a>
  <a href="https://github.com/openads-project/monitoring/releases/latest"><img src="https://img.shields.io/github/v/release/openads-project/monitoring"/></a>
  <a href="https://github.com/openads-project/monitoring/blob/main/LICENSE"><img src="https://img.shields.io/github/license/openads-project/monitoring"/></a>
  <br>
  <a href="https://github.com/openads-project/monitoring/actions/workflows/docker-ros.yml"><img src="https://github.com/openads-project/monitoring/actions/workflows/docker-ros.yml/badge.svg"/></a>
  <a href="https://github.com/openads-project/monitoring/actions/workflows/compose-oci.yml"><img src="https://github.com/openads-project/monitoring/actions/workflows/compose-oci.yml/badge.svg"/></a>
  <a href="https://openads-project.github.io/monitoring"><img src="https://github.com/openads-project/monitoring/actions/workflows/docs.yml/badge.svg"/></a>
  <a href="https://github.com/openads-project/monitoring/actions/workflows/consistency.yml"><img src="https://github.com/openads-project/monitoring/actions/workflows/consistency.yml/badge.svg"/></a>
</p>

This repository provides a monitoring and visualization container including, e.g. [RViz](https://github.com/ros2/rviz) and [RQt](https://docs.ros.org/en/rolling/Concepts/Intermediate/About-RQt.html), as well as, all relevant definitions and visualization plugins for messages used in [OpenADS](https://github.com/openads-project/).

<p align="center">
  <strong>🚀 <a href="#-quick-start">Quick Start</a></strong> • <strong>💻 <a href="#-development">Development</a></strong> • <strong>📝 <a href="#-documentation">Documentation</a></strong>
</p>


> [!IMPORTANT]
> This repository is part of [***OpenADS***](https://github.com/openads-project), the *Open Automated Driving Systems* project. *OpenADS* and its modules have been initiated and are currently being maintained by the [**Institute for Automotive Engineering (ika) at RWTH Aachen University**](https://www.ika.rwth-aachen.de/de/).


## 🚀 Quick Start

1. Start a container of the pre-built runtime image with support for GPU usage and graphical output.
    ```bash
    docker run --gpus all --volume /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY --rm -it ghcr.io/openads-project/monitoring:latest bash
    ```
1. In the container, you can run graphical tools for monitoring and visualization or record data. For the latter, make sure to mount a local folder into the container with the `--volume` argument.

    ```bash
    # RViz: message visualization
    rviz2

    # RQt: Various graphical user interfaces
    rqt

    # ROS 2 Bag: Record and replay ROS communication
    ros2 bag record -a
    ros2 bag play rosbag2_*
    ```

## 💻 Development

### Set up Development Environment

1. Clone the repository.
    ```bash
    git clone https://github.com/openads-project/monitoring.git
    ```
1. Initialize the [`.openads-dev-environment`](https://github.com/openads-project/openads-dev-environment) submodule containing development environment configuration.
    ```bash
    cd monitoring
    git submodule update --init --recursive
    ```
1. Open the repository in [Visual Studio Code](https://code.visualstudio.com).
    ```bash
    code .
    ```
1. Install the recommended VS Code extensions.
    > *Ctrl+Shift+P / Extensions: Show Recommended Extensions / Install Workspace Recommended Extensions (Cloud Download Icon)*
1. Reopen the repository in a [Dev Container](https://code.visualstudio.com/docs/devcontainers/containers).
    > *Ctrl+Shift+P / Dev Containers: Rebuild and Reopen in Container*

### Build

> *Ctrl+Shift+B*

```bash
colcon build
```

### Run Tests

> *Ctrl+Shift+P / Tasks: Run Test Task*

```bash
colcon build --cmake-args -DCMAKE_EXPORT_COMPILE_COMMANDS=1
colcon test
colcon test-result --verbose
```


## 📝 Documentation

Package and node interfaces are documented in the respective package READMEs listed below. Implementation details are found in the [Source Code Documentation](https://openads-project.github.io/monitoring).

| Package | Description |
| --- | --- |
| [rviz_plugins](rviz_plugins/README.md) | Custom RViz plugins not directly associated with a specific repository |

## ⚖️ Licensing

The source code in this repository is licensed under Apache-2.0, see [LICENSE](LICENSE). Container images provided by this repository may contain third-party software shipped with their own license terms.

## 🙏 Acknowledgements

Development and maintenance of this repository are supported by the following projects. We acknowledge the funding of the respective institutions.

| Project | Funding Institution | Grant Number |
| --- | --- | --- |
| [AIGGREGATE](https://aiggregate.eu/) | 🇪🇺 European Union | 101202457 |
| [AIthena](https://aithena.eu/) | 🇪🇺 European Union | 101076754 |
| [autotech.agil](https://www.autotechagil.de/) | 🇩🇪 Federal Ministry for Research, Technology and Space (BMFTR) | 01IS22088A |

<p>
  <img src="https://www.drought.uni-freiburg.de/stressres/images/bmftr-logo/image" height=70>
  <img src="https://ec.europa.eu/regional_policy/images/information-sources/logo-download-center/eu_funded_en.jpg" height=70>
</p>

<sup><sub>Funded by the European Union. Views and opinions expressed are however those of the author(s) only and do not necessarily reflect those of the European Union or the European Climate, Infrastructure and Environment Executive Agency (CINEA). Neither the European Union nor CINEA can be held responsible for them.</sup></sup>
