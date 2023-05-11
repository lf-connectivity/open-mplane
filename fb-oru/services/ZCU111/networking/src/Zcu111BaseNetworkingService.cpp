/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111BaseNetworkingService.cpp
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
#include "LoRestart.h"

#include "IAppOptions.h"
#include "IBootEnv.h"

#include "Zcu111BaseNetworkingService.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111BaseNetworkingService::Zcu111BaseNetworkingService(const std::string& interface) :
	NetworkingService(interface)
{
	// Add a callback to get the local interface (lo) working properly
	std::shared_ptr<INetAddrPolicy> policy(getNetAddrPolicy()) ;
	policy->registerUpFunc([interface](){

		LoRestart::singleton()->restart() ;
	}) ;


//	policy->registerAllocatedFunc([interface](const std::string& itfc, const std::string& ipAddress,
//			const std::string& macAddress, const std::string& allocatorName, INetChange::NetState allocatorType){
//
//		std::cerr << "NET[" << interface << "] IP : LO " << std::endl ;
//
//		LoRestart::singleton()->restart() ;
//	}) ;

}

//-------------------------------------------------------------------------------------------------------------
Zcu111BaseNetworkingService::~Zcu111BaseNetworkingService()
{
}
