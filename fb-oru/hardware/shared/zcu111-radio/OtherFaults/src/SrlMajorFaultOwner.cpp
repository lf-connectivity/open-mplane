/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SrlMajorFaultOwner.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "SrlMajorFaultOwner.h"

#include "SrlTxFaultMajor.h"
#include "IFpgaMgr.h"
#include "IRadio.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SrlMajorFaultOwner::SrlMajorFaultOwner() :
	FaultOwner("SrlMajorFaultOwner", {Mplane::SrlTx1FaultMajor::NAME,
									  Mplane::SrlTx2FaultMajor::NAME,
									  Mplane::SrlTx3FaultMajor::NAME,
									  Mplane::SrlTx4FaultMajor::NAME})
{
}

//-------------------------------------------------------------------------------------------------------------
SrlMajorFaultOwner::~SrlMajorFaultOwner()
{
}

//-------------------------------------------------------------------------------------------------------------
void SrlMajorFaultOwner::updateFaults()
{
    /* *** Update faults, if any exist.*** */
	std::shared_ptr<IFpgaAntennaRegs> fpga = IFpgaMgr::getIFpgaAntennaRegs();

    const char* faultNames[] =
    {
    	Mplane::SrlTx1FaultMajor::NAME,
		Mplane::SrlTx2FaultMajor::NAME,
		Mplane::SrlTx3FaultMajor::NAME,
		Mplane::SrlTx4FaultMajor::NAME,
    };

    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());

	for (int index = 0; index < radio->getNumberOfTxPorts(); index++)
	{
		bool srlAlarm = fpga->read_srlAlarm(index);

		bool status;

		if (true == srlAlarm )
		{
			status = true;
			// Bit is automatically cleared on a read
		}
		else
		{
			status = false;
		}

		// pass to fault
		std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;

		std::shared_ptr<IFault> faultSrlTxMajor(faultsList->getFault(faultNames[index])) ;
		faultSrlTxMajor->setStatus( status );
	}
}
