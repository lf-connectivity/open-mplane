/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FeatureDiscoveryLab.cpp
 * \brief
 *
 *
 * \details   Adds discovery feature iff this is a LAB build
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
#include "DiscoveryLabDiscoveryTestHandler.h"

#include "config.h"
#include "FeatureDiscoveryLab.h"

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
int FeatureDiscoveryLab::handle = BuildFeatureUtils<FeatureDiscoveryLab>::registerBuildFeature() ;

std::shared_ptr<IBuildFeature> FeatureDiscoveryLab::getInstance()
{
	return BuildFeatureUtils<FeatureDiscoveryLab>::getInstance() ;
}

//-------------------------------------------------------------------------------------------------------------
FeatureDiscoveryLab::FeatureDiscoveryLab() :
	BuildFeature()
{
}

//-------------------------------------------------------------------------------------------------------------
FeatureDiscoveryLab::~FeatureDiscoveryLab()
{
}


//-------------------------------------------------------------------------------------------------------------
bool FeatureDiscoveryLab::init(IApplication* app)
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FeatureDiscoveryLab::appPreOptions(std::vector<std::shared_ptr<IAppOptionSpec> >& options)
{
	if (LAB)
	{
		// Discovery needs an extra option to set the discovery network interface name
		options.push_back(
			IAppOptionSpec::factory("ethssdp", DataVariantType::String, "Ethernet interface name (discovery)", "eth_cdi", "ETHSSDP")
		) ;
	}

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool FeatureDiscoveryLab::appPostInit()
{
	if (LAB)
	{
	    std::shared_ptr<IDiscovery> discovery = IDiscovery::getInstance();
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FeatureDiscoveryLab::appPreRun()
{
	if (LAB)
	{
		// Inject the DISCOVERY tif
		std::shared_ptr<ITifEntry> newTif(std::make_shared<DiscoveryLabDiscoveryTestHandler>()) ;
		if (!ITifControl::inject(newTif))
			return false ;

		// Use macro to pass the tif settings from build config
		TIF_BUILD_SETTINGS(DISCOVERY, "/discovery") ;
	}

	return true ;
}
