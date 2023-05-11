/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RefPllLockMajorFaultOwner.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "RefPllLockMajorFaultOwner.h"
#include "RefPllLockFaultMajor.h"
#include "IRadio.h"
#include "IDevices.h"
#include "IRefClock.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RefPllLockMajorFaultOwner::RefPllLockMajorFaultOwner() :
	FaultOwner("RefPllLockMajorFaultOwner", {Mplane::RefPllLockFaultMajor::NAME} )
{
}

//-------------------------------------------------------------------------------------------------------------
RefPllLockMajorFaultOwner::~RefPllLockMajorFaultOwner()
{
}

//-------------------------------------------------------------------------------------------------------------
void RefPllLockMajorFaultOwner::updateFaults()
{
	updateRefPllLockMajorFaults();
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RefPllLockMajorFaultOwner::updateRefPllLockMajorFaults(void)
{
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices( radio->getDevices() ) ;

    std::shared_ptr<IRefClock> txRefClock(std::dynamic_pointer_cast<IRefClock>(
    		devices.getDevice(IDevice::REFCLOCK, IDevices::DeviceCollection::TX, 0)));

    std::shared_ptr<IRefClock> rxRefClock(std::dynamic_pointer_cast<IRefClock>(
    		devices.getDevice(IDevice::REFCLOCK, IDevices::DeviceCollection::RX, 0)));

    std::shared_ptr<IRefClock> rxRefClock1(std::dynamic_pointer_cast<IRefClock>(
    		devices.getDevice(IDevice::REFCLOCK, IDevices::DeviceCollection::RX, 1)));

    bool refPllLockAlarm = false;

    // Check if the PLL is locked for all reference clocks
    if (txRefClock->isPllLocked() == false ||
    	rxRefClock->isPllLocked() == false ||
		rxRefClock1->isPllLocked() == false)
    {
    	refPllLockAlarm = true;
    }

    // pass to fault
    std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;

    std::shared_ptr<IFault> faultRefPllMajor(faultsList->getFault("RefPllLockMajorFault")) ;
    faultRefPllMajor->setStatus( refPllLockAlarm );
}
