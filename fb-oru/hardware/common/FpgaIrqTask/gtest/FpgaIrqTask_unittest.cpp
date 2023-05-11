/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaIrqTask_unittest.cpp
 * \brief     Google Test of FpgaIrqTask
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the FpgaIrqTask class.
 *
 * ATG requirement traceability. Do not remove.
 *
 * \verify{@req_8403{028}}
 * \verify{@req_8403{029}}
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <gtest/gtest.h>

#include <vector>
#include <string>
#include <iostream>

#include <memory>
#include "Task.h"
#include "IFpgaIrqEmu.h"
#include "FpgaIrqTask.h"

using namespace Mplane;

//-------------------------------------------------------------------------------------------------------------
TEST(FpgaIrqTask, Event)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	volatile unsigned count=0 ;
	std::shared_ptr<FpgaIrqTask> irqTask( std::make_shared<FpgaIrqTask>(0,
		[&count](char* timestamp){
			++count;
			std::cerr << "Timestamp: " << timestamp << std::endl ;
		})
	) ;

	std::shared_ptr<IFpgaIrqEmu> irqEmu(IFpgaIrqEmu::getInstance()) ;

//	sleep(2) ;
	EXPECT_TRUE( irqEmu->raiseIrq(0) ) ;
//	sleep(3) ;

	std::cout << test_info->name() << " - DONE" <<  std::endl;
	while (count < 1) Task::msSleep(100) ;
	EXPECT_TRUE( irqEmu->raiseIrq(0) ) ;
	while (count < 2) Task::msSleep(100) ;
	EXPECT_TRUE( irqEmu->raiseIrq(0) ) ;
	while (count < 3) Task::msSleep(100) ;
	EXPECT_TRUE( irqEmu->raiseIrq(0) ) ;
	while (count < 4) Task::msSleep(100) ;

	// Create second
	{
		std::cerr << "*** Second task ***" << std::endl ;
		volatile unsigned count2=0 ;
		std::shared_ptr<FpgaIrqTask> irqTask2( std::make_shared<FpgaIrqTask>(0,
			[&count2](char* timestamp){
				++count2;
				std::cerr << "Timestamp: " << timestamp << std::endl ;
			})
		) ;

		EXPECT_TRUE( irqEmu->raiseIrq(0) ) ;
		while (count2 < 1) Task::msSleep(100) ;
		EXPECT_TRUE( irqEmu->raiseIrq(0) ) ;
		while (count2 < 2) Task::msSleep(100) ;

		// destroy this task
		std::cerr << "*** Second task *** - END" << std::endl ;
	}

	EXPECT_TRUE( irqEmu->raiseIrq(0) ) ;
	while (count < 5) Task::msSleep(100) ;
	EXPECT_TRUE( irqEmu->raiseIrq(0) ) ;
	while (count < 6) Task::msSleep(100) ;
}
