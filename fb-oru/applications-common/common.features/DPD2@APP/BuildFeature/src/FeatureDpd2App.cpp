/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FeatureDpd2App.cpp
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
#include "IDpd2App.h"	// services repo

// Load in the test interface for DPD from the feature area
#include "TifDpdTestHandler.h"

#include "FeatureDpd2App.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================
int FeatureDpd2App::handle = BuildFeatureUtils<FeatureDpd2App>::registerBuildFeature() ;

std::shared_ptr<IBuildFeature> FeatureDpd2App::getInstance()
{
	return BuildFeatureUtils<FeatureDpd2App>::getInstance() ;
}

//-------------------------------------------------------------------------------------------------------------
FeatureDpd2App::FeatureDpd2App() :
	BuildFeature()
{
}

//-------------------------------------------------------------------------------------------------------------
FeatureDpd2App::~FeatureDpd2App()
{
}


//-------------------------------------------------------------------------------------------------------------
bool FeatureDpd2App::init(IApplication* app)
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FeatureDpd2App::appPreInit()
{
    // Ensure DPD application is up
    std::shared_ptr<IDpd2App> dpdApp(IDpd2App::getInstance()) ;
    return dpdApp.get() != nullptr ;
}

//-------------------------------------------------------------------------------------------------------------
bool FeatureDpd2App::appPostInit()
{
	// Now that all the hardware and fpga initialisation is complete, should be ok to start DPD
    std::shared_ptr<IDpd2App> dpdApp(IDpd2App::getInstance()) ;
    dpdApp->start() ;
    Task::msSleep(100) ; // wait for task to start
    if (!dpdApp->isDpdRunning())
    {
        ILoggable::logEventError("DPD2 application not running");
        return false ;
    }
    return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FeatureDpd2App::appPreRun()
{
	// Inject the DPD tif
	std::shared_ptr<ITifEntry> newTif(std::make_shared<TifDpdTestHandler>()) ;
	if (!ITifControl::inject(newTif))
		return false ;

	// Use macro to pass the tif settings from build config
	TIF_BUILD_SETTINGS(DPD2, "/dpd") ;

	return true ;
}
