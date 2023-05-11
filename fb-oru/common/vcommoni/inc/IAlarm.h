#ifndef _COMM_IALARM_H_
#define _COMM_IALARM_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IAlarm.h
 * \brief     Interface to alarms
 *
 *
 * \brief     This file defines the interface to the Alarm classes
 *
 */

#include <iostream>
#include <vector>
#include <set>
#include <memory>

namespace Mplane
{

// Forward
class IFault ;

/*! \brief A general purpose radio application alarm class.
 *
 * The IAlarm class defines a pure virtual interface that must be implemented by
 * all Mplane::Alarm objects. It provides access to relative alarm data and
 * interfaces to its fault.
 *
 * Each Alarm object in the system is instantiated during application initialisation
 * and is exposed through this interface.
 */
class IAlarm
{
public:

    /**
     * Alarm Constructor:@n
     *
     * Initialises the alarm object data from the parameter list.
     * It validates the parameters values before use.
     *
     * The alarm state is initialised to 'cleared'.
     *
     * The alarm is added to the global alarm list.
     *
     * @param name The text string describing this alarm
     */
    IAlarm() {}

    /**
     * Alarm severity
     */
    enum AlarmSeverity {
    	ALARM_WARNING,
		ALARM_MINOR,
		ALARM_MAJOR,
		ALARM_CRITICAL,
    };

    /**
     * Alarm Destructor:
     *
     * This should never be called.
     */
    virtual ~IAlarm() {}

    /**
     * Pure virtual method that forces its implementation.
     * Indicates that the alarm has changed state to the value in the parameter.
     *
     * \param The new alarm state: true means alarm is present
     */
    virtual void alarmStateHasChanged(bool newState) =0;

    /**
     * Resets the alarm object to its initial state.
     * If the alarm transitions state then it will  call the alarmStateHasChanged() interface to the inheritors.
     */
    virtual void reset() =0 ;

    /**
     * Used to return the 'alarm active' status for the alarm object.
     *
     * @return true = The alarm is active, false if not
     */
    virtual bool isAlarmActive() const =0;

    /**
     * Gets the alarm name text string
     *
     * @return The alarm name string
     */
    virtual std::string getName() const =0 ;

    /**
     * Gets the alarm Id
     *
     * @return The alarm Id
     */
    virtual unsigned int getId() const =0;

    /**
     * Gets the alarm descriptive text string
     *
     * @return The alarm description string
     */
    virtual std::string getDescription() const =0 ;

    /**
     * Gets the alarm severity
     *
     * @return The alarm severity
     */
    virtual AlarmSeverity getSeverity() const =0 ;

    /**
     * Gets the alarm severity as  a string
     *
     * @return The alarm severity string
     */
    virtual std::string getSeverityStr() const =0 ;


    /**
     * gets the Alarm state as a string.
     *
     * \return the Alarm state as a string.
     */
    virtual std::string getAlarmStateString() const =0;

    /**
     * Gets the number of resets performed since power up.\n
     *
     * The reset scenarios are part of 'session resets' when sessions are
     * implemented by the application.
     *
     * @return the number of resets performed since power up
     */
    virtual unsigned getResetCount() const =0 ;

    /**
     * Gets the port ID that this alarm relates to.
     *
     * @return the port ID that this alarm relates to
     */
    virtual int getPortId() const =0 ;

    /**
     * Sets the port ID that this alarm relates to.
     *
     * @param the port ID that this alarm relates to
     */
    virtual void setPortId(int port) =0 ;

    /**
     * Gets the sector ID that this alarm relates to.
     *
     * \return the sector ID that this alarm relates to
     */
    virtual int getSectorId() const =0 ;

    /**
     * Sets the sector ID that this alarm relates to.
     *
     * \param the sector ID that this alarm relates to
     */
    virtual void setSectorId(int sector) =0 ;

    /**
     * The show method required by Loggable.
     * Displays its current status.
     */
    virtual void show(std::ostream& os = std::cout) const =0 ;

    /**
     * The show method to show an alarm and its associated faults.
     * Displays its current status.
     */
    virtual void showAlarmAndFault(std::ostream& os = std::cout) const =0 ;

    /**
     * The show name and id method.
     * Displays the fault name and id
     */
    virtual void showNameAndId(std::ostream& os) const =0;

    /**
     * Shows the active trace and debug levels for this class
     */
    virtual void traceTest() const =0 ;

    /**
     * This method is used for system and integration test purposes
     * and allows a tester to raise an alarm without going through
     * the normal fault-raising logic.
     */
    virtual void raiseAlarmForTesting() =0 ;

    /**
     * This method is used for system and integration test purposes
     * and allows a tester to clear a fault without going through
     * the normal fault-clearing logic.
     */
    virtual void clearAlarmForTesting() =0 ;

    /**
     * Sets the status of an alarm.
     *
     * @param condition true = alarm is active, false = alarm is not active.
     */
    virtual void setStatus(bool condition) =0 ;


    // IFault Observer interface

    /**
     * Register this alarm as an Observer of the specified fault(s)
     * @param name
     * @return true if registered ok
     */
    virtual bool registerFault(const std::string& name) =0 ;


    /**
     * Register this alarm as an Observer of the specified fault(s)
     * @param names
     * @return true if registered ok
     */
    virtual bool registerFaults(const std::set<std::string>& names) =0 ;

    /**
     * The callback method used by the corresponding Mplane::Subject implementation
     * to notify the observer of any change in the subject data.
     *
     * @param subject
     */
    virtual void update(IFault& subject) =0 ;


    /**
     * Return the name of the fault that is the root cause of an alarm state change.
     *
     * @return fault name that caused the alarm change state
     */
    virtual std::string getRootCause() const = 0;


    /**
     * Set the name of the fault that is the root cause of an alarm state change.
     *
     */
    virtual void setRootCause( std::string rootCause ) = 0;

    /**
     * Clear the name of the fault that is the root cause of an alarm state change.
     *
     */
    virtual void clearRootCause( void ) = 0;

    /** Return true if alarm state has changed since it was last read
     *
     * @return boolean alarm has changed since last read.
     */
    virtual bool hasAlarmChangedSinceLastRead(void) = 0;

    /** Return the system time stamp of the alarm
     *
     * @return std::string the system time stamp of the alarm being raised.
     */
    virtual std::string getTimeStamp(void) = 0;


};  // end of class Alarm

} /* namespace Mplane */


#endif /* _COMM_IALARM_H_ */
