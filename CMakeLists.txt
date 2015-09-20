cmake_minimum_required(VERSION 2.8.3)
project(ros_restamp_time)
catkin_package(CATKIN_DEPENDS april_tag std_msgs geometry_msgs)
find_package(catkin REQUIRED)
find_package(catkin REQUIRED COMPONENTS   roscpp
                                          rosbag
                                          std_msgs)
message(INFO ${rosbag_INCLUDE_DIRS})                                    
include_directories(${catkin_INCLUDE_DIRS})
add_executable(restamp_time_node src/restamp_time.cpp)
target_link_libraries(restamp_time_node ${catkin_LIBRARIES})
