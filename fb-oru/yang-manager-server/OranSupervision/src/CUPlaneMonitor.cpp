/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CUPlaneMonitor.cpp
 * \brief     ORAN C/U-Plane Monitor
 *
 *
 * \details   Responsible for controlling C/U-plane monitoring and managing associated faults
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <stdexcept>
#include <iostream>

#include "CUPlaneMonitor.h"
#include "Zcu111FbcOranrrhHandlerORanSupervision.h"

using namespace Mplane;

//=============================================================================================================
// DEFINITIONS
//=============================================================================================================
#define DEFAULT_INTERVAL_MIN     0
#define DEFAULT_INTERVAL_MAX     160
#define DEFAULT_MAX_NUM_STREAMS  8

// Definition checking
#if (DEFAULT_INTERVAL_MIN > DEFAULT_INTERVAL_MAX)
#error "CUPlaneMonitor: Invalid interval range"
#endif
#if (DEFAULT_INTERVAL_MAX < 1)
#error "CUPlaneMonitor: Invalid maximum interval"
#endif
#if (DEFAULT_MAX_NUM_STREAMS < 1)
#error "CUPlaneMonitor: Invalid maximum interval"
#endif

//=============================================================================================================
// LOCAL
//=============================================================================================================

//=============================================================================================================
// STATIC
//=============================================================================================================
std::map<CUPlaneMonitor::State_T, std::string> CUPlaneMonitor::mStateStr =
{
	{ State_T::DISABLED,   "DISABLED"      },
	{ State_T::ENABLED,    "ENABLED"       },
	{ State_T::MONITORING, "MONITORING"    },
	{ State_T::FAULT,      "FAULT"         },
};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CUPlaneMonitor::CUPlaneMonitor()
	: Loggable("CUPlaneMonitor","YANG")
	, mName("CUPlaneMonitor")
	, mState(State_T::DISABLED)
	, mInterval(0)
	, mIntervalMin(DEFAULT_INTERVAL_MIN)
	, mIntervalMax(DEFAULT_INTERVAL_MAX)
	, mNumStream(0)
	, mNumStreamMax(DEFAULT_MAX_NUM_STREAMS)
{
#ifdef OFF_TARGET
//	Loggable::setLevel(ILoggable::LogDebugLevel::LOG_DEBUG_NORMAL);
	Loggable::setLevel(ILoggable::LogDebugLevel::LOG_DEBUG_VERBOSE);
#endif

	if (mIntervalMin > mIntervalMax)
		throw std::runtime_error("CUPlaneMonitor: Invalid interval range");
	if (mIntervalMax < 1)
		throw std::runtime_error("CUPlaneMonitor: Invalid maximum interval");
	if (mNumStreamMax < 1)
		throw std::runtime_error("CUPlaneMonitor: Invalid number of streams limit");
}

//-------------------------------------------------------------------------------------------------------------
CUPlaneMonitor::~CUPlaneMonitor()
{
}

