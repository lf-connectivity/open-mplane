/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FileLock.h
 * \brief     File lock RAII class
 *
 *
 * \details   Used only for testing purposes. Locks/unlocks a specific file to coordinate access
 * 			for external resources between multiple test programs
 *
 */


#ifndef FILELOCK_H_
#define FILELOCK_H_

#include <string>

namespace Mplane {

/*!
 * \class FileLock
 */
class FileLock {
public:
	explicit FileLock(const std::string& name) ;
	virtual ~FileLock() ;

	/**
	 * Lock the file - blocks until file is locked
	 * @return true if locked; false on failure
	 */
	virtual bool lock() ;

	/**
	 * Locks the file - blocks until file is locked, or until timed out
	 * @param timeoutMs
	 * @return true if locked; false on failure
	 */
	virtual bool lock(unsigned timeoutMs) ;

	/**
	 * Unlock the file
	 */
	virtual bool unlock() ;

	/**
	 * Get current state
	 */
	virtual bool isLocked() const ;

private:
	// internal method used to call the appropriate system call
	int applyLock(int cmd, short type) ;

private:
	bool mLocked ;
	int mFd ;
} ;

}

#endif /* FILELOCK_H_ */
