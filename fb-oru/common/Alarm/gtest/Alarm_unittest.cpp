/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Alarm_unittest.cpp
 * \brief     Google Test of Alarm
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the Alarm class.
 *
 */

#include <gtest/gtest.h>

#include "ILoggable.h"
#include "AlarmTest.h"

using namespace Mplane;

using namespace std;


//-------------------------------------------------------------------------------------------------------------
TEST(Alarm, Unlatched)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;
	EXPECT_EQ(0, faultsList->getSize()) ;

	std::shared_ptr<IAlarmsList> alarmsList(IAlarmsList::getInstance()) ;
	EXPECT_EQ(0, alarmsList->getSize()) ;

	std::shared_ptr<IFault> faultA(make_fault<FaultA>()) ;
	std::shared_ptr<IFault> faultB(make_fault<FaultB>()) ;
	std::shared_ptr<IFault> faultC(make_fault<FaultC>()) ;

	EXPECT_EQ(3, faultsList->getSize()) ;

	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;

	// Create owner
	std::shared_ptr<IFaultOwner> faultOwner1(make_faultOwner<FaultOwner1>()) ;
	std::shared_ptr<FaultOwner1> fOwner1(std::dynamic_pointer_cast<FaultOwner1>(faultOwner1)) ;

	// Create alarm
	std::shared_ptr<IAlarm> alarm1(make_alarm<Alarm1>()) ;
	EXPECT_EQ(1, alarmsList->getSize()) ;
	EXPECT_FALSE(alarm1->isAlarmActive()) ;

	// Register 2 faults with this alarm
	EXPECT_TRUE(alarm1->registerFaults(std::set<std::string>({"FaultA", "FaultB"}) )) ;

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
	alarmsList->showNamesAndIds() ;

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

	std::cerr << "Fault A: " << faultA->getName() << std::endl ;
	std::cerr << "Fault B: " << faultB->getName() << std::endl ;
	EXPECT_EQ(3, faultsList->getSize()) ;

	std::shared_ptr<IFault> fault ;
	fault = faultsList->getFault("FaultA") ;
	EXPECT_EQ("FaultA", fault->getName()) ;
	fault = faultsList->getFault("FaultB") ;
	EXPECT_EQ("FaultB", fault->getName()) ;
	fault = faultsList->getFault("FaultC") ;
	EXPECT_EQ("FaultC", fault->getName()) ;

	std::shared_ptr<IFaultOwner> faultOwner ;
	faultOwner = faultsList->getFaultOwner("FaultOwner1") ;
	EXPECT_EQ("FaultOwner1", faultOwner->getName()) ;

	// Tidy up
	std::cerr << "TIDY UP" << std::endl ;
	std::shared_ptr<FaultsList> fList(std::dynamic_pointer_cast<FaultsList>(faultsList)) ;
	fList->removeFault(faultA->getName()) ;
	fList->removeFault(faultB->getName()) ;
	fList->removeFault(faultC->getName()) ;
	fList->removeFaultOwner(faultOwner1->getName()) ;

	std::shared_ptr<AlarmsList> aList(std::dynamic_pointer_cast<AlarmsList>(alarmsList)) ;
	aList->removeAlarm(alarm1->getName()) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST(Alarm, Latched)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;
	EXPECT_EQ(0, faultsList->getSize()) ;

	std::shared_ptr<IAlarmsList> alarmsList(IAlarmsList::getInstance()) ;
	EXPECT_EQ(0, alarmsList->getSize()) ;

	std::shared_ptr<IFault> faultA(make_fault<FaultA>()) ;
	std::shared_ptr<IFault> faultB(make_fault<FaultB>()) ;
	std::shared_ptr<IFault> faultC(make_fault<FaultC>()) ;

	EXPECT_EQ(3, faultsList->getSize()) ;

	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;

	// Create owner
	std::shared_ptr<IFaultOwner> faultOwner1(make_faultOwner<FaultOwner1>()) ;
	std::shared_ptr<FaultOwner1> fOwner1(std::dynamic_pointer_cast<FaultOwner1>(faultOwner1)) ;

	// Create alarm
	std::shared_ptr<IAlarm> alarm2(make_alarm<Alarm2>()) ;
	EXPECT_EQ(1, alarmsList->getSize()) ;
	EXPECT_FALSE(alarm2->isAlarmActive()) ;

	// Register 2 faults with this alarm
	EXPECT_TRUE(alarm2->registerFaults(std::set<std::string>({"FaultA", "FaultB"}) )) ;

	// set 1
	fOwner1->mState = true ;
	faultOwner1->updateFaults() ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;
	EXPECT_FALSE(alarm2->isAlarmActive()) ;

	// set 2
	faultOwner1->updateFaults() ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;
	EXPECT_FALSE(alarm2->isAlarmActive()) ;

	// set 3
	faultOwner1->updateFaults() ;
	EXPECT_TRUE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;
	EXPECT_TRUE(alarm2->isAlarmActive()) ;

	// set 4
	faultOwner1->updateFaults() ;
	EXPECT_TRUE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;
	EXPECT_TRUE(alarm2->isAlarmActive()) ;

	// set 5
	faultOwner1->updateFaults() ;
	EXPECT_TRUE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;
	EXPECT_TRUE(alarm2->isAlarmActive()) ;



	// clear 1
	fOwner1->mState = false ;
	faultOwner1->updateFaults() ;
	EXPECT_TRUE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;
	EXPECT_TRUE(alarm2->isAlarmActive()) ;

	// clear 2
	faultOwner1->updateFaults() ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;
	EXPECT_TRUE(alarm2->isAlarmActive()) ;

	// clear 3
	faultOwner1->updateFaults() ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;
	EXPECT_TRUE(alarm2->isAlarmActive()) ;

	// clear 4
	faultOwner1->updateFaults() ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_TRUE(faultB->isFaultPresent()) ;
	EXPECT_TRUE(alarm2->isAlarmActive()) ;

	// clear 5
	faultOwner1->updateFaults() ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;
	EXPECT_TRUE(alarm2->isAlarmActive()) ;


	// reset alarm
	alarm2->reset() ;
	EXPECT_FALSE(alarm2->isAlarmActive()) ;


	std::cerr << "Fault A: " << faultA->getName() << std::endl ;
	std::cerr << "Fault B: " << faultB->getName() << std::endl ;
	EXPECT_EQ(3, faultsList->getSize()) ;

	std::shared_ptr<IFault> fault ;
	fault = faultsList->getFault("FaultA") ;
	EXPECT_EQ("FaultA", fault->getName()) ;
	fault = faultsList->getFault("FaultB") ;
	EXPECT_EQ("FaultB", fault->getName()) ;
	fault = faultsList->getFault("FaultC") ;
	EXPECT_EQ("FaultC", fault->getName()) ;

	std::shared_ptr<IFaultOwner> faultOwner ;
	faultOwner = faultsList->getFaultOwner("FaultOwner1") ;
	EXPECT_EQ("FaultOwner1", faultOwner->getName()) ;

	// Tidy up
	std::cerr << "TIDY UP" << std::endl ;
	std::shared_ptr<FaultsList> fList(std::dynamic_pointer_cast<FaultsList>(faultsList)) ;
	fList->removeFault(faultA->getName()) ;
	fList->removeFault(faultB->getName()) ;
	fList->removeFault(faultC->getName()) ;
	fList->removeFaultOwner(faultOwner1->getName()) ;

	std::shared_ptr<AlarmsList> aList(std::dynamic_pointer_cast<AlarmsList>(alarmsList)) ;
	aList->removeAlarm(alarm2->getName()) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST(Alarm, AlarmReset)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;
	EXPECT_EQ(0, faultsList->getSize()) ;

	std::shared_ptr<IAlarmsList> alarmsList(IAlarmsList::getInstance()) ;
	EXPECT_EQ(0, alarmsList->getSize()) ;

	std::shared_ptr<IFault> faultA(make_fault<FaultA>()) ;
	std::shared_ptr<IFault> faultB(make_fault<FaultB>()) ;

	EXPECT_EQ(2, faultsList->getSize()) ;

	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;

	// Create owner
	std::shared_ptr<IFaultOwner> faultOwner1(make_faultOwner<FaultOwner1>()) ;
	std::shared_ptr<FaultOwner1> fOwner1(std::dynamic_pointer_cast<FaultOwner1>(faultOwner1)) ;

	// Create alarm
	std::shared_ptr<IAlarm> alarm1(make_alarm<Alarm1>()) ;
	EXPECT_EQ(1, alarmsList->getSize()) ;
	EXPECT_FALSE(alarm1->isAlarmActive()) ;

	// Register 2 faults with this alarm
	EXPECT_TRUE(alarm1->registerFaults(std::set<std::string>({"FaultA", "FaultB"}) )) ;

	Mplane::ILoggable::setGroupLogDebugLevel(Mplane::ILoggable::LOG_DEBUG_VERBOSE, "AL") ;
	Mplane::ILoggable::setGroupLogDebugLevel(Mplane::ILoggable::LOG_DEBUG_VERBOSE, "FT") ;

	//-------------------------------------------------------------------------------------
	// Raise then clear fault

	std::shared_ptr<FaultA> testFaultA(std::dynamic_pointer_cast<FaultA>(faultA)) ;

	std::cerr << "** Raise then lower fault ** " << std::endl ;

	// set 1
	testFaultA->testSetState(true) ;
