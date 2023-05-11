/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      cpri_unittest.cpp
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

class CpriTests : public ModelTests
{
};

//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
/**
 * ATG requirements traceability. Do not removed.
 *
 * \verify{@req_8403{142}}
 */

TEST_F(CpriTests, Exists)
{
	// Test all commands are at least present
	std::string result ;

	result = runCmdNoCheck("/cpri/NumPorts") ;
	result = runCmdNoCheck("/cpri/get") ;
	result = runCmdNoCheck("/cpri/set") ;
	result = runCmdNoCheck("/cpri/showAll") ;
	result = runCmdNoCheck("/cpri/showCtl") ;
	result = runCmdNoCheck("/cpri/showPort") ;
	result = runCmdNoCheck("/cpri/getTemp") ;


}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(CpriTests, Basic)
{
	// @TODO
}
