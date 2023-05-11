/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsEmulator_unittest.cpp
 * \brief     Google Test of FpgaCommsEmulator
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the FpgaCommsEmulator class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "Path.h"
#include "comms_fixture.h"
#include "FpgaCommsEmulator.h"

#include "Loggable.h"
#include "OffTargetFPGA.h"
#include "CommsEmuMsg.h"

using namespace Mplane;

using namespace std;

const unsigned CHAN1_LEN = 0x160 ;

//===========================================================================================================
// CLASSES

//-------------------------------------------------------------------------------------------------------------
class FpgaCommsEmulatorTest : public CommsTestFixture
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

#if 0
//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaCommsEmulatorTest, Basic)
{
    std::shared_ptr<FpgaCommsEmulator> dpd(FpgaCommsEmulator::getInstance()) ;

	Loggable::setLogDebugLevel(Loggable::LOG_DEBUG_VERBOSE) ;


    std::shared_ptr<OffTargetFPGA> fpga(OffTargetFPGA::getInstance()) ;

    // a few simple writes / readbacks
    fpga->writeVal(0xA02, 0x04, 0xffff) ;
    EXPECT_EQ( (UINT16)0x0004, fpga->readVal(0xA02, 0xffff)) ;
    fpga->writeVal(0xA04, 0xFACE, 0xffff) ;
    EXPECT_EQ( (UINT16)0xFACE, fpga->readVal(0xA04, 0xffff)) ;

    // Cause trigger - RTS=1, SD=0
    std::cerr << "TEST: RTS=1, SD=0" << std::endl ;
    fpga->writeVal(0xA00, 0x01, 0xffff) ;

    std::cerr << "TEST: Wait for RTR=1" << std::endl ;
    time_t start ;
    time(&start) ;
    while ( fpga->readVal(0xA02, 0x4) == 0)
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

    // write data
    fpga->writeVal(0xA04, 0x437A, 0xffff) ;
    fpga->writeVal(0xA06, 0x0102, 0xffff) ;
    fpga->writeVal(0xA08, 0x0304, 0xffff) ;
    fpga->writeVal(0xA0A, 0x0506, 0xffff) ;
    fpga->writeVal(0xA0C, 0x0708, 0xffff) ;

    std::cerr << "TEST: RTS=0 SD=1" << std::endl ;
    fpga->writeVal(0xA00, 0x02, 0xffff) ;

    std::cerr << "TEST: Wait for RD=1" << std::endl ;
    time(&start) ;
    while ( fpga->readVal(0xA02, 0x8) == 0)
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

    // check the message
    std::vector<CommsEmuMsg> msgs(dpd->getMsgs()) ;
    EXPECT_EQ(1u, msgs.size()) ;
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


//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaCommsEmulatorTest, Send)
{
    std::shared_ptr<FpgaCommsEmulator> dpd(FpgaCommsEmulator::getInstance()) ;

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
TEST_F(FpgaCommsEmulatorTest, Resync)
{
    std::shared_ptr<FpgaCommsEmulator> dpd(FpgaCommsEmulator::getInstance()) ;

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
TEST_F(FpgaCommsEmulatorTest, BadPtr)
{
    std::shared_ptr<FpgaCommsEmulator> dpd(FpgaCommsEmulator::getInstance()) ;

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

#endif
