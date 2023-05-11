/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SystemTask_unittest.cpp
 * \brief     Google Test of SystemTask
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the SystemTask class.
 *
 */

#include <gtest/gtest.h>

#include <string>
#include <iostream>

#include <memory>
#include "SystemTask.h"

using namespace Mplane;

using namespace std;

static std::string status ;

static void setProgress(unsigned progress)
{
	if (!status.empty())
		status.append(", ") ;
	status.append(std::to_string(progress)) ;

	std::cerr << "PROGRESS: " << progress << "%" << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(SystemTask, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<SystemTask> sys1(new SystemTask) ;
	sys1->start() ;

	status.clear() ;
	EXPECT_EQ(0, sys1->runCmd("ls")) ;

	status.clear() ;
	int rc = sys1->runCmd("sleep 5", &setProgress, 5) ;

	std::cout << "STATUS: " << status << std::endl ;
	std::cout << "RC: " << rc << std::endl ;

	// because of timing issues we may see a 98/99% pop in
//	EXPECT_EQ(std::string("0, 20, 40, 60, 80, 100"), status) ;
	EXPECT_TRUE(status.find("0, 20, 40, 60, 80, ") != std::string::npos) ;
	EXPECT_TRUE(status.find(" 100") != std::string::npos) ;
	EXPECT_EQ(0, rc) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(SystemTask, TimeOut)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<SystemTask> sys1(new SystemTask) ;
	sys1->start() ;

	bool timedOut ;

	// Time out
	status.clear() ;
	int rc = sys1->runCmd("sleep 5", &setProgress, 2, 2, timedOut) ;

	std::cout << "STATUS: " << status << std::endl ;
	std::cout << "RC: " << rc << std::endl ;

	EXPECT_EQ(std::string("0, 50, 99"), status) ;
	EXPECT_EQ(SystemTask::STEXIT_TIMEOUT, rc) ;
	EXPECT_TRUE(timedOut) ;


	// Run
	status.clear() ;
	rc = sys1->runCmd("sleep 5", &setProgress, 5, 6, timedOut) ;

	std::cout << "STATUS: " << status << std::endl ;
	std::cout << "RC: " << rc << std::endl ;

	// because of timing issues we may see a 98/99% pop in
//	EXPECT_EQ(std::string("0, 20, 40, 60, 80, 100"), status) ;
	EXPECT_TRUE(status.find("0, 20, 40, 60, 80, ") != std::string::npos) ;
	EXPECT_TRUE(status.find(" 100") != std::string::npos) ;

	EXPECT_EQ(0, rc) ;
	EXPECT_FALSE(timedOut) ;
}
