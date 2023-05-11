/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetVlanDevice.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <net/ethernet.h>
#include <net/route.h>
#include <arpa/inet.h>
#include <linux/if_link.h>
#include <linux/if_vlan.h>
#include <linux/sockios.h>
#include <fcntl.h>
#include <ifaddrs.h>

#include "NetVlanDevice.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
NetVlanDevice::NetVlanDevice(const std::string &parent, unsigned vlanId, const std::string &macId) :
	mParentName(parent),
	mVlanId(vlanId),
	mVlanBaseName(),
	mVlanMac(macId),
	mVlanCreated(false)
{
//std::cerr << "NEW NetVlanDevice parent=" << mParentName << " vlan" << mVlanId << " mac=" << mVlanMac << std::endl ;

	open(mParentName + "." + std::to_string(mVlanId)) ;
}

//-------------------------------------------------------------------------------------------------------------
NetVlanDevice::~NetVlanDevice()
{
//	std::cerr << "DEL NetVlanDevice " << getName() << " vlan" << mVlanId << " mac=" << mVlanMac << std::endl ;
	close() ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetVlanDevice::open(const std::string &name)
{
//std::cerr << "OPEN NetVlanDevice name=" << name << " mac=" << mVlanMac << " Parent " << mParentName << std::endl ;

	std::size_t pos(name.find('.')) ;
	if (pos == std::string::npos)
		return false ;

	// ignore base name (just use the parent) but make sure the VLAN id is used
	int vlan(stoi(name.substr(pos+1))) ;
	if (vlan <= 0)
		return false ;

	mVlanId = vlan ;

	// Create the vlan interface
	struct vlan_ioctl_args ifr;

	memset(&ifr, 0, sizeof(ifr));
	ifr.cmd = ADD_VLAN_CMD;

	strncpy(ifr.device1, mParentName.c_str(), IFNAMSIZ);
	ifr.u.VID = mVlanId ;

	int fd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (::ioctl(fd, SIOCSIFVLAN, &ifr) < 0)
	{
		std::cerr << "SIOCSIFVLAN ADD errno=" << errno << std::endl ;
		return false ;
	}
	mVlanCreated = true ;

	// "open" the device - ignore the errors with trying to get the status
	(void)this->NetDevice::open(name) ;

	// set the mac
	if (!setMac(mVlanMac))
	{
		std::cerr << "ERROR unable to set MAC to " << mVlanMac << std::endl ;
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void NetVlanDevice::close()
{
//	std::cerr << "CLOSE NetVlanDevice name=" << getName() << " vlan" << mVlanId << " mac=" << mVlanMac << std::endl ;

	if (mVlanCreated)
	{
		// delete the vlan interface
		mVlanCreated = false ;

		struct vlan_ioctl_args ifr;
		memset(&ifr, 0, sizeof(ifr));
		ifr.cmd = DEL_VLAN_CMD;
		strncpy(ifr.device1, getName().c_str(), IFNAMSIZ);

		int fd = ::socket(AF_INET, SOCK_STREAM, 0);
		if (::ioctl(fd, SIOCSIFVLAN, &ifr) < 0)
		{
			std::cerr << "SIOCSIFVLAN DEL errno=" << errno << std::endl ;
		}
	}

	this->NetDevice::close() ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetVlanDevice::getStatus()
{
	return this->NetDevice::getStatus() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetVlanDevice::getName() const
{
	return this->NetDevice::getName() ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetVlanDevice::isValid() const
{
	return this->NetDevice::isValid() ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetVlanDevice::isVlan() const
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
int NetVlanDevice::vlanId() const
{
	return mVlanId ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetVlanDevice::getBaseName() const
{
	return mVlanBaseName;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<NetDevice> NetVlanDevice::createVlan(unsigned vlanId, const std::string &macId)
{
	return std::shared_ptr<NetDevice>() ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetVlanDevice::isUp() const
{
	return this->NetDevice::isUp() ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetVlanDevice::isBroadcast() const
{
	return this->NetDevice::isBroadcast() ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetVlanDevice::isMulticast() const
{
	return this->NetDevice::isMulticast() ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetVlanDevice::isConnected() const
{
	return this->NetDevice::isConnected() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetVlanDevice::getAddr() const
{
	return this->NetDevice::getAddr() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetVlanDevice::getBroadcastAddr() const
{
	return this->NetDevice::getBroadcastAddr() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetVlanDevice::getNetmask() const
{
	return this->NetDevice::getNetmask() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetVlanDevice::getMac() const
{
	return this->NetDevice::getMac() ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetVlanDevice::setAddr(const std::string &addr, const std::string &netmask)
{
	return this->NetDevice::setAddr(addr, netmask) ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetVlanDevice::setMac(const std::string &mac)
{
	if (!this->NetDevice::setMac(mac))
		return false ;

	mVlanMac = mac ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetVlanDevice::setUp(bool up)
{
	return this->NetDevice::setUp(up) ;
}


//-------------------------------------------------------------------------------------------------------------
bool NetVlanDevice::addRoute(const std::string &addr, const std::string &netmask)
{
	return this->NetDevice::addRoute(addr, netmask) ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetVlanDevice::addDefaultGateway(const std::string &addr)
{
	return this->NetDevice::addDefaultGateway(addr) ;
}
