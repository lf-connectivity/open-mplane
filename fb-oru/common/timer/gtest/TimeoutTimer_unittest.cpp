/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TimeoutTimer_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <algorithm>
#include <iostream>
#include <fstream>

#include <unistd.h>

#include "gtest/gtest.h"

#include "TimeoutTimer.h"
#include "NullTimeoutTimer.h"

using namespace Mplane ;

//===================================================================================================================
class TimeoutTimerTest : public ::testing::Test
{
public:

    /*! @brief Setup the test
     */
    virtual void SetUp()
    {
    	const ::testing::TestInfo* const test_info =
    	  ::testing::UnitTest::GetInstance()->current_test_info();

    	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    	std::cout << test_info->name() << " - START" <<  std::endl;

    }

    /*! @brief Tear down the test
     */
    virtual void TearDown()
    {

    }

};




//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(TimeoutTimerTest, create)
{
	TimeoutTimer timer ;
	EXPECT_FALSE(timer.isTimedOut()) ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(TimeoutTimerTest, timeout)
{
	bool called(false) ;
	bool nocalled(false) ;

	TimeoutTimer timer ;
	NullTimeoutTimer notimer ;
	timer.setTimedCallback([&called](){ called=true; }) ;
	notimer.setTimedCallback([&nocalled](){ nocalled=true; }) ;

	timer.startTimer(std::chrono::seconds(2)) ;
	notimer.startTimer(std::chrono::seconds(2)) ;
	EXPECT_FALSE(timer.isTimedOut()) ;
	EXPECT_FALSE(called) ;
	EXPECT_FALSE(notimer.isTimedOut()) ;
	EXPECT_FALSE(nocalled) ;

	sleep(1) ;
	EXPECT_FALSE(timer.isTimedOut()) ;
	EXPECT_FALSE(called) ;
	EXPECT_FALSE(notimer.isTimedOut()) ;
	EXPECT_FALSE(nocalled) ;

	sleep(2) ;
	EXPECT_TRUE(timer.isTimedOut()) ;
	EXPECT_TRUE(called) ;
	EXPECT_FALSE(notimer.isTimedOut()) ;
	EXPECT_FALSE(nocalled) ;
	called = false ;
	EXPECT_TRUE(timer.isTimedOut()) ;
	EXPECT_FALSE(called) ;
	EXPECT_FALSE(notimer.isTimedOut()) ;
	EXPECT_FALSE(nocalled) ;

}




//===================================================================================================================
