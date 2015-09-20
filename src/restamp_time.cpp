/** \mainpage 
* \section intro_sec Introduction
* 
* \section use Usage
  rosrun ros_restamp_time restamp_time_node _read_bag:=2015-08-20-21-10-14.bag _write_bag:=bag_out _camera_topic:=usb_cam/image_raw _pose_topic:=slam_out_pose _tag_topic:=april_tags
* \note  
* \author Bhavya Narain Gupta
* \date 
*/

#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <sensor_msgs/Image.h>
#include <april_tag/AprilTag.h>
#include <april_tag/AprilTagList.h>
#include <geometry_msgs/PoseStamped.h>

#include <boost/foreach.hpp>

#include <string>
#include <iostream>
using std::string;
using std::vector;
using sensor_msgs::Image;
using geometry_msgs::PoseStamped;
using april_tag::AprilTagList;

void display_topics(vector<string> &topics);

int main(int argc, char ** argv){
  std::cout << argc << std::endl;
  if(argc <2 ){
    ROS_ERROR("Insufficient parameters");
    exit(-1);
  }
  ros::init(argc,argv,"restamper");
  ros::NodeHandle nh("~");
  ros::Time::init();

  string in_bag_name;
  string out_bag_name;
  string topic_name_camera;
  string topic_name_pose;
  string topic_name_tag;
  nh.getParam("read_bag",in_bag_name);
  nh.getParam("write_bag",out_bag_name);
  nh.getParam("camera_topic",topic_name_camera);
  nh.getParam("pose_topic",topic_name_pose);
  nh.getParam("tag_topic",topic_name_tag);

  vector<string> topics;
  topics.push_back(topic_name_camera);
  topics.push_back(topic_name_pose);
  topics.push_back(topic_name_tag); 

  display_topics(topics);

  Image curr_frame;
  AprilTagList curr_tag;
  PoseStamped curr_pose;

  rosbag::Bag in_bag;
  rosbag::Bag out_bag;  
  out_bag.open(out_bag_name, rosbag::bagmode::Write);
  in_bag.open(in_bag_name,rosbag::bagmode::Read);
  rosbag::View view_in_bag(in_bag, rosbag::TopicQuery(topics));
  
  BOOST_FOREACH(rosbag::MessageInstance const msg, view_in_bag){
    if(msg.getTopic() == topic_name_camera) {
      ROS_INFO_STREAM("image_frame");
      Image::ConstPtr p_curr_frame = msg.instantiate<Image>();
      if(p_curr_frame == NULL){
        ROS_ERROR("Null frame Ptr");   
        exit(-1);
      } 
      curr_frame =  *p_curr_frame;
      curr_frame.header.stamp = ros::Time::now();
      out_bag.write(topic_name_camera,ros::Time::now(),curr_frame);
    }
    if(msg.getTopic() == topic_name_tag){
      ROS_INFO_STREAM("tag");
      AprilTagList::ConstPtr p_curr_tag = msg.instantiate<AprilTagList>();
      if(p_curr_tag == NULL){
        ROS_ERROR("Null tag Ptr") ;       
        exit(-1);
      } 
      curr_tag = *p_curr_tag;
      curr_tag.header.stamp = ros::Time::now();
      out_bag.write(topic_name_tag,ros::Time::now(),curr_tag);
    }
    if(msg.getTopic() == topic_name_pose){
      ROS_INFO_STREAM("pose");
      PoseStamped::ConstPtr p_curr_pose = msg.instantiate<PoseStamped>();
      if(p_curr_pose == NULL){
        ROS_ERROR("Null pose Ptr") ;       
        exit(-1);
      } 
      curr_pose = *p_curr_pose;
      curr_pose.header.stamp = ros::Time::now();
      out_bag.write(topic_name_pose,ros::Time::now(),curr_pose);
    }
  }

  in_bag.close();
  out_bag.close();
  return 0;
}

void display_topics(vector<string> &topics) {
  std::cout<<"Reading Topics: "<<std::endl;
  vector<string>::iterator it;
  for(it = topics.begin(); it != topics.end(); it++){
    std::cout<< *it<<std::endl;
  }
  return;
}

