/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      systemtcp_unittest.cpp
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

class SystemTcpTests : public ModelTests
{
};

//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(SystemTcpTests, Exists)
{
	// Test all commands are at least present
	std::string result ;

	result = runCmdNoCheck("/system/tcp/close") ;
	result = runCmdNoCheck("/system/tcp/open") ;
	result = runCmdNoCheck("/system/tcp/show") ;


}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(SystemTcpTests, Basic)
{
	// @TODO
}
