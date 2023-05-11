/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxOverPowerMinorFaultOwner.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TxOverPowerMinorFaultOwner.h"

#include "TxOverPowerFaultMinor.h"
#include "IFpgaMgr.h"
#include "IRadio.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TxOverPowerMinorFaultOwner::TxOverPowerMinorFaultOwner() :
	FaultOwner("TxOverPowerMinorFaultOwner", {Mplane::Tx1OverPowerFaultMinor::NAME,
										      Mplane::Tx2OverPowerFaultMinor::NAME,
											  Mplane::Tx3OverPowerFaultMinor::NAME,
											  Mplane::Tx4OverPowerFaultMinor::NAME} ),
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
TxOverPowerMinorFaultOwner::~TxOverPowerMinorFaultOwner()
{
    // DeRegister as an observer of the carrier manager TX ON and TX OFF events.
    std::dynamic_pointer_cast<Subject<ITxOn,  const ITxEventData&>>(mCarrierMgr)->detach(*this);
    std::dynamic_pointer_cast<Subject<ITxOff, const ITxEventData&>>(mCarrierMgr)->detach(*this);
}

//-------------------------------------------------------------------------------------------------------------
void TxOverPowerMinorFaultOwner::updateFaults()
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
    	Mplane::Tx1OverPowerFaultMinor::NAME,
		Mplane::Tx2OverPowerFaultMinor::NAME,
		Mplane::Tx3OverPowerFaultMinor::NAME,
		Mplane::Tx4OverPowerFaultMinor::NAME,
    };

    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());

	for (int index = 0; index < radio->getNumberOfTxPorts(); index++)
	{
		bool highPowerAlarm = fpga->read_highPowerAlarm(index);

		bool status;

		if( (true == highPowerAlarm ) &&
			(true == istxOn[index]) )
		{
			status = true;
			fpga->write_highPowerAlarm( index, (UINT16)1); // Clear the FPGA fault, as it is latching
		}
		else
		{
			status = false;
		}

		// pass to fault
		std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;

		std::shared_ptr<IFault> faultTxOverPowerMinor(faultsList->getFault(faultNames[index])) ;
		faultTxOverPowerMinor->setStatus( status );
	}
}

void Mplane::TxOverPowerMinorFaultOwner::update(ITxOn& subject, const ITxEventData& txOnOff)
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

void Mplane::TxOverPowerMinorFaultOwner::update(ITxOff& subject, const ITxEventData& txOnOff)
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
