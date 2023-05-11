#!/bin/sh
# $Id:$
#
# Initialise the MII between fpga and PPC
#

# load config
. /etc/setup.env

max_sfps=1

start()
{

    echo "Configure network bridge bridge"

    #####    log starting rrh-address
    #####    rrh-address -D ${misc_daisy_control}

    #[ "$eth_debug" ] && set -xv

    # create the control device for the tun driver (major+minor match "modinfo tun")
    mkdir -p /dev/net
    [ -c /dev/net/tun ] || mknod /dev/net/tun c 10 200

    # use ethaddr for fpga mac address
    mac_bb=$(i2cenv ethaddr | sed -e 's/^.*=//')
    ifconfig $eth_bb down
    ifconfig $eth_bb hw ether $mac_bb
    if [ -n "$eth_rename_bb" ]
    then
    	nameif $eth_rename_bb $mac_bb
    	eth_bb=$eth_rename_bb
    fi

    # use eth1addr for network mac address
    mac_cdi=$(i2cenv eth1addr | sed -e 's/^.*=//')
    ifconfig $eth_cdi down
    ifconfig $eth_cdi hw ether $mac_cdi
    if [ -n "$eth_rename_cdi" ]
    then
    	nameif $eth_rename_cdi $mac_cdi
    	eth_cdi=$eth_rename_cdi
    fi


    echo "Creating vlans"
    # add the vlan bridge instance and label it "vlanbr"
    brctl addbr vlanbr

    # set a MAC for the bridge (vlanbr), same as eth1 interface's MAC
    ifconfig vlanbr hw ether $(i2cenv eth1addr | sed -e 's/^.*=//')

    # add the vlans depending
    echo "Adding vlan $eth_bb.10"
    vconfig add $eth_bb 10
    ifconfig $eth_bb.10 hw ether $(i2cenv eth2addr | sed -e 's/^.*=//')
    brctl addif vlanbr $eth_bb.10

    echo "Adding vlan $eth_bb.11"
    vconfig add $eth_bb 11
    ifconfig $eth_bb.11 hw ether $(i2cenv eth3addr | sed -e 's/^.*=//')
    brctl addif vlanbr $eth_bb.11
    
    # don't bring up eth_bb if in test mode
    testEthBbDown=$(i2cenv testEthBbDown | sed -e 's/^.*=//')
    if [ -n "$testEthBbDown" ]
    then
		ifconfig $eth_bb down
    else
		ifconfig $eth_bb.10 up
		ifconfig $eth_bb.11 up
	fi

    # Add the network interface
    ifconfig $eth_cdi 0.0.0.0 down
    brctl addif vlanbr $eth_cdi
    ifconfig $eth_cdi 0.0.0.0 up

    # put the bridge into promiscuous mode to ensure it sees all of the traffic
    #       ifconfig RRH_VLAN_IFACE promisc

    # Add a TAP to the bridge. This will also be set with any new MAC address that the bridge is changed to. This ensures
    # the bridge has all the correct MACs in it's list (it doesn't include it's own, so otherwise it would drop any packets
    # with the new MAC. That's why the previous approach of setting the bridge interface into promiscuous mode worked).
    #
    tunctl -t vlantap
    brctl addif vlanbr vlantap

    # Now bring bridge up
    ifconfig vlanbr 0.0.0.0 up

    echo 1 > /proc/sys/net/ipv4/ip_forward

	# We've got a hostname so may as well set it straight away - it's then set for static ip
    myhostname=$(i2cenv hostname)
  	myhostname=${myhostname#*=}
  	hostname $myhostname

	# Check uboot env for static ip settings - only use static ip if both ip and gateway are set
    myipaddr=$(i2cenv ipaddr)
    myipaddr=${myipaddr#*=}
    mygateway=$(i2cenv gatewayip)
    mygateway=${mygateway#*=}
    if [ -n "$myipaddr" ] && [ -n "$mygateway" ]
    then
    
    	## STATIC IP
    	
        mynetmask=$(i2cenv netmask)
        mynetmask=${mynetmask#*=}
        if [ -n "$mynetmask" ]
        then
            ifconfig vlanbr $myipaddr netmask $mynetmask
        else
            ifconfig vlanbr $myipaddr
        fi
        route add default gw $mygateway
        
        echo "STATIC IP: $myipaddr [Gateway $mygateway]"
    	
		## Log the initial static IP address - used by the application to monitor IP setting
		echo "STATIC:vlanbr:$myipaddr" >>/var/log/ip.log
    	
    else
    
    	## DHCP

	    # Lease an IP address
	    echo "Make DHCP request against the VLAN bridge"
	
	    # Run dhcp on vlan - leave running in background
	 	/etc/run-dhcpc.sh vlanbr $myhostname /etc/app-dhcpc.script >/dev/null 2>&1 &
    
    fi
    
    # start the inetd super server
    echo "Starting inetd super server (provides Telnet)"
    inetd
}

stop()
{
    if [ -n "$eth_rename_bb" ]
    then
    	eth_bb=$eth_rename_bb
    fi
    if [ -n "$eth_rename_cdi" ]
    then
    	eth_cdi=$eth_rename_cdi
    fi

    echo Stopping vlan network
    ifconfig vlanbr down

    for pf in /tmp/vlanbr*.pid ; do
    if [[ -f $pf ]] ; then
        pid=$(cat $pf)
        #log killing udhcpc $pid from $pf
        if [[ ! -z "$pid" ]] ; then
        kill $pid
        fi
        rm -f $pf
    fi
    done

    # remove interfaces from bridge
    ifconfig $eth_bb.10 down
    brctl delif vlanbr $eth_bb.10
    
	ifconfig $eth_bb.11 down
	brctl delif vlanbr $eth_bb.11

    ifconfig vlantap down
    brctl delif vlanbr vlantap
    brctl delbr vlanbr
    vconfig rem $eth_bb.10
    vconfig rem $eth_bb.11

    ifconfig $eth_bb down
    ifconfig $eth_cdi down

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
