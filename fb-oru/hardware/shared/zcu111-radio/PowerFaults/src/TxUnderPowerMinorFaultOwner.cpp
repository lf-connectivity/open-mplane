/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxUnderPowerMinorFaultOwner.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TxUnderPowerMinorFaultOwner.h"

#include "TxUnderPowerFaultMinor.h"
#include "IFpgaMgr.h"
#include "IRadio.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TxUnderPowerMinorFaultOwner::TxUnderPowerMinorFaultOwner() :
    FaultOwner("TxUnderPowerMinorFaultOwner", {Mplane::Tx1UnderPowerFaultMinor::NAME,
                                               Mplane::Tx2UnderPowerFaultMinor::NAME,
                                               Mplane::Tx3UnderPowerFaultMinor::NAME,
                                               Mplane::Tx4UnderPowerFaultMinor::NAME} ),
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
TxUnderPowerMinorFaultOwner::~TxUnderPowerMinorFaultOwner()
{
    // DeRegister as an observer of the carrier manager TX ON and TX OFF events.
    std::dynamic_pointer_cast<Subject<ITxOn,  const ITxEventData&>>(mCarrierMgr)->detach(*this);
    std::dynamic_pointer_cast<Subject<ITxOff, const ITxEventData&>>(mCarrierMgr)->detach(*this);
}

//-------------------------------------------------------------------------------------------------------------
void TxUnderPowerMinorFaultOwner::updateFaults()
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
    	Mplane::Tx1UnderPowerFaultMinor::NAME,
		Mplane::Tx2UnderPowerFaultMinor::NAME,
		Mplane::Tx3UnderPowerFaultMinor::NAME,
		Mplane::Tx4UnderPowerFaultMinor::NAME,
    };

    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());

	for (int index = 0; index < radio->getNumberOfTxPorts(); index++)
	{
		bool lowPowerAlarm = fpga->read_lowPowerAlarm(index);

		bool status;

		if( (true == lowPowerAlarm ) &&
			(true == istxOn[index]) )
		{
			status = true;
			fpga->write_lowPowerAlarm( index, (UINT16)1); // Clear the FPGA fault, as it is latching
		}
		else
		{
			status = false;
		}

		// pass to fault
		std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;

		std::shared_ptr<IFault> faultTxUnderPowerMinor(faultsList->getFault(faultNames[index])) ;
		faultTxUnderPowerMinor->setStatus( status );
	}
}

void Mplane::TxUnderPowerMinorFaultOwner::update(ITxOn& subject, const ITxEventData& txOnOff)
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

void Mplane::TxUnderPowerMinorFaultOwner::update(ITxOff& subject, const ITxEventData& txOnOff)
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