//-------------------------------------------------------------------------------------------------------------
const char * CUPlaneMonitor::getName() const
{
	return mName;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CUPlaneMonitor::setIntervalRange(UINT32 min, UINT32 max)
{
	ReturnType::State returnValue = ReturnType::RT_OUT_OF_RANGE;

	// Validate interval range
	if ((min > max) || (max == 0))
	{
		// Invalid range
		returnValue = ReturnType::RT_OUT_OF_RANGE;
	}
	else
	{
		// Valid range
		mIntervalMin = min;
		mIntervalMax = max;
		returnValue = ReturnType::RT_OK;
	}

	return returnValue;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CUPlaneMonitor::setIntervalRange(UINT32 max)
{
	return setIntervalRange(0, max);
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CUPlaneMonitor::setInterval(UINT32 interval)
{
	ReturnType::State returnValue = ReturnType::RT_ERROR;

	// Validate new interval
	if ((interval < mIntervalMin) && (interval > mIntervalMax))
	{
		// Specified interval is out of range
		eventError("%s: Monitoring interval [%d] - Out of range [%d-%d]",
				getName(), interval, mIntervalMin, mIntervalMax);
		returnValue = ReturnType::RT_OUT_OF_RANGE;
	}
	else
	{
		// Specified interval is valid

		// Store new interval
		mInterval = interval;

		logDebugNormal("%s: Set C/U monitoring [interval=%d]", getName(), mInterval);

		// Reconfigure monitoring, depending upon client requests and Tx/Rx stream activity
		updateMonitoring();

		returnValue = ReturnType::RT_OK;
	}

	return returnValue;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CUPlaneMonitor::setStreamLimit(UINT32 limit)
{
	ReturnType::State returnValue = ReturnType::RT_OUT_OF_RANGE;

	// Validate limit Tx/Rx streams
	if (limit > 0)
	{
		mNumStreamMax = limit;
		returnValue = ReturnType::RT_OK;
	}

	return returnValue;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CUPlaneMonitor::addTxRxStream()
{
	ReturnType::State returnValue = ReturnType::RT_ERROR;

	// Validate Tx/Rx streams
	if (mNumStream < DEFAULT_MAX_NUM_STREAMS)
	{
		// Log new stream
		mNumStream++;
		logDebugNormal("%s: Add Tx/Rx stream [numStreams=%d]", getName(), mNumStream);

		// Reconfigure monitoring, depending upon client requests and Tx/Rx stream activity
		updateMonitoring();

		returnValue = ReturnType::RT_OK;
	}
	else
	{
		// Too many streams
		eventError("%s: Add Tx/Rx stream [numStreams=%d] - Too many streams [%d]",
				getName(), mNumStream, DEFAULT_MAX_NUM_STREAMS);
		returnValue = ReturnType::RT_OPERATION_FAILED;
	}

	return returnValue;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CUPlaneMonitor::removeTxRxStream()
{
	ReturnType::State returnValue = ReturnType::RT_ERROR;

	// Validate Tx/Rx streams
	if (mNumStream)
	{
		// Remove stream
		mNumStream--;
		logDebugNormal("%s: Remove Tx/Rx stream [numStreams=%d]", getName(), mNumStream);

		// Reconfigure monitoring, depending upon client requests and Tx/Rx stream activity
		updateMonitoring();

		returnValue = ReturnType::RT_OK;
	}
	else
	{
		// No streams
		eventError("%s: Remove Tx/Rx stream [numStreams=%d] - No streams",
				getName(), mNumStream);
		returnValue = ReturnType::RT_OPERATION_FAILED;
	}

	return returnValue;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CUPlaneMonitor::faultHandler(UINT16 faultId)
{
	logDebugNormal("%s: Fault Handler [fault=%d]", getName(), faultId);

	ReturnType::State returnValue = ReturnType::RT_ERROR;

	returnValue = ReturnType::RT_OK;

	return returnValue;
}

//-------------------------------------------------------------------------------------------------------------
CUPlaneMonitor::State_T CUPlaneMonitor::getState() const
{
	return mState;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void CUPlaneMonitor::setState(State_T state)
{
	if (state != mState)
	{
		logDebugVerbose("%s: State Change [%s] => [%s]",
			getName(), mStateStr[mState].c_str(), mStateStr[state].c_str());
	}
	mState = state;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void CUPlaneMonitor::updateMonitoring()
{
	// Client has requested no monitoring
	// A value of 0 means that the O-RU's shall disable its CU plane monitoring
	if (mInterval == 0)
	{
		setState(State_T::DISABLED);
	}

	// Client has requested monitoring
	// At least one active Tx/Rx stream
	else if (mNumStream > 0)
	{
		setState(State_T::MONITORING);
	}

	// Client has requested monitoring
	// No active Tx/Rx streams
	else
	{
		// Nothing to monitor
		setState(State_T::ENABLED);
	}

	// Update monitoring depending upon new state
	if (mState == State_T::MONITORING)
		watchdogEnable(mInterval);
	else
		watchdogDisable();
}

//-------------------------------------------------------------------------------------------------------------
void CUPlaneMonitor::watchdogEnable(UINT32 interval)
{
	logDebugNormal("%s: Enable monitoring [%dms]", getName(), interval);

	// Configure FPGA C/U Plane watchdog interval
	//fpga->setCuPlaneWatchdogInterval(interval);

	// Enable FPGA C/U Plane watchdog interrupt
	//fpga->enableCuWatchdogInterrupt();
}

//-------------------------------------------------------------------------------------------------------------
void CUPlaneMonitor::watchdogDisable()
{
	logDebugNormal("%s: Disable monitoring", getName());

	// Set FPGA C/U Plane watchdog interval to 0 to disable watchdog
	//fpga->setCuPlaneWatchdogInterval(0);

	// Disable FPGA C/U Plane watchdog interrupt
	//fpga->disableCuWatchdogInterrupt();
}
