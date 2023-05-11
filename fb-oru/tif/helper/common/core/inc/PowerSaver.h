/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PowerSaver.h
 * \brief     TIF helper class which puts the board into a power saving mode
 *
 *
 * \details
 *
 */


#ifndef POWERSAVER_H_
#define POWERSAVER_H_

#include <memory>
#include "Conditional.h"
#include "Mutex.h"
#include "Task.h"

namespace Mplane {

class PowerSaver : public Task
{
public:
	/**
	 * Singleton
	 */
	static std::shared_ptr<PowerSaver> getInstance() ;

	virtual ~PowerSaver() ;

	/**
	 * Starts the shutdown process
	 */
	void shutdown() ;

protected:
	PowerSaver() ;

	int run() ;

private:
	Conditional mStartShutdown ;
} ;

}

#endif /* POWERSAVER_H_ */
