/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaIrqTask.cpp
 * \brief
 *
 *
 * \details
 *
 * ATG requirement traceability. Do not remove.
 *
 * \satisfy{@req_8403{028}}
 * \satisfy{@req_8403{029}}
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/select.h>
#include <fcntl.h>
#include <signal.h>

#ifdef OFF_TARGET
#include "IFpgaIrqEmu.h"
#endif
#include "ILoggable.h"
#include "FpgaIrqTask.h"

using namespace Mplane;

//=============================================================================================================
// MACROS
//=============================================================================================================

#ifdef OFF_TARGET
#define devopen(path, flags) IFpgaIrqEmu::getInstance()->open(path, flags)
#else
#define devopen(path, flags) ::open(path, flags)
#endif

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const std::string DEV_PATH{"/dev/fpga-irq."} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaIrqTask::FpgaIrqTask(unsigned irqBit, FpgaIrqTaskFunction callback) :
	Task(Task::PRIORITY_HIGH, Task::SMALL_STACK,
		std::string("FpgaIrqTask." + std::to_string(irqBit)).c_str(),
		"FpgaIrqTask"
	),
    mIrqBit(irqBit),
    mCallback(callback),
    mDevFd(-1),
    mReadFd(-1),
    mWriteFd(-1),
    mShutdown(false)
{
//	std::cerr << "FpgaIrqTask() NEW @ " << this << std::endl ;

	// Block SIGPIPE signal so we can handle it via errno
	sigset_t blockSet, prevSet ;
	::sigemptyset(&blockSet) ;
	::sigaddset(&blockSet, SIGPIPE) ;
	::sigprocmask(SIG_BLOCK, &blockSet, &prevSet) ;

	// open a pipe
	int filedes[2] ;
	if (::pipe(filedes) != 0)
	{
		ILoggable::logEventWarning("FPGA IRQ bit %u - unable to open internal pipe. IRQ will not be monitored", mIrqBit) ;
		return ;
	}

	mReadFd = filedes[0] ;
	mWriteFd = filedes[1] ;

	// Open the device
	std::string path = DEV_PATH + std::to_string(mIrqBit) ;
	mDevFd = devopen(path.c_str(), O_RDONLY) ;
	if (mDevFd < 0)
	{
		ILoggable::logEventWarning("FPGA IRQ bit %u - unable to open device. IRQ will not be monitored", mIrqBit) ;
		return ;
	}

//	std::cerr << "Dev fd=" << mDevFd <<
//		" Write fd=" << mWriteFd <<
//		" Read fd=" << mReadFd <<
//		std::endl ;

	// self start
	start() ;
}

//-------------------------------------------------------------------------------------------------------------
FpgaIrqTask::~FpgaIrqTask()
{
//	std::cerr << "FpgaIrqTask() DEL @ " << this << std::endl ;
	mShutdown = true ;

	if (mWriteFd > 0)
	{
//		std::cerr << "FpgaIrqTask() DEL - write term to  mWriteFd=" << mWriteFd << std::endl ;
		char buff[8] = {0,0,0,0,0,0,0,0} ;
		::write(mWriteFd, buff, 1) ;
	}

//	std::cerr << "FpgaIrqTask() DEL - mWriteFd=" << mWriteFd << " mDevFd=" << mDevFd << " mReadFd=" << mReadFd << std::endl ;

	if (mDevFd > 0)
		::close(mDevFd) ;
	if (mReadFd > 0)
		::close(mReadFd) ;
	if (mWriteFd > 0)
		::close(mWriteFd) ;

//	std::cerr << "FpgaIrqTask() DEL @ " << this << " DONE"<< std::endl ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int FpgaIrqTask::run()
{
//	std::cerr << "FpgaIrqTask::run() @ " << this << std::endl ;
	while (!mShutdown)
	{
		int nfds = 0 ;
		fd_set fds ;
		FD_ZERO(&fds) ;

		FD_SET(mDevFd, &fds) ;
		if (mDevFd >= nfds)
			nfds = mDevFd + 1 ;
		FD_SET(mReadFd, &fds) ;
		if (mReadFd >= nfds)
			nfds = mReadFd + 1 ;

//		std::cerr << "select... @ " << this << " : DevFd=" << mDevFd << " mReadFd=" << mReadFd << std::endl ;
		int rc = ::select(nfds, &fds, NULL, NULL, NULL) ;
//		std::cerr << "select returned " << rc << " @ " << this <<
//				" dev=" << FD_ISSET(mDevFd, &fds) <<
//				" pipe=" << FD_ISSET(mReadFd, &fds) <<
//				std::endl ;
		if (rc < 0)
		{
//			std::cerr << "select error errno=" << errno << std::endl ;
			return 1 ;
		}

		if (FD_ISSET(mDevFd, &fds))
		{
			char buff[256] ;
//			std::cerr << "Reading.. " << mDevFd << std::endl ;
			int num = ::read(mDevFd, buff, sizeof(buff)) ;
//			std::cerr << "reading=" << num << std::endl ;
			if (num <= 0)
			{
//				std::cerr << "read failed errno=" << errno << std::endl ;
				return 1 ;
			}

			buff[num] = '\0' ;
//			std::cerr << "Calling callback.." << std::endl ;
			mCallback(buff) ;
		}
	}

//	std::cerr << "FpgaIrqTask::run() - done @ " << this << std::endl ;
	return 0 ;
}
