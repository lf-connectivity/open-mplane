/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FeatureDiscoveryEnable.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>

#include "config.h"
#include "ITif.h"
#include "BuildFeatureUtils.hpp"
#include "BuildFeatureList.h"

#include "Task.h"
#include "ILoggable.h"
#include "IServicesCtl.h"
#include "IDiscovery.h"
#include "NetStatus.h"

// Load in the test interface for DISCOVERY from the feature area
#include "DiscoveryEnableDiscoveryTestHandler.h"

#include "FeatureDiscoveryEnable.h"

using namespace Mplane;

//=============================================================================================================
// INetStatus SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<INetStatus> INetStatus::getInstance()
{
	return NetStatus::getInstance() ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================
int FeatureDiscoveryEnable::handle = BuildFeatureUtils<FeatureDiscoveryEnable>::registerBuildFeature() ;

std::shared_ptr<IBuildFeature> FeatureDiscoveryEnable::getInstance()
{
	return BuildFeatureUtils<FeatureDiscoveryEnable>::getInstance() ;
}

//-------------------------------------------------------------------------------------------------------------
FeatureDiscoveryEnable::FeatureDiscoveryEnable() :
	BuildFeature()
{
}

//-------------------------------------------------------------------------------------------------------------
FeatureDiscoveryEnable::~FeatureDiscoveryEnable()
{
}


//-------------------------------------------------------------------------------------------------------------
bool FeatureDiscoveryEnable::init(IApplication* app)
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FeatureDiscoveryEnable::appPreOptions(std::vector<std::shared_ptr<IAppOptionSpec> >& options)
{
	// Discovery needs an extra option to set the discovery network interface name
	options.push_back(
		IAppOptionSpec::factory("ethssdp", DataVariantType::String, "Ethernet interface name (discovery)", "vlanbr", "ETHSSDP")
	) ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool FeatureDiscoveryEnable::appPostInit()
{
	std::shared_ptr<IDiscovery> discovery = IDiscovery::getInstance();
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FeatureDiscoveryEnable::appPreRun()
{
	// Inject the DISCOVERY tif
	std::shared_ptr<ITifEntry> newTif(std::make_shared<DiscoveryEnableDiscoveryTestHandler>()) ;
	if (!ITifControl::inject(newTif))
		return false ;

	// Use macro to pass the tif settings from build config
	TIF_BUILD_SETTINGS(DISCOVERY, "/discovery") ;

	return true ;
}
