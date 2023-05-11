/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WatchdogCount.h
 * \brief     Watchdog counter class
 *
 *
 * \details   Watchdog counter class.
 *
 */

#ifndef _WATCHDOG_COUNT_H_
#define _WATCHDOG_COUNT_H_

#include <cstdlib>
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <functional>

#include "GlobalTypeDefs.h"

namespace Mplane
{

class WatchdogCount
{
public:
	WatchdogCount();
	virtual ~WatchdogCount();

	typedef enum
	{
		UNINIT,
		STOPPED,
		RUNNING,
		EXPIRED,
		FAULT,
	} WatchdogState_T;

	/*
	 * Initialises the watchdog counter parameters
	 */
	virtual ReturnType::State initialise(bool freeRunning);
	virtual ReturnType::State initialise(UINT32 max, bool freeRunning);
	virtual ReturnType::State initialise(UINT32 min, UINT32 max, bool freeRunning);

	/*
	 * Register watchdog timeout (expired) callback
	 */
	using ExpiryFunc = std::function<ReturnType::State(void)>;
	virtual ReturnType::State registerTimeoutHandler(ExpiryFunc func);

	/*
	 * Is the watchdog free running?
	 */
	virtual bool isFreeRunning() const;

	/*
	 * Returns the current state
	 */
	virtual WatchdogState_T getState() const;

	/*
	 * Returns the current state as a string
	 */
	virtual std::string getStateString() const;

	/*
	 * Returns whether to watchdog is running of not
	 */
	virtual bool isRunning() const;

	/*
	 * Start the watchdog with the specified count
	 */
	virtual ReturnType::State start(UINT32 count);

	/*
	 * Stop the watchdog
	 */
	virtual ReturnType::State stop();

	/*
	 * Trigger watchdog timer tick
	 */
	virtual ReturnType::State tick();

	/*
	 * Kick the watchdog
	 */
	virtual ReturnType::State kick();

	/*
	 * Returns the current counter value
	 */
	virtual UINT32 getCounter() const;

	/*
	 * Returns the specified state as a string
	 */
	static std::string toStateString(WatchdogState_T state);

protected:

private:
	//=========================================================================================================
	// Parameters
	//=========================================================================================================

	// State
	WatchdogState_T mState;

	// Counter
	UINT32 mCounter;

	// Counter range
	UINT32 mCountMin;	// Default = 0
	UINT32 mCountMax;	// Default = ((2 pow 32)-1)

	// Reset counter value
	UINT32 mCountReset;

	// Free running flag; If true, then stay in running state following expiry
	bool mFreeRunning;

	// Functions called when watchdog expires
	std::vector<ExpiryFunc> mTimeoutHandlers;

	// Debug
	static std::map<WatchdogState_T, std::string> mStateStr;

};

} /* namespace Mplane */

#endif /* _WATCHDOG_COUNT_H_ */
