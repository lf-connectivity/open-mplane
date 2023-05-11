#ifndef _COMM_ALARM_H_
#define _COMM_ALARM_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Alarm.h
 * \brief     A file to contain general purpose radio alarm handler
 *
 *
 * \brief     This file defines a general purpose radio alarm handler
 *
 */

// Includes go here, before the namespace
#include <map>
#include <memory>
#include <set>

#include "IFault.h"
#include "IAlarm.h"
#include "IAlarmsList.h"
#include "GlobalTypeDefs.h"
#include "Loggable.h"
#include "Mutex.h"
#include "Observer.hpp"
#include "ObserverUtils.hpp"

namespace Mplane
{

/*! \brief A general purpose radio application alarm class.
 *
 * The Alarm class defines a single alarm, its associated data and related
 * interfaces.
 *
 * It inherits from Loggable in order to make use of the general logging
 * and error services.
 *
 * Each Alarm object in the system is instantiated during application initialisation.
 */
class Alarm : public IAlarm, public Loggable, public Subject<IAlarm>
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
    explicit Alarm(const std::string& name, const std::string& description);

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
     * @param type The text string describing this alarm type
     * @param description The text string describing this alarm description
     */
    explicit Alarm(const std::string& name, const std::string& type, const std::string& description);

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
     * @param description The text string describing this alarm description
     * @param severity The text string describing this alarm severity
     */
    Alarm(const std::string& name, const std::string& description, IAlarm::AlarmSeverity severity);

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
     * @param type The text string describing this alarm type
     * @param description The text string describing this alarm description
     * @param severity The text string describing this alarm severity
     */
    Alarm(const std::string& name, const std::string& type, const std::string& description, IAlarm::AlarmSeverity severity);

    /**
     * Alarm Destructor:
     *
     */
    virtual ~Alarm();

    /**
     * Pure virtual method that forces its implementation.
     * Indicates that the alarm has changed state to the value in the parameter.
     *
     * \param The new alarm state: true means alarm is present
     */
    virtual void alarmStateHasChanged(bool newState) override;

    /**
     * Resets the alarm object to its initial state.
     * If the alarm transitions state then it will  call the alarmStateHasChanged() interface to the inheritors.
     */
    virtual void reset() override ;

    /**
     * Used to return the 'alarm active' status for the alarm object.
     *
     * @return true = The alarm is active, false if not
     */
    virtual bool isAlarmActive() const override ;

    /**
     * Gets the alarm name text string
     *
     * @return The alarm name string
     */
    virtual std::string getName() const override ;

    /**
     * Gets the alarm descriptive text string
     *
     * @return The alarm description string
     */
    virtual std::string getDescription() const override ;

    /**
     * Gets the alarm severity
     *
     * @return The alarm severity
     */
    virtual IAlarm::AlarmSeverity getSeverity() const override ;

    /**
     * Gets the alarm severity as  a string
     *
     * @return The alarm severity string
     */
    virtual std::string getSeverityStr() const override ;

    /**
     * Gets the alarm Id
     *
     * @return The alarm Id numeric value
     */
    virtual unsigned int getId() const override ;

    /**
     * gets the Alarm state as a string.
     *
     * \return the Alarm state as a string.
     */
    virtual std::string getAlarmStateString() const override ;

    /**
     * Gets the number of resets performed since power up.\n
     *
     * The reset scenarios are part of 'session resets' when sessions are
     * implemented by the application.
     *
     * @return the number of resets performed since power up
     */
    virtual unsigned getResetCount() const override ;

    /**
     * Gets the port ID that this alarm relates to.
     *
     * @return the port ID that this alarm relates to
     */
    virtual int getPortId() const override ;

    /**
     * Sets the port ID that this alarm relates to.
     *
     * @param the port ID that this alarm relates to
     */
    virtual void setPortId(int port) override ;

    /**
     * Gets the sector ID that this alarm relates to.
     *
     * \return the sector ID that this alarm relates to
     */
    virtual int getSectorId() const override ;

    /**
     * Sets the sector ID that this alarm relates to.
     *
     * \param the sector ID that this alarm relates to
     */
    virtual void setSectorId(int sector) override ;

    /**
     * The show method required by Loggable.
     * Displays its current status.
     */
    virtual void show(std::ostream & os = std::cout) const override ;

    /**
     * The show method to show an alarm and its associated faults.
     * Displays its current status.
     */
    virtual void showAlarmAndFault(std::ostream & os = std::cout) const override ;

    /**
     * The show name and id method.
     * Displays the alarm name and id
     */
    virtual void showNameAndId(std::ostream & os = std::cout) const override;

    /**
     * Shows the active trace and debug levels for this class
     */
    virtual void traceTest() const override ;

    /**
     * This method is used for system and integration test purposes
     * and allows a tester to raise an alarm without going through
     * the normal alarm-raising logic.
     */
    virtual void raiseAlarmForTesting() override ;

    /**
     * This method is used for system and integration test purposes
     * and allows a tester to clear a alarm without going through
     * the normal alarm-clearing logic.
     */
    virtual void clearAlarmForTesting() override ;

