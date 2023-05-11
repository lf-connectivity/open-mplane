/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaMonitor.h
 * \brief     Monitor fpga register(s) for debug purposes
 *
 *
 * \details   Monitors one or more fpga registers looking for changes. When a register value changes, calls the
 * 			callback function (which typically will connect to a TIF output)
 *
 */


#ifndef FPGAPOLLING_H_
#define FPGAPOLLING_H_

#include <vector>

#include "GlobalTypeDefs.h"
#include "Task.h"
#include "Mutex.h"
#include "Conditional.h"
#include "IFpgaMonitor.h"

namespace Mplane {

class FpgaMonitor : public IFpgaMonitor, public Task
{
public:
	FpgaMonitor() ;
	virtual ~FpgaMonitor() ;

	using RegisterCallback = IFpgaMonitor::RegisterCallback ;
	using ShowCallback = IFpgaMonitor::ShowCallback ;


	/**
	 * Add a register to be monitored
	 * @param address	FPGA register address to monitor
	 * @param callback	Callback function to call when register value changes
	 * @param mask		Optional mask used to mask out bits that can be ignored (ignored if mask bit = 0)
	 */
	virtual void addRegister(unsigned address, UINT16 mask, RegisterCallback callback, ShowCallback showCallback = ShowCallback()) override ;

	/**
	 * Remove a register monitor
	 * @param address
	 * @param mask
	 */
	virtual void delRegister(unsigned address, UINT16 mask) override ;

	/**
	 * Display fpga monitors
	 * @param os	Output stream
	 */
	virtual void show(std::ostream& os, const std::string& clientTitle = std::string("")) override ;


protected:
	int run() override ;

private:
	bool mTaskRun ;
	bool mTaskRunning ;
	Conditional mDataReady ;
	Mutex mMutex ;

	class Monitor ;
	std::vector< std::shared_ptr<Monitor> > mMonitors ;
} ;

}

#endif /* FPGAPOLLING_H_ */
