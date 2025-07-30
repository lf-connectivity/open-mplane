/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WatchdogCount.cpp
 * \brief     Watchdog counter class
 *
 *
 * \details   Watchdog counter class.
 *
 *            When the counter reaches 0, the timeout function is called. It is the responsibility of the
 *            parent class to provide the timer to trigger the tick and to reset counter.
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <cmath>

#include "WatchdogCount.h"

using namespace Mplane;

//=============================================================================================================
// DEFINITIONS
//=============================================================================================================

//=============================================================================================================
// LOCAL
//=============================================================================================================

//=============================================================================================================
// STATIC
//=============================================================================================================
std::map<WatchdogCount::WatchdogState_T, std::string> WatchdogCount::mStateStr =
{
	{ WatchdogState_T::UNINIT,  "UNINIT"  },
	{ WatchdogState_T::STOPPED, "STOPPED" },
	{ WatchdogState_T::RUNNING, "RUNNING" },
	{ WatchdogState_T::EXPIRED, "EXPIRED" },
	{ WatchdogState_T::FAULT,   "FAULT"   },
};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
WatchdogCount::WatchdogCount()
	: mState(WatchdogState_T::UNINIT)
	, mCounter(0)
	, mCountMin(0)
	, mCountMax(0)
	, mCountReset(0)
	, mFreeRunning(false)
	, mTimeoutHandlers()
{
}

