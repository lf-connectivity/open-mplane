/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HostFileStderr.h
 * \brief     An IHostFile for host stderr
 *
 *
 * \details   An IHostFile for host stderr
 *
 */


#ifndef COMMON_REMOTEPROC_INC_HOSTFILESTDERR_H_
#define COMMON_REMOTEPROC_INC_HOSTFILESTDERR_H_

#include <unistd.h>
#include <fcntl.h>
#include "HostFileStd.h"

namespace Mplane {

/*!
 * \class  HostFileStderr
 * \brief
 * \details
 *
 */
class HostFileStderr : public HostFileStd {
public:
	HostFileStderr() :
		HostFileStd(STDERR_FILENO, "stderr", O_WRONLY)
	{}
	virtual ~HostFileStderr() {}

} ;

}

#endif /* COMMON_REMOTEPROC_INC_HOSTFILESTDERR_H_ */
