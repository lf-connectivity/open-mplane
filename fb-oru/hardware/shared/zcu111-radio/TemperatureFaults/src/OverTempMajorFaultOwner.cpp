/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OverTempMajorFaultOwner.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "OverTempMajorFaultOwner.h"

#include "IRadio.h"
#include "ITxPort.h"
#include "IPa.h"

#include "BoardTxOverTemperatureFaultMajor.h"
#include "PaOverTemperatureFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
OverTempMajorFaultOwner::OverTempMajorFaultOwner() :
	FaultOwner("OverTempMajorFaultOwner", {Mplane::BoardTx1OverTemperatureFaultMajor::NAME,
										   Mplane::BoardTx2OverTemperatureFaultMajor::NAME,
										   Mplane::BoardTx3OverTemperatureFaultMajor::NAME,
										   Mplane::BoardTx4OverTemperatureFaultMajor::NAME,
					                       Mplane::Pa1OverTemperatureFaultMajor::NAME,
										   Mplane::Pa2OverTemperatureFaultMajor::NAME,
										   Mplane::Pa3OverTemperatureFaultMajor::NAME,
								           Mplane::Pa4OverTemperatureFaultMajor::NAME} ),
   Loggable("OverTempMajorFaultOwner","FT")
{
}

//-------------------------------------------------------------------------------------------------------------
OverTempMajorFaultOwner::~OverTempMajorFaultOwner()
{
}

//-------------------------------------------------------------------------------------------------------------
void OverTempMajorFaultOwner::updateFaults()
{
	updateOverTempMajorFaults();
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::OverTempMajorFaultOwner::updateOverTempMajorFaults(void)
{
    /* *** Update the board temperature faults, if any exist. *** */
    std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());

    // Array of temperature thresholds for Tx port
    const float temperatureThresholds[] =
    {
		BOARD_TX1_ALARM_OVER_TEMP_MAJOR,
		BOARD_TX2_ALARM_OVER_TEMP_MAJOR,
		BOARD_TX3_ALARM_OVER_TEMP_MAJOR,
		BOARD_TX4_ALARM_OVER_TEMP_MAJOR,
    };

    const char* faultNames[] =
    {
    	Mplane::BoardTx1OverTemperatureFaultMajor::NAME,
		Mplane::BoardTx2OverTemperatureFaultMajor::NAME,
		Mplane::BoardTx3OverTemperatureFaultMajor::NAME,
		Mplane::BoardTx4OverTemperatureFaultMajor::NAME,
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
		std::shared_ptr<IFault> faultTxOverMajor(faultsList->getFault(faultNames[index])) ;
		faultTxOverMajor->setStatus( status );
	}

    // TODO Update FPGA core temperature faults and PA faults
}
