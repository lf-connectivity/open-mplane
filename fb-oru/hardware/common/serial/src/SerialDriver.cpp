/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SerialDriver.cpp
 * \brief     Provides methods to access the serial device
 *
 *
 * \details   This file defines methods to access the serial device
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <sys/select.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <termios.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "ILoggable.h"
#include "SerialDriver.h"

using namespace Mplane;
//=============================================================================================================
// Public functions
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SerialDriver::SerialDriver(std::string devPath, unsigned int baud) :
			Task(Task::PRIORITY_DEFAULT, Task::MEDIUM_STACK,
				(std::string("SerialDriverTask.") + devPath).c_str(),
				"SerialDriverTask"
			),
			mData(SerialData(256)),
			mDevPath(devPath),
			mBaud(baud)
{
	mDevFd = -1;
	mReadFd = -1;
	mWriteFd = -1;
	mShutdown = false;

	// Block SIGPIPE signal so we can handle it via errno
	sigset_t blockSet, prevSet ;
	::sigemptyset(&blockSet) ;
	::sigaddset(&blockSet, SIGPIPE) ;
	::sigprocmask(SIG_BLOCK, &blockSet, &prevSet) ;

	// open a pipe
	int filedes[2] ;
	if (::pipe(filedes) != 0)
	{
		ILoggable::logEventWarning("Serial driver %s - unable to open internal pipe. Serial driver cannot be used", mDevPath.c_str()) ;
		return ;
	}

	mReadFd = filedes[0] ;
	mWriteFd = filedes[1] ;

	// Open the device
	mDevFd = ::open(mDevPath.c_str(), O_RDWR | O_NOCTTY | O_SYNC) ;
	if (mDevFd < 0)
	{
		ILoggable::logEventWarning("Serial driver %s - unable to open device. Error:%d %s", mDevPath.c_str(), errno, strerror(errno)) ;
		return ;
	}

	//configure the terminal device
	if (configure() == false)
	{
		ILoggable::logEventWarning("Serial driver %s - unable to configure device", mDevPath.c_str()) ;
		return ;
	}

	// self start
	start() ;
}

//-------------------------------------------------------------------------------------------------------------
SerialDriver::~SerialDriver(void)
{
	mShutdown = true ;

	//Send a dummy packet to the pipe so that select will unblock
	if (mWriteFd > 0)
	{
		char buff[8] = {0,0,0,0,0,0,0,0} ;
		::write(mWriteFd, buff, 1) ;
	}

	//Close the open device and the pipe
	if (mDevFd > 0)
		::close(mDevFd) ;
	if (mReadFd > 0)
		::close(mReadFd) ;
	if (mWriteFd > 0)
		::close(mWriteFd) ;
}

//-------------------------------------------------------------------------------------------------------------
bool SerialDriver::isOpen(void)
{
	return (mDevFd > 0);
}

//-------------------------------------------------------------------------------------------------------------
bool SerialDriver::write(unsigned char* data, unsigned int dataLen)
{
	bool ret = true;

	//If device is opened, then only allow to write
	if (isOpen())
	{
		//Write the data
		int numBytesWritten = ::write(mDevFd, data, dataLen);

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

			if (!ret)
			{
				ILoggable::logEventWarning("Aisg Write failed - Bytes written = %d, Bytes requested = %d, Error %d, %s", numBytesWritten, dataLen, errno, strerror(errno));
			}
		}
	}
	else
	{
		ret = false;
	}

	return ret;
}

//-------------------------------------------------------------------------------------------------------------
SerialData SerialDriver::getSerialData( void )
{
	return mData;
}

//-------------------------------------------------------------------------------------------------------------
bool SerialDriver::configure(void)
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
	switch (mBaud)
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
bool SerialDriver::drain(void)
{
	if (::tcdrain(mDevFd) != 0)
	{
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool SerialDriver::flush(void)
{
	if (::tcflush(mDevFd, TCIFLUSH) != 0)
	{
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------
int SerialDriver::run(void)
{
	while (!mShutdown)
	{
		int nfds = 0 ;
		fd_set fds ;
		FD_ZERO(&fds) ;

		//Add the serial driver descriptor to the list of file descriptors
		FD_SET(mDevFd, &fds) ;
		//Increment the number of file descriptors
		if (mDevFd >= nfds)
			nfds = mDevFd + 1 ;
		//Add the read pipe descriptor to the list of file descriptors
		FD_SET(mReadFd, &fds) ;
		if (mReadFd >= nfds)
			nfds = mReadFd + 1 ;

		//Wait for either the pipe or the serial driver to have some data
		int rc = ::select(nfds, &fds, NULL, NULL, NULL) ;
		//If error occurs, then return
		if (rc < 0)
		{
			return 1 ;
		}

		//Check if select unblocked because of serial driver having data
		if (FD_ISSET(mDevFd, &fds))
		{
			std::vector<unsigned char> buff;
			buff.resize(256);
			//Read from the serial driver
			int num = ::read(mDevFd, buff.data(), buff.size()) ;
			if (num <= 0)
			{
				ILoggable::logEventWarning("Aisg Read failed. Error:%d %s", errno, strerror(errno));
				return 1 ;
			}
			else
			{
				buff.resize(num);
				//Copy the received data into the SerialData container
				mData.setData(buff);

				//Notify observers about received serial data
				notify();

				std::stringstream rxData;

				rxData << "Aisg Rx:";

				for (int i = 0; i < num; i++)
				{
					unsigned int val;
					val = static_cast<unsigned char>(buff[i]);
					rxData << "0x" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << val;
					rxData << " ";
				}

				logDebugNormal("%s", rxData.str().c_str());

				//Clear serial data
				mData.clearData();
			}
		}
	}

	return 0 ;
}
