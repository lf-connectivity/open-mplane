/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IBusLock.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef VHI_INC_IBUSLOCK_H_
#define VHI_INC_IBUSLOCK_H_

#include <memory>

namespace Mplane {

class IBusLocker ;

/*!
 * \class  IBusLock
 * \brief  The lock for a bus
 * \details   A mutex lock used to lock a particular bus
 *
 */
class IBusLock {
public:
	IBusLock() {}
	virtual ~IBusLock() {}

	/**
	 * Lock the bus using an RAII instance that will unlock the bus when the instance is destroyed
	 */
	virtual std::shared_ptr<IBusLocker> locker() =0 ;

} ;

/*!
 * \class  IBusLocker
 * \brief  Lock the bus
 * \details	An RAII class that locks the bus until this instance is destroyed
 *
 */
class IBusLocker {
public:
	IBusLocker() {}
	virtual ~IBusLocker() {}
} ;



}

#endif /* VHI_INC_IBUSLOCK_H_ */
