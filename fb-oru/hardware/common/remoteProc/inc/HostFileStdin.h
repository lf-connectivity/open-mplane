/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HostFileStdin.h
 * \brief     An IHostFile for host stdin
 *
 *
 * \details   An IHostFile for host stdin
 *
 */


#ifndef COMMON_REMOTEPROC_INC_HOSTFILESTDIN_H_
#define COMMON_REMOTEPROC_INC_HOSTFILESTDIN_H_

#include <unistd.h>
#include <fcntl.h>
#include "HostFileStd.h"

namespace Mplane {

/*!
 * \class  HostFileStdin
 * \brief
 * \details
 *
 */
class HostFileStdin : public HostFileStd {
public:
	HostFileStdin() :
		HostFileStd(STDIN_FILENO, "stdin", O_RDONLY)
	{}
	virtual ~HostFileStdin() {}

} ;

}

#endif /* COMMON_REMOTEPROC_INC_HOSTFILESTDIN_H_ */
