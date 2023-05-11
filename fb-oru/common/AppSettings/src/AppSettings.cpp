/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AppSettings.cpp
 * \brief     Application build settings
 *
 *
 * \details   Singleton object containing the current build settings for this particular application/customer/board
 * combination
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <cstring>

// Get build config
#include "config.h"

#include "Tokeniser.h"
#include "AppSettings.h"

using namespace Mplane ;

//=============================================================================================================
// DEFAULTS
//=============================================================================================================
#ifndef GIT_REPOS
#define GIT_REPOS	""
#endif

//=============================================================================================================
// PROTOTYPES
//=============================================================================================================
static IAppSettings::AppType setApp() ;
static IAppSettings::BoardType setBoard() ;
static IAppSettings::CustomerType setCustomer() ;
static IAppSettings::DuplexType setDuplex() ;
static IAppSettings::FibreInterfaceType setFibreInterface() ;
static std::string setAppStr() ;
static std::string setBoardStr() ;
static std::string setCustomerStr() ;
static std::string setDuplexStr() ;
static std::string setFibreInterfaceStr() ;
static std::vector< std::pair<std::string, std::string> > setGitVersions() ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
AppSettings::AppSettings() :
	mDuplex( setDuplex() ),
	mApp( setApp() ),
	mFibreInterface( setFibreInterface() ),
	mBoard( setBoard() ),
	mCustomer( setCustomer() ),
	mBuildVersion( BUILD_VERSION ),
	mBuildNumber( BUILD_NUMBER ),

	mDuplexStr( setDuplexStr() ),
	mAppStr( setAppStr() ),
	mFibreInterfaceStr( setFibreInterfaceStr() ),
	mBoardStr( setBoardStr() ),
	mCustomerStr( setCustomerStr() ),
	mFpgaPart( BUILD_FPGA_PART ),
	mFpgaBuild( BUILD_FPGA_BUILD ),

	mGitVersions( setGitVersions() )

{
}

//-------------------------------------------------------------------------------------------------------------
AppSettings::~AppSettings() {
}

//-------------------------------------------------------------------------------------------------------------
IAppSettings::AppType AppSettings::getApp() const
{
	return mApp;
}

//-------------------------------------------------------------------------------------------------------------
IAppSettings::BoardType AppSettings::getBoard() const
{
	return mBoard;
}

//-------------------------------------------------------------------------------------------------------------
IAppSettings::CustomerType AppSettings::getCustomer() const
{
	return mCustomer;
}

//-------------------------------------------------------------------------------------------------------------
IAppSettings::DuplexType AppSettings::getDuplex() const
{
	return mDuplex;
}

//-------------------------------------------------------------------------------------------------------------
IAppSettings::FibreInterfaceType AppSettings::getFibreInterface() const
{
	return mFibreInterface;
}

//-------------------------------------------------------------------------------------------------------------
std::string AppSettings::getBuildVersion() const
{
	return mBuildVersion ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned AppSettings::getBuildNumber() const
{
	return mBuildNumber ;
}


//-------------------------------------------------------------------------------------------------------------
std::string AppSettings::getAppString() const
{
	return mAppStr;
}

//-------------------------------------------------------------------------------------------------------------
std::string AppSettings::getBoardString() const
{
	return mBoardStr;
}

//-------------------------------------------------------------------------------------------------------------
std::string AppSettings::getCustomerString() const
{
	return mCustomerStr;
}

//-------------------------------------------------------------------------------------------------------------
std::string AppSettings::getDuplexString() const
{
	return mDuplexStr;
}

//-------------------------------------------------------------------------------------------------------------
std::string AppSettings::getFibreInterfaceString() const
{
	return mFibreInterfaceStr;
}

//-------------------------------------------------------------------------------------------------------------
std::string AppSettings::getFpgaPart() const
{
	return mFpgaPart ;
}

//-------------------------------------------------------------------------------------------------------------
std::string AppSettings::getFpgaBuild() const
{
	return mFpgaBuild ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::pair<std::string, std::string> > AppSettings::getGitVersions() const
{
	return mGitVersions ;
}

//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
static IAppSettings::AppType setApp()
{
	return IAppSettings::BUILD_ENUM_APPLICATION ;
}

//-------------------------------------------------------------------------------------------------------------
static IAppSettings::BoardType setBoard()
{
	return IAppSettings::BUILD_ENUM_BOARD ;
}

//-------------------------------------------------------------------------------------------------------------
static IAppSettings::CustomerType setCustomer()
{
	return IAppSettings::BUILD_ENUM_CUSTOMER ;
}

//-------------------------------------------------------------------------------------------------------------
static IAppSettings::DuplexType setDuplex()
{
	return IAppSettings::BUILD_ENUM_DUPLEX ;
}

//-------------------------------------------------------------------------------------------------------------
static IAppSettings::FibreInterfaceType setFibreInterface()
{
	return IAppSettings::BUILD_ENUM_FIBRE_INTERFACE ;
}


//-------------------------------------------------------------------------------------------------------------
static std::string setAppStr()
{
	return BUILD_APPLICATION ;
}

//-------------------------------------------------------------------------------------------------------------
static std::string setBoardStr()
{
	return BUILD_BOARD ;
}

//-------------------------------------------------------------------------------------------------------------
static std::string setCustomerStr()
{
	return BUILD_CUSTOMER ;
}

//-------------------------------------------------------------------------------------------------------------
static std::string setDuplexStr()
{
	return BUILD_DUPLEX ;
}

//-------------------------------------------------------------------------------------------------------------
static std::string setFibreInterfaceStr()
{
	return BUILD_FIBRE_INTERFACE ;
}

//-------------------------------------------------------------------------------------------------------------
static std::vector< std::pair<std::string, std::string> > setGitVersions()
{
	std::vector< std::pair<std::string, std::string> > versions ;
	std::string versionString(GIT_REPOS) ;

	Tokeniser pairsTok(versionString, ";") ;
	for (std::string pairStr : pairsTok.getTokens())
	{
		Tokeniser tok(pairStr, ":") ;
		std::vector< std::string > ver( tok.getTokens() ) ;
		if (ver.size() != 2)
			continue ;

		versions.push_back(std::make_pair(ver[0], ver[1])) ;
	}

	return versions ;
}
