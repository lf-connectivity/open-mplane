/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RssiEmu.h
 * \brief     CPRI Emulator
 *
 *
 * \details   Emulates the Fpga register interface for RSSI readings (RF power)
 *
 */


#ifndef RssiEmu_H_
#define RssiEmu_H_

#include <memory>
#include <vector>
#include <iostream>

#include "ITxPort.h"
#include "OffTargetFPGA.h"
#include "GlobalTypeDefs.h"
#include "TaskPeriodicEvent.h"

namespace Mplane {

class RssiEmu : public TaskPeriodicEvent {
public:
	/**
	 * Create emulator
	 * @param tx				Tx port index
	 */
	explicit RssiEmu(unsigned tx) ;
	virtual ~RssiEmu() ;

protected:
	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	virtual bool runEvent() override ;

private:
	UINT16 writeFwdLowHandler(const UINT32 address, const UINT16 value, const UINT16 mask) ;
	UINT16 readFwdLowHandler(const UINT32 address, const UINT16 mask) ;
	UINT16 writeFwdHighHandler(const UINT32 address, const UINT16 value, const UINT16 mask) ;
	UINT16 readFwdHighHandler(const UINT32 address, const UINT16 mask) ;

	UINT16 writeRevLowHandler(const UINT32 address, const UINT16 value, const UINT16 mask) ;
	UINT16 readRevLowHandler(const UINT32 address, const UINT16 mask) ;
	UINT16 writeRevHighHandler(const UINT32 address, const UINT16 value, const UINT16 mask) ;
	UINT16 readRevHighHandler(const UINT32 address, const UINT16 mask) ;

	void show(std::ostream& os = std::cout) ;

private:
	unsigned mIndex ;
	std::shared_ptr<ITxPort> mTxPort ;

	Mutex mEmuMutex ;
	std::shared_ptr<OffTargetFPGA> mFpga ;

	Power mRfAtten ;
	Power mRfPower ;
	UINT16 mRssiFwdLow ;
	UINT16 mRssiFwdHigh ;
	UINT16 mRssiRevLow ;
	UINT16 mRssiRevHigh ;
} ;

}

#endif /* RssiEmu_H_ */
