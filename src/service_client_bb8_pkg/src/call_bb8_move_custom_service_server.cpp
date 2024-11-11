#include "ros/ros.h"
//#include "std_srvs/Empty.h"
#include <geometry_msgs/Twist.h>
#include "my_custom_srv_msg_pkg/MyCustomServiceMessage.h"

// Import the service message used by the service /trajectory_by_name

int main(int argc, char **argv)
{
  ros::init(argc, argv, "service_client_bb8"); // Initialise a ROS node with the name service_client
  ros::NodeHandle nh;

  ros::service::waitForService("/move_bb8_in_circle_custom");  // wait for service to be running
  ros::ServiceClient move_bb8_in_circle_custom = nh.serviceClient<my_custom_srv_msg_pkg::MyCustomServiceMessage>("/move_bb8_in_circle_custom");
  
 // Set up the request
  my_custom_srv_msg_pkg::MyCustomServiceMessage srv; 
  srv.request.duration = 20; // Set the duration for the robot to move in circles (e.g., 10 seconds)

  if (move_bb8_in_circle_custom.call(srv)) {
    if (srv.response.success) {
      ROS_INFO("The robot will move in circles for %d seconds", srv.request.duration);
    } else {
      ROS_WARN("The robot did not move as expected.");
    }
  } else {
    ROS_ERROR("Failed to call the service");
  }
  return 0;
}