/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CUPlaneMonitor.h
 * \brief     ORAN C/U-Plane Monitor
 *
 *
 * \details   Responsible for controlling C/U-plane monitoring and managing associated faults
 *
 */

#ifndef _CUPLANE_MONITOR_H_
#define _CUPLANE_MONITOR_H_

#include <cstdlib>
#include <cstdbool>
#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <map>

#include "Loggable.h"

#include "ICUPlaneMonitor.h"


namespace Mplane
{

class CUPlaneMonitor : public ICUPlaneMonitor, public Loggable
{
public:
	CUPlaneMonitor();
	virtual ~CUPlaneMonitor();

	/*
	 * Returns the monitors name
	 */
	virtual const char * getName() const;

	/*
	 * Set interval range
	 */
	virtual ReturnType::State setIntervalRange(UINT32 min, UINT32 max);
	virtual ReturnType::State setIntervalRange(UINT32 max);

	/*
	 * Set interval
	 */
	virtual ReturnType::State setInterval(UINT32 interval);

	/*
	 * Set maximum number of supported streams
	 */
	virtual ReturnType::State setStreamLimit(UINT32 limit);

	/*
	 * Add a new stream
	 */
	virtual ReturnType::State addTxRxStream();

	/*
	 * Add a stream
	 */
	virtual ReturnType::State removeTxRxStream();

	/*
	 * Monitoring Fault
	 */
	virtual ReturnType::State faultHandler(UINT16 faultId);

	/*
	 * Returns the current state
	 */
	virtual ICUPlaneMonitor::State_T getState() const;

	/*
	 * Get the singleton instance
	 */
	static std::shared_ptr<ICUPlaneMonitor> singleton(void);	//!> C/U-Plane monitoring manager singleton interface

protected:
	/*
	 * Sets the current state
	 */
	void setState(State_T state);

private:
	//=========================================================================================================
	// Helper Functions
	//=========================================================================================================

	/*
	 * Check settings and reconfigure monitoring accordingly
	 */
	void updateMonitoring();

	/*
	 * Enable / Reconfigure FPGA watchdog
	 */
	void watchdogEnable(UINT32 interval);

	/*
	 * Disable FPGA watchdog
	 */
	void watchdogDisable();

	//=========================================================================================================
	// Parameters
	//=========================================================================================================

	// Object name
	const char * mName;

	// Monitor state
	State_T mState;

	// Requested monitoring interval (in ms)
	UINT32 mInterval;

	// Minimum monitoring interval (in ms)
	UINT32 mIntervalMin;

	// Maximum monitoring interval (in ms)
	UINT32 mIntervalMax;

	// Number of active Tx/Rx streams
	UINT32 mNumStream;

	// Maximum number of active Tx/Rx streams
	UINT32 mNumStreamMax;

	// Debug
	static std::map<State_T, std::string> mStateStr;
};

} /* namespace Mplane */

#endif /* _CUPLANE_MONITOR_H_ */
