/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PopTripMajorFault_unittest.cpp
 * \brief     Google Test of PopTripMajorFault
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the PopTripMajorFault class.
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

#include "IRadio.h"
#include "ITxPort.h"
#include "IDevices.h"
#include "ISynth.h"

#include "PopTripTxFaultMajor.h"
#include "PopTripMajorFaultOwner.h"
#include "OffTargetFPGA.h"

using namespace Mplane;
using namespace std;

//-------------------------------------------------------------------------------------------------------------
TEST(PopTripTxMajorFault, Test)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFault> faultTx1(make_fault<PopTripTx1FaultMajor>());
	std::shared_ptr<IFault> faultTx2(make_fault<PopTripTx2FaultMajor>());
	std::shared_ptr<IFault> faultTx3(make_fault<PopTripTx3FaultMajor>());
	std::shared_ptr<IFault> faultTx4(make_fault<PopTripTx4FaultMajor>());

	std::shared_ptr<IFaultOwner> faultOwner (make_faultOwner<PopTripMajorFaultOwner>());

    // get the fpga emulator
	std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;
    fpgaEmu->reset() ;

	// no fault
	faultOwner->updateFaults() ;
	EXPECT_FALSE(faultTx1->isFaultPresent()) ;
	EXPECT_FALSE(faultTx2->isFaultPresent()) ;
	EXPECT_FALSE(faultTx3->isFaultPresent()) ;
	EXPECT_FALSE(faultTx4->isFaultPresent()) ;

	std::cout << "** No Faults ** " << std::endl ;

    // Check Pop trip major faults for all available Tx ports
    // start with no alarm
    fpgaEmu->writeField("popAlarm[0]", 0) ;
    fpgaEmu->writeField("popAlarm[1]", 0) ;
    fpgaEmu->writeField("popAlarm[2]", 0) ;
    fpgaEmu->writeField("popAlarm[3]", 0) ;

    // Alarm Tx1
    fpgaEmu->writeField("popAlarm[0]", 1) ;
	EXPECT_FALSE(faultTx1->isFaultPresent()) ;
	faultOwner->updateFaults() ;
	EXPECT_TRUE(faultTx1->isFaultPresent()) ;

    // Alarm Tx2
    fpgaEmu->writeField("popAlarm[1]", 1) ;
	EXPECT_FALSE(faultTx2->isFaultPresent()) ;
	faultOwner->updateFaults() ;
	EXPECT_TRUE(faultTx2->isFaultPresent()) ;

    // Alarm Tx3
    fpgaEmu->writeField("popAlarm[2]", 1) ;
	EXPECT_FALSE(faultTx3->isFaultPresent()) ;
	faultOwner->updateFaults() ;
	EXPECT_TRUE(faultTx3->isFaultPresent()) ;

    // Alarm Tx4
    fpgaEmu->writeField("popAlarm[3]", 1) ;
	EXPECT_FALSE(faultTx4->isFaultPresent()) ;
	faultOwner->updateFaults() ;
	EXPECT_TRUE(faultTx4->isFaultPresent()) ;

	// clear fault
    fpgaEmu->writeField("popAlarm[0]", 0) ;
    fpgaEmu->writeField("popAlarm[1]", 0) ;
    fpgaEmu->writeField("popAlarm[2]", 0) ;
    fpgaEmu->writeField("popAlarm[3]", 0) ;
	// no fault
	faultOwner->updateFaults() ;
	EXPECT_FALSE(faultTx1->isFaultPresent()) ;
	EXPECT_FALSE(faultTx2->isFaultPresent()) ;
	EXPECT_FALSE(faultTx3->isFaultPresent()) ;
	EXPECT_FALSE(faultTx4->isFaultPresent()) ;
}
