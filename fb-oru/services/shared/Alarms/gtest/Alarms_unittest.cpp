/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Alarms_unittest.cpp
 * \brief     Google Test of Alarms
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the RrhAlarms class.
 *
 */

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <iostream>
#include <memory>

#include "IFault.h"
#include "IFaultOwner.h"
#include "Fault.h"
#include "FaultOwner.h"
#include "IAlarm.h"
#include "IAlarmsList.h"
#include "IFaultsList.h"

#include "IRadio.h"
#include "IDevices.h"
#include "ISynth.h"
#include "RxPllLockFaultMajor.h"
#include "TxPllLockFaultMajor.h"
#include "RefPllLockFaultMajor.h"
#include "DpdPllLockFaultMajor.h"
#include "SynthClockFault.h"
#include "PllMajorAlarm.h"

using namespace Mplane;

//-------------------------------------------------------------------------------------------------------------
TEST(RrhAlarms, Test)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFault> synthFault(make_fault<SynthClockFault>());
	std::shared_ptr<IFault> txFault(make_fault<TxPllLockFaultMajor>());
	std::shared_ptr<IFault> rxFault(make_fault<RxPllLockFaultMajor>());
	std::shared_ptr<IFault> dpdFault(make_fault<DpdPllLockFaultMajor>());
	std::shared_ptr<IFault> refFault(make_fault<RefPllLockFaultMajor>());
	std::shared_ptr<IAlarm> PllAlarm( make_alarm<PllMajorAlarm>() );
	std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;

	// Raise one fault
	txFault->setStatus(true);
	txFault->setStatus(true);
	txFault->setStatus(true);

	// All faults except the tx fault should be set
	EXPECT_FALSE(synthFault->isFaultPresent());
	EXPECT_FALSE(rxFault->isFaultPresent());
	EXPECT_FALSE(dpdFault->isFaultPresent());
	EXPECT_FALSE(refFault->isFaultPresent());

	// Alarm should be set as one of the faults is raised
	EXPECT_TRUE(txFault->isFaultPresent());
	EXPECT_TRUE(PllAlarm->isAlarmActive());
	EXPECT_EQ(PllAlarm->getRootCause(), "TxPllLockMajorFault");

	// Reset Tx fault
	txFault->setStatus(false);
	txFault->setStatus(false);
	txFault->setStatus(false);

	// All faults should be reset
	EXPECT_FALSE(txFault->isFaultPresent());
	EXPECT_FALSE(synthFault->isFaultPresent());
	EXPECT_FALSE(rxFault->isFaultPresent());
	EXPECT_FALSE(dpdFault->isFaultPresent());
	EXPECT_FALSE(refFault->isFaultPresent());

	// Alarm is reset
	EXPECT_FALSE(PllAlarm->isAlarmActive());

	/*********************2 Faults**************************/

	// Raise 2 faults
	synthFault->setStatus(true);
	synthFault->setStatus(true);
	synthFault->setStatus(true);
	synthFault->setStatus(true);
	synthFault->setStatus(true);
	synthFault->setStatus(true);
	synthFault->setStatus(true);
	synthFault->setStatus(true);
	synthFault->setStatus(true);

	dpdFault->setStatus(true);
	dpdFault->setStatus(true);
	dpdFault->setStatus(true);

	// All faults except the dpd fault should be set
	EXPECT_FALSE(synthFault->isFaultPresent());
	EXPECT_FALSE(rxFault->isFaultPresent());
	EXPECT_TRUE(dpdFault->isFaultPresent());
	EXPECT_FALSE(refFault->isFaultPresent());
	EXPECT_FALSE(txFault->isFaultPresent());

	// Alarm should be set
	EXPECT_TRUE(PllAlarm->isAlarmActive());
	EXPECT_EQ(PllAlarm->getRootCause(), "DpdPllLockMajorFault");

	// Reset the fault
	synthFault->setStatus(false);
	synthFault->setStatus(false);
	synthFault->setStatus(false);

	// Alarm should be set as one of the faults is raised
	EXPECT_TRUE(PllAlarm->isAlarmActive());

	dpdFault->setStatus(false);
	dpdFault->setStatus(false);
	dpdFault->setStatus(false);

	// All faults should be reset
	EXPECT_FALSE(txFault->isFaultPresent());
	EXPECT_FALSE(synthFault->isFaultPresent());
	EXPECT_FALSE(rxFault->isFaultPresent());
	EXPECT_FALSE(dpdFault->isFaultPresent());
	EXPECT_FALSE(refFault->isFaultPresent());

	// Alarm is reset
	EXPECT_FALSE(PllAlarm->isAlarmActive());

	/*********************All Faults**************************/

	// Raise 2 faults
	synthFault->setStatus(true);
	synthFault->setStatus(true);
	synthFault->setStatus(true);
	synthFault->setStatus(true);
	synthFault->setStatus(true);
	synthFault->setStatus(true);
	synthFault->setStatus(true);
	synthFault->setStatus(true);
	synthFault->setStatus(true);
	synthFault->setStatus(true);

	dpdFault->setStatus(true);
	dpdFault->setStatus(true);
	dpdFault->setStatus(true);

	txFault->setStatus(true);
	txFault->setStatus(true);
	txFault->setStatus(true);

	rxFault->setStatus(true);
	rxFault->setStatus(true);
	rxFault->setStatus(true);

	refFault->setStatus(true);
	refFault->setStatus(true);
	refFault->setStatus(true);

	// All faults should be set
	EXPECT_TRUE(synthFault->isFaultPresent());
	EXPECT_TRUE(rxFault->isFaultPresent());
	EXPECT_TRUE(dpdFault->isFaultPresent());
	EXPECT_TRUE(refFault->isFaultPresent());
	EXPECT_TRUE(txFault->isFaultPresent());

	// Alarm should be set
	EXPECT_TRUE(PllAlarm->isAlarmActive());
	EXPECT_EQ(PllAlarm->getRootCause(), "BasebandSynthClockFault");

	// Reset the fault
	synthFault->setStatus(false);
	synthFault->setStatus(false);
	synthFault->setStatus(false);

	dpdFault->setStatus(false);
	dpdFault->setStatus(false);
	dpdFault->setStatus(false);

	txFault->setStatus(false);
	txFault->setStatus(false);
	txFault->setStatus(false);

	// Alarm should be set as one of the faults is raised
	EXPECT_TRUE(PllAlarm->isAlarmActive());

	rxFault->setStatus(false);
	rxFault->setStatus(false);
	rxFault->setStatus(false);

	refFault->setStatus(false);
	refFault->setStatus(false);
	refFault->setStatus(false);

	// All faults should be reset
	EXPECT_FALSE(txFault->isFaultPresent());
	EXPECT_FALSE(synthFault->isFaultPresent());
	EXPECT_FALSE(rxFault->isFaultPresent());
	EXPECT_FALSE(dpdFault->isFaultPresent());
	EXPECT_FALSE(refFault->isFaultPresent());

	// Alarm is reset
	EXPECT_FALSE(PllAlarm->isAlarmActive());

}
