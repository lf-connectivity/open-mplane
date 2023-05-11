/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestAppMonService.cpp
 * \brief     TestApp application monitoring service
 *
 *
 * \details   Responsible for monitoring the TestApp application
 *
 */
#include <iostream>
#include <string>

#include "TestAppMonService.h"

using namespace Mplane;

#define APP_PATH  "/home"
#define APP_CMD   "TestApp"

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TestAppMonService::TestAppMonService()
	: AppMonService(std::string(APP_PATH),
	                std::string(APP_CMD),
	                1000)	// update stuff every 1000 msec
{
}

//-------------------------------------------------------------------------------------------------------------
TestAppMonService::~TestAppMonService()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State TestAppMonService::cleanupApp(const std::string & funcStr)
{
	// Cleanup application
	eventInfo("TestAppMonService::%s() - cleanupApp", funcStr.c_str());
	return ReturnType::RT_OK;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//=============================================================================================================
// PRIVATE
//=============================================================================================================
