#include <ros/ros.h>
//#include <std_msgs/Int32.h>
#include <geometry_msgs/Twist.h>


int main(int argc, char** argv) {

    ros::init(argc, argv, "topic_publisher");
    ros::NodeHandle nh;
    
   

    //ros::Publisher pub = nh.advertise<std_msgs::Int32>("counter", 1000);
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    ros::Rate loop_rate(2);
    
    //std_msgs::Int32 count;
    // eometry_msgs::Twist var;

    //count.data = 0;
    // var.linear = 0;
    // var.angular = 0;

    geometry_msgs::Twist var;

    var.linear.x = 0.5;
    //var.linear.y = 0.0;
    //var.linear.z = 0.0;
    //var.angular.x = 0.0;
    //var.angular.y = 0.0;
    var.angular.z = 0.5;

    while (ros::ok())
    {
        //pub.publish(count);
        pub.publish(var);
        ros::spinOnce();
        loop_rate.sleep();
        //++count.data;
    }
    
    return 0;
}