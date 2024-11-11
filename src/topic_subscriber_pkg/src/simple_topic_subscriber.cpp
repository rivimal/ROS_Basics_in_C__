// #include <ros/ros.h>
// #include <std_msgs/Int32.h>
// #include <nav_msgs/Odometry.h>

// void counterCallback(const Age::ConstPtr& msg)
// {
//   ROS_INFO("%f %f %f", msg.years, msg.months, msg.days);
// }

// int main(int argc, char** argv) {

//     ros::init(argc, argv, "topic_subscriber");
//     ros::NodeHandle nh;
    
//     ros::Subscriber sub = nh.subscribe("odom", 1000, counterCallback);
    
//     ros::spin();
    
//     return 0;
// }