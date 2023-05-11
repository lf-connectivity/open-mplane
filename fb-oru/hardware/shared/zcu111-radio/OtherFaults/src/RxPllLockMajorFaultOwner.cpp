/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxPllLockMajorFaultOwner.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "RxPllLockMajorFaultOwner.h"
#include "IRadio.h"
#include "IDevices.h"
#include "ISynth.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RxPllLockMajorFaultOwner::RxPllLockMajorFaultOwner() :
	FaultOwner("RxPllLockMajorFaultOwner", {"RxPllLockMajorFault"} )
{
}

//-------------------------------------------------------------------------------------------------------------
RxPllLockMajorFaultOwner::~RxPllLockMajorFaultOwner()
{
}

//-------------------------------------------------------------------------------------------------------------
void RxPllLockMajorFaultOwner::updateFaults()
{
	updateRxPllLockMajorFaults();
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RxPllLockMajorFaultOwner::updateRxPllLockMajorFaults(void)
{
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices( radio->getDevices() ) ;

    bool rxPllLockAlarm = false;

    // Check if the PLL is locked for all available Rx ports
    for (int index = 0; index < radio->getNumberOfRxPorts(); index++)
    {
    	std::shared_ptr<ISynth> rxSynth( devices.getRxSynth( index ) ) ;
    	if (rxSynth->isPllLocked() == false)
    	{
    		rxPllLockAlarm = true;
    		break;
    	}
    }

    // pass to fault
    std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;

    std::shared_ptr<IFault> faultRxPllMajor(faultsList->getFault("RxPllLockMajorFault")) ;
    faultRxPllMajor->setStatus( rxPllLockAlarm );
}
