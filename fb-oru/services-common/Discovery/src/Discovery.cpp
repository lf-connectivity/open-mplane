/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Discovery.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IAppSettings.h"
#include "IAppSettingsFactory.h"
#include "IAppOptions.h"

#include "Ssdp.h"
#include "Discovery.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANT
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
static const unsigned CACHE_MAX_AGE{1800} ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Discovery::Discovery() :
	mSsdp()
{
	std::shared_ptr<IAppSettings> appSettings( IAppSettingsFactory::getInterface() ) ;
	std::shared_ptr<IAppOptions> opts(IAppOptions::getInstance() ) ;

	// SSDP handler
	mSsdp = std::make_shared<Ssdp>(
		appSettings->getAppString(),
		appSettings->getBuildVersion() + "-" + std::to_string(appSettings->getBuildNumber()),
		opts->getOption("ethssdp").toString(),
		CACHE_MAX_AGE
	) ;
}

//-------------------------------------------------------------------------------------------------------------
Discovery::~Discovery()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string Discovery::getIp() const
{
	return mSsdp->getIp() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Discovery::getUuid() const
{
	return mSsdp->getUuid() ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned Discovery::getCacheAge() const
{
	return CACHE_MAX_AGE ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned Discovery::getSearchCount() const
{
	return mSsdp->getSearchCount() ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned Discovery::getNotifyCount() const
{
	return mSsdp->getNotifyCount() ;
}
