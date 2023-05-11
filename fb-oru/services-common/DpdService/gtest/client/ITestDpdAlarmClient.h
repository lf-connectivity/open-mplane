/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ITestDpdAlarmClient.h
 * \brief     Interface to a client Observer interested in DPD alarms
 *
 *
 * \details
 *
 */


#ifndef ITestDpdAlarmClient_H_
#define ITestDpdAlarmClient_H_

#include "Observer.hpp"
#include "data/ITestDpdAlarm.h"

namespace Mplane {

class ITestDpdAlarmClient : public Observer<ITestDpdAlarmClient, const ITestDpdAlarm&>
{
public:
	ITestDpdAlarmClient() {}
	virtual ~ITestDpdAlarmClient() {}

    /**
     * The callback method used by the corresponding Mplane::Subject implementation
     * to notify the observer of any change in the subject data.
     *
     * @param subject
     */
    virtual void update(ITestDpdAlarmClient& subject) {}	// not used
    virtual void update(ITestDpdAlarmClient& subject, const ITestDpdAlarm& data) =0 ;

    /**
     * A method used to get the name of the observer
     */
    virtual const char* name() const = 0;

} ;

}

#endif /* ITestDpdAlarmClient_H_ */
