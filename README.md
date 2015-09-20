#ros_restamp_time
ROS node to read a bag file and restamp the time stamps of topics belonging to the following types and writes the output to a new bag:
- sensor_msgs/Image
- april_tag/ApriTagList (Modified to have timestamps)
- geometry_msgs/PoseStamped 

## Why use this?
- This node can be used in situations in which the time stamps of the messages are not generated at the same system time, and you need the time stamps for something like time synchronisation.

For eg- if you ran the april_tag detection code post data acquisition, the time synchronisation module won't work since the time stamps cannot be aligned. Therefore, you must create a new bag in which all other messages have original timestamps and the april_tag data has the new time stamps. Running this code on the new bag will restamp everything to the same timebase and the contents of the new bag can be synchronised.

## Usage:
- rosrun ros_restamp_time restamp_time_node _read_bag:=2015-08-20-21-10-14.bag _write_bag:=bag_out _camera_topic:=usb_cam/image_raw _pose_topic:=slam_out_pose _tag_topic:=april_tags

- Note that all topics are required, i.e. you cannot use a subset of the topics.
