/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HostFileStd.h
 * \brief     A stdXXX Linux file on the host
 *
 *
 * \details   A stdXXX Linux file on the host
 *
 */


#ifndef COMMON_REMOTEPROC_INC_HOSTFILESTD_H_
#define COMMON_REMOTEPROC_INC_HOSTFILESTD_H_

#include "HostFileLinux.h"

namespace Mplane {

/*!
 * \class  HostFile
 * \brief
 * \details
 *
 */
class HostFileStd : public HostFileLinux {
public:
	HostFileStd(int fd, const std::string &filename, int flags) :
		HostFileLinux(filename, flags, 0)
	{
		setFd(fd) ;
	}
	virtual ~HostFileStd() {}

	/**
	 * Close this file
	 */
	virtual int close() override { return 0; }

	/**
	 * Should this file be "freed" when it is closed. Used by the host file manager
	 */
	virtual bool freeOnClose() const override { return false; }


} ;

}

#endif /* COMMON_REMOTEPROC_INC_HOSTFILESTD_H_ */
