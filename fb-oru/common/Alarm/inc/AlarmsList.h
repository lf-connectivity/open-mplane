#ifndef _COMM_ALARMSLIST_H_
#define _COMM_ALARMSLIST_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AlarmList.h
 * \brief     Class for managing a list of Alarm objects
 *
 *
 * \brief     Class for managing a list of Alarm objects
 *
 */

#include <map>
#include <memory>

#include "Loggable.h"
#include "Mutex.h"
#include "IAlarmsList.h"

namespace Mplane
{


/*! \brief The AlarmsList class that keeps a list of all the alarms that are
 * created.
 *
 * The AlarmsList class maintains a list of all the alarms that are
 * created. The list starts empty and Alarms are added to the list by the
 * Alarm objects during their construction.
 *
 */
class AlarmsList: public IAlarmsList, public Loggable
{
public:

    /**
     * Should never get called unless the system is shutting down
     */
    virtual ~AlarmsList();

    /**
     * Add an alarm to the alarms list.
     * Will be called by the Alarm constructor.
     *
     * Throws std::invalid_argument exception if an existing alarm with the same name is already registered
     *
     * \param A Alarm instance
     *
     */
    virtual void addAlarm(std::shared_ptr<IAlarm> alarm) override ;

    /**
     * The show method required by Loggable.
     * Displays its current status.
     */
    virtual void show(std::ostream & os = std::cout) const override ;

    /**
     * The show name and id method.
     */
    virtual void showNamesAndIds(std::ostream & os = std::cout) const override;

    /**
     * Get all alarms that are currently active
     */
    virtual std::vector<std::shared_ptr<IAlarm>> getActiveAlarms() const override ;

    /**
     * Get all alarms
     */
    virtual std::vector<std::shared_ptr<IAlarm>> getAlarms() const override ;

    /**
     * Get the names of all alarms
     */
    virtual std::vector<std::string> getNames() const override ;

    /**
     * Return the alarm list size.
     *
     * @return  the size of the alarm list
     */
    virtual int getSize() const override ;

    /**
     * Get the named alarm
     * @param name
     * @return shared pointer to Alarm if name is correct; pointer to null otherwise
     */
    virtual std::shared_ptr<IAlarm> getAlarm(const std::string& name) const  override ;

    /**
     * Get the named alarm
     * @param name
     * @return shared pointer to Alarm if name is correct; pointer to null otherwise
     */
    virtual std::shared_ptr<IAlarm> getAlarm(const unsigned int ident) const  override ;


    // Test interface
#ifdef OFF_TARGET
    bool removeAlarm(const std::string& name) ;
#endif

protected:

    /**
     * Alarms list constructor
     */
    AlarmsList();

    /**
     * \note: Standard copy constructors defined but not implemented as a
     * AlarmsList cannot be copied.
     */
    AlarmsList& operator=(const AlarmsList&);

private:
    /**
     * The list of alarms
     */
    std::map< std::string, std::shared_ptr<IAlarm> > mAlarmsList;  /*! a list of alarms */

    mutable Mutex mAlarmsListMutex;

};  // end of class AlarmsList


} /* namespace Mplane */


#endif /* _COMM_ALARMSLIST_H_ */
