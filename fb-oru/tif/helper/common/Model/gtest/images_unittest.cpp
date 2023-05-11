/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      images_unittest.cpp
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

class ImagesTests : public ModelTests
{
};

//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(ImagesTests, Exists)
{
	// Test all commands are at least present
	std::string result ;

	result = runCmdNoCheck("/image/bank") ;
	result = runCmdNoCheck("/image/clean") ;
	result = runCmdNoCheck("/image/install") ;
	result = runCmdNoCheck("/image/installFile") ;
	result = runCmdNoCheck("/image/show") ;
	result = runCmdNoCheck("/image/showDetail") ;
	result = runCmdNoCheck("/image/uboot") ;
	result = runCmdNoCheck("/image/url") ;


}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(ImagesTests, Basic)
{
	// @TODO
}
