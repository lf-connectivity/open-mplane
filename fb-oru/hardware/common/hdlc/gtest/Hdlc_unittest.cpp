/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Hdlc_unittest.cpp
 * \brief     Hdlc unit tests
 *
 *
 * \details   Hdlc unit tests.
 *
 */

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <iostream>
#include <memory>

#include "IBus.h"
#include "Hdlc.h"
#include "TestHdlc.h"
#include "TestBus.h"

using namespace Mplane;


class TestClass : public ::testing::Test
{
public:
	virtual ~TestClass(){};

    virtual void SetUp()
    {
        const ::testing::TestInfo* const test_info =
                ::testing::UnitTest::GetInstance()->current_test_info();

        std::cout << std::endl << "*** " << test_info->test_case_name()
                << " Tests ***" << std::endl;
        std::cout << test_info->name() << " - SETUP" << std::endl;

        // Do the setup here
        Mplane::ILoggable::setGroupLogDebugLevel(Mplane::ILoggable::LOG_DEBUG_NORMAL, "YANG") ;

        mBus = std::make_shared<TestSerialBus>("TestSerialBus", "Test Serial Bus");
        mHdlc = new TestHdlc(mBus);

        std::cout << test_info->name() << " - SETUP complete" << std::endl;
    }

    virtual void TearDown()
	{
	  const ::testing::TestInfo* const test_info =
			  ::testing::UnitTest::GetInstance()->current_test_info();

	  std::cout << test_info->name() << " - TEARDOWN" << std::endl;

	  // Do the tear down here
	  delete mHdlc;
	  std::cout << test_info->name() << " - TEARDOWN complete" << std::endl;
	}

    std::shared_ptr<TestSerialBus> mBus;
    TestHdlc * mHdlc;
protected:

private:

};

TEST_F(TestClass, TxRxSuccessful)
{
	std::vector<uint8_t> reqData;
	std::vector<uint8_t> sentData;
	std::vector<uint8_t> respData;
	std::vector<uint8_t> recdData;

	reqData.push_back(0x01);
	reqData.push_back(0xDC);
	reqData.push_back(0x12);
	reqData.push_back(0x0);
	reqData.push_back(0x0);

	respData.push_back(0x7E);
	respData.push_back(0x01);
	respData.push_back(0xFC);
	respData.push_back(0x12);
	respData.push_back(0x01);
	respData.push_back(0x00);
	respData.push_back(0x00);
	respData.push_back(0x39);
	respData.push_back(0xBB);
	respData.push_back(0x7E);

	// Tx and Rx successful from TestSerialBus
	mBus->wrStatus(true);
	mBus->rdStatus(true);

	// Set response that you expect to be returned
	mBus->setResponse(respData);

	// Send the frame
	mHdlc->sendFrame(reqData, TestHdlc::responseCallback, 10);

	mHdlc->event();
	// Wait for task to be executed
	Task::msSleep(100);

	mBus->readWrData(sentData);
	mHdlc->getResp(recdData);

	// No error expected
	EXPECT_EQ(mHdlc->getFlag(), 0);
	// Number of bytes received
	EXPECT_EQ(mHdlc->getNumOctets(), (unsigned)10);
	// Verify that the data is received with the bytes unstuffed and the flags and FCS removed
	EXPECT_EQ(recdData.size(), (unsigned)6);
	EXPECT_EQ(recdData[0], 0x01);
	EXPECT_EQ(recdData[1], 0xFC);
	EXPECT_EQ(recdData[2], 0x12);
	EXPECT_EQ(recdData[3], 0x01);
	EXPECT_EQ(recdData[4], 0x00);
	EXPECT_EQ(recdData[5], 0x00);

	// Verfy that the reqData gets the flags and FCS
	EXPECT_EQ(sentData.size(), (unsigned)9);
	EXPECT_EQ(sentData[0], 0x7E);
	EXPECT_EQ(sentData[1], 0x01);
	EXPECT_EQ(sentData[2], 0xDC);
	EXPECT_EQ(sentData[3], 0x12);
	EXPECT_EQ(sentData[4], 0x00);
	EXPECT_EQ(sentData[5], 0x00);
	EXPECT_EQ(sentData[6], 0x52);
	EXPECT_EQ(sentData[7], 0x9B);
	EXPECT_EQ(sentData[8], 0x7E);
}

