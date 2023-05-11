/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      system_unittest.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "gtest/gtest.h"

#include <regex.h>

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include "stringfunc.hpp"
#include "model_fixture.h"

using namespace Mplane ;

class SystemTests : public ModelTests
{
};

//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(SystemTests, Exists)
{
	// Test all commands are at least present
	std::string result ;

	result = runCmdNoCheck("/system/Application") ;
	result = runCmdNoCheck("/system/Board") ;
	result = runCmdNoCheck("/system/Build") ;
	result = runCmdNoCheck("/system/ClockIn") ;
	result = runCmdNoCheck("/system/CurrentFpgaBuild") ;
	result = runCmdNoCheck("/system/Customer") ;
	result = runCmdNoCheck("/system/Duplex") ;
	result = runCmdNoCheck("/system/FibreInterface") ;
	result = runCmdNoCheck("/system/FpgaBuild") ;
	result = runCmdNoCheck("/system/FpgaPart") ;
	result = runCmdNoCheck("/system/Version") ;
	result = runCmdNoCheck("/system/gitVersions") ;
	result = runCmdNoCheck("/system/powerDown") ;
	result = runCmdNoCheck("/system/reboot") ;
	result = runCmdNoCheck("/system/services") ;
	result = runCmdNoCheck("/system/setClockIn") ;


}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(SystemTests, Basic)
{
	// @TODO
}
