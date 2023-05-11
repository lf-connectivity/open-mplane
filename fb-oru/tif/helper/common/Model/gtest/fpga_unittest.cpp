/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      fpga_unittest.cpp
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

class FpgaTests : public ModelTests
{
};

//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FpgaTests, Exists)
{
	// Test all commands are at least present
	std::string result ;

	result = runCmdNoCheck("/fpga/getTemperature") ;
	result = runCmdNoCheck("/fpga/modify") ;
	result = runCmdNoCheck("/fpga/monitor") ;
	result = runCmdNoCheck("/fpga/monitorShow") ;
	result = runCmdNoCheck("/fpga/read") ;
	result = runCmdNoCheck("/fpga/write") ;


}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(FpgaTests, Basic)
{
	// @TODO
}
