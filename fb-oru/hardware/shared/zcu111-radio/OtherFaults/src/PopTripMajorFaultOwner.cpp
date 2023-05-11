/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PopTripMajorFaultOwner.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "PopTripMajorFaultOwner.h"

#include "PopTripTxFaultMajor.h"
#include "IFpgaMgr.h"
#include "IRadio.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
PopTripMajorFaultOwner::PopTripMajorFaultOwner() :
	FaultOwner("PopTripMajorFaultOwner", {Mplane::PopTripTx1FaultMajor::NAME,
									      Mplane::PopTripTx2FaultMajor::NAME,
									      Mplane::PopTripTx3FaultMajor::NAME,
									      Mplane::PopTripTx4FaultMajor::NAME})
{
}

//-------------------------------------------------------------------------------------------------------------
PopTripMajorFaultOwner::~PopTripMajorFaultOwner()
{
}

//-------------------------------------------------------------------------------------------------------------
void PopTripMajorFaultOwner::updateFaults()
{
    /* *** Update faults, if any exist.*** */
	std::shared_ptr<IFpgaAntennaRegs> fpga = IFpgaMgr::getIFpgaAntennaRegs();

    const char* faultNames[] =
    {
    	Mplane::PopTripTx1FaultMajor::NAME,
		Mplane::PopTripTx2FaultMajor::NAME,
		Mplane::PopTripTx3FaultMajor::NAME,
		Mplane::PopTripTx4FaultMajor::NAME,
    };

    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());

	for (int index = 0; index < radio->getNumberOfTxPorts(); index++)
	{
		bool alarm = fpga->read_popAlarm((unsigned)index);

		bool status;

		if (true == alarm )
		{
			status = true;

	    	// Clear the alarm bit in case this is a transitional problem
	    	fpga->write_popAlarm((unsigned)index, (UINT16)1);
		}
		else
		{
			status = false;
		}

		// pass to fault
		std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;

		std::shared_ptr<IFault> faultPopTripTxMajor(faultsList->getFault(faultNames[index])) ;
		faultPopTripTxMajor->setStatus( status );
	}
}
