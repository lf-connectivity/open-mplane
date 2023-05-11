/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SrlTxMajorFault_unittest.cpp
 * \brief     Google Test of SrlTxMajorFault
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the SrlTxMajorFault class.
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

#include "SrlTxFaultMajor.h"
#include "SrlMajorFaultOwner.h"
#include "OffTargetFPGA.h"

using namespace Mplane;
using namespace std;

//-------------------------------------------------------------------------------------------------------------
TEST(SrlTxMajorFault, Test)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFault> faultTx1(make_fault<SrlTx1FaultMajor>());
	std::shared_ptr<IFault> faultTx2(make_fault<SrlTx2FaultMajor>());
	std::shared_ptr<IFault> faultTx3(make_fault<SrlTx3FaultMajor>());
	std::shared_ptr<IFault> faultTx4(make_fault<SrlTx4FaultMajor>());

	std::shared_ptr<IFaultOwner> faultOwner (make_faultOwner<SrlMajorFaultOwner>());

	// no fault
	faultOwner->updateFaults() ;
	EXPECT_FALSE(faultTx1->isFaultPresent()) ;
	EXPECT_FALSE(faultTx2->isFaultPresent()) ;
	EXPECT_FALSE(faultTx3->isFaultPresent()) ;
	EXPECT_FALSE(faultTx4->isFaultPresent()) ;

	std::cout << "** No Faults ** " << std::endl ;

    // Check SRL major faults for all available Tx ports
    // get the fpga emulator
	std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;
    fpgaEmu->reset() ;
    // start with no alarm
    fpgaEmu->writeField("srlAlarm[0]", 0) ;
    fpgaEmu->writeField("srlAlarm[1]", 0) ;
    fpgaEmu->writeField("srlAlarm[2]", 0) ;
    fpgaEmu->writeField("srlAlarm[3]", 0) ;

    // Alarm Tx1
    fpgaEmu->writeField("srlAlarm[0]", 1) ;
	EXPECT_FALSE(faultTx1->isFaultPresent()) ;
	faultOwner->updateFaults() ;
	EXPECT_TRUE(faultTx1->isFaultPresent()) ;

    // Alarm Tx2
    fpgaEmu->writeField("srlAlarm[1]", 1) ;
	EXPECT_FALSE(faultTx2->isFaultPresent()) ;
	faultOwner->updateFaults() ;
	EXPECT_TRUE(faultTx2->isFaultPresent()) ;

    // Alarm Tx3
    fpgaEmu->writeField("srlAlarm[2]", 1) ;
	EXPECT_FALSE(faultTx3->isFaultPresent()) ;
	faultOwner->updateFaults() ;
	EXPECT_TRUE(faultTx3->isFaultPresent()) ;

    // Alarm Tx4
    fpgaEmu->writeField("srlAlarm[3]", 1) ;
	EXPECT_FALSE(faultTx4->isFaultPresent()) ;
	faultOwner->updateFaults() ;
	EXPECT_TRUE(faultTx4->isFaultPresent()) ;

	// clear fault
    fpgaEmu->writeField("srlAlarm[0]", 0) ;
    fpgaEmu->writeField("srlAlarm[1]", 0) ;
    fpgaEmu->writeField("srlAlarm[2]", 0) ;
    fpgaEmu->writeField("srlAlarm[3]", 0) ;
	// no fault
	faultOwner->updateFaults() ;
	EXPECT_FALSE(faultTx1->isFaultPresent()) ;
	EXPECT_FALSE(faultTx2->isFaultPresent()) ;
	EXPECT_FALSE(faultTx3->isFaultPresent()) ;
	EXPECT_FALSE(faultTx4->isFaultPresent()) ;
}
