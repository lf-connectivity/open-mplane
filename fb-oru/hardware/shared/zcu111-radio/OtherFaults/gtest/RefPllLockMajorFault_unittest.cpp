/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RefPllLockMajorFault_unittest.cpp
 * \brief     Google Test of RefPllLockMajorFault
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the RefPllLockMajorFault class.
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
#include "IRefClock.h"
#include "RefPllLockMajorFaultOwner.h"
#include "RefPllLockFaultMajor.h"

using namespace Mplane;

//-------------------------------------------------------------------------------------------------------------
TEST(RefPllLockMajorFault, Test)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFault> fault(make_fault<RefPllLockFaultMajor>());
	std::shared_ptr<IFaultOwner> faultOwner (make_faultOwner<RefPllLockMajorFaultOwner>());

	// no fault
	faultOwner->updateFaults() ;
	EXPECT_FALSE(fault->isFaultPresent()) ;

	std::cout << "** No Faults ** " << std::endl ;

	// fault
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices( radio->getDevices() ) ;

    std::shared_ptr<IRefClock> refDac( std::dynamic_pointer_cast<IRefClock>(
    		devices.getDevice(IDevice::REFCLOCK, IDevices::DeviceCollection::TX, 0 ) )) ;

    std::shared_ptr<IRefClock> refAdc0( std::dynamic_pointer_cast<IRefClock>(
    		devices.getDevice(IDevice::REFCLOCK, IDevices::DeviceCollection::RX, 0 ) )) ;

    std::shared_ptr<IRefClock> refAdc1( std::dynamic_pointer_cast<IRefClock>(
    		devices.getDevice(IDevice::REFCLOCK, IDevices::DeviceCollection::RX, 1 ) )) ;

    std::shared_ptr<IRefClock> refMain( std::dynamic_pointer_cast<IRefClock>(
    		devices.getDevice(IDevice::REFCLOCK, IDevices::DeviceCollection::SYSTEM, 0 ) )) ;

    // Check if the PLL is locked for all available Ref clocks
    // Fault in ref clock for DACs and ADCs
    refDac->forceOutOfLock();
    faultOwner->updateFaults() ;

    refAdc0->forceOutOfLock();
    faultOwner->updateFaults() ;

	EXPECT_FALSE(fault->isFaultPresent()) ;

	// After 3 lock failures, PLL major fault is asserted
	refAdc1->forceOutOfLock();
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
}