TEST_F(TestClass, ByteStuffing)
{
	std::vector<uint8_t> reqData;
	std::vector<uint8_t> sentData;
	std::vector<uint8_t> respData;
	std::vector<uint8_t> recdData;

	reqData.push_back(0x01);
	reqData.push_back(0x30);
	reqData.push_back(0x12);
	reqData.push_back(0x01);
	reqData.push_back(0x7E);
	reqData.push_back(0x00);

	respData.push_back(0x7E);
	respData.push_back(0x01);
	respData.push_back(0x30);
	respData.push_back(0x12);
	respData.push_back(0x01);
	respData.push_back(0x00);
	respData.push_back(0x00);
	respData.push_back(0x7D);
	respData.push_back(0x5E);
	respData.push_back(0x87);
	respData.push_back(0x7E);

	// Tx and Rx successful from TestSerialBus
	mBus->wrStatus(true);
	mBus->rdStatus(true);
	mBus->setResponse(respData);
	mHdlc->sendFrame(reqData, TestHdlc::responseCallback, 10);

	mHdlc->event();
	// Wait for task to be executed
	Task::msSleep(100);

	mBus->readWrData(sentData);
	mHdlc->getResp(recdData);

	// Verify that there is no error
	EXPECT_EQ(mHdlc->getFlag(), 0);
	// Verify number of byted received
	EXPECT_EQ(mHdlc->getNumOctets(), (unsigned)11);
	// Verify that the data is received with the bytes unstuffed and the flags and FCS removed
	EXPECT_EQ(recdData.size(), (unsigned)6);
	EXPECT_EQ(recdData[0], 0x01);
	EXPECT_EQ(recdData[1], 0x30);
	EXPECT_EQ(recdData[2], 0x12);
	EXPECT_EQ(recdData[3], 0x01);
	EXPECT_EQ(recdData[4], 0x00);
	EXPECT_EQ(recdData[5], 0x00);

	// Verify that the reqData is appended with the flags, FCS and stuffed bytes
	EXPECT_EQ(sentData.size(), (unsigned)11);
	EXPECT_EQ(sentData[0], 0x7E);
	EXPECT_EQ(sentData[1], 0x01);
	EXPECT_EQ(sentData[2], 0x30);
	EXPECT_EQ(sentData[3], 0x12);
	EXPECT_EQ(sentData[4], 0x01);
	EXPECT_EQ(sentData[5], 0x7D);
	EXPECT_EQ(sentData[6], 0x5E);
	EXPECT_EQ(sentData[7], 0x00);
	EXPECT_EQ(sentData[10], 0x7E);
}

TEST_F(TestClass, TxFail)
{
	std::vector<uint8_t> reqData;
	std::vector<uint8_t> sentData;
	std::vector<uint8_t> respData;
	std::vector<uint8_t> recdData;

	reqData.push_back(0x01);
	reqData.push_back(0xDC);
	reqData.push_back(0x12);
	reqData.push_back(0x0);
	reqData.push_back(0x0);

	respData.push_back(0x7E);
	respData.push_back(0x01);
	respData.push_back(0xFC);
	respData.push_back(0x12);
	respData.push_back(0x01);
	respData.push_back(0x00);
	respData.push_back(0x00);
	respData.push_back(0x39);
	respData.push_back(0xBB);
	respData.push_back(0x7E);

	// Tx set to fail
	mBus->wrStatus(false);
	mBus->rdStatus(true);
	mBus->setResponse(respData);
	mHdlc->sendFrame(reqData, TestHdlc::responseCallback, 10);

	mHdlc->event();
	// Wait for task to be executed
	Task::msSleep(100);

	mBus->readWrData(sentData);
	mHdlc->getResp(recdData);

	// Verify that the Tx error flag is set
	EXPECT_TRUE(mHdlc->isTxErr());
	EXPECT_EQ(mHdlc->getNumOctets(), (unsigned)0);
	EXPECT_EQ(recdData.size(), (unsigned)0);
}

TEST_F(TestClass, RxFail)
{
	std::vector<uint8_t> reqData;
	std::vector<uint8_t> sentData;
	std::vector<uint8_t> respData;
	std::vector<uint8_t> recdData;

	reqData.push_back(0x01);
	reqData.push_back(0xDC);
	reqData.push_back(0x12);
	reqData.push_back(0x0);
	reqData.push_back(0x0);

	respData.push_back(0x7E);
	respData.push_back(0x01);
	respData.push_back(0xFC);
	respData.push_back(0x12);
	respData.push_back(0x01);
	respData.push_back(0x00);
	respData.push_back(0x00);
	respData.push_back(0x39);
	respData.push_back(0xBB);
	respData.push_back(0x7E);

	// Rx set to fail
	mBus->wrStatus(true);
	mBus->rdStatus(false);
	mBus->setResponse(respData);
	mHdlc->sendFrame(reqData, TestHdlc::responseCallback, 10);

	mHdlc->event();
	// Wait for task to be executed
	Task::msSleep(100);

	mBus->readWrData(sentData);
	mHdlc->getResp(recdData);

	// Verify that the Rx error flag is set
	EXPECT_TRUE(mHdlc->isRxErr());
	EXPECT_EQ(mHdlc->getNumOctets(), (unsigned)0);
	EXPECT_EQ(recdData.size(), (unsigned)0);

	EXPECT_EQ(sentData.size(), (unsigned)9);
	EXPECT_EQ(sentData[0], 0x7E);
	EXPECT_EQ(sentData[1], 0x01);
	EXPECT_EQ(sentData[2], 0xDC);
	EXPECT_EQ(sentData[3], 0x12);
	EXPECT_EQ(sentData[4], 0x00);
	EXPECT_EQ(sentData[5], 0x00);
	EXPECT_EQ(sentData[6], 0x52);
	EXPECT_EQ(sentData[7], 0x9B);
	EXPECT_EQ(sentData[8], 0x7E);
}