    /**
     * Sets the status of an alarm.
     *
     * @param condition true = alarm is active, false = alarm is not active.
     */
    virtual void setStatus(bool condition) override ;


    // IFault Observer interface

    /**
     * Register this alarm as an Observer of the specified fault(s)
     * @param name
     * @return true if registered ok
     */
    virtual bool registerFault(const std::string& name) override ;

    /**
     * Register this alarm as an Observer of the specified fault(s)
     * @param names
     * @return true if registered ok
     */
    virtual bool registerFaults(const std::set<std::string>& names) override ;

    /**
     * The callback method used by the corresponding Mplane::Subject implementation
     * to notify the observer of any change in the subject data.
     *
     * @param subject
     */
    virtual void update(IFault& subject) override ;


    /**
     * Return a reference to the fault that is the root cause of an alarm state change.
     *
     * @return
     */
    virtual std::string getRootCause() const override;

    /**
     * Return a reference to the fault that is the root cause of an alarm state change.
     *
     * @return
     */
    virtual void setRootCause( std::string rootCause ) override;

    /**
     * Clear the name of the fault that is the root cause of an alarm state change.
     *
     */
    virtual void clearRootCause( void ) override;

    /**
     * Helper method used by make_alarm(). Does the additional work after the alarm shared pointer has been created
     */
    static void makeAlarm(std::shared_ptr<IAlarm> alarm) ;

    /** Return true if alarm state has changed since it was last read
     *
     * @return boolean alarm has changed since last read.
     */
    virtual bool hasAlarmChangedSinceLastRead(void) override;

    /** Return the system time stamp of the alarm
     *
     * @return std::string system time stamp of the alarm being raised.
     *                     Format: 2020-10-23T10:14:25
     *
     */
    virtual std::string getTimeStamp(void) override;


protected:
    std::vector< std::shared_ptr<ObserverWrapper<IAlarm, IFault>> > getObservers() ;

private:

    /**
     * Called when there is a condition change in the alarm.
     *
     * If a contiguous series of samples indicates that the alarm is genuinely
     * active or inactive, a "stateHasChanged" notification is provided to the inheritors of the alarm.
     */
    void stateChange();

    // Clear out all faults related to this alarm
    void resetFaults() ;

    // Set the time stamp of the alarm
    void setTimeStamp(void);

    // Clear the time stamp of the alarm
    void clrTimeStamp(void);

private:
    /**
     * Indicates the current state of the alarm, active or not active.
     *
     * Dealarms to false, meaning alarm not active
     */
    bool mAlarmState;

    /**
     * The alarm object name string. Descriptive text to identify this alarm.
     */
    const std::string mName;

    /**
     * The alarm description
     */
    const std::string mDescription ;

    /**
     * The alarm object type string. Descriptive text to identify type of alarm.
     */
    const std::string mTypeStr;

    /**
     * The alarm object severity.
     */
    const IAlarm::AlarmSeverity mSeverity;

	/**
     * The alarm object ID. Numeric value to identify this fault.
     */
    unsigned int mId;

    /**
     * Count the number of times this alarm has been raised
     */
    unsigned mRaisedCount;

    /**
     * Count the number of times this alarm has been cleared
     */
    unsigned mClearedCount;

    /**
     * The port ID that this alarm relates to.
     *
     * Dealarms to 0.
     */
    int mPortId;

    /**
     * The sector ID that this alarm relates to.
     *
     * Dealarms to 0.
     */
    int mSectorId;

    /**
     * Indicates if the alarm has changed since it was last read.
     */
    bool mAlarmStateHasChanged;

    /**
     * List of Observer objects connected to IFault objects
     */
    std::vector< std::shared_ptr<ObserverWrapper<IAlarm, IFault>> > mObservers ;

    std::string mRootCause;

    /**
     * Records the time stamp at which the alarm was raised.
     */
    std::string mTimeStamp;


    /************************************************************
     * Metric collection area
     ************************************************************/
    /**
     * Count the number of times this alarm has been raised for testing
     */
    unsigned mRaiseForTestingCount;

    /**
     * Count the number of times this alarm has been cleared for testing
     */
    unsigned mClearForTestingCount;

    /**
     * Count the number of resets.
     * Required as part of the system reset procedures.
     */
    unsigned mResetCount;



};  // end of class Alarm





//-------------------------------------------------------------------------------------------------------------

/**
 * All alarms *MUST* be created via this helper template function. This ensures the shared pointer is created
 * and registered to the IAlarmsList. Expects T to be derived from IAlarm
 *
 * @return shared pointer to alarm
 */
template <typename T>
inline std::shared_ptr<T> make_alarm()
{
	// create a new alarm instance (assumes T is derived from IAlarm)
	std::shared_ptr<T> alarm(std::make_shared<T>()) ;

    // Finish off
	Alarm::makeAlarm(alarm) ;

    return alarm ;
}


}
#endif /* _COMM_ALARM_H_ */
