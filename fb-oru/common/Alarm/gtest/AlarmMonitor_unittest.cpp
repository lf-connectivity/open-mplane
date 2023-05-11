/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AlarmMonitor_unittest.cpp
 * \brief     Google Test of AlarmMonitor
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the AlarmMonitor class.
 *
 */
#include <chrono>
#include <gtest/gtest.h>

#include "AlarmMonitor.h"
#include "AlarmTest.h"

using namespace Mplane;

using namespace std;


static const unsigned PERIODIC_REPORT_SECS{5} ;

class AlarmMonOutput {
public:
	AlarmMonOutput() :
		mOutput(),
		lastTime(),
		periodicCount(0)
	{}

	void clear()
	{
		mOutput.clear() ;
	}

	void handler(const IAlarm& alarm)
	{
		std::string status("** ALARM " + alarm.getName() + " " + alarm.getAlarmStateString() + " ** \n") ;
		std::cerr << status ;
		mOutput += status ;
	}

	void periodicHandler(const std::vector<std::shared_ptr<IAlarm>>& activeAlarms)
	{
		std::chrono::system_clock::time_point now(std::chrono::system_clock::now()) ;
		std::string prefix ;
		if (periodicCount++ > 0)
		{
			auto duration(std::chrono::duration_cast<std::chrono::seconds>(now-lastTime)) ;
			std::cerr << "Duration=" << duration.count() << std::endl ;

			// See if report is early
			if (duration.count() < PERIODIC_REPORT_SECS-1)
				prefix="<early> " ;
		}
		lastTime = now ;

		std::string status("== " + prefix + "NoAlarm == \n") ;
		if (!activeAlarms.empty())
		{
			std::string alarmNames;
			for (auto alarm : activeAlarms)
			{
				if (!alarmNames.empty())
					alarmNames += "," ;
				alarmNames += alarm->getName() ;
			}
			status = "== " + prefix + alarmNames + " == \n" ;
		}

		auto unix_timestamp = std::chrono::seconds(std::time(NULL));
		std::cerr << std::to_string(unix_timestamp.count()) << " " << status ;
		mOutput += status ;
	}

	std::string mOutput ;
	std::chrono::system_clock::time_point lastTime ;
	unsigned periodicCount ;

};


//-------------------------------------------------------------------------------------------------------------
/*! @brief Test fixture for alarm monitoring
 *
 *  This class uses the Google test facilities to perform unit testing
 */
