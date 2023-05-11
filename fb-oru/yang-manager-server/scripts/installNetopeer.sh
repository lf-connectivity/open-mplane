#!/bin/sh -x

set -x

REPO_PATH=$1
NETOPEER_PATH=$2
SCRIPTS_PATH=$3

if [ $# == "3" ]
then
	echo Removing sysrepo repository files
	
	rm -rf $REPO_PATH
	rm -rf /dev/shm/sr_*
	rm -rf /dev/shm/srsub_*

	if [ -d $NETOPEER_PATH ]
	then
		echo Installing netopeer
		cd $NETOPEER_PATH
		make install
	else
		echo Unable to find $NETOPEER_PATH
	fi

	## Set up user access
	pwd
	source $SCRIPTS_PATH/../cmake/rootfs/etc/init.d/app.d/23_yang-user_config.sh start

else
	echo Not enough parameters
fi

