/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      tenmhzref_unittest.cpp
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

class TenMHzRefTests : public ModelTests
{
};

//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(TenMHzRefTests, Exists)
{
	// Test all commands are at least present
	std::string result ;

	result = runCmdNoCheck("/ref/getBnc1") ;
	result = runCmdNoCheck("/ref/getBnc2") ;
	result = runCmdNoCheck("/ref/getBnc3") ;
	result = runCmdNoCheck("/ref/getBnc4") ;
	result = runCmdNoCheck("/ref/getBnc5") ;
	result = runCmdNoCheck("/ref/getBncConfig") ;
	result = runCmdNoCheck("/ref/getManualMode") ;
	result = runCmdNoCheck("/ref/getMode") ;
	result = runCmdNoCheck("/ref/getPresent") ;
	result = runCmdNoCheck("/ref/getSyncIn") ;
	result = runCmdNoCheck("/ref/getSyncOut") ;
	result = runCmdNoCheck("/ref/setBnc1") ;
	result = runCmdNoCheck("/ref/setBnc2") ;
	result = runCmdNoCheck("/ref/setBnc3") ;
	result = runCmdNoCheck("/ref/setBnc4") ;
	result = runCmdNoCheck("/ref/setBnc5") ;
	result = runCmdNoCheck("/ref/setBncConfig") ;
	result = runCmdNoCheck("/ref/setManualMode") ;
	result = runCmdNoCheck("/ref/setMode") ;
	result = runCmdNoCheck("/ref/setSyncIn") ;
	result = runCmdNoCheck("/ref/setSyncOut") ;


}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(TenMHzRefTests, Basic)
{
	// @TODO
}
