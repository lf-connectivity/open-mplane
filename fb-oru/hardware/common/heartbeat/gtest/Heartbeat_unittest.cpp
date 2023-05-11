/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Heartbeat_unittest.cpp
 * \brief     Google Test of Heartbeat
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the Heartbeat class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>

#include <memory>
#include "Heartbeat.h"

using namespace Mplane;

using namespace std;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
class HeartbeatInstance : public Heartbeat {
public:
	HeartbeatInstance() : Heartbeat(), mExpireCount(0) {}
	virtual ~HeartbeatInstance() {}

protected:
	void heartbeatEvent(bool expired) override
	{
		if (expired)
			++mExpireCount ;
	}
public:
	unsigned mExpireCount ;
};

std::shared_ptr<IHeartbeat> IHeartbeat::getInstance()
{
	static std::shared_ptr<IHeartbeat> instance(std::make_shared<HeartbeatInstance>()) ;
	return instance ;
}


//-------------------------------------------------------------------------------------------------------------
TEST(Heartbeat, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IHeartbeat> hb(IHeartbeat::getInstance()) ;

	EXPECT_FALSE(hb->isExpired()) ;
	EXPECT_FALSE(hb->getEnable()) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(Heartbeat, TimeOut)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IHeartbeat> hb(IHeartbeat::getInstance()) ;
	std::shared_ptr<HeartbeatInstance> testHeartbeat(std::dynamic_pointer_cast<HeartbeatInstance>(hb)) ;

	hb->setEnable(false) ;
	hb->setTimeoutSecs(1) ;
	EXPECT_FALSE(hb->isExpired()) ;
	EXPECT_FALSE(hb->getEnable()) ;
	testHeartbeat->mExpireCount = 0 ;

	hb->setEnable(true) ;
	sleep(2) ;
	EXPECT_TRUE(hb->isExpired()) ;
	EXPECT_TRUE(hb->getEnable()) ;

	hb->setEnable(false) ;
	EXPECT_EQ(1u, testHeartbeat->mExpireCount) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(Heartbeat, HoldOff)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IHeartbeat> hb(IHeartbeat::getInstance()) ;
	std::shared_ptr<HeartbeatInstance> testHeartbeat(std::dynamic_pointer_cast<HeartbeatInstance>(hb)) ;

	hb->setEnable(false) ;
	hb->setTimeoutSecs(4) ;
	EXPECT_FALSE(hb->isExpired()) ;
	EXPECT_FALSE(hb->getEnable()) ;
	testHeartbeat->mExpireCount = 0 ;

	hb->setEnable(true) ;

	for (unsigned count=1; count <= 4; ++count)
	{
		sleep(1) ;
		hb->resetTimer() ;
		EXPECT_FALSE(hb->isExpired()) ;
		EXPECT_TRUE(hb->getEnable()) ;
	}

	hb->setEnable(false) ;
	EXPECT_EQ(0u, testHeartbeat->mExpireCount) ;
}
