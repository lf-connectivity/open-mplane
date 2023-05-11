/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SavedKey.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "IBootEnv.h"
#include "SavedKey.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
static const std::string LICENSE_ENV{"LICENSE"} ;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IKey> SavedKey::getInstance()
{
	static std::shared_ptr<IKey> instance( std::make_shared<SavedKey>() ) ;
	return instance ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SavedKey::SavedKey()
{
	// Get the u-boot env variable setting
	std::shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance()) ;
	if (!bootEnv->isVar(LICENSE_ENV))
		return ;

	if (!this->super::setFromEncodedKey(bootEnv->getVar(LICENSE_ENV)))
		return ;
}

//-------------------------------------------------------------------------------------------------------------
SavedKey::~SavedKey()
{
}

//-------------------------------------------------------------------------------------------------------------
bool SavedKey::setLicenseKey(const std::string& licenseKey)
{
	bool ok = this->super::setLicenseKey(licenseKey) ;
	return ok ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SavedKey::encodedKey()
{
	return this->super::encodedKey() ;
}

//-------------------------------------------------------------------------------------------------------------
bool SavedKey::setFromEncodedKey(const std::string& encodedKey)
{
	if (!this->super::setFromEncodedKey(encodedKey))
		return false ;

	// Save to u-boot env
	std::shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance()) ;
	bootEnv->setVar(LICENSE_ENV, encodedKey) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<uint32_t> SavedKey::licenseKey() const
{
	return this->super::licenseKey() ;
}

//-------------------------------------------------------------------------------------------------------------
bool SavedKey::isSet() const
{
	return this->super::isSet() ;
}
