# ROS_coraledge_inference


## Prerequisites:
1. A linux Machine x86_64 with ROS installed
2. Optional - EdgeTPU for NN acceleration

## Dependencies:
Links attached for your reference
1. [OpenCV](https://linuxize.com/post/how-to-install-opencv-on-ubuntu-18-04/)
2. [Upgrade GCC](https://www.youtube.com/watch?v=vVzshfYSgRk) - Upgrade your gcc and g++ to the latest version. Don't worry they are always backward compatible.
```bash
$ sudo apt install libgtk2.0-dev
$ sudo apt search libgtk2.0-dev
```
## Build:
```bash
$ cd catkin_ws/src
$ git clone https://github.com/Eashwar93/ROS_coraledge_inference.git
$ cd ..
$ catkin_make
$ source devel/setup.bash
```
## Params:
```bash
$ cd src/ROS_coraledge_inference/launch
```
You can find the following parameters in the coral_pose_inference.launch file:

1. Input_image_topic - Name of the camera topic to subscribe to
2. Output_image_topic - Name of the topic to publish the Inference result to
3. model_path - Path of the posenet model
4. pose_threshold - Overall thresshold for the pose-estimate above which will be processed for keypoint estimation
5. keypoint_threshold - Threshold of keypoint above which will be displayed
6. image_height - Output Image Height
7. image_width - Output Image Width
8. with_edgetpu - Set it to `True` if you have an Edgetpu connected to your computer else `False`

## Launch:
```bash
$ roslaunch ros_coraledge_inference coral_pose_inference.launch
```

## Nodes:
pose_estimation
