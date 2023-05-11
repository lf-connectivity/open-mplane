/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HostFileStdout.h
 * \brief     An IHostFile for host stdout
 *
 *
 * \details   An IHostFile for host stdout
 *
 */


#ifndef COMMON_REMOTEPROC_INC_HOSTFILESTDOUT_H_
#define COMMON_REMOTEPROC_INC_HOSTFILESTDOUT_H_

#include <unistd.h>
#include <fcntl.h>
#include "HostFileStd.h"

namespace Mplane {

/*!
 * \class  HostFileStdout
 * \brief
 * \details
 *
 */
class HostFileStdout : public HostFileStd {
public:
	HostFileStdout() :
		HostFileStd(STDOUT_FILENO, "stdout", O_WRONLY)
	{}
	virtual ~HostFileStdout() {}
} ;

}

#endif /* COMMON_REMOTEPROC_INC_HOSTFILESTDOUT_H_ */
