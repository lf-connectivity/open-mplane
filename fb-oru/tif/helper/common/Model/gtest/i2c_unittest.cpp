/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      i2c_unittest.cpp
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

class I2CTests : public ModelTests
{
};

//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(I2CTests, Exists)
{
	// Test all commands are at least present
	std::string result ;

	result = runCmdNoCheck("/i2c/lock") ;
	result = runCmdNoCheck("/i2c/read") ;
	result = runCmdNoCheck("/i2c/unlock") ;
	result = runCmdNoCheck("/i2c/write") ;


}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(I2CTests, Basic)
{
	// @TODO
}
