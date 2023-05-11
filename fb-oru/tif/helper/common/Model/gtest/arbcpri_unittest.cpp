/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      arbcpri_unittest.cpp
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

class ArbCpriTests : public ModelTests
{
};

//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(ArbCpriTests, Exists)
{
	// Test all commands are at least present
	std::string result ;

	result = runCmdNoCheck("/arb/cpri/capture") ;
	result = runCmdNoCheck("/arb/cpri/playback") ;


}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(ArbCpriTests, Basic)
{
	// @TODO
}
