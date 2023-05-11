/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDpdAlarmClient.h
 * \brief     Interface to a client Observer interested in DPD alarms
 *
 *
 * \details
 *
 */


#ifndef IDPDALARMCLIENT_H_
#define IDPDALARMCLIENT_H_

#include "Observer.hpp"
#include "data/IDpdAlarm.h"

namespace Mplane {

class IDpdAlarmClient : public Observer<IDpdAlarmClient, const IDpdAlarm&>
{
public:
	IDpdAlarmClient() {}
	virtual ~IDpdAlarmClient() {}

    /*! @brief  Get the singleton instance
     *
     *  Method used to obtain a reference to the single instance of the RadioState within the system.
     *
     *  @return the singleton instance
     */
    static std::shared_ptr<IDpdAlarmClient> getInstance( void );

    typedef enum
    {
    	START,
		STOP
    } eDpdState;

    virtual void dpdStateChange(eDpdState dpdState) = 0;

    /**
     * The callback method used by the corresponding Mplane::Subject implementation
     * to notify the observer of any change in the subject data.
     *
     * @param subject
     */
    virtual void update(IDpdAlarmClient& subject) {}	// not used
    virtual void update(IDpdAlarmClient& subject, const IDpdAlarm& data) =0 ;

    /**
     * A method used to get the name of the observer
     */
    virtual const char* name() const = 0;

} ;

}

#endif /* IDPDALARMCLIENT_H_ */
