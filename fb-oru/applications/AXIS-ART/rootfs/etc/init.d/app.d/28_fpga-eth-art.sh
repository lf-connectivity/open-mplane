#!/bin/sh
# $Id:$
#
# Initialise the MII between fpga and PPC
#

# load config
. /etc/setup.env

start()
{

    echo "Configure network bridge bridge"

    #####    log starting rrh-address
    #####    rrh-address -D ${misc_daisy_control}

    #[ "$eth_debug" ] && set -xv

    # create the control device for the tun driver (major+minor match "modinfo tun")
    mkdir -p /dev/net
    [ -c /dev/net/tun ] || mknod /dev/net/tun c 10 200

#    # use ethaddr for fpga mac address
#    mac_bb=$(i2cenv ethaddr | sed -e 's/^.*=//')
#    ifconfig $eth_bb down
#    ifconfig $eth_bb hw ether $mac_bb

    # use eth1addr for network mac address
    mac_cdi=$(i2cenv eth1addr | sed -e 's/^.*=//')
    ifconfig $eth_cdi down
    ifconfig $eth_cdi hw ether $mac_cdi

    echo "Creating vlans"
    # add the vlan bridge instance and label it "vlanbr"
    brctl addbr vlanbr

    # set a MAC for the bridge (vlanbr), same as eth1 interface's MAC
    ifconfig vlanbr hw ether $(i2cenv eth1addr | sed -e 's/^.*=//')

#    # add the vlans depending
#    echo "Adding vlan $eth_bb.10"
#    vconfig add $eth_bb 10
#    ifconfig $eth_bb.10 hw ether $(i2cenv eth2addr | sed -e 's/^.*=//')
#    brctl addif vlanbr $eth_bb.10

    # don't bring up eth_bb if in test mode
    testEthBbDown=$(i2cenv testEthBbDown | sed -e 's/^.*=//')
    if [ -n "$testEthBbDown" ]
    then
		ifconfig $eth_bb down
    else
		ifconfig $eth_bb.10 up
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

}

stop()
{
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

    ifconfig vlantap down
    brctl delif vlanbr vlantap
    brctl delbr vlanbr
    vconfig rem $eth_bb.10

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
