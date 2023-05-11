/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FileLock_unittest.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "Path.h"
#include "FileLock.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST(FileLock, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// unique name for this pid so no other test will clash
	std::string name("test") ;

	FileLock locker1(name) ;
	EXPECT_FALSE(locker1.isLocked()) ;

	std::cerr << "Lock" << std::endl ;
	EXPECT_TRUE(locker1.lock()) ;

	std::cerr << "Wait..." << std::endl ;
	sleep(10) ;

	EXPECT_TRUE(locker1.isLocked()) ;

	std::cerr << "Unlock" << std::endl ;
	EXPECT_TRUE(locker1.unlock()) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST(FileLock, Timeout)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// unique name for this pid so no other test will clash
	std::string name("test") ;

	FileLock locker1(name) ;
	EXPECT_FALSE(locker1.isLocked()) ;

	std::cerr << "Lock (5sec timeout)" << std::endl ;
	if (!locker1.lock(5000))
	{
		std::cerr << "Timed out" << std::endl ;
		return ;
	}

	std::cerr << "Wait..." << std::endl ;
	sleep(10) ;

	EXPECT_TRUE(locker1.isLocked()) ;

	std::cerr << "Unlock" << std::endl ;
	EXPECT_TRUE(locker1.unlock()) ;

}
