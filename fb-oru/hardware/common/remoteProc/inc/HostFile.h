/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HostFile.h
 * \brief     A standard Linux file on the host
 *
 *
 * \details   A standard Linux file on the host
 *
 */


#ifndef COMMON_REMOTEPROC_INC_HOSTFILE_H_
#define COMMON_REMOTEPROC_INC_HOSTFILE_H_

#include "HostFileLinux.h"

namespace Mplane {

/*!
 * \class  HostFile
 * \brief
 * \details
 *
 */
class HostFile : public HostFileLinux {
public:
	HostFile(const std::string& filename, int flags, mode_t mode) ;
	virtual ~HostFile() ;
} ;

}

#endif /* COMMON_REMOTEPROC_INC_HOSTFILE_H_ */
