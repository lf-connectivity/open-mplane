/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HostFileLinux.h
 * \brief     An IHostFile for any Linux file
 *
 *
 * \details   An IHostFile for any Linux file
 *
 */


#ifndef COMMON_REMOTEPROC_INC_HOSTFILELINUX_H_
#define COMMON_REMOTEPROC_INC_HOSTFILELINUX_H_

#include "HostFileBase.h"

namespace Mplane {

/*!
 * \class  HostFileLinux
 * \brief
 * \details
 *
 */
class HostFileLinux : public HostFileBase {
public:
	HostFileLinux(const std::string &filename, int flags, mode_t mode) ;
	virtual ~HostFileLinux() ;

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

} ;

}

#endif /* COMMON_REMOTEPROC_INC_HOSTFILELINUX_H_ */
