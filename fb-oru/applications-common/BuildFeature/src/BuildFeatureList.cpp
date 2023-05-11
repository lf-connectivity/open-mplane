/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BuildFeatureList.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "BuildFeatureList.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<BuildFeatureList> BuildFeatureList::getInstance()
{
	static std::shared_ptr<BuildFeatureList> instance(std::make_shared<BuildFeatureList>()) ;
	return instance ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
BuildFeatureList::BuildFeatureList() :
	mCreateList(),
	mBuildFeatureList()
{
}

//-------------------------------------------------------------------------------------------------------------
BuildFeatureList::~BuildFeatureList()
{
}

//-------------------------------------------------------------------------------------------------------------
int BuildFeatureList::registerBuildFeature(BuildFeatureCreate create)
{
	mCreateList.push_back(create) ;
	return mCreateList.size()-1 ;
}

//-------------------------------------------------------------------------------------------------------------
bool BuildFeatureList::initBuildFeatures(IApplication* app)
{
	for (auto create : mCreateList)
	{
		std::shared_ptr<IBuildFeature> BuildFeature(create()) ;
		if (!BuildFeature)
			return false ;

		mBuildFeatureList.push_back(BuildFeature) ;

		if (!BuildFeature->init(app))
			return false ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned BuildFeatureList::numBuildFeatures() const
{
	return mCreateList.size() ;
}


//=============================================================================================================
// PROXY
//=============================================================================================================

#define PROXY_FWD(nm) \
bool BuildFeatureList::nm() \
{ \
	for (auto feat : mBuildFeatureList) \
	{ \
		if (!feat->nm()) \
			return false ; \
	} \
	return true ; \
}

//-------------------------------------------------------------------------------------------------------------
PROXY_FWD(appStart)
PROXY_FWD(appPreWait)
PROXY_FWD(appPreInit)
PROXY_FWD(appPostInit)
PROXY_FWD(appPreRun)
PROXY_FWD(appEnd)

//-------------------------------------------------------------------------------------------------------------
bool BuildFeatureList::appPreOptions(std::vector<std::shared_ptr<IAppOptionSpec> >& options)
{
	for (auto feat : mBuildFeatureList)
	{
		if (!feat->appPreOptions(options))
			return false ;
	}
	return true ;
}
