#! /usr/bin/env python
 
import rospy
from sensor_msgs.msg import LaserScan
#roslib.load_manifest('rplidar_ros')
import math
from visualization_msgs.msg import Marker 
import numpy as np 
from rplidar_ros.srv import laser

global value, distance


def laser_marker(req):
	
    for i in range(len(ranges)):

	marker_pub = rospy.Publisher('visualization_marker', Marker, queue_size=300)

	#visualization_msgs::Marker marker
	marker.header.frame_id = "base_link"
	marker.header.stamp = now
	marker.ns = "my_namespace"
	marker.id = 0
	marker.type = Marker.SPHERE
	marker.action = Marker.ADD
	marker.pose.position.x = ranges[i] * math.cos(value)
	marker.pose.position.y = ranges[i] * math.sin(value)
	marker.pose.position.z = 0
	marker.pose.orientation.x = 0.0
	marker.pose.orientation.y = 0.0
	marker.pose.orientation.z = 0.0
	marker.pose.orientation.w = 1.0
	marker.scale.x = 1
	marker.scale.y = 0.1
	marker.scale.z = 0.1
	marker.color.a = 1.0 # Don't forget to set the alpha!
	marker.color.r = 0.0
	marker.color.g = 1.0
	marker.color.b = 0.0
	#only if using a MESH_RESOURCE marker type:
	marker.mesh_resource = "package://pr2_description/meshes/base_v0/base.dae"
	vis_pub.publish( marker )

	return laserResponse(marker)
 
def callback(msg):
    #print len(msg.ranges)
    value = int(angle*4)
    distance = msg.ranges[value]

def laser_server():
	#rospy.init_node('laser_server')
        s = rospy.Service('laser_server',laser, laser_marker)
	print ('Publishing a Marker')
	#rospy.spin()

if __name__ == '__main__':
   
	rospy.init_node('scan_values')
	sub = rospy.Subscriber('/scan', LaserScan, callback)
	laser_server()
	rospy.spin()

