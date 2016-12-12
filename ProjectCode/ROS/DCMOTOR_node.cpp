#include <ros/ros.h>
//#include "DCMOTOR.h"
#include <unistd.h>

void control_Callback(const std_msgs::String::ConstPtr& msg){
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
  ros::init(argc,argv,"DCMOTOR_node");
  ros::NodeHandle nh;
  ros::Rate loop_rate(10);

  ros::Subscriber sub = n.subscribe("control_signal", 1000, control_Callback);

}
