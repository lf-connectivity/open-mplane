/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HostFileChannel.h
 * \brief     An IHostFile for special "channel" files
 *
 *
 * \details   An IHostFile for special "channel" files
 *
 */


#ifndef COMMON_REMOTEPROC_INC_HOSTFILECHANNEL_H_
#define COMMON_REMOTEPROC_INC_HOSTFILECHANNEL_H_

#include <map>
#include <functional>
#include "HostFileBase.h"

namespace Mplane {

/*!
 * \class  HostFileChannel
 * \brief
 * \details
 *
 */
class HostFileChannel : public HostFileBase {
public:
	HostFileChannel(const std::string& filename, int flags, mode_t mode) ;
	virtual ~HostFileChannel() ;

	/**
	 * Get just the name. For normal files this will be the same as the filename. For special files (e.g. channels) this will be a
	 * simplified name
	 */
	virtual std::string name() const override ;

	/**
	 * Add a write function to this channel
	 */
	virtual bool registerWriteFunc(const std::string& funcId, IHostFile::WriteFunc func) override ;

	/**
	 * Remove a write function from this channel
	 */
	virtual bool unregisterWriteFunc(const std::string& funcId) override ;

	/**
	 * Close this file
	 */
	virtual int close() override ;

	/**
	 * Read from the file
	 */
	virtual int read(uint8_t* buffer, unsigned buffer_len) override ;

	/**
	 * Write to the file
	 */
	virtual int write(const uint8_t* buffer, unsigned buffer_len) override ;

	/**
	 * Is this file a special "channel" ?
	 */
	virtual bool isChannel() const override ;

protected:
	static int mAllocatedChannelFd ; //<! FD reported back to the remote proc

	int mChanFd ; //<! Host fd used to store channel data in a file as well as it's "channel"
	bool mBinary ;
	bool mNoFile ; //<! if set then does NOT save data to file
	std::map<std::string, IHostFile::WriteFunc> mFuncs ;
	std::string mName ;
} ;

}

#endif /* COMMON_REMOTEPROC_INC_HOSTFILECHANNEL_H_ */
