#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <vector>

std::vector<float> laserValue(720, 0);

void callback(const sensor_msgs::LaserScan::ConstPtr& Laserdata) {
    laserValue = Laserdata->ranges;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "topics_quiz_node");
    ros::NodeHandle nh;
    
    ros::Rate rate(10);
    
    ros::Subscriber sub = nh.subscribe("/kobuki/laser/scan", 1, callback);
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
    
    geometry_msgs::Twist velocity;
    velocity.linear.x = 0;
    velocity.angular.z = 0;
    
    while (ros::ok()) {
        pub.publish(velocity);
        ROS_INFO_STREAM("Laser Value at 360: " << laserValue[360]);
        
        if (laserValue[360] > 1) {
            velocity.linear.x = 0.2;
            velocity.angular.z = 0;
        }
        
        if (laserValue[360] <= 1) {
            velocity.angular.z = 0.4;
        }
        
        while (laserValue[0] <= 1) {
            velocity.linear.x = 0;
            velocity.angular.z = 0.4;
            pub.publish(velocity);
            ros::spinOnce();
        }
        
        while (laserValue[719] <= 1) {
            velocity.linear.x = 0;
            velocity.angular.z = -0.4;
            pub.publish(velocity);
            ros::spinOnce();
        }
        
        ros::spinOnce();
        rate.sleep();
    }
    
    return 0;
}



// #include <algorithm>
// #include <geometry_msgs/Twist.h>
// #include <limits>
// #include <ros/ros.h>
// #include <sensor_msgs/LaserScan.h>
// ros::Publisher pub_cmd_vel;
// void laserCallback(const sensor_msgs::LaserScan::ConstPtr &msg) {
//   geometry_msgs::Twist cmd;
//   int range_size = msg->ranges.size();
//   // Calculate indices for front, left, and right sections
//   int front_index = range_size / 2;
//   int left_index = range_size * 1 / 4;
//   int right_index = range_size * 3 / 4;
//   // Define the ranges to check for each direction (taking a small window around
//   // each)
//   int window_size = 10; // Adjust window size if necessary
//   // Helper function to get the minimum range in a specific window
//   auto get_min_range = [&](int start_index, int window) {
//     float min_range = std::numeric_limits<float>::infinity();
//     for (int i = start_index - window / 2; i <= start_index + window / 2; ++i) {
//       if (i >= 0 && i < range_size && msg->ranges[i] < min_range) {
//         min_range = msg->ranges[i];
//       }
//     }
//     return min_range;
//   };
//   // Get minimum distances in each direction, ignoring inf values
//   float front_distance = get_min_range(front_index, window_size);
//   float left_distance = get_min_range(left_index, window_size);
//   float right_distance = get_min_range(right_index, window_size);

//   // Logic for movement based on distances
//   // 1. front > 1.0 && right_distance > 1.0
//   // move forward

//   if (front_distance > 1.0 && right_distance > 1.0 && left_distance > 1.0) {
//     // No obstacles nearby 8
//     cmd.linear.x = 0.5; // Move forward
//     // cmd.angular.z = 0.0;
//   } else if (front_distance < 1.0 && right_distance > 1.0 &&
//              left_distance > 1.0) {
//     // Obstacle in front only 4
//     // cmd.linear.x = 0.0;
//     cmd.angular.z = 0.5; // Turn left
//   } else if (front_distance > 1.0 && right_distance < 1.0 &&
//              left_distance > 1.0) {
//     // Obstacle on the right only 7
//     cmd.linear.x = 0.5; // Move forward
//                         // cmd.angular.z = 0.0;
//   } else if (front_distance > 1.0 && right_distance > 1.0 &&
//              left_distance < 1.0) {
//     // Obstacle on the left only 6
//     cmd.linear.x = 0.5; // Move forward
//                         // cmd.angular.z = 0.0;
//   } else if (front_distance < 1.0 && right_distance < 1.0 &&
//              left_distance > 1.0) {
//     // Obstacles in front and right 3
//     // cmd.linear.x = 0.0;
//     cmd.angular.z = 0.5; // Turn left
//   } else if (front_distance < 1.0 && right_distance > 1.0 &&
//              left_distance < 1.0) {
//     // Obstacles in front and left 2
//     // cmd.linear.x = 0.0;
//     cmd.angular.z = -0.5; // Turn right
//   } else if (front_distance > 1.0 && right_distance < 1.0 &&
//              left_distance < 1.0) {
//     // Obstacles on both sides, but clear in front 5
//     cmd.linear.x = 0.5; // Move forward
//                         // cmd.angular.z = 0.0;
//   } else if (front_distance < 1.0 && right_distance < 1.0 &&
//              left_distance < 1.0) {
//     // Obstacles in all directions 1
//     // cmd.linear.x = 0.0;
//     cmd.angular.z = 0.5; // Turn left (arbitrary choice)
//   }

//   pub_cmd_vel.publish(cmd);
// }
// int main(int argc, char **argv) {
//   ros::init(argc, argv, "topics_quiz_node");
//   ros::NodeHandle nh;
//   // Publisher and Subscriber
//   pub_cmd_vel = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
//   ros::Subscriber sub_laser =
//       nh.subscribe("/kobuki/laser/scan", 10, laserCallback);
//   ros::spin();
//   return 0;
// }
