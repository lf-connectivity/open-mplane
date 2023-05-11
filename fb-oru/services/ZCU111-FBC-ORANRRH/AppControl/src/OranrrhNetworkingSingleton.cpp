/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranrrhNetworkingSingleton.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "INetworkingService.h"
#include "IAppOptions.h"

#include "NetDevice.h"
#include "OranNetworkingService.h"
#include "CdiNetworkingService.h"
#include "NetworkingService.h"


using namespace Mplane ;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

namespace {

	std::shared_ptr<INetworkingService> ethbbSingleton(const std::string& interface)
	{
		static std::shared_ptr<INetworkingService> instance(std::make_shared<OranNetworkingService>(interface)) ;
		return instance ;
	}

	std::shared_ptr<INetworkingService> ethcdiSingleton(const std::string& interface)
	{
		static std::shared_ptr<INetworkingService> instance(std::make_shared<CdiNetworkingService>(interface)) ;
		return instance ;
	}

}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<INetworkingService> INetworkingService::singleton(const std::string& interface)
{
	static std::string ethcdi(IAppOptions::getInstance()->getOption("ethcdi").toString()) ;
	static std::string ethbb(IAppOptions::getInstance()->getOption("ethbb").toString()) ;

	if (interface == ethcdi)
		return ethcdiSingleton(ethcdi) ;

	if (interface == ethbb)
		return ethbbSingleton(ethbb) ;

	return std::shared_ptr<INetworkingService>() ;
}
