/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxMajorAlarm.h
 * \brief     Rx major alarm
 *
 *
 * \details
 *
 */


#ifndef RX_MAJOR_ALARM_H_
#define RX_MAJOR_ALARM_H_

#include "AlarmLatched.h"

namespace Mplane {

class Rx1MajorAlarm : public AlarmLatched
{
public:
	Rx1MajorAlarm() ;

	virtual ~Rx1MajorAlarm() ;

    static const char* NAME;

} ;

class Rx2MajorAlarm : public AlarmLatched
{
public:
	Rx2MajorAlarm() ;

	virtual ~Rx2MajorAlarm() ;

    static const char* NAME;

} ;

class Rx3MajorAlarm : public AlarmLatched
{
public:
	Rx3MajorAlarm() ;

	virtual ~Rx3MajorAlarm() ;

    static const char* NAME;

} ;

class Rx4MajorAlarm : public AlarmLatched
{
public:
	Rx4MajorAlarm() ;

	virtual ~Rx4MajorAlarm() ;

    static const char* NAME;

} ;

}

#endif /* RX_MAJOR_ALARM_H_ */
