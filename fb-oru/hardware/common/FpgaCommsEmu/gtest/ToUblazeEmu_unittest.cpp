/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ToUblazeEmu_unittest.cpp
 * \brief     Google Test of ToUblazeEmu
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the ToUblazeEmu class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "Path.h"
#include "comms_fixture.h"
#include "ToUblazeEmu.h"

using namespace Mplane;

using namespace std;

//===========================================================================================================
// CLASSES

//-------------------------------------------------------------------------------------------------------------
class ToUblazeEmuTest : public CommsTestFixture
{
};


//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST_F(ToUblazeEmuTest, Basic)
{
    std::shared_ptr<ToUblazeEmu> dpd(new ToUblazeEmu(0xA00, 0x80, true)) ;
    dpd->start() ;

	Loggable::setLogDebugLevel(Loggable::LOG_DEBUG_VERBOSE) ;


    std::shared_ptr<OffTargetFPGA> fpga(OffTargetFPGA::getInstance()) ;

    // a few simple writes / readbacks
    fpga->writeVal(0xA02, 0x04, 0xffff) ;
    EXPECT_EQ( (UINT16)0x0004, fpga->readVal(0xA02, 0xffff)) ;
    fpga->writeVal(0xA04, 0xFACE, 0xffff) ;
    EXPECT_EQ( (UINT16)0xFACE, fpga->readVal(0xA04, 0xffff)) ;

    // write data
    fpga->writeVal(0xA04, 0x4300, 0xffff) ;
    fpga->writeVal(0xA06, 0x007A, 0xffff) ;
    fpga->writeVal(0xA08, 0x0102, 0xffff) ;
    fpga->writeVal(0xA0a, 0x0304, 0xffff) ;
    fpga->writeVal(0xA0c, 0x0506, 0xffff) ;
    fpga->writeVal(0xA0e, 0x0708, 0xffff) ;

    // Cause trigger - SEND=1
    std::cerr << "TEST: SEND=1" << std::endl ;
    fpga->writeVal(0xA00, 0x01, 0xffff) ;


    std::cerr << "TEST: Wait for SEND=0" << std::endl ;
    time_t start ;
    time(&start) ;
    while ( fpga->readVal(0xA00, 0xffff) != 0)
    {
    	// timeout
        time_t now ;
        time(&now) ;
        if (difftime(now, start) > 1.0)
        {
        	EXPECT_TRUE(false) ;
        	break ;
        }
    }




    std::cerr << "TEST: RECEVER READY=1" << std::endl ;
    EXPECT_EQ(1, fpga->readVal(0xA02, 0xffff)) ;

    // check the message
    std::vector<CommsEmuMsg> msgs(dpd->getMsgs()) ;
    ASSERT_EQ(1u, msgs.size()) ;
    EXPECT_EQ(67u, msgs[0].getType()) ;

    std::vector<UINT8> data(msgs[0].getData()) ;
    EXPECT_EQ(122u, data.size()) ;
    EXPECT_EQ(0x01, data[0]) ;
    EXPECT_EQ(0x02, data[1]) ;
    EXPECT_EQ(0x03, data[2]) ;
    EXPECT_EQ(0x04, data[3]) ;
    EXPECT_EQ(0x05, data[4]) ;
    EXPECT_EQ(0x06, data[5]) ;
    EXPECT_EQ(0x07, data[6]) ;
    EXPECT_EQ(0x08, data[7]) ;

}
