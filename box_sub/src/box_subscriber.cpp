#include "ros/ros.h"
#include "std_msgs/String.h"

#include "darknet_ros_msgs/BoundingBoxes.h"
#include "darknet_ros_msgs/BoundingBox.h"
#include "cam_angle/pixel.h"
#include <iostream>

#include <cstdlib>

using namespace std;

//darknet_ros_msgs::BoundingBoxes globalboxes;
int i,c;
char ch;
int size, actual_size;
int xmax,xmin,ymax,ymin, xavg, yavg;
ros::ServiceClient *clientPtr; //pointer for a client


void boxesCallback(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg)
{
  ros::NodeHandle n;
  cam_angle::pixel srv;
  ros::ServiceClient client = n.serviceClient<cam_angle::pixel>("pixel_server");

 size = msg->bounding_boxes.size();
 actual_size = size-1;
cout << size << endl;

 if (size == 0)
  cout << "Nothing in sight" << endl;

  if (size > 0 ) 
  {
	
    for (int i = 0; i <= actual_size; i++)
    {

    	//cout << "x min:"<<  msg->bounding_boxes[i].xmin << endl;
    	//cout << "x max:"<<msg->bounding_boxes[i].xmax << endl;
        //cout << "y min:" <<msg->bounding_boxes[i].ymin << endl;
    	//cout << "y max:"  <<msg->bounding_boxes[i].ymax << endl; 

	xmax = msg->bounding_boxes[i].xmax;
        xmin = msg->bounding_boxes[i].xmin;
        ymax = msg->bounding_boxes[i].ymax;
	ymin = msg->bounding_boxes[i].ymin;

	xavg = (xmax+xmin)/2;
	yavg =(ymax+ymin)/2;

	cout << xavg << endl;

        srv.request.x = xmax;

       // cout << xmax << endl; 

        srv.request.y = yavg;

     //   cout << ymax<< endl;

	if(xmax<320) // Left side of coordinate system 
		srv.response.angle = 360 - srv.response.angle;


     if (getchar() == 'g')
{
    if(client.call(srv))
  {  
    //clientPtr->call(srv);
  
    ROS_INFO("Angle: %f", (float)srv.response.angle);
    break;
  
  
  } 

}
   


    } //for loop end

 
  } // if statement end

} // function end

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "boxes");

  ros::NodeHandle n;

  cam_angle::pixel srv;

  ros::Subscriber boxes_sub = n.subscribe("darknet_ros/bounding_boxes", 1000, boxesCallback);

  ros::spin();




  return 0;
}
