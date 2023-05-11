/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BusLock.hpp
 * \brief     Implements the IBusLock interface
 *
 *
 * \details   Create a lock on a particular bus
 *
 */


#ifndef COMMON_BUS_INC_BUSLOCK_H_
#define COMMON_BUS_INC_BUSLOCK_H_

#include <memory>
#include <mutex>

#include "IBusLock.h"

namespace Mplane {

/*!
 * \class  BusLocker
 * \brief  Lock the bus
 * \details	An RAII class that locks the bus until this instance is destroyed
 *
 */
class BusLocker : public virtual IBusLocker {
public:
	BusLocker(std::mutex& mutex) :
		mLock(std::make_shared<std::unique_lock<std::mutex>>(mutex))
	{}
	virtual ~BusLocker() {}

private:
	std::shared_ptr<std::unique_lock<std::mutex>> mLock ;
} ;

/*!
 * \class  BusLock
 * \brief  Lock the bus
 * \details
 *
 */
class BusLock : public virtual IBusLock {
public:
	BusLock() {}
	virtual ~BusLock() {}

	/**
	 * Lock the bus using an RAII instance that will unlock the bus when the instance is destroyed
	 */
	virtual std::shared_ptr<IBusLocker> locker() override
	{
		std::shared_ptr<IBusLocker> lock(std::make_shared<BusLocker>(mMutex)) ;
		return lock ;
	}

private:
	std::mutex mMutex ;
} ;

/*!
 * \class  NullBusLock
 * \brief  NO OP
 * \details
 *
 */
class NullBusLock : public virtual IBusLock {
public:
	NullBusLock() {}
	virtual ~NullBusLock() {}

	/**
	 * Lock the bus using an RAII instance that will unlock the bus when the instance is destroyed
	 */
	virtual std::shared_ptr<IBusLocker> locker() override { return std::shared_ptr<IBusLocker>(); }

} ;



}

#endif /* COMMON_BUS_INC_BUSLOCK_H_ */
