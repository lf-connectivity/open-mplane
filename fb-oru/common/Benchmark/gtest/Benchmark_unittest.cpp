/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariant_unittest.cpp
 * \brief     Google Test of DataVariant
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the DataVariant class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "Benchmark.h"

using namespace Mplane;

using namespace std;

//-------------------------------------------------------------------------------------------------------------
TEST(Benchmark, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<Benchmark> benchmark( Benchmark::getInstance() ) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(Benchmark, Access)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<Benchmark> benchmark( Benchmark::getInstance() ) ;
	benchmark->start("t1") ;
	benchmark->start("t2") ;

	std::string elapsed ;
	elapsed = benchmark->stop("t1") ;
	EXPECT_TRUE(elapsed.find("ERROR") == std::string::npos);
	elapsed = benchmark->stop("t2") ;
	EXPECT_TRUE(elapsed.find("ERROR") == std::string::npos);
	elapsed = benchmark->stop("t3") ;
	EXPECT_FALSE(elapsed.find("ERROR") == std::string::npos);

	std::cout << "Up Time: " << benchmark->upTime() << std::endl ;


}

//-------------------------------------------------------------------------------------------------------------
TEST(Benchmark, TimingString)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<Benchmark> benchmark( Benchmark::getInstance() ) ;
	benchmark->start("t1") ;

    struct timespec ts = {0};
    ts.tv_sec = 0;
    ts.tv_nsec = 1000000L; // 1 msec delay
    nanosleep(&ts, (struct timespec *)0);

	benchmark->start("t2") ;

    ts.tv_sec = 0;
    ts.tv_nsec = 1000000L; // 2 msec delay
    nanosleep(&ts, (struct timespec *)0);

    // t1 = 0.002290
    // t2 = 0.001169
	std::string elapsedT1 = benchmark->elapsed("t1") ;
//	EXPECT_TRUE(elapsedT1.find("0.002") != std::string::npos);
	std::string elapsedT2 = benchmark->stop("t2") ;
//	EXPECT_TRUE(elapsedT2.find("0.001") != std::string::npos);

	// t2 now deleted
	std::string elapsed = benchmark->elapsed("t2") ;
	EXPECT_TRUE(elapsed.find("ERROR") != std::string::npos);

	std::string elapsedT = benchmark->stop("t1") ;
//	EXPECT_TRUE(elapsedT.find("0.002") != std::string::npos);

	// t1 now deleted
	elapsed = benchmark->elapsed("t1") ;
	EXPECT_TRUE(elapsed.find("ERROR") != std::string::npos);

	std::cout << "t1 = " << elapsedT1 << std::endl ;
	std::cout << "t2 = " << elapsedT2 << std::endl ;
	std::cout << "total = " << elapsedT << std::endl ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(Benchmark, TimingFloat)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<Benchmark> benchmark( Benchmark::getInstance() ) ;
	benchmark->start("t1") ;

	sleep(1) ;

	benchmark->start("t2") ;


	sleep(1) ;

    // t1 = 2
    // t2 = 1

	float T1 = benchmark->elapsedTime("t1") ;
	float T2 = benchmark->elapsedTime("t2") ;

	std::cout << "t1 = " << T1 << std::endl ;
	std::cout << "t2 = " << T2 << std::endl ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(Benchmark, Timestamp)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<Benchmark> benchmark( Benchmark::getInstance() ) ;
	std::string timestamp = benchmark->timestamp() ;

	std::cout << "Timestamp = " << timestamp << std::endl ;
}
