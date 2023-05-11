/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Rs485BusFpga.cpp
 * \brief     Base-level Rs485 bus driven via the FPGA
 *
 *
 * \details   Base-level Rs485 bus driven via the FPGA
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <string.h>
#include <sstream>
#include <iomanip>
#include <unistd.h>
#include "Rs485BusFpga.h"
#include "ILoggable.h"
#include "Task.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Rs485BusFpga::Rs485BusFpga(const std::string& busName, const std::string& busDetails,
		unsigned baud, std::shared_ptr<IBusLock> busLock,
		std::shared_ptr<IBusReadonlySettings> busSettings) :
	SerialBusFpga(busName, busDetails, baud, busLock, busSettings)
{
	// Enable Rx and disable Tx
	mFpga->write_UartRxEnableControl(1);
	mFpga->write_UartTxEnableControl(0);
}

//-------------------------------------------------------------------------------------------------------------
Rs485BusFpga::~Rs485BusFpga()
{
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Rs485BusFpga::doWriteData(const std::vector<uint8_t>& bytes)
{
	unsigned int dataLen = bytes.size();
	unsigned int numBytesWritten = 0;
	bool timeout = false;

	// Enable Tx and disable Rx
	mFpga->write_UartRxEnableControl(0);
	mFpga->write_UartTxEnableControl(1);
	mFpga->write_UartAutoRxMode(0);

	// 1 byte data + start/stop bits = 10 bits
	// Block size * 10 = number of bits to transmit
	// Accounting the inter-byte delay, we times it by 4
	double maxDelayMs = ((double)(UART_BLOCK_SIZE * 10 * 4 * 1000) / baud());

	// Continue till all the bytes are written
	while (numBytesWritten < dataLen && timeout == false)
	{
		// Wait till the FIFO is empty
		int empty = mFpga->read_UartTxBufferEmpty();

		if (empty == false)
		{
			unsigned int retries = 0;

			// If FIFO contains data and the trigger is not asserted, then assert the trigger
			if (mFpga->read_UartFifoTrigger() == 0)
			{
				// Trigger transmission
				mFpga->write_UartFifoTrigger(1);
			}

			while (empty == false)
			{
				Task::msSleep(1);

				// After timeout stop trying
				retries++;
				if (retries >= maxDelayMs)
				{
					timeout = true;
					break;
				}
			}
		}

		if (timeout == false)
		{
			// Remove the transmit trigger till the data is being copied into the FIFO
			mFpga->write_UartFifoTrigger(0);

			// Write a block of data
			unsigned int numBytes = dataLen - numBytesWritten;
			if (numBytes > UART_BLOCK_SIZE)
			{
				numBytes = UART_BLOCK_SIZE;
			}

			std::stringstream txData;
			for (unsigned int index = 0; index < numBytes; index++)
			{
				mFpga->write_UartFifoWrite(bytes[numBytesWritten++]);
			}

			// If this is the last block, then set auto mode
			if (numBytesWritten == dataLen)
			{
				mFpga->write_UartAutoRxMode(1);
			}

			// Trigger transmission
			mFpga->write_UartFifoTrigger(1);
		}
	}

	if (timeout == false)
	{
		return true;
	}
	else
	{
		return setError("Transmission timed out - Transmit buffer not empty");
	}
}
