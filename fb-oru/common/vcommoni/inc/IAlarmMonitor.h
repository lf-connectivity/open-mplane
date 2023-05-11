/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IAlarmMonitor.h
 * \brief     Monitors alarm events
 *
 *
 * \details   A singleton that associates a callback function with alarm events
 *
 */


#ifndef IALARMMONITOR_H_
#define IALARMMONITOR_H_

#include <functional>
#include <memory>
#include "IAlarm.h"

namespace Mplane {

/**
 * The IAlarmMonitor class defines a pure virtual interface to the application alarm monitoring
 * and update module. This interface allows an Mplane::EventHandler to register for an
 * update callback each time any alarm condition changes.
 *

@code

#include "Service.h"
#include "IAlarmsList.h"
#include "IAlarmMonitor.h"


class MyAlarmStateService: public Service
{

    MyAlarmStateService()
    {
        // Lambda method to register the update method to handle updates from the Alarm Monitor
        std::shared_ptr<IAlarmMonitor> monitor(IAlarmMonitor::getInstance()) ;

        monitor->registerHandler([this](const IAlarm& alarm) {this->update(alarm);} );
    }

    virtual void update(const IAlarm& alarm)
    {
        // The alarm monitor is telling us that an alarm has changed.
        // We need to action this ASAP and we cannot wait for the next timer expiry
        eventInfo("MyAlarmStateService::update alarm - %s; state = %s", alarm.getName().c_str(), alarm.getAlarmStateString().c_str());

        mNotify.signal();   // signal our service to run
    }


}

@endcode

 *
 *
 */
class IAlarmMonitor {
public:
	IAlarmMonitor() {}
	virtual ~IAlarmMonitor() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IAlarmMonitor> getInstance() ;

	// Define a callback function type for immediate reporting of alarm status changes
	using EventHandler = std::function< void(const IAlarm& alarm) > ;

	// Define callback function for periodic reporting of all active alarms
	using PeriodicHandler = std::function< void(const std::vector<std::shared_ptr<IAlarm>>& activeAlarms) > ;

	/**
	 * Change the periodic report period - mainly for debug
	 */
	virtual void setPeriod(unsigned periodSecs) =0 ;

	/**
	 * Get the current period time in seconds
	 */
	virtual unsigned getPeriod() =0 ;

	/**
	 * Register an event handler
	 * @param handler callback function called with the alarm that causes the event
	 */
	virtual void registerHandler(EventHandler handler) =0 ;

	/**
	 * Remove the callback
	 */
	virtual void unregisterHandler() =0 ;


	/**
	 * Register a handler for periodic updates
	 * @param handler callback function called with the list of active alarms
	 */
	virtual void registerPeriodicHandler(PeriodicHandler handler) =0 ;

	/**
	 * Remove the callback
	 */
	virtual void unregisterPeriodicHandler() =0 ;

} ;

}

#endif /* IALARMMONITOR_H_ */
