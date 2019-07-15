#!/usr/bin/env python
import rospy 
import numpy as np
from sensor_msgs.msg import Image 
from cv_bridge import CvBridge
import cv2
import math

cap = cv2.VideoCapture(0) #Capture the video 

width = cap.get(3) # Saves the pixel width of the video 
height = cap.get(4) #Saves the pixel height of the video
center_x = width/2 # Locates the center of the camera field of view x
center_y = height/2 # Locates the center of the camera field of view y

ix,iy = -1,-1

pi = 3.14159

def talker():

	def draw_circle(event,x,y,flags,param): #mouse double click
		global ix, iy
		if event == cv2.EVENT_LBUTTONDBLCLK:
			ix,iy = x,y


	cv2.namedWindow('frame2')
	cv2.setMouseCallback('frame2',draw_circle)

	rospy.init_node('angle', anonymous=True) #initialize ros node 

	while(True):
	    # Capture frame-by-frame
	    ret, frame = cap.read()

	    cv2.imshow('frame2', frame)

	    #print ix,iy

	    f = (center_x)/(math.tan(0.61453))

	    center = np.array([0,f])
    
	    pixel = np.array([abs(ix-center_x), f])

	    dot = np.dot(center,pixel)  #dot product between two vectors
 
	    w = np.linalg.norm(center) #magnitude of the vectors

	    z = np.linalg.norm(pixel)

	    angle= math.acos(dot/(w*z)) #dot product formula

	    deg_angle = angle * 180 / pi 


	    print deg_angle

	    if cv2.waitKey(1) & 0xFF == ord('q'):
		break
    
	# When everything done, release the capture
	cap.release()
	cv2.destroyAllWindows()

if __name__ == '__main__':

	try:
		talker()

	except rospy.ROSInterruptException:

		pass
