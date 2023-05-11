/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Cpri1RemoteAlarmIndicationFaultMajor.h
 * \brief     CPRI0 Remote Alarm Indication fault major
 *
 *
 * \details
 *
 */


#ifndef CPRI1_REMOTE_ALARM_IND_FAULT_MAJOR_H_
#define CPRI1_REMOTE_ALARM_IND_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class Cpri1RemoteAlarmIndicationFaultMajor : public Fault
{
public:
	Cpri1RemoteAlarmIndicationFaultMajor() ;
	virtual ~Cpri1RemoteAlarmIndicationFaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* CPRI1_REMOTE_ALARM_IND_FAULT_MAJOR_H_ */
