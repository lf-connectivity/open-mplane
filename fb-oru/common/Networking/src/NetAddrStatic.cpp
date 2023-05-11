/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetAddrStatic.cpp
 * \brief
 *
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IBootEnv.h"
#include "SystemTask.h"
#include "NetAddrStatic.h"

using namespace Mplane;

//=============================================================================================================
// CONST
//=============================================================================================================

static const std::string ENV_IP{"ipaddr"} ;
static const std::string ENV_NETMASK{"netmask"} ;
static const std::string ENV_GATEWAY{"gatewayip"} ;
static const std::string ENV_GATEWAY2{"serverip"} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
NetAddrStatic::NetAddrStatic(const std::string& interface) :
	NetAddr("Static", INetChange::NET_STATIC, interface)
{
}

//-------------------------------------------------------------------------------------------------------------
NetAddrStatic::~NetAddrStatic()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void NetAddrStatic::doStart()
{
}

//-------------------------------------------------------------------------------------------------------------
void NetAddrStatic::doAllocate()
{
	logDebugVerbose("[STATIC:%s] Check static settings ... ", interface().c_str()) ;

	std::shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance()) ;

    std::string ip(bootEnv->getVar(ENV_IP)) ;
    std::string netmask(bootEnv->getVar(ENV_NETMASK)) ;
    std::string gateway(bootEnv->getVar(ENV_GATEWAY)) ;
    std::string gateway2(bootEnv->getVar(ENV_GATEWAY2)) ;

	logDebugVerbose("[STATIC:%s] settings: ip=%s gateway=%s(%s) netmask=%s",
			interface().c_str(), ip.c_str(), gateway.c_str(), gateway2.c_str(), netmask.c_str()) ;

    // assume we'll fail
	setStatus(INetAddr::NET_TIMED_OUT) ;

	if (ip.empty())
		return ;
	if (gateway.empty() && gateway2.empty())
		return ;

	if (gateway.empty())
		gateway = gateway2 ;

	if (netmask.empty())
		netmask = "255.255.255.0" ;

	logDebugVerbose("[STATIC:%s] SET", interface().c_str()) ;

	// We've done
	setIpAddress(ip) ;
	setInterfaceIp(ip, netmask, gateway) ;
	setStatus(INetAddr::NET_IP_ALLOCATED) ;
}
