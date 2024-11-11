#include "ros/ros.h"
//#include "std_srvs/Empty.h"
#include "services_quiz/BB8CustomServiceMessage.h"
#include <geometry_msgs/Twist.h>

// Import the service message header file generated from the Empty.srv message

// We define the callback function of the service

// Declare cmd_vel_pub globally
ros::Publisher cmd_vel_pub;

bool my_callback(services_quiz::BB8CustomServiceMessage::Request  &req,
                 services_quiz::BB8CustomServiceMessage::Response &res)
{  

ROS_INFO("Request Data ==> repetitions=%d side=%f ", req.repetitions, req.side);

  if (req.repetitions > 0)
  {
    // Move the robot in circles
    geometry_msgs::Twist vel_msg;
    

    float duration = req.side/0.5;


    ros::Rate loop_rate(1/duration);  // 10 Hz
    int count = 0;
    
    //int repetitions_ticks = req.repetitions * 10; // duration in ticks (10 ticks per second)
    
    while (req.repetitions > 0) {
        count = 0;
        while (count < 4)
        {
            vel_msg.linear.x = 0.5;   // Forward speed
            vel_msg.angular.z = 0.0;  // Turn rate to create a circle

            cmd_vel_pub.publish(vel_msg);  // Publish the message
            loop_rate.sleep();             // Sleep for 1/10th of a second

            vel_msg.angular.z = 0.42;
            vel_msg.linear.x = 0.0;

            cmd_vel_pub.publish(vel_msg);  // Publish the message
            loop_rate.sleep();             // Sleep for 1/10th of a second

            count++;
        }
        req.repetitions--;
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
  ros::ServiceServer move_bb8_in_square_custom = nh.advertiseService("/move_bb8_in_square_custom", my_callback); // create the Service called                                                                                          // my_service with the defined                                                                                        // callback
  ROS_INFO("Service server ready to move the robot in circles.");

  ros::spin(); // mantain the service open.

  return 0;
}