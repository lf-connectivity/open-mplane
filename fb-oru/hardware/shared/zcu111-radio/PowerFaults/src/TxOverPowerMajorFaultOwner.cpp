/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxOverPowerMajorFaultOwner.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TxOverPowerMajorFaultOwner.h"

#include "TxOverPowerFaultMajor.h"
#include "IFpgaMgr.h"
#include "IRadio.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TxOverPowerMajorFaultOwner::TxOverPowerMajorFaultOwner() :
	FaultOwner("TxOverPowerMajorFaultOwner", { Mplane::Tx1OverPowerFaultMajor::NAME,
											   Mplane::Tx2OverPowerFaultMajor::NAME,
											   Mplane::Tx3OverPowerFaultMajor::NAME,
											   Mplane::Tx4OverPowerFaultMajor::NAME } ),
										       mIsTx1On(false),
											   mIsTx2On(false),
											   mIsTx3On(false),
											   mIsTx4On(false),
											   mCarrierMgr(ICarrierServer::getInstance())
{
    // Register as an observer of the carrier manager TX ON and TX OFF events.
    std::dynamic_pointer_cast<Subject<ITxOn,  const ITxEventData&>>(mCarrierMgr)->attach(*this);
    std::dynamic_pointer_cast<Subject<ITxOff, const ITxEventData&>>(mCarrierMgr)->attach(*this);
}

//-------------------------------------------------------------------------------------------------------------
TxOverPowerMajorFaultOwner::~TxOverPowerMajorFaultOwner()
{
    // DeRegister as an observer of the carrier manager TX ON and TX OFF events.
    std::dynamic_pointer_cast<Subject<ITxOn,  const ITxEventData&>>(mCarrierMgr)->detach(*this);
    std::dynamic_pointer_cast<Subject<ITxOff, const ITxEventData&>>(mCarrierMgr)->detach(*this);
}

//-------------------------------------------------------------------------------------------------------------
void TxOverPowerMajorFaultOwner::updateFaults()
{
    /* *** Update faults, if any exist.*** */
	std::shared_ptr<IFpgaAntennaRegs> fpga = IFpgaMgr::getIFpgaAntennaRegs();

	bool istxOn[]=
	{
		mIsTx1On,
		mIsTx2On,
		mIsTx3On,
		mIsTx4On
	};

    const char* faultNames[] =
    {
    	Mplane::Tx1OverPowerFaultMajor::NAME,
		Mplane::Tx2OverPowerFaultMajor::NAME,
		Mplane::Tx3OverPowerFaultMajor::NAME,
		Mplane::Tx4OverPowerFaultMajor::NAME,
    };

    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());

	for (int index = 0; index < radio->getNumberOfTxPorts(); index++)
	{
		bool shutdownAlarm = fpga->read_shutdownAlarm(index);

		bool status;

		if( (true == shutdownAlarm ) &&
			(true == istxOn[index]) )
		{
			status = true;
			fpga->write_shutdownAlarm( index, (UINT16)1); // Clear the FPGA fault, as it is latching
		}
		else
		{
			status = false;
		}

		// pass to fault
		std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;

		std::shared_ptr<IFault> faultTxOverPowerMajor(faultsList->getFault(faultNames[index])) ;
		faultTxOverPowerMajor->setStatus( status );
	}
}

void Mplane::TxOverPowerMajorFaultOwner::update(ITxOn& subject, const ITxEventData& txOnOff)
{
	switch (txOnOff.getPort())
	{
	case 0:
		mIsTx1On = true;
		break;

	case 1:
		mIsTx2On = true;
		break;

	case 2:
		mIsTx3On = true;
		break;

	case 3:
		mIsTx4On = true;
		break;

	default:
		break;
	}
}

void Mplane::TxOverPowerMajorFaultOwner::update(ITxOff& subject, const ITxEventData& txOnOff)
{
	switch (txOnOff.getPort())
	{
	case 0:
		mIsTx1On = false;
		break;

	case 1:
		mIsTx2On = false;
		break;

	case 2:
		mIsTx3On = false;
		break;

	case 3:
		mIsTx4On = false;
		break;

	default:
		break;
	}
}
