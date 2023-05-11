/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdPllLockMajorFaultOwner.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DpdPllLockMajorFaultOwner.h"
#include "IRadio.h"
#include "IDevices.h"
#include "ISynth.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DpdPllLockMajorFaultOwner::DpdPllLockMajorFaultOwner() :
	FaultOwner("DpdPllLockMajorFaultOwner", {"DpdPllLockMajorFault"} )
{
}

//-------------------------------------------------------------------------------------------------------------
DpdPllLockMajorFaultOwner::~DpdPllLockMajorFaultOwner()
{
}

//-------------------------------------------------------------------------------------------------------------
void DpdPllLockMajorFaultOwner::updateFaults()
{
	updateDpdPllLockMajorFaults();
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::DpdPllLockMajorFaultOwner::updateDpdPllLockMajorFaults(void)
{
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices( radio->getDevices() ) ;

    bool dpdPllLockAlarm = false;

    // Check if the PLL is locked for all available SRx ports
    for (int index = 0; index < radio->getNumberOfSRxPorts(); index++)
    {
    	std::shared_ptr<ISynth> dpdSynth( devices.getDpdSynth( index ) ) ;
    	if (dpdSynth->isPllLocked() == false)
    	{
    		dpdPllLockAlarm = true;
    		break;
    	}
    }

    // pass to fault
    std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;

    std::shared_ptr<IFault> faultDpdPllMajor(faultsList->getFault("DpdPllLockMajorFault")) ;
    faultDpdPllMajor->setStatus( dpdPllLockAlarm );
}
