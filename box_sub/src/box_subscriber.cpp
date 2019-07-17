#include "ros/ros.h"
#include "std_msgs/String.h"

#include "darknet_ros_msgs/BoundingBoxes.h"
#include "darknet_ros_msgs/BoundingBox.h"
#include "cam_angle/pixel.h"
#include <visualization_msgs/Marker.h>
#include <sensor_msgs/LaserScan.h>
#include <iostream>


#include <cstdlib>

using namespace std;
int i,c;
char ch;
int size, actual_size, new_size;
int xmax,xmin,ymax,ymin, xavg, yavg;
ros::ServiceClient *clientPtr; //pointer for a client
int angle;
int value;

ros::Publisher vis_pub;


void LaserCallback(const sensor_msgs::LaserScan::ConstPtr& scan){

	//ros::NodeHandle n;

	value = int(angle*4);

	cout << "ANGLE  " <<  angle << endl;

	cout << "LSR VALUE   " <<value << endl; 

        cout << "DISTANCE     " <<  scan->ranges[value]; //are laser readings

	//ros::Publisher vis_pub = n.advertise<visualization_msgs::Marker>( "yolo_marker", 0 );

	visualization_msgs::Marker marker;
	marker.header.frame_id = "laser";
	marker.header.stamp = ros::Time();
	marker.ns = "my_namespace";
	marker.id = 0;
	marker.type = visualization_msgs::Marker::SPHERE;
	marker.action = visualization_msgs::Marker::ADD;
	marker.pose.position.x = scan->ranges[i] * sin(angle);
	marker.pose.position.y = scan->ranges[i] * cos(angle);
	marker.pose.position.z = 0;
	marker.pose.orientation.x = 0.0;
	marker.pose.orientation.y = 0.0;
	marker.pose.orientation.z = 0.0;
	marker.pose.orientation.w = 1.0;
	marker.scale.x = 1;
	marker.scale.y = 0.1;
	marker.scale.z = 0.1;
	marker.color.a = 1.0; //Don't forget to set the alpha!
	marker.color.r = 0.0;
	marker.color.g = 1.0;
	marker.color.b = 0.0;
	//only if using a MESH_RESOURCE marker type:
	marker.mesh_resource = "package://pr2_description/meshes/base_v0/base.dae";
	vis_pub.publish(marker);

    
}

void boxesCallback(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg)
{  
  ros::NodeHandle n;
  cam_angle::pixel srv;
  ros::ServiceClient client = n.serviceClient<cam_angle::pixel>("pixel_server");
// while(1)
//{angle
 //size = msg->bounding_boxes.size();
 //cout << size << endl;
 //actual_size = size-1;
 cout << "SIZE" << "     " <<  msg->bounding_boxes.size() << endl;
 if (msg->bounding_boxes.size() == 0)
  cout << "Nothing in sight" << endl;

 // while (msg->bounding_boxes.size() > 0 ) 
  //{
  



 

    for (int i = 0; i < msg->bounding_boxes.size() ; i++)
    {

    //	cout << "x min for box:"<<i << "     "  << msg->bounding_boxes[i].xmin << endl;
    //	cout << "x max for box:"<<i << "     " << msg->bounding_boxes[i].xmax << endl;
    //    cout << "y min for box:" <<i << "     " << msg->bounding_boxes[i].ymin << endl;
    	cout << "y max for box:"  <<i << "     " << msg->bounding_boxes[i].ymax << endl; 

	xmax = msg->bounding_boxes[i].xmax;
        xmin = msg->bounding_boxes[i].xmin;
        ymax = msg->bounding_boxes[i].ymax;
	ymin = msg->bounding_boxes[i].ymin;

	xavg = (xmax+xmin)/2;
	yavg =(ymax+ymin)/2;

        srv.request.x = xmax;

       // cout << xmax << endl; 

        srv.request.y = yavg;

     //   cout << ymax<< endl;

	//if(xmax<320) // Left side of coordinate system 
		//srv.response.angle = 360 - srv.response.angle;


    // if (getchar() == 'g')
//{
   // if(client.call(srv))
  //{ 
//ros::Duration five_seconds(5.0); 
     client.call(srv);
   // clientPtr->call(srv);
  
    ROS_INFO("Angle: %f", (float)srv.response.angle);
    angle = srv.response.angle;
    //break;
  
  
  //} 


//}
//else continue ;

//ros::Subscriber scanSub;

//scanSub=n.subscribe<sensor_msgs::LaserScan>("/scan",10,&AutoExp::processLaserScan,this);

	//ros::Subscriber sub = n.subscribe("/scan", 10, LaserCallback);

   
	//ros::Publisher vis_pub = n.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );

	//visualization_msgs::Marker marker;
	//marker.header.frame_id = "base_link";
	//marker.header.stamp = ros::Time();
	//marker.ns = "my_namespace";
	//marker.id = 0;
	//marker.type = visualization_msgs::Marker::SPHERE;
	//marker.action = visualization_msgs::Marker::ADD;
	//marker.pose.position.x = scan->ranges[i] * sin(angle);
	//marker.pose.position.y = scan->ranges[i] * cos(angle);
	//marker.pose.position.z = 0;
	//marker.pose.orientation.x = 0.0;
	//marker.pose.orientation.y = 0.0;
	//marker.pose.orientation.z = 0.0;
	//marker.pose.orientation.w = 1.0;
	//marker.scale.x = 1;
	//marker.scale.y = 0.1;
	//marker.scale.z = 0.1;
	//marker.color.a = 1.0; //Don't forget to set the alpha!
	//marker.color.r = 0.0;
	//marker.color.g = 1.0;
	//marker.color.b = 0.0;
	//only if using a MESH_RESOURCE marker type:
	//marker.mesh_resource = "package://pr2_description/meshes/base_v0/base.dae";
	//vis_pub.publish( marker );


   } //for loop end

 
  //} // while statement end

} // function end

//}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "boxes");

  ros::NodeHandle n;

 // cam_angle::pixel srv;

  ros::Subscriber boxes_sub = n.subscribe("darknet_ros/bounding_boxes", 1000, boxesCallback);

  ros::Subscriber sub = n.subscribe("/scan", 10, LaserCallback);

  vis_pub = n.advertise<visualization_msgs::Marker>( "yolo_marker", 0 );

//  ros::Publisher vis_pub = n.advertise<visualization_msgs::Marker>( "yolo_marker", 0 );

  //ros::MultiThreadedSpinner spinner(2); // Use 4 threads

  //spinner.spin(); // spin() will not return until the node has been shutdown


  ros::spin();




  return 0;
}
