/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FileLockSockets.h
 * \brief     Locks access to sockets on this machine
 *
 *
 * \details
 *
 */


#ifndef FILELOCKSOCKETS_H_
#define FILELOCKSOCKETS_H_

#include "FileLock.h"

namespace Mplane {

/*!
 * \class FileLockSockets
 */
class FileLockSockets : public FileLock {
public:
	FileLockSockets() ;
	virtual ~FileLockSockets() ;

} ;

}

#endif /* FILELOCKSOCKETS_H_ */
