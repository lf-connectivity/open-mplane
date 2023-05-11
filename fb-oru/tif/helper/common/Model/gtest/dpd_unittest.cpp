/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      dpd_unittest.cpp
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

class DpdTests : public ModelTests
{
};

//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(DpdTests, Exists)
{
	// Test all commands are at least present
	std::string result ;

	result = runCmdNoCheck("/dpd/apiVersion") ;
	result = runCmdNoCheck("/dpd/capture") ;
	result = runCmdNoCheck("/dpd/dumpFpga") ;
	result = runCmdNoCheck("/dpd/dumpLuts") ;
	result = runCmdNoCheck("/dpd/frd") ;
	result = runCmdNoCheck("/dpd/fwr") ;
	result = runCmdNoCheck("/dpd/get") ;
	result = runCmdNoCheck("/dpd/logClose") ;
	result = runCmdNoCheck("/dpd/logOpen") ;
	result = runCmdNoCheck("/dpd/portClose") ;
	result = runCmdNoCheck("/dpd/portOpen") ;
	result = runCmdNoCheck("/dpd/reset") ;
	result = runCmdNoCheck("/dpd/reboot") ;
	result = runCmdNoCheck("/dpd/runTest") ;
	result = runCmdNoCheck("/dpd/set") ;


}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(DpdTests, Basic)
{
	// @TODO
}
