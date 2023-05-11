/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaIrqDevice.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
//#include <signal.h>
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

#include <iostream>

#include "FpgaIrqDevice.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaIrqDevice::FpgaIrqDevice(unsigned bitNum) :
	mBitNum(bitNum),
	mPipeList()
{
	std::cerr << "FpgaIrqDevice NEW " << mBitNum << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
FpgaIrqDevice::~FpgaIrqDevice()
{
	std::cerr << "FpgaIrqDevice DEL " << mBitNum << std::endl ;

	// close all of this end file descriptors
	for (auto entry : mPipeList)
	{
		::close(entry.second) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
int FpgaIrqDevice::open(const char* pathname, int flags)
{
	int filedes[2] ;
	int rc = ::pipe(filedes) ;
	if (rc != 0)
		return rc ;

	// [0] = read end (app); [1] = write end (this)
	mPipeList[ filedes[0] ] = filedes[1] ;

std::cerr << "FpgaIrqDevice::open(" << pathname << ") fd=" << filedes[0] << " (pipe fd=" << filedes[1] << ") Pipe List size=" << mPipeList.size() << std::endl ;
	return filedes[0] ;
}

//-------------------------------------------------------------------------------------------------------------
int FpgaIrqDevice::close(int fd)
{
std::cerr << "FpgaIrqDevice::close() fd=" << fd << std::endl ;
	auto entry(mPipeList.find(fd)) ;
	if (entry == mPipeList.end())
		return -1 ;

	::close(entry->second) ;
	mPipeList.erase(entry) ;

std::cerr << "FpgaIrqDevice::close() fd=" << fd << " (pipe fd=" << entry->second << ") Pipe List size=" << mPipeList.size() << std::endl ;
	return 0 ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaIrqDevice::raiseIrq()
{
	struct timeval tv ;
	gettimeofday(&tv, NULL);

	char buff[128] ;
	::snprintf(buff, sizeof(buff), "%u.%06u\n", (unsigned)tv.tv_sec, (unsigned)tv.tv_usec) ;
	unsigned size(::strlen(buff)) ;

	std::cerr << "FpgaIrqDevice::raiseIrq() Pipe List size=" << mPipeList.size() << std::endl ;

//	// Ignore SIGPIPE
//	sigset_t blockSet, prevSet ;
//	::sigemptyset(&blockSet) ;
//	::sigaddset(&blockSet, SIGPIPE) ;
//	::sigprocmask(SIG_BLOCK, &blockSet, &prevSet) ;

	// send buffer to all listeners
	std::map<int, int> newPipeList ;
	for (auto entry : mPipeList)
	{
		std::cerr << "FpgaIrqDevice::raiseIrq() pipe fd=" << entry.second << std::endl ;

		int flags = fcntl(entry.second, F_GETFL);
		std::cerr << std::hex << "flags = 0x" << flags << std::dec << std::endl ;

		int num = ::write(entry.second, buff, size) ;
		if (num == (int)size)
		{
			newPipeList[entry.first] = entry.second ;
			continue ;
		}

		std::cerr << "Failed write on fd=" << entry.second << " status=" << num << " errno=" << errno << std::endl ;
	}
	mPipeList = newPipeList ;

//	// Restore
//	::sigprocmask(SIG_SETMASK, &prevSet, NULL) ;
}