TEST_F(TestClass, NoStartFlag)
{
	std::vector<uint8_t> reqData;
	std::vector<uint8_t> sentData;
	std::vector<uint8_t> respData;
	std::vector<uint8_t> recdData;

	reqData.push_back(0x01);
	reqData.push_back(0xDC);
	reqData.push_back(0x12);
	reqData.push_back(0x0);
	reqData.push_back(0x0);

	respData.push_back(0x01);
	respData.push_back(0xFC);
	respData.push_back(0x12);
	respData.push_back(0x01);
	respData.push_back(0x00);
	respData.push_back(0x00);
	respData.push_back(0x39);
	respData.push_back(0xBB);
	respData.push_back(0x7E);

	// Rx and Tx successful
	mBus->wrStatus(true);
	mBus->rdStatus(true);
	mBus->setResponse(respData);
	mHdlc->sendFrame(reqData, TestHdlc::responseCallback, 10);

	mHdlc->event();
	// Wait for task to be executed
	Task::msSleep(100);

	mBus->readWrData(sentData);
	mHdlc->getResp(recdData);

	// Verify that the start flag error is set
	EXPECT_TRUE(mHdlc->isStartFlagErr());
	EXPECT_TRUE(mHdlc->isFCSErr());
	EXPECT_EQ(mHdlc->getNumOctets(), (unsigned)9);
	EXPECT_EQ(recdData.size(), (unsigned)6);
	EXPECT_EQ(recdData[0], 0x01);
	EXPECT_EQ(recdData[1], 0xFC);
	EXPECT_EQ(recdData[2], 0x12);
	EXPECT_EQ(recdData[3], 0x01);
	EXPECT_EQ(recdData[4], 0x00);
	EXPECT_EQ(recdData[5], 0x00);

	EXPECT_EQ(sentData.size(), (unsigned)9);
	EXPECT_EQ(sentData[0], 0x7E);
	EXPECT_EQ(sentData[1], 0x01);
	EXPECT_EQ(sentData[2], 0xDC);
	EXPECT_EQ(sentData[3], 0x12);
	EXPECT_EQ(sentData[4], 0x00);
	EXPECT_EQ(sentData[5], 0x00);
	EXPECT_EQ(sentData[6], 0x52);
	EXPECT_EQ(sentData[7], 0x9B);
	EXPECT_EQ(sentData[8], 0x7E);
}

TEST_F(TestClass, NoStopFlag)
{
	std::vector<uint8_t> reqData;
	std::vector<uint8_t> sentData;
	std::vector<uint8_t> respData;
	std::vector<uint8_t> recdData;

	reqData.push_back(0x01);
	reqData.push_back(0xDC);
	reqData.push_back(0x12);
	reqData.push_back(0x0);
	reqData.push_back(0x0);

	respData.push_back(0x7E);
	respData.push_back(0x01);
	respData.push_back(0xFC);
	respData.push_back(0x12);
	respData.push_back(0x01);
	respData.push_back(0x00);
	respData.push_back(0x00);
	respData.push_back(0x39);
	respData.push_back(0xBB);

	// Rx and Tx successful
	mBus->wrStatus(true);
	mBus->rdStatus(true);
	mBus->setResponse(respData);
	mHdlc->sendFrame(reqData, TestHdlc::responseCallback, 10);

	mHdlc->event();
	// Wait for task to be executed
	Task::msSleep(100);

	mBus->readWrData(sentData);
	mHdlc->getResp(recdData);

	// Verify that the stop flag error is set
	EXPECT_TRUE(mHdlc->isStopFlagErr());
	EXPECT_TRUE(mHdlc->isFCSErr());
	EXPECT_EQ(mHdlc->getNumOctets(), (unsigned)9);
	EXPECT_EQ(recdData.size(), (unsigned)6);
	EXPECT_EQ(recdData[0], 0x01);
	EXPECT_EQ(recdData[1], 0xFC);
	EXPECT_EQ(recdData[2], 0x12);
	EXPECT_EQ(recdData[3], 0x01);
	EXPECT_EQ(recdData[4], 0x00);
	EXPECT_EQ(recdData[5], 0x00);

	EXPECT_EQ(sentData.size(), (unsigned)9);
	EXPECT_EQ(sentData[0], 0x7E);
	EXPECT_EQ(sentData[1], 0x01);
	EXPECT_EQ(sentData[2], 0xDC);
	EXPECT_EQ(sentData[3], 0x12);
	EXPECT_EQ(sentData[4], 0x00);
	EXPECT_EQ(sentData[5], 0x00);
	EXPECT_EQ(sentData[6], 0x52);
	EXPECT_EQ(sentData[7], 0x9B);
	EXPECT_EQ(sentData[8], 0x7E);
}

