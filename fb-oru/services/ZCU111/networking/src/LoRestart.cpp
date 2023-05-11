/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LoRestart.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <unistd.h>
#include "NetDevice.h"

#include "LoRestart.h"

using namespace Mplane;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<LoRestart> LoRestart::singleton()
{
	static std::shared_ptr<LoRestart> instance(std::make_shared<LoRestart>()) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
LoRestart::LoRestart() :
	mRestarted(false)
{
}

//-------------------------------------------------------------------------------------------------------------
LoRestart::~LoRestart()
{
}

//-------------------------------------------------------------------------------------------------------------
void LoRestart::restart()
{
	std::cerr << "LoRestart::restart() : restarted=" << mRestarted << std::endl ;

	if (mRestarted)
		return ;

	mRestarted = true ;

	// restart the LO interface so that Linux kernel updates the local routing table
	std::shared_ptr<NetDevice> nd(std::make_shared<NetDevice>("lo")) ;
	nd->setUp(false) ;
	sleep(1) ;
	nd->setUp(true) ;

	std::cerr << "LoRestart::restart() : now restarted" << std::endl ;

}
