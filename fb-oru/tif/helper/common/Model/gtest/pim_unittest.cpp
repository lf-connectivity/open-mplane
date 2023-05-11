/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      pim_unittest.cpp
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

class PimTests : public ModelTests
{
};

//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(PimTests, Exists)
{
	// Test all commands are at least present
	std::string result ;

	result = runCmdNoCheck("/pim/apiVersion") ;
	result = runCmdNoCheck("/pim/avgPdp") ;
	result = runCmdNoCheck("/pim/capture") ;
	result = runCmdNoCheck("/pim/disableStim") ;
	result = runCmdNoCheck("/pim/dispersiveSearch") ;
	result = runCmdNoCheck("/pim/dump") ;
	result = runCmdNoCheck("/pim/enableStim") ;
	result = runCmdNoCheck("/pim/frd") ;
	result = runCmdNoCheck("/pim/fwr") ;
	result = runCmdNoCheck("/pim/get") ;
	result = runCmdNoCheck("/pim/getCoeffs") ;
	result = runCmdNoCheck("/pim/initialSearch") ;
	result = runCmdNoCheck("/pim/logClose") ;
	result = runCmdNoCheck("/pim/logOpen") ;
	result = runCmdNoCheck("/pim/logShow") ;
	result = runCmdNoCheck("/pim/orthogonalise") ;
	result = runCmdNoCheck("/pim/pdp") ;
	result = runCmdNoCheck("/pim/portClose") ;
	result = runCmdNoCheck("/pim/portOpen") ;
	result = runCmdNoCheck("/pim/portShow") ;
	result = runCmdNoCheck("/pim/reset") ;
	result = runCmdNoCheck("/pim/restart") ;
	result = runCmdNoCheck("/pim/runTest") ;
	result = runCmdNoCheck("/pim/search") ;
	result = runCmdNoCheck("/pim/set") ;
	result = runCmdNoCheck("/pim/setCarriers") ;
	result = runCmdNoCheck("/pim/start") ;
	result = runCmdNoCheck("/pim/startTssi") ;
	result = runCmdNoCheck("/pim/stop") ;
	result = runCmdNoCheck("/pim/stopTssi") ;
	result = runCmdNoCheck("/pim/update") ;
	result = runCmdNoCheck("/pim/xcorr") ;


}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(PimTests, Basic)
{
	// @TODO
}
