#ifndef ACSL_LOCAL_POSITION_PUBLISHER_H
#define ACSL_LOCAL_POSITION_PUBLISHER_H

#include <ros/ros.h>
#include <std_msgs/UInt8.h>
#include <dji_sdk/ACSL_local_position.h>



void ACSL_seqeunce_callback(const std_msgs::UInt8::ConstPtr& msg);


#endif