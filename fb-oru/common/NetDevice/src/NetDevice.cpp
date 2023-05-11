/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetDevice.cpp
 * \brief
 *
 *
 * \details
 *
 */


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
#include <fcntl.h>
#include <ifaddrs.h>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>

#include "stringfunc.hpp"
#include "NetVlanDevice.h"
#include "NetDevice.h"

using namespace Mplane;

//#define DEBUG_ERRORS

//=============================================================================================================
// TYPES
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
using IfReq = struct ifreq ;



//=============================================================================================================
// FACTORY
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::vector<std::shared_ptr<NetDevice>> NetDevice::getInterfaces()
{
	std::vector<std::shared_ptr<NetDevice>> interfaces ;

	// get the linked list of interfaces
	struct ifaddrs *ifaddr, *ifa;
	if (::getifaddrs(&ifaddr) == -1)
		return std::vector<std::shared_ptr<NetDevice>>() ;

	// create a list of just the interface names
	std::set<std::string> names ;
	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
	{
		if (ifa->ifa_addr == NULL)
			continue;

		names.insert(ifa->ifa_name) ;
	}
	::freeifaddrs(ifaddr);

	// Create a NetDevice per name
	for (auto name : names)
	{
		std::shared_ptr<NetDevice> nd(std::make_shared<NetDevice>()) ;
		if (!nd->open(name))
			continue ;

		nd->getStatus() ;
		interfaces.push_back(nd) ;
	}

	return interfaces ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
NetDevice::NetDevice() :
	mName(),
	mFd(-1),
	mGotInfo(false),
	mGotHwInfo(false),
	mIfFlags(0),
	mAddr(),
	mBroadcastAddr(),
	mNetMask(),
	mMac(),
	mConnected(false)
{
}

//-------------------------------------------------------------------------------------------------------------
NetDevice::NetDevice(const std::string& name, int64_t speed, const std::string& descName) :
	NetDevice()
{
	open(name) ;
}

//-------------------------------------------------------------------------------------------------------------
NetDevice::~NetDevice()
{
	close() ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetDevice::isValid() const
{
	if (mFd < 0)
		return false ;

	return mGotInfo ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetDevice::isVlan() const
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
int NetDevice::vlanId() const
{
	return -1 ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetDevice::getBaseName() const
{
	return "";
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<NetDevice> NetDevice::createVlan(unsigned vlanId, const std::string &macId)
{
	auto device(std::make_shared<NetVlanDevice>(mName, vlanId, macId)) ;
	return device ;
}


//-------------------------------------------------------------------------------------------------------------
bool NetDevice::open(const std::string& name)
{
	mName = name ;

	/* Create a channel to the NET kernel. */
	errno = 0 ;
	mFd = ::socket(AF_INET, SOCK_DGRAM, 0);

	// update with status
	return getStatus() ;
}

//-------------------------------------------------------------------------------------------------------------
void NetDevice::close()
{
	if (mFd > 0)
		::close(mFd) ;
	mFd = -1 ;
	mName.clear() ;
	mIfFlags = 0 ;
	mGotHwInfo = false ;
	mGotInfo = false ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetDevice::getStatus()
{
	mGotInfo = false ;
	if (!getHwStatus())
		return false ;

	struct ifreq ifr ;
	::memset((void *)&ifr, 0, sizeof(ifr)) ;

	::strncpy(ifr.ifr_name, mName.c_str(), sizeof(ifr.ifr_name)-1) ;
	if (::ioctl(mFd, SIOCGIFADDR, &ifr) < 0)
	{
#ifdef DEBUG_ERRORS
		std::cerr << "SIOCGIFADDR errno=" << errno << std::endl ;
#endif
		return false ;
	}
	mAddr = addrToString(&ifr.ifr_addr) ;

	::strncpy(ifr.ifr_name, mName.c_str(), sizeof(ifr.ifr_name)-1) ;
	if (::ioctl(mFd, SIOCGIFNETMASK, &ifr) < 0)
	{
#ifdef DEBUG_ERRORS
		std::cerr << "SIOCGIFNETMASK errno=" << errno << std::endl ;
#endif
		return false ;
	}
	mNetMask = addrToString(&ifr.ifr_netmask) ;

	::strncpy(ifr.ifr_name, mName.c_str(), sizeof(ifr.ifr_name)-1) ;
	if (::ioctl(mFd, SIOCGIFBRDADDR, &ifr) < 0)
	{
#ifdef DEBUG_ERRORS
		std::cerr << "SIOCGIFBRDADDR errno=" << errno << std::endl ;
#endif
		return false ;
	}
	mBroadcastAddr = addrToString(&ifr.ifr_broadaddr) ;

	mGotInfo = true ;
	return mGotInfo ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetDevice::getName() const
{
	return mName ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetDevice::isUp() const
{
	if (!mGotHwInfo)
		return false ;

	return mIfFlags & IFF_UP ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetDevice::isBroadcast() const
{
	if (!mGotHwInfo)
		return false ;

	return mIfFlags & IFF_BROADCAST ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetDevice::isMulticast() const
{
	if (!mGotHwInfo)
		return false ;

	return mIfFlags & IFF_MULTICAST ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetDevice::getAddr() const
{
	if (!mGotInfo)
		return "" ;

	return mAddr ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetDevice::getBroadcastAddr() const
{
	if (!mGotInfo)
		return "" ;

	return mBroadcastAddr ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetDevice::getNetmask() const
{
	if (!mGotInfo)
		return "" ;

	return mNetMask ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetDevice::getMac() const
{
	if (!mGotHwInfo)
		return "" ;

	return mMac ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetDevice::getMacFormatted() const
{
	if (!mGotHwInfo)
		return "" ;

	std::string macFormatted;

	for(uint32_t idx = 0; idx < mMac.size(); idx+=2)
	{
		macFormatted += mMac[idx];
		macFormatted += mMac[idx+1];
		if(idx < (mMac.size()-2))
		{
			macFormatted += ":";
		}
	}

	return macFormatted;
}


//-------------------------------------------------------------------------------------------------------------
bool NetDevice::isConnected() const
{
	return mConnected ;
}


//-------------------------------------------------------------------------------------------------------------
bool NetDevice::setAddr(const std::string& addr, const std::string& netmask)
{
	if (mFd < 0)
		return false ;

	struct ifreq ifr ;
	::memset((void *)&ifr, 0, sizeof(ifr)) ;

    struct sockaddr_in sin;

    // set address
    memset(&sin, 0, sizeof(struct sockaddr));
    sin.sin_family = AF_INET;
    sin.sin_port = 0;
    sin.sin_addr.s_addr = inet_addr(addr.c_str());
    memcpy(&ifr.ifr_addr, &sin, sizeof(struct sockaddr));

	::strncpy(ifr.ifr_name, mName.c_str(), sizeof(ifr.ifr_name)-1) ;
	if (::ioctl(mFd, SIOCSIFADDR, &ifr) < 0)
	{
#ifdef DEBUG_ERRORS
		std::cerr << "SIOCSIFADDR errno=" << errno << std::endl ;
#endif
		return false ;
	}

	// skip if netmask empty
	if (netmask.empty())
		return true ;

	// set netmask
    memset(&sin, 0, sizeof(struct sockaddr));
    sin.sin_family = AF_INET;
    sin.sin_port = 0;
    sin.sin_addr.s_addr = inet_addr(netmask.c_str());
    memcpy(&ifr.ifr_addr, &sin, sizeof(struct sockaddr));

	::strncpy(ifr.ifr_name, mName.c_str(), sizeof(ifr.ifr_name)-1) ;
	if (::ioctl(mFd, SIOCSIFNETMASK, &ifr) < 0)
	{
#ifdef DEBUG_ERRORS
		std::cerr << "SIOCSIFNETMASK errno=" << errno << std::endl ;
#endif
		return false ;
	}

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool NetDevice::setMac(const std::string &macstr)
{
//std::cerr << "NetDevice::setMac " << macstr << " [" << mName << "]" << std::endl ;

	if (mFd < 0)
		return false ;

	struct ifreq ifr ;
	::memset((void *)&ifr, 0, sizeof(ifr)) ;
	::strncpy(ifr.ifr_name, mName.c_str(), sizeof(ifr.ifr_name)-1) ;


    // convert mac address string into a value
    uint64_t macId(strToMac(macstr)) ;

//std::cerr << "NetDevice::setMac id=0x" << std::hex << macId << std::dec << " [" << mName << "]" << std::endl ;

    // store mac
    struct sockaddr sa ;
	sa.sa_family = ARPHRD_ETHER;
	char *ptr((char *)sa.sa_data);
	for (unsigned i=0; i < 6; ++i)
	{
		*ptr++ = (char)( (macId >> ((5-i)*8)) & 0xff ) ;
	}
	memcpy( ((char *)&ifr) + offsetof(struct ifreq, ifr_hwaddr), (char *)&sa, sizeof(struct sockaddr));


	// If interface is up then we need to take it down first
	bool up(isUp()) ;
	if (up)
	{
		if (!setUp(false))
		{
//std::cerr << " + ERROR Failed to take interface down" << std::endl ;
			return false ;
		}
	}

	// set hw address
	if (::ioctl(mFd, SIOCSIFHWADDR, &ifr) < 0)
	{
#ifdef DEBUG_ERRORS
		std::cerr << "SIOCSIFHWADDR errno=" << errno << std::endl ;
#endif
		return false ;
	}

	// ok to update cached mac
	setMacStr(macstr) ;

	if (up)
		setUp(true) ;

//std::cerr << "NetDevice::setMac " << macstr << " [" << mName << "] - OK" << std::endl ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool NetDevice::setUp(bool up)
{
	if (mFd < 0)
		return false ;

	struct ifreq ifr ;
	::memset((void *)&ifr, 0, sizeof(ifr)) ;

	// get flags
	::strncpy(ifr.ifr_name, mName.c_str(), sizeof(ifr.ifr_name)-1) ;
	if (::ioctl(mFd, SIOCGIFFLAGS, &ifr) < 0)
	{
#ifdef DEBUG_ERRORS
		std::cerr << "SIOCGIFFLAGS errno=" << errno << std::endl ;
#endif
		return false ;
	}

	// set UP or DOWN
	if (up)
	{
		// UP
		ifr.ifr_flags |= IFF_UP | IFF_RUNNING;
	}
	else
	{
		// DOWN
		ifr.ifr_flags &= ~(IFF_UP | IFF_RUNNING) ;
	}

	// set flags
	if (::ioctl(mFd, SIOCSIFFLAGS, &ifr) < 0)
	{
#ifdef DEBUG_ERRORS
		std::cerr << "SIOCSIFFLAGS errno=" << errno << std::endl ;
#endif
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetDevice::addRoute(const std::string& addr, const std::string& netmask)
{
	if (mFd < 0)
		return false ;

	struct rtentry rt;
	::memset((void *)&rt, 0, sizeof(rt)) ;

	struct sockaddr_in *sockinfo = (struct sockaddr_in *)&rt.rt_gateway;
	sockinfo->sin_family = AF_INET;
	sockinfo->sin_addr.s_addr = inet_addr("0.0.0.0") ;

	sockinfo = (struct sockaddr_in *)&rt.rt_dst;
	sockinfo->sin_family = AF_INET;
	sockinfo->sin_addr.s_addr = inet_addr(addr.c_str()) ;

	sockinfo = (struct sockaddr_in *)&rt.rt_genmask;
	sockinfo->sin_family = AF_INET;
	if (netmask.empty())
		sockinfo->sin_addr.s_addr = inet_addr("255.255.255.0");
	else
		sockinfo->sin_addr.s_addr = inet_addr(netmask.c_str()) ;

	rt.rt_flags = RTF_UP;
	rt.rt_dev = &mName[0] ;

	if(ioctl(mFd, SIOCADDRT, &rt) < 0 )
	{
#ifdef DEBUG_ERRORS
		perror("SIOCADDRT") ;
#endif
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetDevice::addDefaultGateway(const std::string& addr)
{
	if (mFd < 0)
		return false ;

	struct rtentry rt;
	::memset((void *)&rt, 0, sizeof(rt)) ;

	struct sockaddr_in *sockinfo = (struct sockaddr_in *)&rt.rt_gateway;
	sockinfo->sin_family = AF_INET;
	sockinfo->sin_addr.s_addr = inet_addr(addr.c_str());

	sockinfo = (struct sockaddr_in *)&rt.rt_dst;
	sockinfo->sin_family = AF_INET;
	sockinfo->sin_addr.s_addr = INADDR_ANY;

	sockinfo = (struct sockaddr_in *)&rt.rt_genmask;
	sockinfo->sin_family = AF_INET;
	sockinfo->sin_addr.s_addr = INADDR_ANY;

	rt.rt_flags = RTF_UP | RTF_GATEWAY;
	rt.rt_dev = &mName[0] ;

	if(ioctl(mFd, SIOCADDRT, &rt) < 0 )
	{
#ifdef DEBUG_ERRORS
		perror("SIOCADDRT") ;
#endif
		return false ;
	}

	return true ;
}


//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool NetDevice::getHwStatus()
{
	mGotHwInfo = false ;

	if (mFd < 0)
		return false ;
	if (mName.empty())
		return false ;

	struct ifreq ifr ;
	::memset((void *)&ifr, 0, sizeof(ifr)) ;

	// Get the connection status
	mConnected = carrierStatus(mName) ;

	::strncpy(ifr.ifr_name, mName.c_str(), sizeof(ifr.ifr_name)-1) ;
	if (::ioctl(mFd, SIOCGIFFLAGS, &ifr) < 0)
	{
#ifdef DEBUG_ERRORS
		std::cerr << "SIOCGIFFLAGS errno=" << errno << std::endl ;
#endif
		return false ;
	}
	mIfFlags = ifr.ifr_flags ;

	::strncpy(ifr.ifr_name, mName.c_str(), sizeof(ifr.ifr_name)-1) ;
	if (::ioctl(mFd, SIOCGIFHWADDR, &ifr) < 0)
	{
#ifdef DEBUG_ERRORS
		std::cerr << "SIOCGIFHWADDR errno=" << errno << std::endl ;
#endif
		return false ;
	}
	mMac = macToString(&ifr.ifr_hwaddr) ;

	mGotHwInfo = true ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void NetDevice::setMacStr(const std::string &macstr)
{
	mMac = macstr ;
}


//=============================================================================================================
// PRIVATE STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string NetDevice::addrToString(struct sockaddr* addr)
{
	if (!addr)
		return "";

	if (addr->sa_family != AF_INET)
		return "" ;

	char ipaddr[INET_ADDRSTRLEN+1] ;
	struct sockaddr_in* in_addr = (struct sockaddr_in*)addr ;
	if (!::inet_ntop(addr->sa_family, &(in_addr->sin_addr), ipaddr, sizeof(ipaddr)))
		return "" ;

	return std::string(ipaddr) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetDevice::macToString(struct sockaddr* addr)
{
	if (!addr)
		return "";

	if (addr->sa_family != AF_FILE)
		return "" ;

	std::stringstream ss ;
	for (unsigned idx=0; idx < 6; ++idx)
	{
		ss << std::setw(2) << std::setfill('0') << std::hex << (0xff & (unsigned)addr->sa_data[idx]) ;
	}
	return toUpper(ss.str()) ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetDevice::carrierStatus(const std::string& interface)
{
	std::string path("/sys/class/net/" + interface + "/carrier") ;
	int sysfd = ::open(path.c_str(), O_RDONLY) ;
	if (sysfd < 0)
	{
		return false ;
	}

	// contents will be "0" or "1"
	char buff[16] ;
	int num = read(sysfd, buff, 1) ;
	::close(sysfd) ;

	if (num < 1)
	{
		return false ;
	}

	return (buff[0] == '1') ;
}

#if 0
//-------------------------------------------------------------------------------------------------------------
void NetDevice::dump(struct sockaddr* addr)
{
	std::cout << "Family: " << addr->sa_family << std::endl ;
	for (unsigned idx=0; idx < 14; ++idx)
	{
		std::cout << std::hex << "0x" << (0xff & (unsigned)addr->sa_data[idx]) << " " ;
	}
	std::cout << std::dec << std::endl ;
}
#endif