//	fOwner1->mState = true ;
//	faultOwner1->updateFaults() ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;
	EXPECT_FALSE(alarm1->isAlarmActive()) ;

	// set 2
	testFaultA->testSetState(true) ;
//	fOwner1->mState = true ;
//	faultOwner1->updateFaults() ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;
	EXPECT_FALSE(alarm1->isAlarmActive()) ;

	// set 3
	testFaultA->testSetState(true) ;
//	fOwner1->mState = true ;
//	faultOwner1->updateFaults() ;
	EXPECT_TRUE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;
	EXPECT_TRUE(alarm1->isAlarmActive()) ;

	alarmsList->show() ;
	alarmsList->showNamesAndIds() ;

	// clear 1
	testFaultA->testSetState(false) ;
//	fOwner1->mState = false ;
//	faultOwner1->updateFaults() ;
	EXPECT_TRUE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;
	EXPECT_TRUE(alarm1->isAlarmActive()) ;

	// clear 2
	testFaultA->testSetState(false) ;
//	fOwner1->mState = false ;
//	faultOwner1->updateFaults() ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;
	EXPECT_FALSE(alarm1->isAlarmActive()) ;

	// reset alarm
	std::cerr << "* Reset alarm" << std::endl ;
	alarm1->reset() ;
	EXPECT_FALSE(alarm1->isAlarmActive()) ;


	//-------------------------------------------------------------------------------------
	// Reset alarm while fault still active

	std::cerr << "** Reset alarm while fault active ** " << std::endl ;

	// set 1
	testFaultA->testSetState(true) ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;
	EXPECT_FALSE(alarm1->isAlarmActive()) ;

	// set 2
	testFaultA->testSetState(true) ;
	EXPECT_FALSE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;
	EXPECT_FALSE(alarm1->isAlarmActive()) ;

	// set 3
	testFaultA->testSetState(true) ;
	EXPECT_TRUE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;
	EXPECT_TRUE(alarm1->isAlarmActive()) ;

	alarmsList->show() ;
//	alarmsList->showNamesAndIds() ;

	// reset alarm
	std::cerr << "* Reset alarm" << std::endl ;
	alarm1->reset() ;
	EXPECT_TRUE(alarm1->isAlarmActive()) ;
	EXPECT_TRUE(faultA->isFaultPresent()) ;

	// fault is active so alarm should still be active
	EXPECT_TRUE(faultA->isFaultPresent()) ;
	EXPECT_FALSE(faultB->isFaultPresent()) ;
	EXPECT_TRUE(alarm1->isAlarmActive()) ;

	alarmsList->show() ;
//	alarmsList->showNamesAndIds() ;

	//-------------------------------------------------------------------------------------



	// Tidy up
	std::cerr << "TIDY UP" << std::endl ;
	std::shared_ptr<FaultsList> fList(std::dynamic_pointer_cast<FaultsList>(faultsList)) ;
	fList->removeFault(faultA->getName()) ;
	fList->removeFault(faultB->getName()) ;
	fList->removeFaultOwner(faultOwner1->getName()) ;

	std::shared_ptr<AlarmsList> aList(std::dynamic_pointer_cast<AlarmsList>(alarmsList)) ;
	aList->removeAlarm(alarm1->getName()) ;
}
