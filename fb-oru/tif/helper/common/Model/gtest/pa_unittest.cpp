/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      lna_unittest.cpp
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

class PaTests : public ModelTests
{
};

//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PaTests, Exists)
{
	// Test all commands are at least present
	std::string result ;

	result = runCmdNoCheck("/pa/getTemperature 1") ;
	result = runCmdNoCheck("/pa/getTemperature 2") ;

	result = runCmdNoCheck("/pa/getID") ;

	result = runCmdNoCheck("/pa/isConnected 1") ;
	result = runCmdNoCheck("/pa/isConnected 2") ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(PaTests, Basic)
{
	// @TODO
}
