/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      carrier_unittest.cpp
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

class CarrierTests : public ModelTests
{
};

//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(CarrierTests, Exists)
{
	// Test all commands are at least present
	std::string result ;

	result = runCmdNoCheck("/carrier/NumCarriers") ;
	result = runCmdNoCheck("/carrier/RxPaths") ;
	result = runCmdNoCheck("/carrier/TxPaths") ;
	result = runCmdNoCheck("/carrier/get") ;
	result = runCmdNoCheck("/carrier/set") ;
	result = runCmdNoCheck("/carrier/show") ;
	result = runCmdNoCheck("/carrier/showAll") ;
	result = runCmdNoCheck("/carrier/getRssi") ;


}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(CarrierTests, Basic)
{
	// @TODO
}
