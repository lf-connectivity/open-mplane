/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      UnderTempMajorFaultOwner.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "UnderTempMajorFaultOwner.h"

#include "IRadio.h"
#include "ITxPort.h"

#include "BoardTxUnderTemperatureFaultMajor.h"
#include "PaUnderTemperatureFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
UnderTempMajorFaultOwner::UnderTempMajorFaultOwner() :
	FaultOwner("UnderTempMajorFaultOwner", {Mplane::BoardTx1UnderTemperatureFaultMajor::NAME,
										   Mplane::BoardTx2UnderTemperatureFaultMajor::NAME,
										   Mplane::BoardTx3UnderTemperatureFaultMajor::NAME,
										   Mplane::BoardTx4UnderTemperatureFaultMajor::NAME,
										   Mplane::Pa1UnderTemperatureFaultMajor::NAME,
										   Mplane::Pa2UnderTemperatureFaultMajor::NAME,
										   Mplane::Pa3UnderTemperatureFaultMajor::NAME,
										   Mplane::Pa4UnderTemperatureFaultMajor::NAME}  ),
	Loggable("UnderTempMajorFaultOwner","FT")
{
}

//-------------------------------------------------------------------------------------------------------------
UnderTempMajorFaultOwner::~UnderTempMajorFaultOwner()
{
}

//-------------------------------------------------------------------------------------------------------------
void UnderTempMajorFaultOwner::updateFaults()
{
	updateUnderTempMajorFaults();
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::UnderTempMajorFaultOwner::updateUnderTempMajorFaults(void)
{
   /* *** Update the board temperature faults, if any exist. *** */
	std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;
	std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());

	// Array of temperature thresholds for Tx port
	const float temperatureThresholds[] =
	{
		BOARD_TX1_ALARM_UNDER_TEMP_MAJOR,
		BOARD_TX2_ALARM_UNDER_TEMP_MAJOR,
		BOARD_TX3_ALARM_UNDER_TEMP_MAJOR,
		BOARD_TX4_ALARM_UNDER_TEMP_MAJOR,
	};

	const char* faultNames[] =
	{
		Mplane::BoardTx1UnderTemperatureFaultMajor::NAME,
		Mplane::BoardTx2UnderTemperatureFaultMajor::NAME,
		Mplane::BoardTx3UnderTemperatureFaultMajor::NAME,
		Mplane::BoardTx4UnderTemperatureFaultMajor::NAME,
	};

	// Update temperature faults for all Tx ports
	for (int index = 0; index < radio->getNumberOfTxPorts(); index++)
	{
		ITxPort& txPort = radio->getTxPort(index);
		float txTemperature = txPort.getTemperature().get();
		bool   status;

		if ( temperatureThresholds[index] >= txTemperature )
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
		std::shared_ptr<IFault> faultTxUnderMajor(faultsList->getFault(faultNames[index])) ;
		faultTxUnderMajor->setStatus( status );
	}

	// TODO Update FPGA core temperature faults and PA faults

}
