/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      alarms_unittest.cpp
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

class AlarmsTests : public ModelTests
{
};

//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(AlarmsTests, Exists)
{
	// Test all commands are at least present
	std::string result ;

	result = runCmdNoCheck("/alarms/portClose") ;
	result = runCmdNoCheck("/alarms/portOpen") ;
	result = runCmdNoCheck("/alarms/showAll") ;
	result = runCmdNoCheck("/alarms/showAlarmId") ;
	result = runCmdNoCheck("/alarms/showFaultId") ;
	result = runCmdNoCheck("/alarms/status") ;
	result = runCmdNoCheck("/alarms/raiseFault 1") ;
	result = runCmdNoCheck("/alarms/clearFault 1") ;
	result = runCmdNoCheck("/alarms/getAlarm 1") ;

}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(AlarmsTests, Basic)
{
	// @TODO
}
