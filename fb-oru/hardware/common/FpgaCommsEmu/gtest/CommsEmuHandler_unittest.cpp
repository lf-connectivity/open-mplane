/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommsEmuHandler_unittest.cpp
 * \brief     Google Test of CommsEmuHandler
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the CommsEmuHandler class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "Path.h"
#include "comms_fixture.h"
#include "CommsEmuHandler.h"

using namespace Mplane;

using namespace std;

//===========================================================================================================
// CLASSES

//-------------------------------------------------------------------------------------------------------------
class CommsEmuHandlerTest : public CommsTestFixture
{
};

class TestCommsEmuHandler : public CommsEmuHandler
{
public:

	TestCommsEmuHandler(const std::string& name, UINT32 startAddress, unsigned numAddresses, UINT32 triggerAddress) :
		CommsEmuHandler(name, startAddress, numAddresses, triggerAddress)
	{}

	virtual ~TestCommsEmuHandler() {}

	virtual int run() override
	{
	    /*
	     * Now our thread is running we just enter an infinite loop so we never end.
	     * ALl image management is triggered by invocation of class methods, which are explicit action requests.
	     */
	    while (true)
	    {
	        // Wait for trigger
	        mTrigger.wait() ;
	        {
	        	std::cerr << "Triggered" << std::endl ;
	        	logDebugVerbose("DPD EMU trigger") ;
	        }
	    }

	    return 0;
	}

};

//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST_F(CommsEmuHandlerTest, Basic)
{
    std::shared_ptr<CommsEmuHandler> dpd(new TestCommsEmuHandler("CommsEmu", 0xA00, 0x80, 0xA00)) ;
    dpd->start() ;

	Loggable::setLogDebugLevel(Loggable::LOG_DEBUG_VERBOSE) ;


    std::shared_ptr<OffTargetFPGA> fpga(OffTargetFPGA::getInstance()) ;

    // a few simple writes / readbacks
    fpga->writeVal(0xA02, 0x04, 0xffff) ;
    EXPECT_EQ( (UINT16)0x0004, fpga->readVal(0xA02, 0xffff)) ;
    fpga->writeVal(0xA04, 0xFACE, 0xffff) ;
    EXPECT_EQ( (UINT16)0xFACE, fpga->readVal(0xA04, 0xffff)) ;

    // Cause trigger
    fpga->writeVal(0xA00, 0x01, 0xffff) ;

}
