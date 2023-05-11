/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Heartbeat.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Heartbeat.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Heartbeat::Heartbeat() :
	TaskPeriodicEvent(1000, Task::PRIORITY_MEDIUM, Task::SMALL_STACK, "Heartbeat", "HB"),
	mTimerMutex(),
	mEnabled(false),
	mTimeoutSecs(30),
	mTimeoutCounter(0),
	mTimerExpired(false)
{
}

//-------------------------------------------------------------------------------------------------------------
Heartbeat::~Heartbeat()
{
}

//-------------------------------------------------------------------------------------------------------------
unsigned Heartbeat::getTimeoutSecs() const
{
	return mTimeoutSecs ;
}

//-------------------------------------------------------------------------------------------------------------
void Heartbeat::setTimeoutSecs(unsigned timeout)
{
	{
		Mutex::Lock lock(mTimerMutex) ;
		mTimeoutSecs = timeout ;
		mTimeoutCounter = mTimeoutSecs ;
	}

	// update flag
	updateExpiredFlag() ;
}

//-------------------------------------------------------------------------------------------------------------
bool Heartbeat::getEnable() const
{
	Mutex::Lock lock(mTimerMutex) ;
	return mEnabled ;
}

//-------------------------------------------------------------------------------------------------------------
void Heartbeat::setEnable(bool enable)
{
	{
		Mutex::Lock lock(mTimerMutex) ;
		mEnabled = enable ;
		mTimeoutCounter = mTimeoutSecs ;
	}

	// update flag
	updateExpiredFlag() ;
}

//-------------------------------------------------------------------------------------------------------------
void Heartbeat::resetTimer()
{
	{
		Mutex::Lock lock(mTimerMutex) ;
		mTimeoutCounter = mTimeoutSecs ;

	}

	// update flag
	updateExpiredFlag() ;
}

//-------------------------------------------------------------------------------------------------------------
bool Heartbeat::isExpired() const
{
	Mutex::Lock lock(mTimerMutex) ;
	return mTimerExpired ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Heartbeat::runEvent()
{
	{
		Mutex::Lock lock(mTimerMutex) ;

		// skip if not enabled
		if (!mEnabled)
			return true ;

		// skip if already timed out
		if (mTimeoutCounter == 0)
			return true ;

		// see if now timed out
		if (--mTimeoutCounter == 0)
		{
			eventError("Heartbeat monitor timed out") ;
		}
	}

	// update flag
	updateExpiredFlag() ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::Heartbeat::heartbeatEvent(bool expired)
{
	// Derived classes should override this method to act
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Mplane::Heartbeat::updateExpiredFlag()
{
	bool eventRequired(false) ;

	{
		Mutex::Lock lock(mTimerMutex) ;

		// calculate the new flag state
		bool expired(false) ;
		if (mEnabled && (mTimeoutCounter == 0))
			expired = true ;

		// check for change
		if (mTimerExpired != expired)
			eventRequired = true ;

		// update flag
		mTimerExpired = expired ;
	}

	// Create event
	if (eventRequired)
		heartbeatEvent(mTimerExpired) ;
}
