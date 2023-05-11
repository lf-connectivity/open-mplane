/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AlarmMonitor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "IAlarmsList.h"
#include "AlarmMonitor.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
static const unsigned DEFAULT_PERIOD_SECS{30} ;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAlarmMonitor> IAlarmMonitor::getInstance()
{
	static std::shared_ptr<IAlarmMonitor> instance(std::make_shared<AlarmMonitor>()) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
AlarmMonitor::AlarmMonitor() :
	// 1sec periodic update
	TaskPeriodicEvent(1000, Task::PRIORITY_MEDIUM, Task::SMALL_STACK, "AlarmMonitor", "AM"),

	mHandler(),
	mPeriodicHandler(),

	mObservers(),

	mMonitorMutex(),
	mPeriodSecs(DEFAULT_PERIOD_SECS),
	mPeriodicTimer(DEFAULT_PERIOD_SECS),

	mSeenAlarms()

{
	// Register ourself as an observer of all alarms
	std::shared_ptr<IAlarmsList> alarmsList(IAlarmsList::getInstance()) ;
	for (auto alarm : alarmsList->getAlarms())
	{
		// create an object to handle Observer updates
		std::shared_ptr<ObserverWrapper<AlarmMonitor, IAlarm>> observer(
			new ObserverWrapper<AlarmMonitor, IAlarm>(this, alarm->getName(), alarm)
		) ;
		mObservers.push_back(observer) ;

		// Attatch observer to the IAlarm
		std::shared_ptr<Subject<IAlarm>> subject( std::dynamic_pointer_cast<Subject<IAlarm>>(alarm) ) ;
		subject->attach(*observer) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
AlarmMonitor::~AlarmMonitor()
{
	// Un-Register ourself from all alarms
	for (auto obs : mObservers)
	{
		// Detach observer from the IAlarm
		std::shared_ptr<Subject<IAlarm>> subject( std::dynamic_pointer_cast<Subject<IAlarm>>(obs->getSubject()) ) ;
		subject->detach(*obs) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void AlarmMonitor::registerHandler(EventHandler handler)
{
	mHandler = handler ;
}

//-------------------------------------------------------------------------------------------------------------
void AlarmMonitor::unregisterHandler()
{
	mHandler = EventHandler() ;
}

//-------------------------------------------------------------------------------------------------------------
void AlarmMonitor::setPeriod(unsigned periodSecs)
{
	if (periodSecs < 1)
		return ;

	Mutex::Lock lock(mMonitorMutex) ;
	mPeriodSecs = periodSecs ;
	mPeriodicTimer = mPeriodSecs ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned AlarmMonitor::getPeriod()
{
	Mutex::Lock lock(mMonitorMutex) ;
	return mPeriodSecs ;
}

//-------------------------------------------------------------------------------------------------------------
void AlarmMonitor::registerPeriodicHandler(PeriodicHandler handler)
{
	Mutex::Lock lock(mMonitorMutex) ;
	mPeriodicHandler = handler ;
}

//-------------------------------------------------------------------------------------------------------------
void AlarmMonitor::unregisterPeriodicHandler()
{
	Mutex::Lock lock(mMonitorMutex) ;
	mPeriodicHandler = PeriodicHandler() ;
}

//-------------------------------------------------------------------------------------------------------------
void AlarmMonitor::update(IAlarm& subject)
{
//std::cerr << "AlarmMonitor::update" << std::endl ;

	// If active then cause an immediate periodic report
	if (subject.isAlarmActive())
	{
		// Update list of seen active alarms
		{
			Mutex::Lock lock(mMonitorMutex) ;

			std::shared_ptr<IAlarmsList> alarmsList(IAlarmsList::getInstance()) ;
			std::shared_ptr<IAlarm> alarm(alarmsList->getAlarm(subject.getName())) ;
			mSeenAlarms[alarm] = true ;
		}

		// Cause an "immediate" report
		scheduleReport() ;
	}

	// Skip if no handler set
	if (!mHandler)
		return ;

	// call handler with alarm
	mHandler(subject) ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool AlarmMonitor::runEvent()
{
//std::cerr << "AlarmMonitor::runEvent counter=" << mPeriodicTimer << std::endl ;

	// Called every 1 sec
	if (!timeout())
		return true ;

//std::cerr << "AlarmMonitor PERIODIC" << std::endl ;

	// skip if no handler
	if (!mPeriodicHandler)
		return true ;

	// Get list of active alarms
	std::shared_ptr<IAlarmsList> alarmsList(IAlarmsList::getInstance()) ;
	std::vector<std::shared_ptr<IAlarm>> activeAlarms(alarmsList->getActiveAlarms()) ;

	// Handle any seen alarms that "pulsed"
	{
		Mutex::Lock lock(mMonitorMutex) ;

//std::cerr << "# seen alarms=" << mSeenAlarms.size() << " # alarms=" << activeAlarms.size() << std::endl ;
		if (!mSeenAlarms.empty())
		{
			// Cross off any already in the list of active alarms
			for (auto active : activeAlarms)
			{
				auto entry(mSeenAlarms.find(active)) ;
				if (entry != mSeenAlarms.end())
					entry->second = false ;
			}

			// Now add any that were seen but not in the list
			for (auto seen : mSeenAlarms)
			{
				if (!seen.second)
					continue ;

				activeAlarms.push_back(seen.first) ;
//				std::cerr << " * Added seen alarm: " << seen.first->getName() << std::endl ;
			}

			mSeenAlarms.clear() ;
		}
	}

	// notify client
	mPeriodicHandler( activeAlarms ) ;

	return true ;
}


//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool AlarmMonitor::timeout()
{
	Mutex::Lock lock(mMonitorMutex) ;

	// Decrement the counter and see if a new reporting period is required. If so, restarts the countdown timer
	if (mPeriodicTimer > 0)
		--mPeriodicTimer ;

	bool timeout(false) ;
	if (mPeriodicTimer == 0)
	{
		mPeriodicTimer = mPeriodSecs ;
		timeout = true ;
	}
	return timeout ;
}

//-------------------------------------------------------------------------------------------------------------
void AlarmMonitor::scheduleReport()
{
	Mutex::Lock lock(mMonitorMutex) ;

	// make timer expire in a second (or 2) (allows multiple alarms to collect together in one report)
	if (mPeriodicTimer <= 2)
		return ;

	mPeriodicTimer = 2 ;
}
