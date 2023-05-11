/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SynthClockFault_unittest.cpp
 * \brief     Google Test of SynthClockFault
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the SynthClockFault class.
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

//#include "ClockFaultPackage.h"
#include "OffTargetFPGA.h"

#include "ClockFaultOwner.h"
#include "SynthClockFault.h"

using namespace Mplane;

//-------------------------------------------------------------------------------------------------------------
TEST(SynthClockFault, Test)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    // get the fpga emulator
    std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;
    fpgaEmu->reset() ;

    // start with no alarm
    fpgaEmu->writeField("alarmUnlatchedSynthStatus", 0) ;

	std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;

	// create faults
//	std::shared_ptr<IFaultPackage> package(std::make_shared<ClockFaultPackage>()) ;

    std::shared_ptr<IFault> theFault(make_fault<SynthClockFault>()) ;

    // Create the owner
    std::shared_ptr<IFaultOwner> theFaultOwner(make_faultOwner<ClockFaultOwner>()) ;

	std::shared_ptr<IFaultOwner> faultOwner(faultsList->getFaultOwner("ClockFaultOwner")) ;
	std::shared_ptr<IFault> fault(faultsList->getFault("BasebandSynthClockFault")) ;

	// no fault
    fpgaEmu->writeField("alarmUnlatchedSynthStatus", 0) ;
	faultsList->updateFaults() ;
	EXPECT_FALSE(fault->isFaultPresent()) ;

	std::cout << "** No Faults ** " << std::endl ;
	faultsList->show() ;

	// fault
    fpgaEmu->writeField("alarmUnlatchedSynthStatus", 1) ;
	faultsList->updateFaults() ;
    fpgaEmu->writeField("alarmUnlatchedSynthStatus", 1) ;
	faultsList->updateFaults() ;
	EXPECT_FALSE(fault->isFaultPresent()) ;

    fpgaEmu->writeField("alarmUnlatchedSynthStatus", 1) ;
	faultsList->updateFaults() ;
	EXPECT_TRUE(fault->isFaultPresent()) ;

	std::cout << "** Clock Fault ** " << std::endl ;
	faultsList->show() ;

	faultsList->updateFaults() ;
	EXPECT_TRUE(fault->isFaultPresent()) ;
	faultsList->updateFaults() ;
	EXPECT_TRUE(fault->isFaultPresent()) ;

	// no fault
    fpgaEmu->writeField("alarmUnlatchedSynthStatus", 0) ;
	faultsList->updateFaults() ;
    fpgaEmu->writeField("alarmUnlatchedSynthStatus", 0) ;
	faultsList->updateFaults() ;
	EXPECT_TRUE(fault->isFaultPresent()) ;

    fpgaEmu->writeField("alarmUnlatchedSynthStatus", 0) ;
	faultsList->updateFaults() ;
	EXPECT_FALSE(fault->isFaultPresent()) ;

	std::cout << "** No Faults ** " << std::endl ;
	faultsList->show() ;

    // Tidy up
    std::cerr << "TIDY UP" << std::endl ;
    std::shared_ptr<FaultsList> fList(std::dynamic_pointer_cast<FaultsList>(faultsList)) ;
    fList->removeFault(fault->getName()) ;

    fList->removeFaultOwner(faultOwner->getName()) ;
}
