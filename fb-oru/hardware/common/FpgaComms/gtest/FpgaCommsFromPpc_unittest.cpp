/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsFromPpc_unittest.cpp
 * \brief     Google Test of FpgaCommsFromPpc
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the FpgaCommsFromPpc class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "Loggable.h"
#include "OffTargetFPGA.h"
#include "CommsEmuMsg.h"
#include "dpd_fixture.h"
#include "IFpgaCommsConstants.h"
#include "FpgaCommsEmulator.h"
#include "FpgaCommsFromPpcShim.h"
#include "FpgaCommsFromPpc.h"

using namespace Mplane;

using namespace std;

//===========================================================================================================
//

#define DPRAM_LEN               (0x200)
#define DPDSTATUS_LEN           (0x020)    // this is in bytes and must be a multiple of 4
#define CHANNEL_2_LEN           (0x080)
#define CHANNEL_1_LEN           (DPRAM_LEN-CHANNEL_2_LEN-DPDSTATUS_LEN)
#define CHANNEL_2_OFFSET_PPC    (0xA00)
#define CHANNEL_1_OFFSET_PPC    (CHANNEL_2_OFFSET_PPC+CHANNEL_2_LEN)
#define CHANNEL_2_OFFSET_FPGA   (0x0)
#define CHANNEL_1_OFFSET_FPGA   (CHANNEL_2_OFFSET_FPGA+CHANNEL_2_LEN)

// define the constants for FIFO lengths and PDU lengths
#define FIFO_LEN     (CHANNEL_1_LEN-HEADER_LEN)
#define PDU_LEN      (CHANNEL_2_LEN-HEADER_LEN-2)
#define FIFO_PDU_LEN ((FIFO_LEN-2)/2)

//-------------------------------------------------------------------------------------------------------------
class FpgaCommsFromPpcTest : public DpdTestFixture
{
};

// Wait time when waiting for a message - note this needs to be reasonably long to ensure Valgrind tests run
const float MSG_TIMEOUT = 4.0 ;

const std::string MSGQ_NAME("/cmdqtx") ;
const unsigned MSGQ_SIZE(256) ;
const unsigned MSGQ_NUM_MSGS(4) ;


//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaCommsFromPpcTest, Basic)
{
	Mplane::ILoggable::setLogDebugLevel(Mplane::ILoggable::LOG_DEBUG_VERBOSE) ;

	std::shared_ptr<OffTargetFPGA> fpga(OffTargetFPGA::getInstance());
	std::shared_ptr<FpgaCommsEmulator> dpdEmu(FpgaCommsEmulator::getInstance()) ;
	dpdEmu->bufferMsgs(true) ;

	std::shared_ptr<FpgaCommsFromPpcShim> shim(new FpgaCommsFromPpcShim(MSGQ_NAME, MSGQ_SIZE, MSGQ_NUM_MSGS,
			CHANNEL_2_OFFSET_PPC, PDU_LEN)) ;

	std::shared_ptr<FpgaCommsFromPpc> dpd(new FpgaCommsFromPpc(MSGQ_NAME)) ;
	dpd->start() ;

	UINT16 ch2Tx = fpga.readVal(0xA00) ;
	UINT16 ch2Rx = fpga.readVal(0xA02) ;
	UINT16 ch1Tx = fpga.readVal(0xA80) ;
	UINT16 ch1Rx = fpga.readVal(0xA82) ;
	std::cerr << std::hex << "PPC->uBlaze TX:0x" << ch2Tx << " RX:0x" << ch2Rx << " " <<
			"uBlaze->PPC TX:0x" << ch1Tx << " RX:0x" << ch1Rx <<
			std::dec << std::endl ;

	// Command
	std::string pduText("this is a test1") ;
    std::shared_ptr<FpgaPdu> pdu(new FpgaPdu(FpgaPdu::PDU_TYPE_CMD, pduText) ) ;

    // send it
    dpd->sendPdu(pdu) ;

    time_t start ;

    // wait for message to ripple through
    std::vector<CommsEmuMsg> emuMsgs(dpdEmu->getMsgs()) ;
    time(&start) ;
    while (emuMsgs.empty())
    {
    	emuMsgs = dpdEmu->getMsgs() ;

    	// timeout
        time_t now ;
        time(&now) ;
        if (difftime(now, start) > MSG_TIMEOUT)
        {
        	EXPECT_TRUE(false) ;
        	break ;
        }
    }

    // Expect a single message
    EXPECT_EQ(1u, emuMsgs.size()) ;

    if (emuMsgs.size() > 0)
    {
		FpgaPdu pduRx( emuMsgs[0].getPdu() ) ;
		EXPECT_EQ(FpgaPdu::PDU_TYPE_CMD, pduRx.getType()) ;

		pduText.append(1, '\0') ;
		EXPECT_EQ(pduText, pduRx.getData()) ;
    }
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaCommsFromPpcTest, Multiple)
{
	Mplane::ILoggable::setLogDebugLevel(Mplane::ILoggable::LOG_DEBUG_VERBOSE) ;

	std::shared_ptr<FpgaCommsEmulator> dpdEmu(FpgaCommsEmulator::getInstance()) ;
	dpdEmu->bufferMsgs(true) ;

	std::shared_ptr<FpgaCommsFromPpcShim> shim(new FpgaCommsFromPpcShim(MSGQ_NAME, MSGQ_SIZE, MSGQ_NUM_MSGS,
			CHANNEL_2_OFFSET_PPC, PDU_LEN)) ;

	std::shared_ptr<FpgaCommsFromPpc> dpd(new FpgaCommsFromPpc(MSGQ_NAME)) ;
	dpd->start() ;

	// Commands
	std::vector<std::string> pduText{
		{"this is a test1"},
		{"another test"},
		{"some more stuff"},
	} ;
	for (auto str : pduText)
	{
	    std::shared_ptr<FpgaPdu> pdu(new FpgaPdu(FpgaPdu::PDU_TYPE_CMD, str) ) ;
	    dpd->sendPdu(pdu) ;
	}

    time_t start ;

    unsigned pdusProcessed = 0 ;
    while (pdusProcessed < pduText.size())
    {
		// wait for message to ripple through
		std::vector<CommsEmuMsg> emuMsgs(dpdEmu->getMsgs()) ;
		time(&start) ;
		while (emuMsgs.empty())
		{
			emuMsgs = dpdEmu->getMsgs() ;

			// timeout
			time_t now ;
			time(&now) ;
			if (difftime(now, start) > MSG_TIMEOUT)
			{
				EXPECT_TRUE(false) ;
				break ;
			}
		}

		for (auto rxEmuMsg : emuMsgs)
		{
			FpgaPdu pduRx( rxEmuMsg.getPdu() ) ;
			EXPECT_EQ(FpgaPdu::PDU_TYPE_CMD, pduRx.getType()) ;

			std::string expected(pduText[pdusProcessed]) ;
			if (expected.size() % 2 != 0)
				expected.append(1, '\0') ;

			EXPECT_EQ(expected, pduRx.getData()) ;

			++pdusProcessed ;
		}
    }

}
