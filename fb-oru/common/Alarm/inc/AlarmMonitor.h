/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AlarmMonitor.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef ALARMMONITOR_H_
#define ALARMMONITOR_H_

#include "IAlarmMonitor.h"

#include "TaskPeriodicEvent.h"
#include "Observer.hpp"
#include "ObserverUtils.hpp"

namespace Mplane {

class AlarmMonitor : public virtual IAlarmMonitor, public Observer<IAlarm>, public TaskPeriodicEvent
{
public:
	AlarmMonitor() ;
	virtual ~AlarmMonitor() ;


	// IAlarmMonitor interface

	/**
	 * Change the periodic report period - mainly for debug
	 */
	virtual void setPeriod(unsigned periodSecs) override ;

	/**
	 * Get the current period time in seconds
	 */
	virtual unsigned getPeriod() override ;

	/**
	 * Register an event handler
	 * @param handler callback function called with the alarm that causes the event
	 */
	virtual void registerHandler(EventHandler handler) override ;

	/**
	 * Remove the callback
	 */
	virtual void unregisterHandler() override ;

	/**
	 * Register a handler for periodic updates
	 * @param handler callback function called with the list of active alarms
	 */
	virtual void registerPeriodicHandler(PeriodicHandler handler) override ;

	/**
	 * Remove the callback
	 */
	virtual void unregisterPeriodicHandler() override ;


    // IAlarm Observer interface

    /**
     * The callback method used by the corresponding Mplane::Subject implementation
     * to notify the observer of any change in the subject data.
     *
     * @param subject
     */
    virtual void update(IAlarm& subject) override ;

    /**
     * Return name
     * @return
     */
    virtual const char* name() const override {return "AlarmMonitor";}

protected:
	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	virtual bool runEvent() override ;

private:
    bool timeout() ;
    void scheduleReport() ;

private:
    // The handler
    EventHandler	mHandler ;
    PeriodicHandler	mPeriodicHandler ;

    /**
     * List of Observer objects connected to IFault objects
     */
    std::vector< std::shared_ptr<ObserverWrapper<AlarmMonitor, IAlarm>> > mObservers ;

    Mutex mMonitorMutex ;
    unsigned mPeriodSecs ;
    unsigned mPeriodicTimer ;

    // Keep track of *every* active alarm so that we catch any alarm "pulses"
    std::map<std::shared_ptr<IAlarm>, bool> mSeenAlarms ;
} ;

}

#endif /* ALARMMONITOR_H_ */
