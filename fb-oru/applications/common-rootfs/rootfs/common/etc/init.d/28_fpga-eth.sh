#!/bin/sh
# $Id:$
#
# Initialise the MII between fpga and PPC
#

# load config
. /etc/setup.env

max_sfps=1
mac_bb=$(i2cenv ethaddr | sed -e 's/^.*=//')
mac_cdi=$(i2cenv eth1addr | sed -e 's/^.*=//')
mac_sfp0=$(i2cenv eth2addr | sed -e 's/^.*=//')
sfp_vlan=10

start()
{
    echo "Configure network"

    #[ "$eth_debug" ] && set -xv

    # use ethaddr for fpga mac address
    ifconfig $eth_bb down
    ifconfig $eth_bb hw ether $mac_bb
    if [ -n "$eth_rename_bb" ]
    then
    	nameif $eth_rename_bb $mac_bb
    	eth_bb=$eth_rename_bb
    fi

    # use eth1addr for network mac address
    ifconfig $eth_cdi down
    ifconfig $eth_cdi hw ether $mac_cdi
    if [ -n "$eth_rename_cdi" ]
    then
    	nameif $eth_rename_cdi $mac_cdi
    	eth_cdi=$eth_rename_cdi
    fi

    echo 1 > /proc/sys/net/ipv4/ip_forward

    # Lease an IP address
    myhostname=$(i2cenv hostname)
  	myhostname=${myhostname#*=}


    # Add SFP0 vlan
    echo "Adding vlan $eth_bb.$sfp_vlan"
	ifconfig $eth_bb up
    vconfig add $eth_bb $sfp_vlan
    ifconfig $eth_bb.$sfp_vlan hw ether $mac_sfp0

    echo "Make DHCP requests"

    # Run dhcp on sfp0 - leave running in background
	ifconfig $eth_bb.$sfp_vlan up
 	/etc/run-dhcpc.sh $eth_bb.$sfp_vlan $myhostname-BB /etc/app-dhcpc.script >/dev/null 2>&1 &

    # Run dhcp on cdi interface
    ifconfig $eth_cdi up
 	/etc/run-dhcpc.sh $eth_cdi $myhostname /etc/app-dhcpc.script >/dev/null 2>&1 &

 	# Put the CDI interface into promiscuous mode so that LAB discovery works. In normal operation this won't be connected
 	ifconfig $eth_cdi promisc

    # start the inetd super server
    echo "Starting inetd super server (provides Telnet)"
    inetd

}

stop()
{
	orig_eth_bb=$eth_bb
	orig_eth_cdi=$eth_cdi

    if [ -n "$eth_rename_bb" ]
    then
    	eth_bb=$eth_rename_bb
    fi
    if [ -n "$eth_rename_cdi" ]
    then
    	eth_cdi=$eth_rename_cdi
    fi

    echo Stopping network

    ifconfig $eth_bb.$sfp_vlan down
    ifconfig $eth_bb down
    ifconfig $eth_cdi down

    vconfig rem $eth_bb.$sfp_vlan

    killall udhcpc

	# Restore names if necessary
    if [ -n "$eth_rename_bb" ]
    then
    	nameif $orig_eth_bb $mac_bb
    fi
    if [ -n "$eth_rename_cdi" ]
    then
    	nameif $orig_eth_cdi $mac_cdi
    fi

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