TEST_F(TestClass, FCSError)
{
	std::vector<uint8_t> reqData;
	std::vector<uint8_t> sentData;
	std::vector<uint8_t> respData;
	std::vector<uint8_t> recdData;

	reqData.push_back(0x01);
	reqData.push_back(0xDC);
	reqData.push_back(0x12);
	reqData.push_back(0x0);
	reqData.push_back(0x0);

	respData.push_back(0x7E);
	respData.push_back(0x01);
	respData.push_back(0xFC);
	respData.push_back(0x12);
	respData.push_back(0x01);
	respData.push_back(0x00);
	respData.push_back(0x00);
	respData.push_back(0x38);
	respData.push_back(0xBC);
	respData.push_back(0x7E);

	// Rx and Tx successful
	mBus->wrStatus(true);
	mBus->rdStatus(true);
	mBus->setResponse(respData);
	mHdlc->sendFrame(reqData, TestHdlc::responseCallback, 10);

	mHdlc->event();
	// Wait for task to be executed
	Task::msSleep(100);

	mBus->readWrData(sentData);
	mHdlc->getResp(recdData);

	// Verify that the FCS error is set
	EXPECT_TRUE(mHdlc->isFCSErr());
	EXPECT_EQ(mHdlc->getNumOctets(), (unsigned)10);
	EXPECT_EQ(recdData.size(), (unsigned)6);
	EXPECT_EQ(recdData[0], 0x01);
	EXPECT_EQ(recdData[1], 0xFC);
	EXPECT_EQ(recdData[2], 0x12);
	EXPECT_EQ(recdData[3], 0x01);
	EXPECT_EQ(recdData[4], 0x00);
	EXPECT_EQ(recdData[5], 0x00);

	EXPECT_EQ(sentData.size(), (unsigned)9);
	EXPECT_EQ(sentData[0], 0x7E);
	EXPECT_EQ(sentData[1], 0x01);
	EXPECT_EQ(sentData[2], 0xDC);
	EXPECT_EQ(sentData[3], 0x12);
	EXPECT_EQ(sentData[4], 0x00);
	EXPECT_EQ(sentData[5], 0x00);
	EXPECT_EQ(sentData[6], 0x52);
	EXPECT_EQ(sentData[7], 0x9B);
	EXPECT_EQ(sentData[8], 0x7E);
}

TEST_F(TestClass, TimeoutError)
{
	std::vector<uint8_t> reqData;
	std::vector<uint8_t> sentData;
	std::vector<uint8_t> recdData;

	reqData.push_back(0x01);
	reqData.push_back(0xDC);
	reqData.push_back(0x12);
	reqData.push_back(0x0);
	reqData.push_back(0x0);

	// Rx and Tx successful
	mBus->wrStatus(true);
	mBus->rdStatus(true);
	mHdlc->sendFrame(reqData, TestHdlc::responseCallback, 10);

	mHdlc->event();
	// Wait for task to be executed
	Task::msSleep(100);

	mBus->readWrData(sentData);
	mHdlc->getResp(recdData);

	// Verify that the timeout error is set
	EXPECT_TRUE(mHdlc->isTimeoutErr());
	EXPECT_EQ(mHdlc->getNumOctets(), (unsigned)0);
	EXPECT_EQ(recdData.size(), (unsigned)0);

	EXPECT_EQ(sentData.size(), (unsigned)9);
	EXPECT_EQ(sentData[0], 0x7E);
	EXPECT_EQ(sentData[1], 0x01);
	EXPECT_EQ(sentData[2], 0xDC);
	EXPECT_EQ(sentData[3], 0x12);
	EXPECT_EQ(sentData[4], 0x00);
	EXPECT_EQ(sentData[5], 0x00);
	EXPECT_EQ(sentData[6], 0x52);
	EXPECT_EQ(sentData[7], 0x9B);
	EXPECT_EQ(sentData[8], 0x7E);
}
