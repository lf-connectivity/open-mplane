#!/bin/sh
# $Id:$
#
# Initialise the interface MACs
#

# load config
. /etc/setup.env

start()
{
    echo "Configure interface MACs"
    
    # use ethaddr for CDI mac address
    mac_cdi=$(i2cenv ethaddr | sed -e 's/^.*=//')
    ifconfig $eth_cdi down
    if [ -n "$mac_cdi" ]; then
    	ifconfig $eth_cdi hw ether $mac_cdi
	fi
	
    # use ethaddr1 for BB mac address
    mac_bb=$(i2cenv ethaddr1 | sed -e 's/^.*=//')
    ifconfig $eth_bb down
    if [ -n "$mac_bb" ]; then
	    ifconfig $eth_bb hw ether $mac_bb
	fi

    echo 1 > /proc/sys/net/ipv4/ip_forward

	# We've got a hostname so may as well set it straight away - it's then set for static ip
    myhostname=$(i2cenv hostname)
  	myhostname=${myhostname#*=}
    if [ -n "$myhostname" ]; then
  		hostname $myhostname
  	fi
}

stop()
{
    echo Stopping network

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
        start
        ;;
    *)
        echo >&2 "$0 - '$1' invalid action"
        exit 2
        ;;
    esac