class AlarmMonitorTest : public ::testing::Test
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

    	faultsList=(IFaultsList::getInstance()) ;
    	EXPECT_EQ(0, faultsList->getSize()) ;

    	alarmsList=(IAlarmsList::getInstance()) ;
    	EXPECT_EQ(0, alarmsList->getSize()) ;


    	// Create the fault builder
    	std::shared_ptr<IFaultBuilder> faultBuild1(std::make_shared<FaultBuilder1>()) ;
    	EXPECT_EQ(2, faultsList->getSize()) ;
    	std::shared_ptr<IFaultBuilder> faultBuild2(std::make_shared<FaultBuilder2>()) ;
    	EXPECT_EQ(3, faultsList->getSize()) ;

    	// get hold of the faults/owner for testing
    	faultA=(faultsList->getFault("FaultA")) ;
    	faultB=(faultsList->getFault("FaultB")) ;
    	faultC=(faultsList->getFault("FaultC")) ;
    	faultOwner1=(faultsList->getFaultOwner("FaultOwner1")) ;
    	fOwner1=(std::dynamic_pointer_cast<FaultOwner1>(faultOwner1)) ;
    	faultOwner2=(faultsList->getFaultOwner("FaultOwner2")) ;
    	fOwner2=(std::dynamic_pointer_cast<FaultOwner2>(faultOwner2)) ;

    	// create alarm package
    	std::shared_ptr<IAlarmPackage> alarmPackage1(std::make_shared<AlarmPackage1>()) ;
    	EXPECT_EQ(1, alarmsList->getSize()) ;
    	std::shared_ptr<IAlarmPackage> alarmPackage2(std::make_shared<AlarmPackage2>()) ;
    	EXPECT_EQ(2, alarmsList->getSize()) ;

    	alarm1=(alarmsList->getAlarm("Alarm1")) ;
    	alarm2=(alarmsList->getAlarm("Alarm2")) ;

    	// Create monitor - NOTE: Create by hand rather than using singleton otherwise the instance isn't destroyed
    	// until exit() and that's too late for it to be hanging onto all the alarms in the list (and causes a segfault)
    	alarmMon=(std::make_shared<AlarmMonitor>()) ;
    }

    /*! @brief Tear down the test
     */
    virtual void TearDown()
    {
    	// Tidy up - NOTE: *MUST* destroy alarms first followed by faults
    	std::cerr << "TIDY UP" << std::endl ;

    	std::cerr << "Destroy AlarmMonitor" << std::endl ;

    	// disconnect
    	alarmMon.reset() ;

    	std::shared_ptr<AlarmsList> aList(std::dynamic_pointer_cast<AlarmsList>(alarmsList)) ;
    	aList->removeAlarm(alarm1->getName()) ;
    	aList->removeAlarm(alarm2->getName()) ;
    	alarm1.reset() ;
    	alarm2.reset() ;

    	std::shared_ptr<FaultsList> fList(std::dynamic_pointer_cast<FaultsList>(faultsList)) ;
    	fList->removeFault(faultA->getName()) ;
    	fList->removeFault(faultB->getName()) ;
    	fList->removeFaultOwner(faultOwner1->getName()) ;
    	fList->removeFault(faultC->getName()) ;
    	fList->removeFaultOwner(faultOwner2->getName()) ;
    }


    void triggerAlarm1()
    {
    	std::cerr << "**Trigger Alarm1**" << std::endl ;

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

    }

    void clearAlarm1()
    {
    	std::cerr << "!!Clear Alarm1!!" << std::endl ;

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

    }


    void triggerAlarm2()
    {
    	std::cerr << "**Trigger Alarm2**" << std::endl ;

    	// set 1
    	fOwner2->mState = true ;
    	faultOwner1->updateFaults() ;
    	EXPECT_FALSE(faultC->isFaultPresent()) ;
    	EXPECT_FALSE(alarm2->isAlarmActive()) ;

    	// set 2
    	faultOwner2->updateFaults() ;
    	EXPECT_FALSE(faultC->isFaultPresent()) ;
    	EXPECT_FALSE(alarm2->isAlarmActive()) ;

    	// set 3
    	faultOwner2->updateFaults() ;
    	EXPECT_FALSE(faultC->isFaultPresent()) ;
    	EXPECT_FALSE(alarm2->isAlarmActive()) ;

    	// set 4
    	faultOwner2->updateFaults() ;
    	EXPECT_TRUE(faultC->isFaultPresent()) ;
    	EXPECT_TRUE(alarm2->isAlarmActive()) ;

    	// set 5
    	faultOwner2->updateFaults() ;
    	EXPECT_TRUE(faultC->isFaultPresent()) ;
    	EXPECT_TRUE(alarm2->isAlarmActive()) ;


    }

    void clearAlarm2()
    {
    	std::cerr << "!!Clear Alarm2!!" << std::endl ;

    	// clear 1
    	fOwner2->mState = false ;
    	faultOwner2->updateFaults() ;
    	EXPECT_TRUE(faultC->isFaultPresent()) ;
    	EXPECT_TRUE(alarm2->isAlarmActive()) ;

    	// clear 2
    	faultOwner2->updateFaults() ;
    	EXPECT_TRUE(faultC->isFaultPresent()) ;
    	EXPECT_TRUE(alarm2->isAlarmActive()) ;

    	// clear 3
    	faultOwner2->updateFaults() ;
    	EXPECT_TRUE(faultC->isFaultPresent()) ;
    	EXPECT_TRUE(alarm2->isAlarmActive()) ;

    	// clear 4
    	faultOwner2->updateFaults() ;
    	EXPECT_TRUE(faultC->isFaultPresent()) ;
    	EXPECT_TRUE(alarm2->isAlarmActive()) ;

    	// clear 5
    	faultOwner2->updateFaults() ;
    	EXPECT_FALSE(faultC->isFaultPresent()) ;
    	EXPECT_TRUE(alarm2->isAlarmActive()) ;


    	// reset alarm
    	alarm2->reset() ;
    	EXPECT_FALSE(alarm2->isAlarmActive()) ;
    }


