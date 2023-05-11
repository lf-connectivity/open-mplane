/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonPostInit.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IAppOptions.h"
#include "Ati.h"
#include "CommonPostInit.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<CommonPostInit> CommonPostInit::getInterface()
{
	static std::shared_ptr<CommonPostInit> instance( std::make_shared<CommonPostInit>() ) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonPostInit::CommonPostInit() :
	mAti()
{
	// number of connections
	unsigned numTifConnections{3} ;

	// get the port number to use for TIF
	std::shared_ptr<IAppOptions> appOptions(IAppOptions::getInstance()) ;
	unsigned tifPort{ static_cast<unsigned>(appOptions->getOption("port").toInt()) } ;

	// create the interface(s)
	mAti = Ati::createInstance(tifPort, numTifConnections) ;
}

//-------------------------------------------------------------------------------------------------------------
CommonPostInit::~CommonPostInit()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::CommonPostInit::operator ()()
{
	// start the radio test interface
	mAti->start() ;

	return ReturnType::RT_OK ;
}
