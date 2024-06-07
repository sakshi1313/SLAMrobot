# TurtleBot3 SLAM Comparison in ROS Foxy

This repository contains a simulation of the TurtleBot3 in ROS Foxy, implementing SLAM with Cartographer and SLAM Toolbox. It also includes a package for adding noise to odometry and the transformation, allowing for a comparison between both SLAM methods under noisy conditions.

## Getting Started

Follow these instructions to get a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

- ROS Foxy installed on your system.
- TurtleBot3 packages installed.
- `rosdep` installed and initialized.

### Installation

1. Clone the repository:
   ```bash
   git clone <link>
   cd <name>
   ```

2. Install dependencies:
   ```bash
   rosdep install --from-paths src --ignore-src -r -y
   ```

3. Build the workspace:
   ```bash
   colcon build
   ```

4. Source the workspace:
   ```bash
   source install/setup.bash
   ```

## Running the Simulation

### Cartographer SLAM

1. Launch the TurtleBot3 simulation in Gazebo:
   ```bash
   ros2 launch turtlebot3_gazebo turtlebot3_house.launch.py
   ```

2. Launch Cartographer SLAM:
   ```bash
   ros2 launch turtlebot3_cartographer cartographer.launch.py use_sim_time:=True
   ```

3. Control the TurtleBot3 with the keyboard:
   ```bash
   ros2 run turtlebot3_teleop teleop_keyboard
   ```

4. Add noise to the odometry and transformation:
   ```bash
   ros2 run task noisyodom
   ```

### SLAM Toolbox

1. Launch the TurtleBot3 simulation in Gazebo (if not already running):
   ```bash
   ros2 launch turtlebot3_gazebo turtlebot3_house.launch.py
   ```

2. Launch SLAM Toolbox:
   ```bash
   ros2 launch slam_toolbox online_sync_launch.py
   ```

3. Open RViz for visualization:
   ```bash
   ros2 run rviz2 rviz2
   ```

## Package Overview

- `turtlebot3_gazebo`: Contains the simulation environment for TurtleBot3.
- `turtlebot3_cartographer`: SLAM implementation using Cartographer.
- `slam_toolbox`: SLAM implementation using SLAM Toolbox.
- `task`: Contains the node for adding noise to the odometry and transformation.

## Comparing SLAM Algorithms

After running the simulations, you can compare the performance of Cartographer and SLAM Toolbox by observing the maps generated in RViz and the impact of the added noise on the odometry.


## Acknowledgments

- [Cartographer](https://google-cartographer-ros.readthedocs.io/en/latest/)
- [SLAM Toolbox](https://github.com/SteveMacenski/slam_toolbox)
- [TurtleBot3](https://emanual.robotis.com/docs/en/platform/turtlebot3/overview/)

---

Feel free to adjust the content as needed to better fit your repository and any additional details you may want to include.
