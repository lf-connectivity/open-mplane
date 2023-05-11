/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FromUblazeEmu_unittest.cpp
 * \brief     Google Test of FromUblazeEmu
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the FromUblazeEmu class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "Path.h"
#include "comms_fixture.h"
#include "FromUblazeEmu.h"

using namespace Mplane;

using namespace std;

const unsigned CHAN1_LEN = 0x160 ;

//===========================================================================================================
// CLASSES

//-------------------------------------------------------------------------------------------------------------
class FromUblazeEmuTest : public CommsTestFixture
{
public:
	bool resync(void)
	{
	    std::shared_ptr<OffTargetFPGA> fpga(OffTargetFPGA::getInstance()) ;
	    time_t start ;

	    // wait to see -2 (may have already happened and skipped on to -1)
	    std::cerr << "TEST: Wait for reset req" << std::endl ;
	    time(&start) ;
	    while ( (fpga->readVal(0xA80, 0xffff) != 0xFFFE) && (fpga->readVal(0xA80, 0xffff) != 0xFFFF) )
	    {
	    	// timeout
	        time_t now ;
	        time(&now) ;
	        if (difftime(now, start) > 2.0)
	        {
	        	EXPECT_TRUE(false) ;
	        	return false ;
	        }
	    }

	    fpga->writeVal(0xA82, 0xFFFF, 0xffff) ;

	    // wait to see -1
	    std::cerr << "TEST: Wait for reset ack" << std::endl ;
	    time(&start) ;
	    while ( fpga->readVal(0xA80, 0xffff) != 0xFFFF)
	    {
	    	// timeout
	        time_t now ;
	        time(&now) ;
	        if (difftime(now, start) > 2.0)
	        {
	        	EXPECT_TRUE(false) ;
	        	return false ;
	        }
	    }

	    fpga->writeVal(0xA82, 0, 0xffff) ;

	    // wait to see ack cleared
	    std::cerr << "TEST: Wait for release" << std::endl ;
	    time(&start) ;
	    while ( fpga->readVal(0xA80, 0xffff) == 0xFFFF)
	    {
	    	// timeout
	        time_t now ;
	        time(&now) ;
	        if (difftime(now, start) > 2.0)
	        {
	        	EXPECT_TRUE(false) ;
	        	return false ;
	        }
	    }

	    std::cerr << "TEST: resync complete" << std::endl ;
	    return true ;
	}


	bool ppcReceive(void)
	{
	    std::shared_ptr<OffTargetFPGA> fpga(OffTargetFPGA::getInstance()) ;
	    time_t start ;

	    // Get the read pointer
	    UINT16 readPtr(fpga->readVal(0xA82, 0xffff)) ;

	    if (fpga->readVal(0xA80, 0xffff) < 0)
	    	if (!resync())
	    		return false ;

	    // wait to see a difference
	    std::cerr << "TEST: Wait for data..." << std::endl ;
	    time(&start) ;
	    while ( fpga->readVal(0xA80, 0xffff) == readPtr)
	    {
	    	// timeout
	        time_t now ;
	        time(&now) ;
	        if (difftime(now, start) > 2.0)
	        {
	    	    std::cerr << "TEST: Wait for data...TIMED OUT" << std::endl ;
	        	EXPECT_TRUE(false) ;
	        	return false ;
	        }
	    }

	    // Get the write pointer
	    UINT16 writePtr(fpga->readVal(0xA80, 0xffff)) ;

	    // Read the data
	    // TODO.....
	    int numBytes = writePtr - readPtr ;
	    if (numBytes < 0)
	    	numBytes += CHAN1_LEN ;
	    std::cerr << "Read " << numBytes << " bytes" << std::endl ;


	    // Done with the data
	    fpga->writeVal(0xA82, writePtr, 0xffff) ;


	    return true ;

	}


};


//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST_F(FromUblazeEmuTest, Basic)
{
    std::shared_ptr<FromUblazeEmu> dpd(new FromUblazeEmu(0xA80, CHAN1_LEN)) ;
    dpd->start() ;

	Loggable::setLogDebugLevel(Loggable::LOG_DEBUG_VERBOSE) ;

//    std::shared_ptr<OffTargetFPGA> fpga(OffTargetFPGA::getInstance()) ;

    // Need to resync first
    EXPECT_TRUE(resync()) ;


}

//-------------------------------------------------------------------------------------------------------------
TEST_F(FromUblazeEmuTest, Send)
{
    std::shared_ptr<FromUblazeEmu> dpd(new FromUblazeEmu(0xA80, 0x160)) ;
    dpd->start() ;

	Loggable::setLogDebugLevel(Loggable::LOG_DEBUG_VERBOSE) ;

//    std::shared_ptr<OffTargetFPGA> fpga(OffTargetFPGA::getInstance()) ;

    // Need to resync first
    EXPECT_TRUE(resync()) ;

    // Create a message
    std::vector<UINT8> data ;
    for (unsigned byte=1; byte <= 121; ++byte)
    {
    	data.push_back( (UINT8)byte ) ;
    }
    EXPECT_TRUE(dpd->sendMsg(CommsEmuMsg::createCommand(data))) ;

    // now need to handshake it across the comms
    EXPECT_TRUE(ppcReceive()) ;


}

//-------------------------------------------------------------------------------------------------------------
TEST_F(FromUblazeEmuTest, Resync)
{
    std::shared_ptr<FromUblazeEmu> dpd(new FromUblazeEmu(0xA80, 0x160)) ;
    dpd->start() ;

	Loggable::setLogDebugLevel(Loggable::LOG_DEBUG_VERBOSE) ;

    std::shared_ptr<OffTargetFPGA> fpga(OffTargetFPGA::getInstance()) ;

    // Need to resync first
    EXPECT_TRUE(resync()) ;


    // Cause a resync to start
	fpga->writeVal(0xA82, 0xFFFF) ;

    // Create a message
    std::vector<UINT8> data ;
    for (unsigned byte=1; byte <= 121; ++byte)
    {
    	data.push_back( (UINT8)byte ) ;
    }
    EXPECT_TRUE(dpd->sendMsg(CommsEmuMsg::createCommand(data))) ;

    EXPECT_TRUE(resync()) ;

    // now need to handshake it across the comms
    EXPECT_TRUE(ppcReceive()) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST_F(FromUblazeEmuTest, BadPtr)
{
    std::shared_ptr<FromUblazeEmu> dpd(new FromUblazeEmu(0xA80, 0x160)) ;
    dpd->start() ;

	Loggable::setLogDebugLevel(Loggable::LOG_DEBUG_VERBOSE) ;

    std::shared_ptr<OffTargetFPGA> fpga(OffTargetFPGA::getInstance()) ;

    // Need to resync first
    EXPECT_TRUE(resync()) ;


    // Cause a resync to start
	fpga->writeVal(0xA82, 0xEEEE) ;

    // Create a message
    std::vector<UINT8> data ;
    for (unsigned byte=1; byte <= 121; ++byte)
    {
    	data.push_back( (UINT8)byte ) ;
    }
    EXPECT_TRUE(dpd->sendMsg(CommsEmuMsg::createCommand(data))) ;

    EXPECT_TRUE(resync()) ;

    // now need to handshake it across the comms
    EXPECT_TRUE(ppcReceive()) ;

}
