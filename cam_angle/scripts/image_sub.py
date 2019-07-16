#!/usr/bin/env python
from __future__ import print_function

import roslib
import numpy as np
roslib.load_manifest('cam_angle')
import sys
import rospy
import cv2
from std_msgs.msg import String
from cam_angle.srv import *
from threading import Thread
import math
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError

width = 640 # Savthat rosrunes the pixel width of the video 
height = 480 #Saves the pixel height of the video
center_x = width/2 # Locates the center of the camera field of view x
center_y = height/2 # Locates the center of the camera field of view y
pi = 3.14159


class image_converter:

    def __init__(self):
        self.image_pub = rospy.Publisher("image_topic_2",Image,1000)

        self.bridge = CvBridge()
        self.image_sub = rospy.Subscriber("/usb_cam/image_raw",Image,self.callback)

    def callback(self,data):
        try:
            cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
        except CvBridgeError as e:
            print(e)

        (rows,cols,channels) = cv_image.shape
        if cols > 60 and rows > 60 :
            cv2.circle(cv_image, (50,50), 10, 255)

        cv2.imshow("Image window", cv_image)
        cv2.waitKey(3)

        try:
            self.image_pub.publish(self.bridge.cv2_to_imgmsg(cv_image, "bgr8"))
        except CvBridgeError as e:
            print(e)

def main(args):
    ic = image_converter()
    rospy.init_node('image_converter', anonymous=True)
    #pixel_server()
    try:
        rospy.spin()
    except KeyboardInterrupt:
        print("Shutting down")
    cv2.destroyAllWindows()

def cam_angle(req):


    f = (center_x)/(math.tan(0.61453)) #decimal is half of the horizontal fov of camera

    center = np.array([0,f])

    pixel = np.array([abs(req.x-center_x), f])

    dot = np.dot(center,pixel)  #dot product between two vectors



    w = np.linalg.norm(center) #magnitude of the vectors


    z = np.linalg.norm(pixel)



    angle = math.acos(dot/(w*z)) #dot product formula

    deg_angle = angle * 180 / pi 

    print ("[x: %s   y: %s]"%(req.x, req.y))

    return pixelResponse(deg_angle)

def pixel_server():
    rospy.init_node('pixel_server')
    s = rospy.Service('pixel_server',pixel, cam_angle)
    print ('Ready to display angle')
    rospy.spin()

if __name__ == '__main__':
    pixel_server()
    main(sys.argv)
 
