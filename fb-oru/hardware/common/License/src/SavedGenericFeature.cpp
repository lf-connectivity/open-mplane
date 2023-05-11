/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SavedGenericFeature.cpp
 * \brief     Implements IGenericFeature saved in u-boot env
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
#include "SavedGenericFeature.h"

using namespace Mplane ;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
static const std::string FEATURE_ENV{"FEATURE"} ;

//=============================================================================================================
// FACTORY
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IGenericFeature> SavedGenericFeature::factory(const std::vector<std::string>& featureNames)
{
	return std::make_shared<SavedGenericFeature>(featureNames) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IGenericFeature> SavedGenericFeature::factory(const std::map<std::string, unsigned>& featureNames)
{
	return std::make_shared<SavedGenericFeature>(featureNames) ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SavedGenericFeature::SavedGenericFeature(const std::vector<std::string>& featureNames) :
	GenericFeature(featureNames)
{
	init() ;
}

//-------------------------------------------------------------------------------------------------------------
SavedGenericFeature::SavedGenericFeature(const std::map<std::string, unsigned>& featureNames) :
	GenericFeature(featureNames)
{
	init() ;
}

//-------------------------------------------------------------------------------------------------------------
SavedGenericFeature::~SavedGenericFeature()
{
}

//-------------------------------------------------------------------------------------------------------------
bool SavedGenericFeature::setFeatures(const std::string& encodedFeatures)
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

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void SavedGenericFeature::init()
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
