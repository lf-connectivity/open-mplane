#! /bin/sh
#
# Jenkins script for building ROS
# Uses the environment variables to set parameters in the script
#
# Required variables:
#
# WORKSPACE = Jenkins workspace area
# BUILD_BOARD = Board
# BUILD_NUMBER = Jenkins build number
#

cd $WORKSPACE/ros

rm -f $WORKSPACE/ros/build/$BUILD_BOARD/packages/* >/dev/null 2>&1 

make clean-all BUILD_BOARD=$BUILD_BOARD BUILD_NUMBER=$BUILD_NUMBER
make init BUILD_BOARD=$BUILD_BOARD BUILD_NUMBER=$BUILD_NUMBER
if [ $? -ne 0 ]; then
	exit 1
fi
make install BUILD_BOARD=$BUILD_BOARD BUILD_NUMBER=$BUILD_NUMBER
if [ $? -ne 0 ]; then
	exit 1
fi
