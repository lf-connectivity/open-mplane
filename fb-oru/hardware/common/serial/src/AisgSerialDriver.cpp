/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AisgSerialDriver.cpp
 * \brief     Provides methods to access the serial device on the Aisg bus
 *
 *
 * \details   This file defines methods to access the serial device on the Aisg bus
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "AisgSerialDriver.h"
#include "ILoggable.h"
#include <sstream>
#include <iomanip>
#include <sys/select.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

const unsigned int AisgSerialDriver::AISG_TX_EN_BIT(1 << 9); //Pin 22 position is 31 - 22 = 9
const unsigned int AisgSerialDriver::AISG_RX_EN_N_BIT(1 << 5);//Pin 26 position is 31 - 26 = 5
const unsigned int AisgSerialDriver::AISG_TX_RX_MASK(0x0220); //Mask has both Tx and Rx en bits set

//=============================================================================================================
// Public functions
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
AisgSerialDriver::AisgSerialDriver(std::string devPath, unsigned int baud) :
			SerialDriver(devPath, baud),
			mGpio(CommonGpio::getInstance())
{
	//By default start listening
	setRx();
}

//-------------------------------------------------------------------------------------------------------------
bool AisgSerialDriver::write(unsigned char* data, unsigned int dataLen)
{
	std::lock_guard<std::mutex> guard(mMutex);

	bool ret = true;

	//Enable transmission
	setTx();

	//Write data
	int numBytesWritten = ::write(mDevFd, data, dataLen);

	//If write returns error or is not able to write the entire data, then return error
	if (numBytesWritten < 0 ||
	    (unsigned int)numBytesWritten != dataLen)
	{
		ret = false;
	}
	else
	{
		/*
		 * The drain system call has some random latency due to the way it is implemented.
		 * It checks for the transmitter empty after some delays (uses sleep).
		 * This can cause a context switch and random latency. If the drain takes time,
		 * then the direction change is delayed (Tx to Rx). This can cause ransom loss of initial
		 * few characters in the response.
		 * With the below do-while loop, the application checks for the transmitter empty flag itself.
		 * Though the implementation is not very efficient, it guarantees the latency of a
		 * transmission and changes the direction (Tx to Rx) in time such the the response is not missed.
		 */
		unsigned int lsr;
		do {
			::ioctl(mDevFd, TIOCSERGETLSR, &lsr);
		} while( !lsr & TIOCSER_TEMT );

		ret = drain();
		//Drain the data to the bus
		if (!ret)
		{
			ILoggable::logEventWarning("Aisg Write failed - Bytes written = %d, Bytes requested = %d, Error %d, %s", numBytesWritten, dataLen, errno, strerror(errno));
		}
	}

	//Enable reception
	setRx();

	if (ret)
	{
		std::stringstream txData;

		txData << "Aisg Tx:";

		for (unsigned int i = 0; i < dataLen; i++)
		{
			unsigned int val;
			val = static_cast<unsigned char>(data[i]);
			txData << "0x" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << val;
			txData << " ";
		}

		logDebugNormal("%s", txData.str().c_str());
	}

	return ret;
}

//-------------------------------------------------------------------------------------------------------------
void AisgSerialDriver::setTx(void)
{
	//Set Tx enable and Rx enable
	//Rx enable is active low, Tx enable is active high output
	mGpio->modifyRegister(CommonGpioRegs::GPIO_REG_OUTPUT_ADDR, (AISG_TX_EN_BIT | AISG_RX_EN_N_BIT), AISG_TX_RX_MASK);
}

//-------------------------------------------------------------------------------------------------------------
void AisgSerialDriver::setRx(void)
{
	//Reset Tx enable and Rx enable
	//Rx enable is active low, Tx enable is active high output
	mGpio->modifyRegister(CommonGpioRegs::GPIO_REG_OUTPUT_ADDR, 0, AISG_TX_RX_MASK);
}
