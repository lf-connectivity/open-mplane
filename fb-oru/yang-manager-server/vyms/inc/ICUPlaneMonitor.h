/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICUPlaneMonitor.h
 * \brief     ORAN C/U-Plane Monitor virtual interface
 *
 *
 * \details   Virtual interface for ORAN C/U-Plane Monitor
 *
 */

#ifndef _VYMS_INC_ICUPLANE_MONITOR_H_
#define _VYMS_INC_ICUPLANE_MONITOR_H_

#include <memory>
#include <string>

#include "GlobalTypeDefs.h"

namespace Mplane
{

class ICUPlaneMonitor
{
public:
	ICUPlaneMonitor() {}
	virtual ~ICUPlaneMonitor() {}

	typedef enum
	{
		DISABLED,   	// Monitoring is not running
		ENABLED,    	// Monitoring is enabled, though nothing to monitor
		MONITORING, 	// Monitoring is enabled and running
		FAULT,      	// Fault
	} State_T;

	/*
	 * Returns the monitors name
	 */
	virtual const char * getName() const = 0;

	/*
	 * Set interval range
	 */
	virtual ReturnType::State setIntervalRange(UINT32 min, UINT32 max) = 0;
	virtual ReturnType::State setIntervalRange(UINT32 max) = 0;

	/*
	 * Set interval
	 */
	virtual ReturnType::State setInterval(UINT32 interval) = 0;

	/*
	 * Set maximum number of supported streams
	 */
	virtual ReturnType::State setStreamLimit(UINT32 limit) = 0;

	/*
	 * Add a new stream
	 */
	virtual ReturnType::State addTxRxStream() = 0;

	/*
	 * Add a stream
	 */
	virtual ReturnType::State removeTxRxStream() = 0;

	/*
	 * Monitoring Fault
	 */
	virtual ReturnType::State faultHandler(UINT16 faultId) = 0;

	/*
	 * Returns the current state
	 */
	virtual ICUPlaneMonitor::State_T getState() const = 0;

	/*
	 * Get the singleton instance
	 */
	static std::shared_ptr<ICUPlaneMonitor> singleton(void);	//!> C/U-Plane monitoring manager singleton interface
};

}

#endif /* _VYMS_INC_ICUPLANE_MONITOR_H_ */
