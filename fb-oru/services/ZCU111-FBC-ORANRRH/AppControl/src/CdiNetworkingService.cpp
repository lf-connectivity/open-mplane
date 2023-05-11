/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CdiNetworkingService.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IBootEnv.h"

#include "NetAddrMac.h"
#include "NetAddrStatic.h"
#include "NetAddrLinkLocal.h"
#include "NetAddrDhcp.h"

#include "CdiNetworkingService.h"

using namespace Mplane;

//=============================================================================================================
// CONST
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const unsigned TIMEOUT_MS{30000} ;
const std::string ENV_HOSTNAME{"hostname"} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CdiNetworkingService::CdiNetworkingService(const std::string &interface) :
	Zcu111BaseNetworkingService(interface)
{
	// Try static IP first
	addAllocator(std::make_shared<NetAddrStatic>(netInterface())) ;

	// followed by link local
	addAllocator(std::make_shared<NetAddrLinkLocal>(netInterface(), TIMEOUT_MS)) ;

#ifndef TEST_BB_ON_CDI
	// then keep running DHCP until get an address
	std::shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance()) ;
	std::string hostname(bootEnv->getVar(ENV_HOSTNAME)) ;
	addAllocator(std::make_shared<NetAddrDhcp>(netInterface(), hostname)) ;
#endif
}

//-------------------------------------------------------------------------------------------------------------
CdiNetworkingService::~CdiNetworkingService()
{
}
