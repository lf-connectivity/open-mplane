/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonPort.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "Task.h"
#include "CommonPort.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
//const unsigned EXPECTED_SYNTH_LOCK_TIME_MS{4} ;
const unsigned SYNTH_WAIT_TIME_MS{2} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int CommonPort::getIndex() const
{
    return mIndex;
}

//-------------------------------------------------------------------------------------------------------------
std::string CommonPort::getName() const
{
    return mName;
}

//-------------------------------------------------------------------------------------------------------------
CommonPort::CommonPort(int index, const char* name):
	mIndex( index ), mName( name )
{
}

//-------------------------------------------------------------------------------------------------------------
CommonPort::~CommonPort()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonPort::waitSynthLocked(unsigned timeMs, SynthLockFunc synthLocked)
{
	// see if synth is already in lock
	if (synthLocked())
		return ReturnType::RT_OK ;

	// Wait until lock or timeout
	do
	{
		// Wait the expected synth lock time...
		Task::msSleep(SYNTH_WAIT_TIME_MS) ;

		// .. synth should now be in lock
		if (synthLocked())
			return ReturnType::RT_OK ;

		// need to retry until we time out
		if (timeMs >= SYNTH_WAIT_TIME_MS)
			timeMs -= SYNTH_WAIT_TIME_MS ;
		else
			timeMs = 0 ;

	} while (timeMs > 0) ;

	// failed
	return ReturnType::RT_TIMED_OUT ;
}
