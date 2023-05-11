/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TaskEvent_unittest.cpp
 * \brief     Google Test of TaskEvent
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the TaskEvent class.
 *
 */

#include <gtest/gtest.h>

#include <string>
#include <iostream>

#include <memory>
#include "TaskEvent.h"

using namespace Mplane;

using namespace std;

//=============================================================================================================
class TestTaskEvent : public TaskEvent {
public:
	TestTaskEvent() : TaskEvent(), mEventCount(0) {}
	~TestTaskEvent() {}

	bool runEvent() {
		++mEventCount ;
		return true ;
	}

	void trigger() {
		event() ;

		// pause for task to respond for test purposes
		msSleep(500) ;
	}

public:
	unsigned mEventCount ;
};

//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST(TaskEvent, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	{
	std::shared_ptr<TestTaskEvent> tevent(new TestTaskEvent) ;
	EXPECT_EQ(0u, tevent->mEventCount) ;

	tevent->trigger() ;
	EXPECT_EQ(1u, tevent->mEventCount) ;

	tevent->trigger() ;
	EXPECT_EQ(2u, tevent->mEventCount) ;

	tevent->trigger() ;
	EXPECT_EQ(3u, tevent->mEventCount) ;
	}

	// task will have shutdown here
}
