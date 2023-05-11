/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OverTempMinorFaultOwner.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "OverTempMinorFaultOwner.h"

#include "IRadio.h"
#include "ITxPort.h"

#include "BoardTxOverTemperatureFaultMinor.h"
#include "PaOverTemperatureFaultMinor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
OverTempMinorFaultOwner::OverTempMinorFaultOwner() :
	FaultOwner("OverTempMinorFaultOwner", {	Mplane::BoardTx1OverTemperatureFaultMinor::NAME,
										   Mplane::BoardTx2OverTemperatureFaultMinor::NAME,
										   Mplane::BoardTx3OverTemperatureFaultMinor::NAME,
										   Mplane::BoardTx4OverTemperatureFaultMinor::NAME,
										   Mplane::Pa1OverTemperatureFaultMinor::NAME,
										   Mplane::Pa2OverTemperatureFaultMinor::NAME,
										   Mplane::Pa3OverTemperatureFaultMinor::NAME,
										   Mplane::Pa4OverTemperatureFaultMinor::NAME} )
{
}

//-------------------------------------------------------------------------------------------------------------
OverTempMinorFaultOwner::~OverTempMinorFaultOwner()
{
}

//-------------------------------------------------------------------------------------------------------------
void OverTempMinorFaultOwner::updateFaults()
{
	updateOverTempMinorFaults();
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::OverTempMinorFaultOwner::updateOverTempMinorFaults(void)
{
	/* *** Update the board temperature faults, if any exist. *** */
    std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());

    // Array of temperature thresholds for Tx port
    const float temperatureThresholds[] =
    {
		BOARD_TX1_ALARM_OVER_TEMP_MINOR,
		BOARD_TX2_ALARM_OVER_TEMP_MINOR,
		BOARD_TX3_ALARM_OVER_TEMP_MINOR,
		BOARD_TX4_ALARM_OVER_TEMP_MINOR,
    };

    const char* faultNames[] =
    {
		Mplane::BoardTx1OverTemperatureFaultMinor::NAME,
 	    Mplane::BoardTx2OverTemperatureFaultMinor::NAME,
 	    Mplane::BoardTx3OverTemperatureFaultMinor::NAME,
	    Mplane::BoardTx4OverTemperatureFaultMinor::NAME
    };

    // Update temperature faults for all Tx ports
    for (int index = 0; index < radio->getNumberOfTxPorts(); index++)
	{
		ITxPort& txPort = radio->getTxPort(index);
		float txTemperature = txPort.getTemperature().get();
	    bool   status;

		if ( temperatureThresholds[index] <= txTemperature )
		{
			// Temperature is greater than the allowed limit
			// Set the status to 1 to generate the fault.
			status = true;
		}
		else
		{
			status = false;
		}

		// pass to fault
		std::shared_ptr<IFault> faultTxOverMinor(faultsList->getFault(faultNames[index])) ;
		faultTxOverMinor->setStatus( status );
	}

    // TODO Update FPGA core temperature faults and PA faults
}
