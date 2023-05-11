/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AlarmPackage_unittest.cpp
 * \brief     Google Test of AlarmPackage
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the AlarmPackage class.
 *
 */

#include <gtest/gtest.h>

#include "AlarmTest.h"

using namespace Mplane;

using namespace std;


//-------------------------------------------------------------------------------------------------------------
TEST(AlarmPackage, Test)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;
	EXPECT_EQ(0, faultsList->getSize()) ;

	std::shared_ptr<IAlarmsList> alarmsList(IAlarmsList::getInstance()) ;
	EXPECT_EQ(0, alarmsList->getSize()) ;


	// Create the fault builder
	std::shared_ptr<IFaultBuilder> faultPackage(std::make_shared<FaultBuilder1>()) ;
	EXPECT_EQ(2, faultsList->getSize()) ;

	// get hold of the faults/owner for testing
	std::shared_ptr<IFault> faultA(faultsList->getFault("FaultA")) ;
	std::shared_ptr<IFault> faultB(faultsList->getFault("FaultB")) ;
	std::shared_ptr<IFaultOwner> faultOwner1(faultsList->getFaultOwner("FaultOwner1")) ;
	std::shared_ptr<FaultOwner1> fOwner1(std::dynamic_pointer_cast<FaultOwner1>(faultOwner1)) ;

	// create alarm package
	std::shared_ptr<IAlarmPackage> alarmPackage(std::make_shared<AlarmPackage1>()) ;
	EXPECT_EQ(1, alarmsList->getSize()) ;

	std::shared_ptr<IAlarm> alarm1(alarmsList->getAlarm("Alarm1")) ;



	// set 1
	fOwner1->mState = true ;
	faultOwner1->updateFaults() ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;
	EXPECT_FALSE(alarm1->isAlarmActive()) ;

	// set 2
	faultOwner1->updateFaults() ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;
	EXPECT_FALSE(alarm1->isAlarmActive()) ;

	// set 3
	faultOwner1->updateFaults() ;
	EXPECT_TRUE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;
	EXPECT_TRUE(alarm1->isAlarmActive()) ;

	// set 4
	faultOwner1->updateFaults() ;
	EXPECT_TRUE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;
	EXPECT_TRUE(alarm1->isAlarmActive()) ;

	// set 5
	faultOwner1->updateFaults() ;
	EXPECT_TRUE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;
	EXPECT_TRUE(alarm1->isAlarmActive()) ;

	alarmsList->show() ;
//	faultsList->show() ;

	// clear 1
	fOwner1->mState = false ;
	faultOwner1->updateFaults() ;
	EXPECT_TRUE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;
	EXPECT_TRUE(alarm1->isAlarmActive()) ;

	// clear 2
	faultOwner1->updateFaults() ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;
	EXPECT_TRUE(alarm1->isAlarmActive()) ;

	// clear 3
	faultOwner1->updateFaults() ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;
	EXPECT_TRUE(alarm1->isAlarmActive()) ;

	// clear 4
	faultOwner1->updateFaults() ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;
	EXPECT_TRUE(alarm1->isAlarmActive()) ;

	// clear 5
	faultOwner1->updateFaults() ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;
	EXPECT_FALSE(alarm1->isAlarmActive()) ;


	// reset alarm
	alarm1->reset() ;
	EXPECT_FALSE(alarm1->isAlarmActive()) ;

	// Tidy up - NOTE: *MUST* destroy alarms first followed by faults
	std::cerr << "TIDY UP" << std::endl ;

	std::shared_ptr<AlarmsList> aList(std::dynamic_pointer_cast<AlarmsList>(alarmsList)) ;
	aList->removeAlarm(alarm1->getName()) ;
	alarm1 = std::shared_ptr<IAlarm>() ;

	std::shared_ptr<FaultsList> fList(std::dynamic_pointer_cast<FaultsList>(faultsList)) ;
	fList->removeFault(faultA->getName()) ;
	fList->removeFault(faultB->getName()) ;
	fList->removeFaultOwner(faultOwner1->getName()) ;

}
