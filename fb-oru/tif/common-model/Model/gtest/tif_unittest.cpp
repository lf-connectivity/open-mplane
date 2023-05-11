/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      tif_unittest.cpp
 * \brief     Unit tests for the TIF class error handling
 *
 *
 *
 */
#include "gtest/gtest.h"

#include <regex.h>

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include "Path.h"
#include "stringfunc.hpp"
#include "ILoggable.h"

#include "model_fixture.h"

#include <memory>

using namespace Mplane ;
using namespace std ;

//-------------------------------------------------------------------------------------------------------------------
class TifErrorTests : public ModelTests
{
public:
};

//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(TifErrorTests, UnitTests)
{
    ILoggable::setLogDebugLevel(ILoggable::LOG_DEBUG_NORMAL);

    std::string result;

//    result = runCmdError("/led/set 3 blue off") ;
//    EXPECT_TRUE( result.find("Status=ERROR Message=\"Function: set - Invalid value 'blue' for 'colour'\"") != std::string::npos );

    result = runCmdError("/dummy") ;
    EXPECT_TRUE( result.find("Status=ERROR Message=\"Syntax error: No handler for /dummy\"") != std::string::npos );

//    result = runCmdError("/led/set") ;
//    EXPECT_TRUE( result.find("Status=ERROR Message=\"Function: set - unset argument index, colour, state\"") != std::string::npos );

    result = runCmdError("/system/tcp/open 1 ") ;
    EXPECT_TRUE( result.find("Status=ERROR Message=\"Function: open - port less than minimum 1024\"") != std::string::npos );

//    result = runCmdOk("ls") ;
//    result = runCmdOk("help") ;
//    result = runCmdOk("cd /") ;
}


//===================================================================================================================
