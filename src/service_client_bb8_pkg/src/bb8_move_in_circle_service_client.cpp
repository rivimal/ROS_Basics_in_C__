#include "ros/ros.h"
#include "std_srvs/Empty.h"
#include <geometry_msgs/Twist.h>

// Import the service message used by the service /trajectory_by_name

int main(int argc, char **argv)
{
  ros::init(argc, argv, "service_client_bb8"); // Initialise a ROS node with the name service_client
  ros::NodeHandle nh;
  //std_srvs/Empty
  // Create the connection to the service /trajectory_by_name
  ros::service::waitForService("/move_bb8_in_circle");  // wait for service to be running
  ros::ServiceClient move_bb8_in_circle = nh.serviceClient<std_srvs::Empty>("/move_bb8_in_circle");
  std_srvs::Empty srv; // Create an object of type TrajByName
  //srv.request.Empty = "release_food"; // Fill the variable traj_name with the desired value
  
  move_bb8_in_circle.call(srv);

  //if (move_bb8_in_circle.call(srv)) // Send through the connection the name of the trajectory to execute
  //{
    //ROS_INFO("%s", srv.response.status_message.c_str()); // Print the result given by the service called
  //}
  //else
  //{
    //ROS_ERROR("Failed to call service /move_bb8_in_circle");
    //return 1;
  //}

  return 0;
}