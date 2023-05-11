/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HeartbeatFault_unittest.cpp
 * \brief     Google Test of HeartbeatFault
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the HeartbeatFault class.
 *
 */

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <iostream>
#include <memory>

#include "IFault.h"
#include "IFaultOwner.h"
#include "IFaultsList.h"
#include "Fault.h"
#include "FaultsList.h"
#include "FaultOwner.h"

#include "OffTargetFPGA.h"

#include "IHeartbeat.h"
#include "HeartBeatFaultMajor.h"
#include "HeartBeatMajorFaultOwner.h"

using namespace Mplane;

//-------------------------------------------------------------------------------------------------------------
TEST(HeartbeatFault, Test)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

 	std::shared_ptr<IFault> fault(make_fault<HeartBeatFaultMajor>());
	std::shared_ptr<IFaultOwner> faultOwner (make_faultOwner<HeartBeatFaultOwner>());

	fault->reset();

	std::shared_ptr<IHeartbeat> heartbeat(IHeartbeat::getInstance()) ;
	heartbeat->setEnable(false) ;
	heartbeat->setTimeoutSecs(1) ;
	EXPECT_FALSE(heartbeat->isExpired()) ;
	EXPECT_FALSE(heartbeat->getEnable()) ;
	heartbeat->setEnable(true) ;

	// no fault
	faultOwner->updateFaults() ;
	EXPECT_FALSE(fault->isFaultPresent()) ;

	std::cout << "** No Faults ** " << std::endl ;

	// wait for timeout
	sleep(2) ;

	// fault
	EXPECT_TRUE(heartbeat->isExpired()) ;
	EXPECT_TRUE(heartbeat->getEnable()) ;
	EXPECT_TRUE(fault->isFaultPresent()) ;

	std::cout << "** Heartbeat Fault ** " << std::endl ;

	// clear fault
	heartbeat->resetTimer() ;
	EXPECT_FALSE(fault->isFaultPresent()) ;
	EXPECT_FALSE(heartbeat->isExpired()) ;

	// wait for timeout
	sleep(2) ;

	// fault
	EXPECT_TRUE(heartbeat->isExpired()) ;
	EXPECT_TRUE(heartbeat->getEnable()) ;
	EXPECT_TRUE(fault->isFaultPresent()) ;

	// clear fault
	heartbeat->setEnable(false) ;
	EXPECT_FALSE(fault->isFaultPresent()) ;
	EXPECT_FALSE(heartbeat->isExpired()) ;

	// wait for timeout
	sleep(2) ;

	// should be no fault
	EXPECT_FALSE(heartbeat->isExpired()) ;
	EXPECT_FALSE(heartbeat->getEnable()) ;
	EXPECT_FALSE(fault->isFaultPresent()) ;

	// Clean up
	std::cout << "** No Faults ** " << std::endl ;
}
