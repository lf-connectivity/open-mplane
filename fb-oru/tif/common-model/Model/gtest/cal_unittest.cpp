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

#include "Path.h"
#include "stringfunc.hpp"
#include "ILoggable.h"

#include "model_fixture.h"

#include <memory>

using namespace Mplane ;
using namespace std ;

//-------------------------------------------------------------------------------------------------------------------
class CalModelTests : public ModelTests
{
public:
};

//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(CalModelTests, UnitTests)
{
    ILoggable::setLogDebugLevel(ILoggable::LOG_DEBUG_NORMAL);

    std::string result;

    // no url set - only works the first time of running these model tests
    result = runCmdOk(".cal.url");
    if (result.find("Value=http") == std::string::npos)
    {
		result = runCmdError(".cal.install tx ftu_tx_cal.xml2");
//		EXPECT_TRUE(result.find("Remote URL not set") != std::string::npos) ;
		result = runCmdError(".cal.install rx ftu_rx_cal.xml2");
//		EXPECT_TRUE(result.find("Remote URL not set") != std::string::npos) ;
    }
    result = runCmdOk(".cal.url");
    result = runCmdOk(".cal.url http://swin-11/~guest/test_files/cal");
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(CalModelTests, Tx)
{
    ILoggable::setLogDebugLevel(ILoggable::LOG_DEBUG_NORMAL);

    std::string result;

    result = runCmdOk(".cal.url http://swin-11/~guest/test_files/cal");

    // Only do this next bit if the machine is configured with a writable /nandflash directory
    if (Path::isDir("/nandflash"))
    {
        // unable to download file
        result = runCmdError(".cal.install tx ftu_tx_cal.xml2");
//        EXPECT_TRUE(result.find("Failed to download ftu_tx_cal.xml2") != std::string::npos) ;

    	Path::remove("/nandflash/caldata/txcal.xml") ;

    	// should fail - no download installed
        result = runCmdError(".cal.install tx ftu_tx_cal.xml");

//        EXPECT_TRUE(Path::isFile("/nandflash/caldata/txcal.xml")) ;
    }

}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(CalModelTests, Rx)
{
    ILoggable::setLogDebugLevel(ILoggable::LOG_DEBUG_NORMAL);

    std::string result;

    result = runCmdOk(".cal.url http://swin-11/~guest/test_files/cal");

    // Only do this next bit if the machine is configured with a writable /nandflash directory
    if (Path::isDir("/nandflash"))
    {
        // unable to download file
        result = runCmdError(".cal.install rx ftu_rx_cal.xml2");
//        EXPECT_TRUE(result.find("Failed to download ftu_rx_cal.xml2") != std::string::npos) ;

    	Path::remove("/nandflash/caldata/rxcal.xml") ;

    	// should fail - no download installed
        result = runCmdError(".cal.install rx ftu_rx_cal.xml");

//        EXPECT_TRUE(Path::isFile("/nandflash/caldata/rxcal.xml")) ;
    }

}


//===================================================================================================================
