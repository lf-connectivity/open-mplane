/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111NetworkingService.cpp
 * \brief
 *
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "NetAddrStatic.h"
#include "NetAddrLinkLocal.h"
#include "NetAddrDhcp.h"

#include "IAppOptions.h"
#include "IBootEnv.h"

#include "Zcu111NetworkingService.h"

using namespace Mplane;

//=============================================================================================================
// CONST
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const unsigned TIMEOUT_MS{30000} ;
static const std::string ENV_HOSTNAME{"hostname"} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111NetworkingService::Zcu111NetworkingService(const std::string& interface) :
	Zcu111BaseNetworkingService(interface)
{
	// Try static IP first
	addAllocator(std::make_shared<NetAddrStatic>(netInterface())) ;

	// followed by link local
	addAllocator(std::make_shared<NetAddrLinkLocal>(netInterface(), TIMEOUT_MS)) ;

	// then keep running DHCP until get an address
	std::shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance()) ;
	std::string hostname(bootEnv->getVar(ENV_HOSTNAME)) ;
	addAllocator(std::make_shared<NetAddrDhcp>(netInterface(), hostname)) ;

}

//-------------------------------------------------------------------------------------------------------------
Zcu111NetworkingService::~Zcu111NetworkingService()
{
}
