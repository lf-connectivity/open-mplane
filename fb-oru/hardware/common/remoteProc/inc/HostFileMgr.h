/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HostFileMgr.h
 * \brief     Manager for IHostFile objects
 *
 *
 * \details   Manager for IHostFile objects
 *
 */


#ifndef COMMON_REMOTEPROC_INC_HOSTFILEMGR_H_
#define COMMON_REMOTEPROC_INC_HOSTFILEMGR_H_

#include "IHostFileMgr.h"

namespace Mplane {

/*!
 * \class  HostFileMgr
 * \brief
 * \details
 *
 */
class HostFileMgr : public virtual IHostFileMgr {
public:
	HostFileMgr() ;
	virtual ~HostFileMgr() ;

	/**
	 * Open a file with the given filename
	 */
	virtual int open(const std::string& filename, int flags, mode_t mode) override ;

	/**
	 * Close this file
	 */
	virtual int close(int fd) override ;

	/**
	 * Read from the file
	 */
	virtual int read(int fd, uint8_t* buffer, unsigned buffer_len) override ;

	/**
	 * Write to the file
	 */
	virtual int write(int fd, const uint8_t* buffer, unsigned buffer_len) override ;

	/**
	 * Get the IHostFile using the file descriptor
	 */
	virtual std::shared_ptr<IHostFile> hostFile(int fd) override ;

	/**
	 * Get the IHostFile using the file name
	 */
	virtual std::shared_ptr<IHostFile> hostFile(const std::string& filename) override ;

	/**
	 * Get the list of all files currently available
	 */
	virtual std::vector<std::shared_ptr<IHostFile>> hostFiles() override ;

private:
	void addFile(std::shared_ptr<IHostFile> file) ;
	void delFile(std::shared_ptr<IHostFile> file) ;


private:
	std::map<int, std::shared_ptr<IHostFile>> mFiles ;
	std::map<std::string, std::shared_ptr<IHostFile>> mFileNames ;

} ;

}

#endif /* COMMON_REMOTEPROC_INC_HOSTFILEMGR_H_ */
