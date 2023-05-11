/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TaskPeriodicEvent.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TaskPeriodicEvent.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TaskPeriodicEvent::TaskPeriodicEvent(unsigned periodMs, int priority,
		StackSize stacksize, const std::string& name,
		const std::string& suName) :
	Task(priority, stacksize, name.c_str(), suName.c_str()),
	mTaskRun(true),
	mTaskRunning(false),
	mEvent(),
	mPeriodMs(periodMs),
	mPeriodicEvent(false)
{
	// self-starting
	start() ;
}

//-------------------------------------------------------------------------------------------------------------
TaskPeriodicEvent::~TaskPeriodicEvent()
{
	shutdown() ;
}

//-------------------------------------------------------------------------------------------------------------
void TaskPeriodicEvent::shutdown()
{
	if (!mTaskRunning)
		return ;

	// clear run flag to stop task
	mTaskRun = false ;

	// keep trying until task stops
	while(mTaskRunning)
	{
		// trigger task to wait up
		event() ;

		// wait for task to respond
		msSleep(10) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void TaskPeriodicEvent::event()
{
	// signal to task that event has occurred
	Conditional::Lock condLock(mEvent) ;
	mEvent.signal() ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int TaskPeriodicEvent::run()
{
	int rc = 0 ;
	mTaskRunning = true ;

    /*
     * Now our thread is running we just enter an infinite loop so we never end.
     * ALl image management is triggered by invocation of class methods, which are explicit action requests.
     */
    while (mTaskRun)
    {
    	// wait for event - set flag if time out (i.e. this is a periodic run)
    	mPeriodicEvent = false ;
		if (!mEvent.wait(mPeriodMs))
			mPeriodicEvent = true ;

		// check for task stop
		if (!mTaskRun)
			break ;

		// run method
		if (!runEvent())
		{
			// exit with error
			rc = 1 ;
			break ;
		}

    }

	mTaskRunning = false ;
    return rc;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::TaskPeriodicEvent::isEvent() const
{
	return !mPeriodicEvent ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::TaskPeriodicEvent::isPeriodic() const
{
	return mPeriodicEvent ;
}
