/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxPllLockMajorFaultOwner.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TxPllLockMajorFaultOwner.h"
#include "IRadio.h"
#include "IDevices.h"
#include "ISynth.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TxPllLockMajorFaultOwner::TxPllLockMajorFaultOwner() :
	FaultOwner("TxPllLockMajorFaultOwner", {"TxPllLockMajorFault"} )
{
}

//-------------------------------------------------------------------------------------------------------------
TxPllLockMajorFaultOwner::~TxPllLockMajorFaultOwner()
{
}

//-------------------------------------------------------------------------------------------------------------
void TxPllLockMajorFaultOwner::updateFaults()
{
	updateTxPllLockMajorFaults();
}

void Mplane::TxPllLockMajorFaultOwner::updateTxPllLockMajorFaults(void)
{
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices( radio->getDevices() ) ;

    bool txPllLockAlarm = false;

    // Check if the PLL is locked for all available Tx ports
    for (int index = 0; index < radio->getNumberOfTxPorts(); index++)
    {
    	std::shared_ptr<ISynth> txSynth( devices.getTxSynth( index ) ) ;
    	if (txSynth->isPllLocked() == false)
    	{
    		txPllLockAlarm = true;
    		//break;
    	}
    }

    // pass to fault
    std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;

    std::shared_ptr<IFault> faultTxPllMajor(faultsList->getFault("TxPllLockMajorFault")) ;
    faultTxPllMajor->setStatus( txPllLockAlarm );
}
