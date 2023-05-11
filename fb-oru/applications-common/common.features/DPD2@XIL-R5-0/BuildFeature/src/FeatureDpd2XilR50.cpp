/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FeatureDpd2XilR50.cpp
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

#include "ITif.h"
#include "BuildFeatureUtils.hpp"
#include "BuildFeatureList.h"

#include "config.h"

// Load in the test interface for DPD from the feature area
#include "TifDpdTestHandler.h"

#include "FeatureDpd2XilR50.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const unsigned R5_0(0);

//=============================================================================================================
// PUBLIC
//=============================================================================================================
int FeatureDpd2XilR50::handle = BuildFeatureUtils<FeatureDpd2XilR50>::registerBuildFeature() ;

std::shared_ptr<IBuildFeature> FeatureDpd2XilR50::getInstance()
{
	return BuildFeatureUtils<FeatureDpd2XilR50>::getInstance() ;
}

//-------------------------------------------------------------------------------------------------------------
FeatureDpd2XilR50::FeatureDpd2XilR50() :
	BuildFeature(),
	mMgr(IEmbeddedMgr::singleton())
{
}

//-------------------------------------------------------------------------------------------------------------
FeatureDpd2XilR50::~FeatureDpd2XilR50()
{
}


//-------------------------------------------------------------------------------------------------------------
bool FeatureDpd2XilR50::init(IApplication* app)
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FeatureDpd2XilR50::appPreInit()
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FeatureDpd2XilR50::appPostInit()
{
	// Now that all the hardware and fpga initialisation is complete, should be ok to start DPD
	if (! mMgr->loadFirmware(R5_0) )
    {
        ILoggable::logEventError("DPD2 unable to load firmware: %s", mMgr->error().c_str());
        return false ;
    }

	if (!mMgr->eventLoop(R5_0, true))
    {
        ILoggable::logEventError("DPD2 unable to start event loop: %s", mMgr->error().c_str());
        return false ;
    }

    std::shared_ptr<IRemoteMsgHandler> hdlr(mMgr->msgHandler(R5_0)) ;
    if (!hdlr->isEventLoop())
    {
        ILoggable::logEventError("DPD2 event loop not running");
        return false ;
    }
    return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FeatureDpd2XilR50::appPreWait()
{

    return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FeatureDpd2XilR50::appPreRun()
{
	// Inject the DPD tif
	std::shared_ptr<ITifEntry> newTif(std::make_shared<TifDpdTestHandler>()) ;
	if (!ITifControl::inject(newTif))
		return false ;

	// Use macro to pass the tif settings from build config
	TIF_BUILD_SETTINGS(DPD2, "/dpd") ;

	return true ;
}
