/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HostFile.h
 * \brief     Represent a file on the host system
 *
 *
 * \details   Represent a file on the host system
 *
 */


#ifndef COMMON_REMOTEPROC_INC_IHOSTFILE_H_
#define COMMON_REMOTEPROC_INC_IHOSTFILE_H_

#include <sys/stat.h>
#include <cstdint>
#include <memory>
#include <functional>

namespace Mplane {

/*!
 * \class  IHostFile
 * \brief
 * \details
 *
 */
class IHostFile {
public:
	IHostFile() {}
	virtual ~IHostFile() {}

	/**
	 * Factory. Create a new host file based on the filename
	 */
	static std::shared_ptr<IHostFile> factory(const std::string& name, int flags, mode_t mode) ;

	/**
	 * Get the filename
	 */
	virtual std::string filename() const =0 ;

	/**
	 * Get just the name. For normal files this will be the same as the filename. For special files (e.g. channels) this will be a
	 * simplified name
	 */
	virtual std::string name() const =0 ;

	/**
	 * Get flags
	 */
	virtual int flags() const =0 ;

	/**
	 * Get mode
	 */
	virtual mode_t mode() const =0 ;

	/**
	 * Get the allocated file descriptor
	 */
	virtual int fd() const =0 ;

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
	virtual bool freeOnClose() const =0 ;

	/**
	 * Is this file a special "channel" ?
	 */
	virtual bool isChannel() const =0 ;


	using WriteFunc = std::function<int(const uint8_t* buffer, unsigned buffer_len)> ;

	/**
	 * Add a write function to this channel
	 */
	virtual bool registerWriteFunc(const std::string& funcId, WriteFunc func) =0 ;

	/**
	 * Remove a write function from this channel
	 */
	virtual bool unregisterWriteFunc(const std::string& funcId) =0 ;


} ;

}

#endif /* COMMON_REMOTEPROC_INC_HOSTFILEBASE_H_ */
