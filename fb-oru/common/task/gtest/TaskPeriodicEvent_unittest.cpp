/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TaskPeriodicEvent_unittest.cpp
 * \brief     Google Test of TaskPeriodicEvent
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the TaskPeriodicEvent class.
 *
 */

#include <gtest/gtest.h>

#include <string>
#include <iostream>

#include <memory>
#include "TaskPeriodicEvent.h"

using namespace Mplane;

using namespace std;

//=============================================================================================================
class TestTaskPeriodicEvent : public TaskPeriodicEvent {
public:
	TestTaskPeriodicEvent() :
		TaskPeriodicEvent(1000),
		mEventCount(0),
		mEventWasPeriodic(false)
	{}
	~TestTaskPeriodicEvent() {}

	bool runEvent() {
		++mEventCount ;
		mEventWasPeriodic = mPeriodicEvent ;
		return true ;
	}

	void trigger() {
		event() ;

		// pause for task to respond for test purposes
		msSleep(300) ;
	}

public:
	unsigned mEventCount ;
	bool mEventWasPeriodic ;
};

//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST(TaskPeriodicEvent, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	{
	std::shared_ptr<TestTaskPeriodicEvent> tevent(new TestTaskPeriodicEvent) ;
	EXPECT_EQ(0u, tevent->mEventCount) ;
	EXPECT_FALSE(tevent->mEventWasPeriodic) ;

	tevent->trigger() ;
	EXPECT_EQ(1u, tevent->mEventCount) ;
	EXPECT_FALSE(tevent->mEventWasPeriodic) ;

	tevent->trigger() ;
	EXPECT_EQ(2u, tevent->mEventCount) ;
	EXPECT_FALSE(tevent->mEventWasPeriodic) ;

	tevent->trigger() ;
	EXPECT_EQ(3u, tevent->mEventCount) ;
	EXPECT_FALSE(tevent->mEventWasPeriodic) ;
	}

	// task will have shutdown here
}

//-------------------------------------------------------------------------------------------------------------
TEST(TaskPeriodicEvent, Period)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	{
	std::shared_ptr<TestTaskPeriodicEvent> tevent(new TestTaskPeriodicEvent) ;
	EXPECT_EQ(0u, tevent->mEventCount) ;
	EXPECT_FALSE(tevent->mEventWasPeriodic) ;

	// wait longer than period - will cause event
	Task::msSleep(1500) ;

	EXPECT_EQ(1u, tevent->mEventCount) ;
	EXPECT_TRUE(tevent->mEventWasPeriodic) ;

	tevent->trigger() ;
	EXPECT_EQ(2u, tevent->mEventCount) ;
	EXPECT_FALSE(tevent->mEventWasPeriodic) ;

	tevent->trigger() ;
	EXPECT_EQ(3u, tevent->mEventCount) ;
	EXPECT_FALSE(tevent->mEventWasPeriodic) ;
	}

	// task will have shutdown here
}
