/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HostFileBase.h
 * \brief     Represent a file on the host system
 *
 *
 * \details   Represent a file on the host system
 *
 */


#ifndef COMMON_REMOTEPROC_INC_HOSTFILEBASE_H_
#define COMMON_REMOTEPROC_INC_HOSTFILEBASE_H_

#include "IHostFile.h"

namespace Mplane {

/*!
 * \class  HostFile
 * \brief
 * \details
 *
 */
class HostFileBase : public virtual IHostFile {
public:
	HostFileBase(const std::string& filename, int flags, mode_t mode) ;
	virtual ~HostFileBase() ;

	/**
	 * Get the filename
	 */
	virtual std::string filename() const override ;

	/**
	 * Get just the name. For normal files this will be the same as the filename. For special files (e.g. channels) this will be a
	 * simplified name
	 */
	virtual std::string name() const override ;

	/**
	 * Get the allocated file descriptor
	 */
	virtual int fd() const override ;

	/**
	 * Get flags
	 */
	virtual int flags() const override ;

	/**
	 * Get mode
	 */
	virtual mode_t mode() const override ;

	/**
	 * Close this file
	 */
	virtual int close() =0 ;

	/**
	 * Read from the file
	 */
	virtual int read(uint8_t* buffer, unsigned buffer_len) =0 ;

	/**
	 * Write to the file
	 */
	virtual int write(const uint8_t* buffer, unsigned buffer_len) =0 ;

	/**
	 * Should this file be "freed" when it is closed. Used by the host file manager
	 */
	virtual bool freeOnClose() const override ;

	/**
	 * Is this file a special "channel" ?
	 */
	virtual bool isChannel() const override ;

	/**
	 * Add a write function to this channel
	 */
	virtual bool registerWriteFunc(const std::string& funcId, IHostFile::WriteFunc func) override ;

	/**
	 * Remove a write function from this channel
	 */
	virtual bool unregisterWriteFunc(const std::string& funcId) override ;


protected:
	void setFd(int fd) ;

private:
	std::string mFilename ;
	int mFlags ;
	mode_t mMode ;
	int mFd ;
} ;

}

#endif /* COMMON_REMOTEPROC_INC_HOSTFILEBASE_H_ */
