#!/usr/bin/env python

import rospy 
import numpy as np
from sensor_msgs.msg import Image 
from cv_bridge import CvBridge
from cam_angle.srv import *
from threading import Thread
import cv2
import math

cap = cv2.VideoCapture(0) #Capture the video 




width = cap.get(3) # Savthat rosrunes the pixel width of the video 
height = cap.get(4) #Saves the pixel height of the video
center_x = width/2 # Locates the center of the camera field of view x
center_y = height/2 # Locates the center of the camera field of view y

pi = 3.14159

def talker():

	


	cv2.namedWindow('frame2')
	#cv2.setMouseCallback('frame2',draw_circle)

	#rospy.init_node('angle', anonymous=True) #initialize ros node 



	while(True):
	    # Capture frame-by-frame
	    ret, frame = cap.read()

	    cv2.imshow('frame2', frame)


	    if cv2.waitKey(1) & 0xFF == ord('q'):
		break


    	
	# When everything done, release the capture
	cap.release()
	cv2.destroyAllWindows()

def cam_angle(req):


        f = (center_x)/(math.tan(0.61453)) #decimal is half of the horizontal fov of camera

        center = np.array([0,f])

        pixel = np.array([abs(req.x-center_x), f])

        dot = np.dot(center,pixel)  #dot product between two vectors

        print dot

        w = np.linalg.norm(center) #magnitude of the vectors

        print w

        z = np.linalg.norm(pixel)

        print z

        angle = math.acos(dot/(w*z)) #dot product formula

        deg_angle = angle * 180 / pi 

        print "[x: %s   y: %s]"%(req.x, req.y)

	return pixelResponse(deg_angle)

def pixel_server():
	rospy.init_node('pixel_server')
        s = rospy.Service('pixel_server',pixel, cam_angle)
	print 'Ready to display angle'
	rospy.spin()

if __name__ == '__main__':

	try:
		
		pixel_server()
		#talker()
		

	except rospy.ROSInterruptException:

		pass
