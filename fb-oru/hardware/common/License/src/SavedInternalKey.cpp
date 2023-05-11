/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SavedInternalKey.cpp
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
#include "SavedInternalKey.h"

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
std::shared_ptr<IKey> SavedInternalKey::getInstance()
{
	static std::shared_ptr<IKey> instance( std::make_shared<SavedInternalKey>() ) ;
	return instance ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SavedInternalKey::SavedInternalKey() :
	SavedKey()
{
	// Get the u-boot env variable setting
	std::shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance()) ;
	if (bootEnv->isVar(LICENSE_ENV))
	{
		std::string key(bootEnv->getVar(LICENSE_ENV)) ;
		if ( !key.empty() && (key != "0") )
			return ;
	}

	// need to set the initial value of the key
	setInitialKey() ;
}

//-------------------------------------------------------------------------------------------------------------
SavedInternalKey::~SavedInternalKey()
{
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool SavedInternalKey::setInitialKey()
{
	std::vector<std::string> info ;
    std::shared_ptr<IBootEnv> bootEnv( IBootEnv::getInstance() );
    info.push_back( bootEnv->getVar("hostname") ); // serial
    info.push_back( bootEnv->getVar("eth1addr") ); // hostid

    // Add a random component
    unsigned rnd ;
    rnd = 	randomNumber() << 24 |
    		randomNumber() << 16 |
    		randomNumber() << 8 |
    		randomNumber() ;

    info.push_back(std::to_string(rnd)) ;

std::cerr << "SavedInternalKey::setInitialKey() : " << info[0] << " : " << info[1] << " : " << info[2] << std::endl ;

    // Set the key
	if (!this->Key::setLicenseKey(info))
		return false ;

std::cerr << "SavedInternalKey::setInitialKey() : encoded key=" << encodedKey() << std::endl ;

	// Save the key in non-volatile storage
	if (!this->SavedKey::setFromEncodedKey(encodedKey()))
		return false ;

std::cerr << "SavedInternalKey::setInitialKey() : Key STORED" << std::endl ;
	return true ;
}
