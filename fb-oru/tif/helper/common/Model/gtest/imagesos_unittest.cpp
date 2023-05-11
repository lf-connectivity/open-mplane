/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      imagesos_unittest.cpp
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

class ImagesOsTests : public ModelTests
{
};

//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(ImagesOsTests, Exists)
{
	// Test all commands are at least present
	std::string result ;

	result = runCmdNoCheck("/image/os/clean") ;
	result = runCmdNoCheck("/image/os/install") ;
	result = runCmdNoCheck("/image/os/installFile") ;
	result = runCmdNoCheck("/image/os/show") ;


}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(ImagesOsTests, Basic)
{
	// @TODO
}
