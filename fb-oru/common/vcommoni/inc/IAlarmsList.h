#ifndef _COMM_IALARMSLIST_H_
#define _COMM_IALARMSLIST_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IAlarmsList.h
 * \brief     Interface to alarms list
 *
 *
 * \brief     This file defines the interface to the AlarmList class
 *
 */

#include <iostream>
#include <vector>
#include <memory>

namespace Mplane
{

// forward ref
class IAlarm ;

/*! \brief The AlarmsList class that keeps a list of all the alarms that are
 * created.
 *
 * The IAlarmList class provides a pure virtual interface to an implementation
 * that maintains a list of IAlarm objects. The purpose of this interface is
 * to provide a generic interface to the implementation.
 *
 *
 */
class IAlarmsList
{
public:

	/**
	 * Singleton method for getting an instance of the applications alarm list implementation.
	 * @return shared pointer to singleton
	 */
	static std::shared_ptr<IAlarmsList> getInstance() ;

    /**
     * Should never get called unless the system is shutting down
     */
    virtual ~IAlarmsList() {}

    /**
     * Add an alarm to the alarms list.
     * Will be called by the Alarm constructor.
     *
     * Throws std::invalid_argument exception if an existing alarm with the same name is already registered
     *
     * \param A Alarm instance
     */
    virtual void addAlarm(std::shared_ptr<IAlarm> alarm) =0 ;

    /**
     * The show method required by Loggable.
     * Displays its current status.
     */
    virtual void show(std::ostream& os = std::cout) const =0 ;

    /**
     * The show names and id's method.
     */
    virtual void showNamesAndIds(std::ostream& os = std::cout) const =0 ;

    /**
     * Get all alarms that are currently active
     */
    virtual std::vector<std::shared_ptr<IAlarm>> getActiveAlarms() const =0 ;

    /**
     * Get all alarms
     */
    virtual std::vector<std::shared_ptr<IAlarm>> getAlarms() const =0 ;

    /**
     * Get the names of all alarms
     */
    virtual std::vector<std::string> getNames() const =0 ;

    /**
     * Return the alarm list size.
     *
     * @return  the size of the alarm list
     */
    virtual int getSize() const =0 ;

    /**
     * Get the named alarm
     * @param name
     * @return shared pointer to Alarm if name is correct; pointer to null otherwise
     */
    virtual std::shared_ptr<IAlarm> getAlarm(const std::string& name) const  =0 ;

    /**
     * Get the identified alarm
     * @param ident fault identification
     * @return shared pointer to named fault, or null pointer if invalid name
     */
    virtual std::shared_ptr<IAlarm> getAlarm(const unsigned int ident) const  =0 ;


protected:

    /**
     * Alarms list constructor
     */
    IAlarmsList() {}

};  // end of class AlarmsList


} /* namespace Mplane */


#endif /* _COMM_IALARMSLIST_H_ */
