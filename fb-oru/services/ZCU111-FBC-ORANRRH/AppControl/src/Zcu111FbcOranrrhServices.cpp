/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhServices.cpp
 * \brief     Implementation of services interface to create and controls all services
 *
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IAppOptions.h"
#include "INetworkingService.h"
#include "IPacketSniffer.h"

#include "Zcu111FbcOranrrhServices.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

/**
 * NOTE: This service is ONLY used for non-ORAN builds. In other words it's likely to be NEVER used!
 *
 */
//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhServices::Zcu111FbcOranrrhServices():
	OranRrhServices()
{
	std::string ethcdi(IAppOptions::getInstance()->getOption("ethcdi").toString()) ;
	std::string ethbb(IAppOptions::getInstance()->getOption("ethbb").toString()) ;

	// Task based services
	if (INetworkingService::singleton(ethcdi))
	{
		std::cerr << "Zcu111FbcOranrrhServices registering INetworkingService '" << ethcdi << "'" << std::endl ;
		registerTaskService( std::dynamic_pointer_cast<Task>(INetworkingService::singleton(ethcdi)) ) ;
	}

	if (INetworkingService::singleton(ethbb))
	{
		std::cerr << "Zcu111FbcOranrrhServices registering INetworkingService '" << ethbb << "'" << std::endl ;
		registerTaskService( std::dynamic_pointer_cast<Task>(INetworkingService::singleton(ethbb)) ) ;
	}

	if (IPacketSniffer::singleton(ethbb))
	{
		std::cerr << "Zcu111FbcOranrrhServices registering IPacketSniffer" << std::endl ;
		registerTaskService( std::dynamic_pointer_cast<Task>(IPacketSniffer::singleton(ethbb)) ) ;
	}

}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhServices::~Zcu111FbcOranrrhServices()
{
}
