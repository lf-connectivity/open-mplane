/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AlarmLatched.h
 * \brief     A latched Alarm class
 *
 *
 * \details
 *
 */


#ifndef ALARMLATCHED_H_
#define ALARMLATCHED_H_

#include "Alarm.h"

namespace Mplane {

/*! \brief A latched alarm class.
 *
 * Exactly the same as an Alarm, but once the alarm is set it stays set until it is reset
 */
class AlarmLatched : public Alarm
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
	AlarmLatched(const std::string& name, const std::string& description);
	AlarmLatched(const std::string& name, const std::string& description, IAlarm::AlarmSeverity severity);

    /**
     * Alarm Destructor:
     *
     */
    virtual ~AlarmLatched();

    /**
     * The callback method used by the corresponding Mplane::Subject implementation
     * to notify the observer of any change in the subject data.
     *
     * @param subject
     */
    virtual void update(IFault& subject) override ;

};  // end of class AlarmLatched


}

#endif /* ALARMLATCHED_H_ */
