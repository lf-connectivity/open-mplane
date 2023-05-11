/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      etna_ftu_waveform_unittest.cpp
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

class ArbTests : public ModelTests
{
};

//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(ArbTests, Exists)
{
	// Test all commands are at least present
	std::string result ;

	result = runCmdNoCheck(".arb.set") ;
	result = runCmdNoCheck(".arb.show") ;

	result = runCmdNoCheck(".arb.capture.files") ;
	result = runCmdNoCheck(".arb.capture.start") ;

	result = runCmdNoCheck(".arb.cpri.playback") ;
	result = runCmdNoCheck(".arb.cpri.capture") ;

	result = runCmdNoCheck(".arb.playback.files") ;
	result = runCmdNoCheck(".arb.playback.start") ;
	result = runCmdNoCheck(".arb.playback.stop") ;
	result = runCmdNoCheck(".arb.playback.multicast") ;

	result = runCmdNoCheck(".arb.rf.playback") ;
	result = runCmdNoCheck(".arb.rf.capture") ;


}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(ArbTests, Basic)
{
	// Test parameters
	std::string result ;

	result = runCmdOk(".arb.show") ;
	result = runCmdNoCheck(".arb.playback.start") ;
	result = runCmdNoCheck(".arb.playback.stop") ;
	result = runCmdNoCheck(".arb.capture.start") ;

	result = runCmdOk(".arb.set LTE 10") ;
	result = runCmdOk(".arb.show") ;

	result = runCmdError(".arb.cpri.playback port=3 trigger=307890") ;
	result = runCmdError(".arb.cpri.capture port=3 trigger=307890") ;
	result = runCmdError(".arb.rf.playback port=3 trigger=307890") ;
	result = runCmdError(".arb.rf.capture port=3 trigger=307890") ;
	result = runCmdError(".arb.cpri.playback port=0 trigger=307890") ;
	result = runCmdError(".arb.cpri.capture port=0 trigger=307890") ;
	result = runCmdError(".arb.rf.playback port=0 trigger=307890") ;
	result = runCmdError(".arb.rf.capture port=0 trigger=307890") ;

}
