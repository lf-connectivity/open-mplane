/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Cpri0MajorAlarm.h
 * \brief     Alarm for Cpri0 Major faults
 *
 *
 * \details
 *
 */


#ifndef CPRI0_MAJOR_ALARM_H_
#define CPRI0_MAJOR_ALARM_H_

#include "Alarm.h"

namespace Mplane {

class Cpri0MajorAlarm : public Alarm
{
public:
	Cpri0MajorAlarm() ;

	virtual ~Cpri0MajorAlarm() ;

    static const char* NAME;

} ;

}

#endif /* CPRI0_MAJOR_ALARM_H_ */
