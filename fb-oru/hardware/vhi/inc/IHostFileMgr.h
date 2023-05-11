/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IHostFileMgr.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef COMMON_REMOTEPROC_INC_IHOSTFILEMGR_H_
#define COMMON_REMOTEPROC_INC_IHOSTFILEMGR_H_

#include <map>
#include <memory>
#include <vector>
#include "IHostFile.h"

namespace Mplane {

/*!
 * \class  IHostFileMgr
 * \brief
 * \details
 *
 */
class IHostFileMgr {
public:
	IHostFileMgr() {}
	virtual ~IHostFileMgr() {}

	/**
	 * Open a file with the given filename
	 */
	virtual int open(const std::string& filename, int flags, mode_t mode) =0 ;

	/**
	 * Close this file
	 */
	virtual int close(int fd) =0 ;

	/**
	 * Read from the file
	 */
	virtual int read(int fd, uint8_t* buffer, unsigned buffer_len) =0 ;

	/**
	 * Write to the file
	 */
	virtual int write(int fd, const uint8_t* buffer, unsigned buffer_len) =0 ;

	/**
	 * Get the IHostFile using the file descriptor
	 */
	virtual std::shared_ptr<IHostFile> hostFile(int fd) =0 ;

	/**
	 * Get the IHostFile using the file name
	 */
	virtual std::shared_ptr<IHostFile> hostFile(const std::string& filename) =0 ;

	/**
	 * Get the list of all files currently available
	 */
	virtual std::vector<std::shared_ptr<IHostFile>> hostFiles() =0 ;

} ;

}

#endif /* COMMON_REMOTEPROC_INC_IHOSTFILEMGR_H_ */
