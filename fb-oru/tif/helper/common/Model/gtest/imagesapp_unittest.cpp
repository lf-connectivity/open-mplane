/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      imagesapp_unittest.cpp
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

class ImagesAppTests : public ModelTests
{
};

//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(ImagesAppTests, Exists)
{
	// Test all commands are at least present
	std::string result ;

	result = runCmdNoCheck("/image/app/clean") ;
	result = runCmdNoCheck("/image/app/install") ;
	result = runCmdNoCheck("/image/app/installFile") ;
	result = runCmdNoCheck("/image/app/show") ;


}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(ImagesAppTests, Basic)
{
	// @TODO
}
