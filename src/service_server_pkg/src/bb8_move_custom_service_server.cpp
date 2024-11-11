#include "ros/ros.h"
//#include "std_srvs/Empty.h"
#include "my_custom_srv_msg_pkg/MyCustomServiceMessage.h"
#include <geometry_msgs/Twist.h>

// Import the service message header file generated from the Empty.srv message

// We define the callback function of the service

// Declare cmd_vel_pub globally
ros::Publisher cmd_vel_pub;

bool my_callback(my_custom_srv_msg_pkg::MyCustomServiceMessage::Request  &req,
                 my_custom_srv_msg_pkg::MyCustomServiceMessage::Response &res)
{  

ROS_INFO("Request Data ==> duration=%d", req.duration);

  if (req.duration > 5)
  {
    // Move the robot in circles
    geometry_msgs::Twist vel_msg;
    vel_msg.linear.x = 0.5;   // Forward speed
    vel_msg.angular.z = 0.5;  // Turn rate to create a circle

    ros::Rate loop_rate(10);  // 10 Hz
    int count = 0;
    int duration_ticks = req.duration * 10; // duration in ticks (10 ticks per second)

    while (count < duration_ticks)
    {
      cmd_vel_pub.publish(vel_msg);  // Publish the message
      loop_rate.sleep();             // Sleep for 1/10th of a second
      count++;
    }

    // Stop the robot after the duration
    vel_msg.linear.x = 0.0;
    vel_msg.angular.z = 0.0;
    cmd_vel_pub.publish(vel_msg);

    res.success = true;
    ROS_INFO("Sending back response: true");
  }
  else
  {
    res.success = false;
    ROS_INFO("Sending back response: false");
  }
  
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "service_server");
  ros::NodeHandle nh;

  // Initialize the publisher
  cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

  // Create the service server
  ros::ServiceServer move_bb8_in_circle_custom = nh.advertiseService("/move_bb8_in_circle_custom", my_callback); // create the Service called                                                                                          // my_service with the defined                                                                                        // callback
  ROS_INFO("Service server ready to move the robot in circles.");

  ros::spin(); // mantain the service open.

  return 0;
}