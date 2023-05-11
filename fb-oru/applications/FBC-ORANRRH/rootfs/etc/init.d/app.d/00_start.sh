#!/bin/sh
#
# Miscellaneous start up settings

start()
{
	## Set TCP keepalive settings
	## 10secs + (3-1)*10secs = 30 secs total between inactivity and connection dead
	##
	echo 10 > /proc/sys/net/ipv4/tcp_keepalive_intvl
	echo 3 > /proc/sys/net/ipv4/tcp_keepalive_probes
	echo 10 > /proc/sys/net/ipv4/tcp_keepalive_time
}

stop()
{
	:
}


case $1 in
    start)
		start
	;;
    stop)
    	stop
	;;
    restart)
    	stop
    	sleep 1
		start
	;;
    *)
    	echo >&2 "$0 - '$1' invalid action"
	exit 2
	;;
esac

