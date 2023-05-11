/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BootTimer_unittest.cpp
 * \brief     Google Test of BootTimer
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the BootTimer class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "BootTimer.h"

using namespace Mplane;

using namespace std;

//-------------------------------------------------------------------------------------------------------------
TEST(BootTimer, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IBootTimer> bootTimer( IBootTimer::getInstance() ) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(BootTimer, Access)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IBootTimer> bootTimer( IBootTimer::getInstance() ) ;

	std::cerr << "Start: " << bootTimer->getStartTime() << std::endl ;
	float start(bootTimer->getStartTime()) ;

	sleep(1) ;
	bootTimer->nameComplete("init") ;
	sleep(1) ;
	bootTimer->tifStarted() ;
	sleep(1) ;
	bootTimer->appStarted() ;

	std::cerr << "Init: " << bootTimer->getNameElapsed("init") << " : " << bootTimer->getNameTime("init") << std::endl ;
	std::cerr << "TIF : " << bootTimer->getTifElapsed() << " : " << bootTimer->getTifTime() << std::endl ;
	std::cerr << "APP : " << bootTimer->getAppElapsed() << " : " << bootTimer->getAppTime() << std::endl ;

	float nameElapsed(bootTimer->getNameElapsed("init")) ;
	float tifElapsed(bootTimer->getTifElapsed()) ;
	float appElapsed(bootTimer->getAppElapsed()) ;

	EXPECT_TRUE(nameElapsed >= 1.0) ;
	EXPECT_TRUE(tifElapsed >= 2.0) ;
	EXPECT_TRUE(appElapsed >= 3.0) ;

	float nameTime(bootTimer->getNameTime("init")) ;
	float tifTime(bootTimer->getTifTime()) ;
	float appTime(bootTimer->getAppTime()) ;

	EXPECT_TRUE(nameTime-start >= 1.0) ;
	EXPECT_TRUE(tifTime-start >= 2.0) ;
	EXPECT_TRUE(appTime-start >= 3.0) ;
}
