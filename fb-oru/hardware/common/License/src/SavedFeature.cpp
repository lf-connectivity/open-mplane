/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SavedFeature.cpp
 * \brief     Implements IFeature saved in u-boot env
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IKey.h"
#include "IBootEnv.h"
#include "SavedFeature.h"

using namespace Mplane ;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
static const std::string FEATURE_ENV{"FEATURE"} ;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFeature> SavedFeature::getInstance()
{
	static std::shared_ptr<IFeature> instance( std::make_shared<SavedFeature>() ) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SavedFeature::SavedFeature()
{
	// Get the u-boot env variable setting
	std::shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance()) ;
	if (!bootEnv->isVar(FEATURE_ENV))
		return ;

	// Get key
	setKey(IKey::getApplicationInstance()) ;

	// Set the feature from the saved string
	if (!this->super::setFeatures(bootEnv->getVar(FEATURE_ENV)))
		return ;

}

//-------------------------------------------------------------------------------------------------------------
SavedFeature::~SavedFeature()
{
}

//-------------------------------------------------------------------------------------------------------------
bool SavedFeature::setFeatures(const std::string& encodedFeatures)
{
	// Ensure key is set
	setKey(IKey::getApplicationInstance()) ;

	// Use parent to actually set the features
	if (!this->super::setFeatures(encodedFeatures))
		return false ;

	// Save to u-boot env
	std::shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance()) ;
	bootEnv->setVar(FEATURE_ENV, encodedFeatures) ;
	return true ;
}
