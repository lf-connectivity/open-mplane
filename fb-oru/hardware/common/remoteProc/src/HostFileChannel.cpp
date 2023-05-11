/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HostFileChannel.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include <limits>
#include <algorithm>

#include "stringfunc.hpp"
#include "Path.h"
#include "HostFileChannel.h"

using namespace Mplane;


//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int HostFileChannel::mAllocatedChannelFd = std::numeric_limits<int>::max() -1 ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
HostFileChannel::HostFileChannel(const std::string &filename, int flags, mode_t mode) :
	HostFileBase(filename, flags, mode),
	mChanFd(-1),
	mBinary(false),
	mNoFile(false),
	mFuncs(),
	mName(filename)
{
	setFd(HostFileChannel::mAllocatedChannelFd--) ;

	// Open the filename to also store the data - skip starting '>' control char
	std::string fname(filename.substr(1)) ;
	mName = Path::basename(fname) ;

	// Check for any trailing ':' modifiers
	std::size_t pos(fname.find(':')) ;
	if (pos != std::string::npos)
	{
		std::vector<std::string> modifiers(splitStr(fname.substr(pos+1), ':')) ;
		fname = fname.substr(0, pos) ;
		for (auto& mod : modifiers)
		{
			if (mod == "binary")
				mBinary = true ;
			else if (mod == "text")
				mBinary = false ;
			else if (mod == "nofile")
				mNoFile = true ;
		}

		pos = mName.find(':') ;
		mName = mName.substr(0, pos) ;
	}

	// remove extension from name
	pos = mName.find_last_of('.') ;
	if (pos != std::string::npos)
		mName = mName.substr(0, pos) ;

#ifdef OFF_TARGET
	// for simulation keep all files in the app directory
	fname = Path::basename(fname) ;
#endif

	if (!mNoFile)
		mChanFd = ::open(fname.c_str(), flags, mode) ;

//std::cerr << "NEW HostFileChannel " << filename << " (" << fname << ") chan fd=" << mChanFd << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
std::string HostFileChannel::name() const
{
	return mName ;
}

//-------------------------------------------------------------------------------------------------------------
HostFileChannel::~HostFileChannel()
{
}

//-------------------------------------------------------------------------------------------------------------
int HostFileChannel::close()
{
	if (mChanFd > 0)
		::close(mChanFd) ;

	setFd(-1) ;
	mChanFd = -1 ;
	return 0 ;
}

//-------------------------------------------------------------------------------------------------------------
int HostFileChannel::read(uint8_t* buffer, unsigned buffer_len)
{
	return -EACCES ;
}

//-------------------------------------------------------------------------------------------------------------
int HostFileChannel::write(const uint8_t* buffer, unsigned buffer_len)
{
	int rc(0) ;

	// for now just write to stdout if not binary
	if (!mBinary)
	{
		rc = ::write(STDOUT_FILENO, buffer, buffer_len) ;
		if (rc < 0)
			return rc ;
	}

	// write to channel file (if open)
	if (mChanFd > 0)
	{
		rc = ::write(mChanFd, buffer, buffer_len) ;
		if (rc < 0)
			return rc ;
	}

	// use any registered functions
	for (auto& entry : mFuncs)
	{
		int rc = entry.second(buffer, buffer_len) ;
		if (rc < 0)
			return rc ;
	}

	return 0 ;
}

//-------------------------------------------------------------------------------------------------------------
bool HostFileChannel::registerWriteFunc(const std::string& funcId, IHostFile::WriteFunc func)
{
	auto entry(mFuncs.find(funcId)) ;
	if (entry != mFuncs.end())
	{
		entry->second = func ;
		return true ;
	}

	mFuncs[funcId] = func ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool HostFileChannel::unregisterWriteFunc(const std::string& funcId)
{
	auto entry(mFuncs.find(funcId)) ;

	if (entry == mFuncs.end())
		return false ;

	mFuncs.erase(funcId) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool HostFileChannel::isChannel() const
{
	return true ;
}
