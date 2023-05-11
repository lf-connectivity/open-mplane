/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Rs485BusLinux.cpp
 * \brief     Base-level RS485 bus
 *
 *
 * \details   Base-level RS485 bus
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "Rs485BusLinux.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Rs485BusLinux::Rs485BusLinux(const std::string& devicePath, unsigned baud, std::shared_ptr<IBusLock> busLock,
		std::shared_ptr<IBusReadonlySettings> busSettings) :
	SerialBusLinux(devicePath, baud, busLock, busSettings)
{
	//By default start listening
	setRx();
}

//-------------------------------------------------------------------------------------------------------------
Rs485BusLinux::~Rs485BusLinux()
{
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Rs485BusLinux::doWriteData(const std::vector<uint8_t>& bytes)
{
	bool ret = true;
	unsigned dataLen;
	int numBytesWritten;

	//If device is opened, then only allow to write
	if (isOpen())
	{
		//Enable transmission
		setTx();

		dataLen = bytes.size();
		//Write the data
		numBytesWritten = ::write(mDevFd, bytes.data(), dataLen);

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
			 * then the direction change is delayed (Tx to Rx). This can cause random loss of initial
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

			//Enable reception
			setRx();
		}
	}
	else
	{
		//Enable reception
		setRx();

		return setError("SerialBusLinux::doWriteData failed - Device not opened");
	}

	if (!ret)
	{
		return setError("SerialBusLinux::doWriteData failed - Bytes written = " + std::to_string(numBytesWritten) +
				"Bytes requested = " + std::to_string(dataLen) + "Error : " + strerror(errno));
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------
void Rs485BusLinux::setTx(void)
{
}

//-------------------------------------------------------------------------------------------------------------
void Rs485BusLinux::setRx(void)
{
}
