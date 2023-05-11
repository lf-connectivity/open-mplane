/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      spi_unittest.cpp
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

class SPITests : public ModelTests
{
};

//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(SPITests, Exists)
{
	// Test all commands are at least present
	std::string result ;

	result = runCmdNoCheck("/spi/get") ;
	result = runCmdNoCheck("/spi/lock") ;
	result = runCmdNoCheck("/spi/read") ;
	result = runCmdNoCheck("/spi/set") ;
	result = runCmdNoCheck("/spi/setbus") ;
	result = runCmdNoCheck("/spi/unlock") ;
	result = runCmdNoCheck("/spi/write") ;


}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(SPITests, Basic)
{
	// @TODO
}
