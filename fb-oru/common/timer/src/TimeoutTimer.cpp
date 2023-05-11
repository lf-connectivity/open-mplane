/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TimeoutTimer.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TimeoutTimer.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TimeoutTimer::TimeoutTimer() :
	mDuration(),
	mCallback (),
	mTimedOut(false),
	mEndTime(),
	mRunning(false)
{
}

//-------------------------------------------------------------------------------------------------------------
TimeoutTimer::TimeoutTimer(const std::chrono::milliseconds &timerTime) :
	TimeoutTimer()
{
	startTimer(timerTime) ;
}

//-------------------------------------------------------------------------------------------------------------
TimeoutTimer::~TimeoutTimer()
{
}

//-------------------------------------------------------------------------------------------------------------
void TimeoutTimer::setTimedCallback(TimerCallback func)
{
	mCallback = func ;
}

//-------------------------------------------------------------------------------------------------------------
void TimeoutTimer::startTimer()
{
	startTimer(mDuration) ;
}

//-------------------------------------------------------------------------------------------------------------
void TimeoutTimer::startTimer(const std::chrono::milliseconds &timerTime)
{
	mRunning = true ;
	mDuration = timerTime ;
	mEndTime = std::chrono::steady_clock::now() + mDuration ;
	isTimedOut() ;
}

//-------------------------------------------------------------------------------------------------------------
void TimeoutTimer::stopTimer()
{
	mRunning = false ;
}

//-------------------------------------------------------------------------------------------------------------
bool TimeoutTimer::isTimedOut()
{
	if (!mRunning)
		return false ;

	if (mTimedOut)
		return true ;

	if (std::chrono::steady_clock::now() < mEndTime)
		return false ;

	if (mCallback)
		mCallback() ;

	mTimedOut = true ;
	return true ;
}