public:
	std::shared_ptr<IFaultsList> faultsList ;
	std::shared_ptr<IAlarmsList> alarmsList ;

	std::shared_ptr<IFault> faultA ;
	std::shared_ptr<IFault> faultB ;
	std::shared_ptr<IFault> faultC ;
	std::shared_ptr<IFaultOwner> faultOwner1 ;
	std::shared_ptr<FaultOwner1> fOwner1 ;
	std::shared_ptr<IFaultOwner> faultOwner2 ;
	std::shared_ptr<FaultOwner2> fOwner2 ;

	std::shared_ptr<IAlarm> alarm1 ;
	std::shared_ptr<IAlarm> alarm2 ;

	std::shared_ptr<IAlarmMonitor> alarmMon;
};


//-------------------------------------------------------------------------------------------------------------
TEST_F(AlarmMonitorTest, Handler)
{
	// Create output capture
	std::shared_ptr<AlarmMonOutput> alarmOut(std::make_shared<AlarmMonOutput>()) ;

	// connect up
	alarmMon->registerHandler([alarmOut](const IAlarm& alarm){alarmOut->handler(alarm);}) ;

std::cerr << "Alarm1 use=" << alarm1.use_count() << " Alarm2 use=" << alarm2.use_count() << std::endl ;

	triggerAlarm1() ;
	alarmsList->show() ;
	clearAlarm1() ;

	triggerAlarm1() ;
	clearAlarm1() ;

	triggerAlarm1() ;
	clearAlarm1() ;

	std::string expected(
		"** ALARM Alarm1 ALARM_PRESENT ** \n"
		"** ALARM Alarm1 ALARM_NOT_PRESENT ** \n"
		"** ALARM Alarm1 ALARM_PRESENT ** \n"
		"** ALARM Alarm1 ALARM_NOT_PRESENT ** \n"
		"** ALARM Alarm1 ALARM_PRESENT ** \n"
		"** ALARM Alarm1 ALARM_NOT_PRESENT ** \n"
	) ;
	EXPECT_EQ(expected, alarmOut->mOutput) ;

	// disconnect
	alarmMon->unregisterHandler() ;
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(AlarmMonitorTest, Periodic)
{
//	std::shared_ptr<AlarmMonitor> amon(std::dynamic_pointer_cast<AlarmMonitor>(alarmMon)) ;
	alarmMon->setPeriod(PERIODIC_REPORT_SECS) ;
	EXPECT_EQ(PERIODIC_REPORT_SECS, alarmMon->getPeriod()) ;

	// Create output capture
	std::shared_ptr<AlarmMonOutput> alarmOut(std::make_shared<AlarmMonOutput>()) ;

	// connect up
	alarmMon->registerPeriodicHandler(
		[alarmOut](const std::vector<std::shared_ptr<IAlarm>>& activeAlarms){
			alarmOut->periodicHandler(activeAlarms);
		}
	) ;


	sleep(PERIODIC_REPORT_SECS+1) ;

	// Alarm1 & Alarm2
	{
		std::cerr << "[Trigger early alarms: 1&2]" << std::endl ;
		triggerAlarm1() ;
		triggerAlarm2() ;

		sleep(2*PERIODIC_REPORT_SECS) ;

		clearAlarm1() ;
		clearAlarm2() ;
	}

	sleep(3) ;

	// Alarm2
	{
		std::cerr << "[Trigger early alarm: 2]" << std::endl ;
		triggerAlarm2() ;

		sleep(2*PERIODIC_REPORT_SECS) ;

		clearAlarm2() ;
	}


	sleep(2*PERIODIC_REPORT_SECS) ;

	sleep(3) ;


	// Cause Alarm1 to pulse quickly
	{
		std::cerr << "[Pulse Alarm1]" << std::endl ;
		triggerAlarm1() ;
		clearAlarm1() ;
	}

	sleep(2*PERIODIC_REPORT_SECS) ;



	// Finsh up
	std::cerr << alarmOut->mOutput << std::endl ;

	std::string expected(
		"== NoAlarm == \n"
		"== <early> Alarm1,Alarm2 == \n"
		"== Alarm1,Alarm2 == \n"
		"== NoAlarm == \n"
		"== <early> Alarm2 == \n"
		"== Alarm2 == \n"
		"== NoAlarm == \n"
		"== NoAlarm == \n"
		"== NoAlarm == \n"
		"== <early> Alarm1 == \n"
		"== NoAlarm == \n"
	) ;
	EXPECT_TRUE(alarmOut->mOutput.find(expected) != std::string::npos) ;


	// disconnect
	alarmMon->unregisterPeriodicHandler() ;
}
