/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MsgQ_unittest.cpp
 * \brief     Google Test of MsgQ
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the MsgQ class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>

#include <memory>
#include "MsgQ.h"

using namespace Mplane;

using namespace std;

//-------------------------------------------------------------------------------------------------------------
TEST(MsgQ, Create)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// clear out from any previous failure
	::mq_unlink("/msgTx") ;

	std::shared_ptr<MsgQ> msgq1(std::make_shared<MsgQ>("/msgTx")) ;
	EXPECT_EQ("/msgTx", msgq1->getName()) ;
	EXPECT_TRUE(msgq1->create(256, 1)) ;
	msgq1->close() ;

	EXPECT_TRUE(msgq1->create(256, 1)) ;
	EXPECT_FALSE(msgq1->create(256, 1)) ;
	msgq1->close() ;

	// should now be removed so unlink should fail
//	EXPECT_TRUE( ::mq_unlink("/msgTx") == -1 ) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(MsgQ, SendReceive)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<MsgQ> msgq1(std::make_shared<MsgQ>("/msgTx")) ;
	std::shared_ptr<MsgQ> msgqTx(std::make_shared<MsgQ>("/msgTx")) ;
	std::shared_ptr<MsgQ> msgqRx(std::make_shared<MsgQ>("/msgTx")) ;

	EXPECT_EQ("/msgTx", msgq1->getName()) ;
	EXPECT_EQ("/msgTx", msgqTx->getName()) ;
	EXPECT_EQ("/msgTx", msgqRx->getName()) ;

	// can't connect until created
	EXPECT_FALSE(msgqTx->connectWrite()) ;
	EXPECT_FALSE(msgqRx->connectRead()) ;

	EXPECT_TRUE(msgq1->create(256, 2)) ;
	EXPECT_TRUE(msgqTx->connectWrite()) ;
	EXPECT_TRUE(msgqRx->connectRead()) ;

	// Should all now know the maximum message size
	EXPECT_EQ(256u, msgq1->getMaxMsgSize()) ;
	EXPECT_EQ(256u, msgqTx->getMaxMsgSize()) ;
	EXPECT_EQ(256u, msgqRx->getMaxMsgSize()) ;

	std::string msgStr("Hello - this is a message") ;
	std::vector<unsigned char> msg(msgStr.begin(), msgStr.end()) ;
	std::string msgStr2("this is another message") ;
	std::vector<unsigned char> msg2(msgStr2.begin(), msgStr2.end()) ;
	EXPECT_TRUE(msgqTx->sendData(msg)) ;
	EXPECT_TRUE(msgqTx->sendData(msg2)) ;

	std::vector<unsigned char> rx ;
	EXPECT_TRUE(msgqRx->getData(rx)) ;
	std::string rxStr(rx.begin(), rx.end()) ;
	EXPECT_EQ(rxStr, msgStr) ;
	EXPECT_TRUE(msgqRx->getData(rx)) ;
	std::string rxStr2(rx.begin(), rx.end()) ;
	EXPECT_EQ(rxStr2, msgStr2) ;

	// kill off queue
	msgq1->close() ;

//	// Shouldn't be able to write
//	EXPECT_FALSE(msgqTx->sendData(msg)) ;
//	EXPECT_FALSE(msgqRx->getData(rx)) ;
//	std::string rxStr3(rx.begin(), rx.end()) ;
//	std::cerr << "RX: '" << rxStr3 << "'" << std::endl ;

}


//-------------------------------------------------------------------------------------------------------------
TEST(MsgQ, SlaveSendMasterReceive)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<MsgQ> msgq1(std::make_shared<MsgQ>("/msgTx")) ;
	std::shared_ptr<MsgQ> msgqTx(std::make_shared<MsgQ>("/msgTx")) ;

	// can't connect until created
	EXPECT_FALSE(msgqTx->connectWrite()) ;

	EXPECT_TRUE(msgq1->create(256, 2)) ;
	EXPECT_TRUE(msgqTx->connectWrite()) ;

	// Should all now know the maximum message size
	EXPECT_EQ(256u, msgq1->getMaxMsgSize()) ;
	EXPECT_EQ(256u, msgqTx->getMaxMsgSize()) ;

	std::string msgStr("Hello - this is a message") ;
	std::vector<unsigned char> msg(msgStr.begin(), msgStr.end()) ;
	std::string msgStr2("this is another message") ;
	std::vector<unsigned char> msg2(msgStr2.begin(), msgStr2.end()) ;
	EXPECT_TRUE(msgqTx->sendData(msg)) ;
	EXPECT_TRUE(msgqTx->sendData(msg2)) ;

	std::vector<unsigned char> rx ;
	EXPECT_TRUE(msgq1->getData(rx)) ;
	std::string rxStr(rx.begin(), rx.end()) ;
	EXPECT_EQ(rxStr, msgStr) ;
	EXPECT_TRUE(msgq1->getData(rx)) ;
	std::string rxStr2(rx.begin(), rx.end()) ;
	EXPECT_EQ(rxStr2, msgStr2) ;

	// kill off queue
	msgq1->close() ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(MsgQ, MasterSendSlaveReceive)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<MsgQ> msgq1(std::make_shared<MsgQ>("/msgTx")) ;
	std::shared_ptr<MsgQ> msgqRx(std::make_shared<MsgQ>("/msgTx")) ;

	// can't connect until created
	EXPECT_FALSE(msgqRx->connectRead()) ;

	EXPECT_TRUE(msgq1->create(256, 2)) ;
	EXPECT_TRUE(msgqRx->connectRead()) ;

	// Should all now know the maximum message size
	EXPECT_EQ(256u, msgq1->getMaxMsgSize()) ;
	EXPECT_EQ(256u, msgqRx->getMaxMsgSize()) ;

	std::string msgStr("Hello - this is a message") ;
	std::vector<unsigned char> msg(msgStr.begin(), msgStr.end()) ;
	std::string msgStr2("this is another message") ;
	std::vector<unsigned char> msg2(msgStr2.begin(), msgStr2.end()) ;
	EXPECT_TRUE(msgq1->sendData(msg)) ;
	EXPECT_TRUE(msgq1->sendData(msg2)) ;

	std::vector<unsigned char> rx ;
	EXPECT_TRUE(msgqRx->getData(rx)) ;
	std::string rxStr(rx.begin(), rx.end()) ;
	EXPECT_EQ(rxStr, msgStr) ;
	EXPECT_TRUE(msgqRx->getData(rx)) ;
	std::string rxStr2(rx.begin(), rx.end()) ;
	EXPECT_EQ(rxStr2, msgStr2) ;

	// kill off queue
	msgq1->close() ;

}
