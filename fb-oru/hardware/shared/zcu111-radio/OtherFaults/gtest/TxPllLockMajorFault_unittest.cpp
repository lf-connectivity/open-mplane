/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxPllLockMajorFault_unittest.cpp
 * \brief     Google Test of TxPllLockMajorFault
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the TxPllLockMajorFault class.
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
#include "TxPllLockMajorFaultOwner.h"
#include "TxPllLockFaultMajor.h"

using namespace Mplane;

//-------------------------------------------------------------------------------------------------------------
TEST(TxPllLockMajorFault, Test)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFault> fault(make_fault<TxPllLockFaultMajor>());
	std::shared_ptr<IFaultOwner> faultOwner (make_faultOwner<TxPllLockMajorFaultOwner>());

	// no fault
	faultOwner->updateFaults() ;
	EXPECT_FALSE(fault->isFaultPresent()) ;

	std::cout << "** No Faults ** " << std::endl ;

	// fault
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices( radio->getDevices() ) ;

    std::shared_ptr<ISynth> txSynth1( devices.getTxSynth( 0 ) ) ;
    std::shared_ptr<ISynth> txSynth2( devices.getTxSynth( 1 ) ) ;
    std::shared_ptr<ISynth> txSynth3( devices.getTxSynth( 2 ) ) ;
    std::shared_ptr<ISynth> txSynth4( devices.getTxSynth( 3 ) ) ;

    // Check if the PLL is locked for all available Tx ports
    // Fault in synth 1,2,3
    txSynth1->forceOutOfLock();
    faultOwner->updateFaults() ;

    txSynth2->forceOutOfLock();
    faultOwner->updateFaults() ;

	EXPECT_FALSE(fault->isFaultPresent()) ;

	// After 3 lock failures, PLL major fault is asserted
	txSynth3->forceOutOfLock();
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

    // Check if the PLL is locked for all available Tx ports
	// Fault in synth 4,3,1
    txSynth4->forceOutOfLock();
    faultOwner->updateFaults() ;

    txSynth3->forceOutOfLock();
    faultOwner->updateFaults() ;

	EXPECT_FALSE(fault->isFaultPresent()) ;

	// After 3 lock failures, PLL major fault is asserted
	txSynth1->forceOutOfLock();
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
