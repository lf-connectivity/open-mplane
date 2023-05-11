/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsToPpc_unittest.cpp
 * \brief     Google Test of FpgaCommsToPpc
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the FpgaCommsToPpc class.
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
#include "FpgaCommsToPpcShim.h"
#include "FpgaCommsToPpc.h"
#include "MsgText.h"

using namespace Mplane;

using namespace std;

//===========================================================================================================
// CLASSES

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

const std::string MSGQ_NAME("/cmdqrx") ;
const unsigned MSGQ_SIZE(256) ;
const unsigned MSGQ_NUM_MSGS(4) ;

//-------------------------------------------------------------------------------------------------------------
class FpgaCommsToPpcTest : public DpdTestFixture
{
public:
};

//===========================================================================================================
// TESTS


//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaCommsToPpcTest, Basic)
{
	Mplane::ILoggable::setLogDebugLevel(Mplane::ILoggable::LOG_DEBUG_VERBOSE) ;

	std::shared_ptr<FpgaCommsEmulator> dpdEmu(FpgaCommsEmulator::getInstance()) ;

	std::shared_ptr<FpgaCommsToPpcShim> shim(new FpgaCommsToPpcShim(MSGQ_NAME, MSGQ_SIZE, MSGQ_NUM_MSGS,
			CHANNEL_1_OFFSET_PPC, FIFO_LEN)) ;

	std::shared_ptr<FpgaCommsToPpc> dpd(new FpgaCommsToPpc(MSGQ_NAME)) ;
	dpd->start() ;

	std::string failReason ;
	EXPECT_TRUE(dpd->registerMsgHandler(FpgaPdu::PDU_TYPE_CMD, this,
		[this](std::shared_ptr<IFpgaMsg> msg) {handleMsg(msg);},
		[this](const FpgaPdu& pdu)->std::shared_ptr<IFpgaMsg> {return createMsg(pdu);},
		failReason)) ;

	mRxMsgs.clear() ;

	// Reply
	std::string msgText("this is a test1") ;
    FpgaPdu msg(FpgaPdu::PDU_TYPE_CMD, msgText) ;

    // send it
    dpdEmu->sendMsg(CommsEmuMsg::createCommand(msg.getDataBytes())) ;

//    sleep(1) ;
	EXPECT_TRUE(doRx()) ;

	EXPECT_EQ(1u, mRxMsgs.size()) ;
	if (mRxMsgs.size() == 1)
	{
		std::shared_ptr<MsgText> rxMsg( dynamic_pointer_cast<MsgText>(mRxMsgs[0]) ) ;
		EXPECT_EQ(FpgaPdu::PDU_TYPE_CMD, rxMsg->getType()) ;

		std::cerr << "RX PDU:" << mRxMsgs[0]->getPdu()->getData() << std::endl ;
	}


	dpd->unRegisterMsgHandler(FpgaPdu::PDU_TYPE_REPLY, this) ;
}