//-------------------------------------------------------------------------------------------------------------
WatchdogCount::~WatchdogCount()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State WatchdogCount::initialise(bool freeRunning)
{
	UINT32 numBits = (sizeof(UINT32)*8);
	UINT32 max = (pow(2, numBits)-1);

	return initialise(0, max, freeRunning);
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State WatchdogCount::initialise(UINT32 max, bool freeRunning)
{
	return initialise(0, max, freeRunning);
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State WatchdogCount::initialise(UINT32 min, UINT32 max, bool freeRunning)
{
	if (mState == WatchdogState_T::RUNNING)
		return ReturnType::RT_NOT_ALLOWED;

	ReturnType::State returnValue = ReturnType::RT_ERROR;

	// Reset values whether we have an issue or not.
	mCounter      = 0;
	mCountReset   = 0;
	mCountMin     = min;
	mCountMax     = max;
	mFreeRunning  = false;

	if ((min > max) || (max == 0))
	{
		mState = WatchdogState_T::FAULT;
		returnValue = ReturnType::RT_SYNTAX_ERROR;
	}
	else
	{
		mState = WatchdogState_T::STOPPED;
		mFreeRunning = freeRunning;
		returnValue = ReturnType::RT_OK;
	}

	return returnValue;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State WatchdogCount::registerTimeoutHandler(ExpiryFunc func)
{
	ReturnType::State returnValue = ReturnType::RT_ERROR;

	// Only allow handler registration, whilst not running
	switch (mState)
	{
		case WatchdogState_T::STOPPED:
		case WatchdogState_T::EXPIRED:
		case WatchdogState_T::FAULT:
			// Validate function
			if (func)
			{
				mTimeoutHandlers.push_back(func);
				returnValue = ReturnType::RT_OK;
			}
			else
			{
				returnValue = ReturnType::RT_SYNTAX_ERROR;
			}
			break;

		case WatchdogState_T::RUNNING:
			returnValue = ReturnType::RT_NOT_ALLOWED;
			break;

		case WatchdogState_T::UNINIT:
			returnValue = ReturnType::RT_NOT_INITIALISED;
			break;

		// Unexpected state
		default:
			mState = WatchdogState_T::FAULT;
			break;
	}

	return returnValue;
}

//-------------------------------------------------------------------------------------------------------------
bool WatchdogCount::isFreeRunning() const
{
	return mFreeRunning;
}

//-------------------------------------------------------------------------------------------------------------
WatchdogCount::WatchdogState_T WatchdogCount::getState() const
{
	return mState;
}

//-------------------------------------------------------------------------------------------------------------
std::string WatchdogCount::getStateString() const
{
	return mStateStr[mState];
}

//-------------------------------------------------------------------------------------------------------------
bool WatchdogCount::isRunning() const
{
	return (mState == WatchdogState_T::RUNNING);
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State WatchdogCount::start(UINT32 count)
{
	if (mState == WatchdogState_T::UNINIT)
		return ReturnType::RT_NOT_INITIALISED;

	ReturnType::State returnValue = ReturnType::RT_ERROR;

	if ((count < mCountMin) || (count > mCountMax))
	{
		// Requested count is out of range
		mState = WatchdogState_T::FAULT;
		returnValue = ReturnType::RT_OUT_OF_RANGE;
	}
	else
	{
		switch (mState)
		{
			case WatchdogState_T::STOPPED:
			case WatchdogState_T::EXPIRED:
				mState = WatchdogState_T::RUNNING;
				// Fall through

			case WatchdogState_T::RUNNING:
				mCounter    = count;
				mCountReset = count;
				returnValue = ReturnType::RT_OK;
				break;

			case WatchdogState_T::FAULT:
				// Must stop the counter, clearing the fault, before restarting
				returnValue = ReturnType::RT_NOT_ALLOWED;
				break;

			// Unexpected state
			case WatchdogState_T::UNINIT:
			default:
				mState = WatchdogState_T::FAULT;
				break;
		}
	}

	return returnValue;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State WatchdogCount::stop()
{
	if (mState == WatchdogState_T::UNINIT)
		return ReturnType::RT_NOT_INITIALISED;

	ReturnType::State returnValue = ReturnType::RT_ERROR;

	switch (mState)
	{
		case WatchdogState_T::RUNNING:
			mState = WatchdogState_T::STOPPED;
			returnValue = ReturnType::RT_OK;
			break;

		case WatchdogState_T::EXPIRED:
		case WatchdogState_T::FAULT:
			mState = WatchdogState_T::STOPPED;
			returnValue = ReturnType::RT_OK;
			break;

		case WatchdogState_T::STOPPED:
			returnValue = ReturnType::RT_INUSE;
			break;

		// Unexpected state
		case WatchdogState_T::UNINIT:
		default:
			break;
	}

	return returnValue;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State WatchdogCount::tick()
{
	if (mState == WatchdogState_T::UNINIT)
		return ReturnType::RT_NOT_INITIALISED;

	ReturnType::State returnValue = ReturnType::RT_ERROR;

	switch (mState)
	{
		case WatchdogState_T::EXPIRED:
			// If free running, then reset
			if (mFreeRunning)
			{
				mState = WatchdogState_T::RUNNING;
			}
			else
			{
				// Ignore unexpected tick request
				returnValue = ReturnType::RT_NOT_ALLOWED;
				break;
			}
			// Fall Through

		case WatchdogState_T::RUNNING:
			// Process watchdog counter
			mCounter--;

			returnValue = ReturnType::RT_OK;

			// Has the watchdog expired?
			if (mCounter == 0)
			{
				// Watchdog has expired, call registered handlers
				if (!mTimeoutHandlers.empty())
				{
					// Call all registered handlers
					for (auto handler : mTimeoutHandlers)
					{
						handler();
					}
				}
				else
				{
					// No registered handlers
					returnValue = ReturnType::RT_NOT_INITIALISED;
				}

				// Reset counter
				mCounter = mCountReset;

				// Enter EXPIRED state
				mState = WatchdogState_T::EXPIRED;
			}
			break;

		case WatchdogState_T::STOPPED:
		case WatchdogState_T::FAULT:
			// Ignore unexpected tick request
			returnValue = ReturnType::RT_NOT_ALLOWED;
			break;

		// Unexpected state
		case WatchdogState_T::UNINIT:
		default:
			mState = WatchdogState_T::FAULT;
			break;
	}

	return returnValue;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State WatchdogCount::kick()
{
	if (mState == WatchdogState_T::UNINIT)
		return ReturnType::RT_NOT_INITIALISED;

	ReturnType::State returnValue = ReturnType::RT_ERROR;

	switch (mState)
	{
		case WatchdogState_T::RUNNING:
			// Reset counter
			mCounter = mCountReset;
			returnValue = ReturnType::RT_OK;
			break;

		case WatchdogState_T::STOPPED:
		case WatchdogState_T::EXPIRED:
		case WatchdogState_T::FAULT:
			// Ignore unexpected kick request
			returnValue = ReturnType::RT_NOT_ALLOWED;
			break;

		// Unexpected state
		case WatchdogState_T::UNINIT:
		default:
			mState = WatchdogState_T::FAULT;
			break;
	}

	return returnValue;
}

//-------------------------------------------------------------------------------------------------------------
UINT32 WatchdogCount::getCounter() const
{
	return mCounter;
}

//-------------------------------------------------------------------------------------------------------------
std::string WatchdogCount::toStateString(WatchdogState_T state)
{
	return mStateStr[state];
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//=============================================================================================================
// PRIVATE
//=============================================================================================================
