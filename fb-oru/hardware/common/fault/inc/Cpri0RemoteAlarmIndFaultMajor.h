/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Cpri0RemoteAlarmIndicationFaultMajor.h
 * \brief     CPRI0 Remote Alarm Indication fault major
 *
 *
 * \details
 *
 */


#ifndef CPRI0_REMOTE_ALARM_IND_FAULT_MAJOR_H_
#define CPRI0_REMOTE_ALARM_IND_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class Cpri0RemoteAlarmIndicationFaultMajor : public Fault
{
public:
	Cpri0RemoteAlarmIndicationFaultMajor() ;
	virtual ~Cpri0RemoteAlarmIndicationFaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* CPRI0_REMOTE_ALARM_IND_FAULT_MAJOR_H_ */
