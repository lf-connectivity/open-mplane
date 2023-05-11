/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SerialBusLinux.cpp
 * \brief     Base-level serial bus
 *
 *
 * \details   Base-level serial bus
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
#include <sstream>
#include <iomanip>
#include <unistd.h>
#include "SerialBusLinux.h"
#include "ILoggable.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SerialBusLinux::SerialBusLinux(const std::string& devicePath, unsigned baud, std::shared_ptr<IBusLock> busLock,
		std::shared_ptr<IBusReadonlySettings> busSettings) :
	SerialBus("Linux Serial bus", devicePath, baud, busLock, busSettings),
	mDevicePath(devicePath)
{
	// Open the device
	mDevFd = ::open(mDevicePath.c_str(), O_RDWR | O_NOCTTY | O_SYNC) ;
	if (mDevFd < 0)
	{
		ILoggable::logEventWarning("Serial device %s - unable to open device. Error:%s", mDevicePath.c_str(), strerror(errno)) ;
		return ;
	}

	//configure the terminal device
	if (configure() == false)
	{
		ILoggable::logEventWarning("Serial driver %s - unable to configure device", mDevicePath.c_str()) ;
		return ;
	}
}

//-------------------------------------------------------------------------------------------------------------
SerialBusLinux::~SerialBusLinux()
{
	if (mDevFd >= 0)
	{
		close(mDevFd);
	}
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool SerialBusLinux::isOpen(void)
{
	return (mDevFd > 0);
}

//-------------------------------------------------------------------------------------------------------------
bool SerialBusLinux::doWriteData(const std::vector<uint8_t>& bytes)
{
	bool ret = true;
	unsigned dataLen;
	int numBytesWritten;

	//If device is opened, then only allow to write
	if (isOpen())
	{
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
			//Drain the data to the bus
			ret = drain();
		}
	}
	else
	{
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
bool SerialBusLinux::doReadData(std::vector<uint8_t>& bytes, unsigned numBytes)
{
	if (numBytes == 0)
	{
		bytes.resize(64);
	}
	else
	{
		bytes.resize(numBytes);
	}

	//Read from the serial driver
	int num = ::read(mDevFd, bytes.data(), bytes.size()) ;
	if (num <= 0)
	{
		return setError("SerialBusLinux::doReadData failed - " + std::string(strerror(errno)));
	}
	else
	{
		bytes.resize(num);
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool SerialBusLinux::configure(void)
{
	struct termios setting;
	bool ret = true;

	memset(&setting, 0, sizeof(setting));

	//Ignore framing and [parity errors
	setting.c_iflag = IGNPAR;

	//Set output mode flags to 0
	setting.c_oflag = 0;

	//Set character size as 8 bit, ignore modem control lines and enable receiver
	setting.c_cflag = CS8 | CLOCAL | CREAD;

	//Set baud rate
	switch (baud())
	{
	case 115200:
		setting.c_cflag |= B115200;
		break;

	case 57600:
		setting.c_cflag |= B57600;
		break;

	case 38400:
		setting.c_cflag |= B38400;
		break;

	case 19200:
		setting.c_cflag |= B19200;
		break;

	case 9600:
		setting.c_cflag |= B9600;
		break;

	//If baud rate is invalid, then return false;
	default:
		return false;
	}

	//Set local mode flags as 0
	setting.c_lflag = 0;

	//Set VTIME set to 0.1 and VMIN to 0 which means that read system call
	//should return after timeout specified in VTIME or when single byte of data is available
	setting.c_cc[VTIME] = 0.1;
	setting.c_cc[VMIN] = 0;

	//Flush the data in the input buffer
	(void)flush();

	//Set new attributes
	if (::tcsetattr(mDevFd, TCSANOW, &setting) != 0)
	{
		ret = false;
	}

	return ret;
}

//-------------------------------------------------------------------------------------------------------------
bool SerialBusLinux::drain(void)
{
	if (::tcdrain(mDevFd) != 0)
	{
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool SerialBusLinux::flush(void)
{
	if (::tcflush(mDevFd, TCIFLUSH) != 0)
	{
		return false;
	}

	return true;
}
