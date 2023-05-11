/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaSRxAttenuatorBus.cpp
 * \brief     Bus interface to the SRx attenuator via the FPGA
 *
 *
 * \details   Bus interface to the SRx attenuator via the FPGA
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <string.h>
#include <iostream>
#include "FpgaSRxAttenuatorBus.h"
#include "Task.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================
// 5ms timeout
static const unsigned SPI_DONE_TIMEOUT_MS{5} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaSRxAttenuatorBus::FpgaSRxAttenuatorBus(const std::string& busName, const std::string& busDetails, std::shared_ptr<IBusLock> busLock,
		std::shared_ptr<ISpiBusReadonlySettings> busSettings, unsigned index) :
		SpiBus(busName, busDetails, busLock, busSettings),
		mFpga(IFpgaMgr::getIFpgaAntennaRegs()),
		mIndex( index )
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaSRxAttenuatorBus::~FpgaSRxAttenuatorBus()
{
}


//=============================================================================================================
// PROTECTED HOOKS
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
bool FpgaSRxAttenuatorBus::doWriteByte(uint32_t offset, uint8_t byte)
{
	/// Set the attenuation value
	mFpga->write_srxAtten(mIndex, byte);

	/// Toggle the attenuation update bit
	mFpga->write_srxAttenUpdate(mIndex, (unsigned int)0);
	usleep(50);
	mFpga->write_srxAttenUpdate(mIndex, (unsigned int)1);

    unsigned timeMs = 0;

	do
	{
		// check whether the access is complete
		if (mFpga->read_srxAttenDone(mIndex))
		{
			return true;
		}

		// Sleep for 1ms
		Task::msSleep(1) ;
		timeMs++;

	} while (timeMs <= SPI_DONE_TIMEOUT_MS) ;

	// If SPI transaction is not complete within the timeout, then return false
	return false;
}
