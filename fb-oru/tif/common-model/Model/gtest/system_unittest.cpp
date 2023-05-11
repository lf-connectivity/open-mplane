/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      system_unittest.cpp
 * \brief     Unit tests for the system TIF class
 *
 *
 * \details   Unit tests for the system TIF class
 *
 */
#include "gtest/gtest.h"

#include <regex.h>

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include "stringfunc.hpp"
#include "model_fixture.h"

#include "ILoggable.h"
#include <memory>
#include <wordexp.h>
#include "ITifImageCommandHandler.h"

using namespace Mplane ;
using namespace std ;

class SystemModelTests : public ModelTests
{
public:
};

//===================================================================================================================
/*
 * Unit tests
 */
// global data used during the off target tests.
// they are global so that they remain active between the tests.

//-------------------------------------------------------------------------------------------------------------------
TEST_F(SystemModelTests, SetupEnvironment)
{
	std::string result;

    ILoggable::setLogDebugLevel(ILoggable::LOG_DEBUG_NORMAL);
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(SystemModelTests, LogTests)
{
    std::string result;

    // console logging is now deprecated
    result = runCmdOk(".system.log.console");
    result = runCmdError(".system.log.console yes");
    result = runCmdOk("ls /system/log");
    EXPECT_TRUE(result.find("console=no") != std::string::npos) ;
    result = runCmdError(".system.log.console no");
    result = runCmdOk("ls /system/log");
    EXPECT_TRUE(result.find("console=no") != std::string::npos) ;

    result = runCmdOk(".system.log.forward");
    result = runCmdOk(".system.log.forward 1.2.3.4");
    result = runCmdOk("ls /system/log");
    EXPECT_TRUE(result.find("forward=\"1.2.3.4\"") != std::string::npos) ;
    result = runCmdOk(".system.log.forward NO");
    result = runCmdOk("ls /system/log");
    EXPECT_TRUE(result.find("forward=\"-\"") != std::string::npos) ;


    result = runCmdOk(".system.log.show");
    result = runCmdOk(".system.log.set verbose");

    // Expect these loggable instances:
	//    RtiMsgHandler                 TIF       Off
	//    TaskList                      SY        Off

    result = runCmdOk(".system.log.set normal RtiMsgHandler");
    result = runCmdOk(".system.log.set off name=rtimsghandler");
    result = runCmdOk(".system.log.set normal group=tif");
    result = runCmdError(".system.log.set normal xxx");
    result = runCmdError(".system.log.set normal group=xxx");


}


//===================================================================================================================
