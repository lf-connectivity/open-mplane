/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NullTimeoutTimer.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "NullTimeoutTimer.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
NullTimeoutTimer::NullTimeoutTimer() :
	TimeoutTimer()
{
}

//-------------------------------------------------------------------------------------------------------------
NullTimeoutTimer::~NullTimeoutTimer()
{
}

//-------------------------------------------------------------------------------------------------------------
void NullTimeoutTimer::startTimer()
{
}

//-------------------------------------------------------------------------------------------------------------
void NullTimeoutTimer::startTimer(const std::chrono::milliseconds &timerTime)
{
}

//-------------------------------------------------------------------------------------------------------------
void NullTimeoutTimer::stopTimer()
{
}

//-------------------------------------------------------------------------------------------------------------
bool NullTimeoutTimer::isTimedOut()
{
	return false ;
}
