# USAN

This repository contains packages developed for proposed USAN architecture, developed during  summer'19

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. 

### Prerequisites

What things you need to install the software and how to install them

```
*leggedrobotics/darknet_ros
*angusleigh/leg_tracker
*rplidar_ros
*rosaria

### Installing

All their packages can be installed from their github repos.

When installing rosaria:

Install libaria: header files 

https://web.archive.org/web/20180205212122/http://robots.mobilerobots.com/wiki/Aria

This is the archive. Download based on the description of your machine. 

Then do a git clone of the rosaria pacakge (linked below)

https://github.com/amor-ros-pkg/rosaria

Need to be done in this order

## Running

Follow the instructions below:

```
To launch the picture frame localization: run the following commands...
* roslaunch usb_cam usb_cam-test.launch
* roslaunch darknet_ros yolo_v3_custom.launch
* rosrun cam_angle image_sub.py
* rosrun box_sub box_subscriber

To launch the P3DX Navigation ...

* roslaunch pioneer_nav pioneer_nav.launch 
* rosrun rosaria Rosaria 
* roslaunch p3dx_description rviz.launch      

Make sure laser is USB 0 and the USB to serial cable from the pioneer is USB1. Always configure it using:

* chmod a+rw /dev/ttyUSB0
* chmod a+rw /dev/ttyUSB1

In order to make a map
* roslaunch teleop_twist_joy teleop.launch (Press the LB  and the arrow keys in order to move the robot around)
* roslaunch gmapping slam_gmapping_pr2.launch


```

## Authors

* **Fausto Vega** - *REU student* - [Link](https://github.com/vegaf1)
* **Santosh Balajee Banisetty** - *Grad Mentor* - [Link](https://github.com/SantoshBanisetty)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## Acknowledgments

* Hat tip to anyone whose code was used
* Inspiration
* etc

