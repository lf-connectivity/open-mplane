/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SerialBusFpga.cpp
 * \brief     Base-level serial bus driven via the FPGA
 *
 *
 * \details   Base-level serial bus driven via the FPGA
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <string.h>
#include <sstream>
#include <iomanip>
#include <unistd.h>
#include "SerialBusFpga.h"
#include "ILoggable.h"
#include "Task.h"

using namespace Mplane;

const unsigned int SerialBusFpga::UART_BLOCK_SIZE(64);

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SerialBusFpga::SerialBusFpga(const std::string& busName, const std::string& busDetails,
		unsigned baud, std::shared_ptr<IBusLock> busLock,
		std::shared_ptr<IBusReadonlySettings> busSettings) :
	SerialBus(busName, busDetails, baud, busLock, busSettings),
	mFpga(IFpgaMgr::getIFpgaSystemRegs())
{
	// Reset the Tx and Rx FIFO
	mFpga->write_UartRxFifoReset(1);
	mFpga->write_UartTxFifoReset(1);

	// Set manual mode for Tx and Rx enable
	mFpga->write_UartAutoRxMode(0);

	// Enable Tx and Rx
	mFpga->write_UartRxEnableControl(1);
	mFpga->write_UartTxEnableControl(1);

	// Remove the reset
	mFpga->write_UartRxFifoReset(0);
	mFpga->write_UartTxFifoReset(0);
}

//-------------------------------------------------------------------------------------------------------------
SerialBusFpga::~SerialBusFpga()
{
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool SerialBusFpga::doWriteData(const std::vector<uint8_t>& bytes)
{
	unsigned int dataLen = bytes.size();
	unsigned int numBytesWritten = 0;
	bool timeout = false;

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

			for (unsigned int index = 0; index < numBytes; index++)
			{
				mFpga->write_UartFifoWrite(bytes[numBytesWritten++]);
			}

			// Trigger transmission
			mFpga->write_UartFifoTrigger(1);
		}
	}
	return (timeout == false);
}

//-------------------------------------------------------------------------------------------------------------
bool SerialBusFpga::doReadData(std::vector<uint8_t>& bytes, unsigned numBytes)
{
	if (numBytes == 0)
	{
		numBytes = UART_BLOCK_SIZE;
	}

	bytes.resize(numBytes);

	// Read from the Fpga
	unsigned int index = 0;
	int present = true;

	// Loop till either there is no more data or numBytes are read
	while (present)
	{
		present = mFpga->read_UartRxDataPresent();

		// If data is present, then read one byte and add to the vector
		if (present)
		{
			uint8_t data = mFpga->read_UartFifoRead();
			bytes[index++] = data;

			// If the number of required bytes are read, then stop reading
			if (index >= numBytes)
			{
				break;
			}
		}
	}

	// Resize the vector as per the actual number of bytes read
	bytes.resize(index);

	// Check that there were no Rx errors
	int overrun = mFpga->read_UartRxOverrunError();
	int frameErr = mFpga->read_UartRxFrameError();

	if (overrun != 0)
	{
		return setError("Rx Overrun flag set");
	}
	else if (frameErr != 0)
	{
		return setError("Rx frame error flag set");
	}
	return true;
}
