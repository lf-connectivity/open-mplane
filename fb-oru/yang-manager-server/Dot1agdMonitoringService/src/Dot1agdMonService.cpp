/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Dot1agdMonService.cpp
 * \brief     Dot1agd monitoring service
 *
 *
 * \details   Responsible for monitoring the Dot1agd (IEEE 802.1ag Daemon) application
 *
 */
#include <iostream>
#include <string>

#include "Dot1agdMonService.h"

using namespace Mplane;

#define DOT1AGD_CMD  "dot1agd"

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Dot1agdMonService::Dot1agdMonService()
	: AppMonService(std::string(DOT1AGD_PATH),
	                std::string(DOT1AGD_CMD),
	                1000)	// update stuff every 1000 msec
{
}

//-------------------------------------------------------------------------------------------------------------
Dot1agdMonService::~Dot1agdMonService()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Dot1agdMonService::cleanupApp(const std::string & funcStr)
{
	// Cleanup application
	eventInfo("Dot1agdMonService::%s() - cleanupApp", funcStr.c_str());
	return ReturnType::RT_OK;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//=============================================================================================================
// PRIVATE
//=============================================================================================================
