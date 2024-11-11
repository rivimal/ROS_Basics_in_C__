// #include <ros/ros.h>
// //#include <std_msgs/Int32.h>
// #include <geometry_msgs/Twist.h>


// int main(int argc, char** argv) {

//     ros::init(argc, argv, "topic_publisher");
//     ros::NodeHandle nh;
    
   

//     //ros::Publisher pub = nh.advertise<std_msgs::Int32>("counter", 1000);
//     ros::Publisher pub = nh.advertise<Age>("odom", 1000);
//     ros::Rate loop_rate(2);

//     msg::Age age;

//     age.years = 28.0
//     age.months = 5.0
//     age.days = 11.0

//     while (ros::ok())
//     {
//         //pub.publish(count);
//         pub.publish(age);
//         ros::spinOnce();
//         loop_rate.sleep();
//         ++age.days;
//     }
    
//     return 0;
// }