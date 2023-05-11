/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxPllLockMajorFault_unittest.cpp
 * \brief     Google Test of RxPllLockMajorFault
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the RxPllLockMajorFault class.
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
#include "IDevices.h"
#include "ISynth.h"
#include "RxPllLockMajorFaultOwner.h"
#include "RxPllLockFaultMajor.h"

using namespace Mplane;

//-------------------------------------------------------------------------------------------------------------
TEST(RxPllLockMajorFault, Test)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFault> fault(make_fault<RxPllLockFaultMajor>());
	std::shared_ptr<IFaultOwner> faultOwner (make_faultOwner<RxPllLockMajorFaultOwner>());

	// no fault
	faultOwner->updateFaults() ;
	EXPECT_FALSE(fault->isFaultPresent()) ;

	std::cout << "** No Faults ** " << std::endl ;

	// fault
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices( radio->getDevices() ) ;

    std::shared_ptr<ISynth> rxSynth1( devices.getRxSynth( 0 ) ) ;
    std::shared_ptr<ISynth> rxSynth2( devices.getRxSynth( 1 ) ) ;
    std::shared_ptr<ISynth> rxSynth3( devices.getRxSynth( 2 ) ) ;
    std::shared_ptr<ISynth> rxSynth4( devices.getRxSynth( 3 ) ) ;

    // Check if the PLL is locked for all available Rx ports
    // Fault in synth 1,2,3
    rxSynth1->forceOutOfLock();
    faultOwner->updateFaults() ;

    rxSynth2->forceOutOfLock();
    faultOwner->updateFaults() ;

	EXPECT_FALSE(fault->isFaultPresent()) ;

	// After 3 lock failures, PLL major fault is asserted
	rxSynth3->forceOutOfLock();
    faultOwner->updateFaults() ;
	EXPECT_TRUE(fault->isFaultPresent()) ;

	std::cout << "** Clock Fault ** " << std::endl ;

    // no fault

	faultOwner->updateFaults() ;
	faultOwner->updateFaults() ;
	EXPECT_TRUE(fault->isFaultPresent()) ;

	// After 3 lock detections, fault is cleared
	faultOwner->updateFaults() ;
	EXPECT_FALSE(fault->isFaultPresent()) ;

	std::cout << "** No Faults ** " << std::endl ;

    // Check if the PLL is locked for all available Rx ports
	// Fault in synth 4,3,1
    rxSynth4->forceOutOfLock();
    faultOwner->updateFaults() ;

    rxSynth3->forceOutOfLock();
    faultOwner->updateFaults() ;

	EXPECT_FALSE(fault->isFaultPresent()) ;

	// After 3 lock failures, PLL major fault is asserted
	rxSynth1->forceOutOfLock();
    faultOwner->updateFaults() ;
	EXPECT_TRUE(fault->isFaultPresent()) ;

	std::cout << "** Clock Fault ** " << std::endl ;

    // no fault

	faultOwner->updateFaults() ;
	faultOwner->updateFaults() ;
	EXPECT_TRUE(fault->isFaultPresent()) ;

	// After 3 lock detections, fault is cleared
	faultOwner->updateFaults() ;
	EXPECT_FALSE(fault->isFaultPresent()) ;

}
