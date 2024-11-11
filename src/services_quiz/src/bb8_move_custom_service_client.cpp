#include "ros/ros.h"
//#include "std_srvs/Empty.h"
#include <geometry_msgs/Twist.h>
#include "services_quiz/BB8CustomServiceMessage.h"


// Import the service message used by the service /trajectory_by_name

int main(int argc, char **argv)
{
  ros::init(argc, argv, "service_client_bb8"); // Initialise a ROS node with the name service_client
  ros::NodeHandle nh;

  ros::service::waitForService("/move_bb8_in_square_custom");  // wait for service to be running
  ros::ServiceClient move_bb8_in_square_custom = nh.serviceClient<services_quiz::BB8CustomServiceMessage>("/move_bb8_in_square_custom");
  
 // Set up the request
  services_quiz::BB8CustomServiceMessage srv; 
  srv.request.repetitions = 2; // Set the duration for the robot to move in circles (e.g., 10 seconds)
  srv.request.side = 2; 

  if (move_bb8_in_square_custom.call(srv)) {
    if (srv.response.success) {
      ROS_INFO("The robot will move in circles for %d seconds", srv.request.repetitions);
    } else {
      ROS_WARN("The robot did not move as expected.");
    }
  } else {
    ROS_ERROR("Failed to call the service");
  }

  srv.request.repetitions = 1; // Set the duration for the robot to move in circles (e.g., 10 seconds)
  srv.request.side = 3; 

  if (move_bb8_in_square_custom.call(srv)) {
    if (srv.response.success) {
      ROS_INFO("The robot will move in circles for %d seconds", srv.request.repetitions);
    } else {
      ROS_WARN("The robot did not move as expected.");
    }
  } else {
    ROS_ERROR("Failed to call the service");
  }
  
  return 0;
}