/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranNetworkingService.cpp
 * \brief
 *
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <string>

#include "IBootEnv.h"

#include "NetAddrMac.h"
#include "NetAddrStatic.h"
#include "NetAddrLinkLocal.h"

#include "OranNetworkingService.h"

using namespace Mplane;

//=============================================================================================================
// CONST
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const unsigned TIMEOUT_MS{30000} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
OranNetworkingService::OranNetworkingService(const std::string& interface) :
	Zcu111BaseNetworkingService(interface)
{
	// Try static IP first
	addAllocator(std::make_shared<NetAddrStatic>(netInterface())) ;

	// NOTE: Additional policies may be added to this list by other repos (e.g. yang-manager-server if used)

}

//-------------------------------------------------------------------------------------------------------------
OranNetworkingService::~OranNetworkingService()
{
}
