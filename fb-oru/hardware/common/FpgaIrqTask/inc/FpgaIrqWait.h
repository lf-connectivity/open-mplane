/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaIrqWait.h
 * \brief     Wait for an IRQ
 *
 *
 * \details   Yields the calling task until the IRQ triggers. Some methods also provide a timeout option so that the wait
 * 			  can also return after a timeout. All methods return true if IRQ triggered; false otherwise (i.e. on timeout)
 *
 */


#ifndef FPGAIRQWAIT_H_
#define FPGAIRQWAIT_H_

#include <atomic>
#include "Mutex.h"
#include "Conditional.h"
#include "FpgaIrqTask.h"

namespace Mplane {

class FpgaIrqWait : public FpgaIrqTask {
public:
	explicit FpgaIrqWait(unsigned irqBit) ;
	virtual ~FpgaIrqWait() ;

	/**
	 * Wait indefinitely until IRQ triggers
	 * @return true if IRQ triggered
	 */
	virtual bool wait() ;

	/**
	 * Waits for IRQ or for a specified timeout period
	 * @param timeoutMs	Timeout time in millisecs
	 * @return true if IRQ triggered; false on timeout
	 */
	virtual bool wait(unsigned timeoutMs) ;

private:
	void irqCallback() ;

private:
	std::atomic<bool> mIrq ;
	Mutex mMutex ;
	Conditional mCond ;
	bool mWaiting ;
} ;

}

#endif /* FPGAIRQWAIT_H_ */
