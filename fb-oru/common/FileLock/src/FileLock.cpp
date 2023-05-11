/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FileLock.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include "Task.h"
#include "Path.h"
#include "FileLock.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
static const std::string LOCK_DIR{"/tmp/FileLock/"} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FileLock::FileLock(const std::string& name) :
	mLocked(false),
	mFd(-1)
{
	Path::mkpath(LOCK_DIR) ;
	std::string filename(LOCK_DIR + name) ;
	mFd = ::open(filename.c_str(), O_RDWR | O_CREAT, 0666) ;

//	std::cerr << "FileLock(" <<filename <<") fd=" << mFd << " err=" << errno << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
FileLock::~FileLock()
{
	unlock() ;

	if (mFd > 0)
	{
		::close(mFd) ;
		mFd = -1 ;
	}
}

//-------------------------------------------------------------------------------------------------------------
bool FileLock::lock()
{
	if (mLocked)
		return true ;

	if (mFd < 0)
		return false ;

	if (applyLock(F_SETLKW, F_LOCK) != 0)
		return false ;

	mLocked = true ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileLock::lock(unsigned timeoutMs)
{
	if (mLocked)
		return true ;

	if (mFd < 0)
		return false ;

	while ( applyLock(F_SETLK, F_LOCK) != 0)
	{
		if (errno == EAGAIN || errno == EACCES)
		{
			// locked - run timeout
			Task::msSleep(1) ;
			if (timeoutMs <= 1)
				return false ;

			--timeoutMs ;
			continue ;
		}

		// failed
		return false ;
	}

	mLocked = true ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileLock::unlock()
{
	if (!mLocked)
		return true ;

	if (mFd < 0)
		return false ;

	if (applyLock(F_SETLKW, F_UNLCK) != 0)
		return false ;

	mLocked = false ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileLock::isLocked() const
{
	return mLocked ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int FileLock::applyLock(int cmd, short type)
{
	struct flock fl ;
	fl.l_type = type ;
	fl.l_start = 0 ;
	fl.l_len = 0 ;
	fl.l_whence = SEEK_SET ;

	return fcntl(mFd, cmd, &fl) ;
}
