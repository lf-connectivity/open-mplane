/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PaTempMinorAlarm.h
 * \brief     Alarm for all Pa Temperature Minor faults
 *
 *
 * \details
 *
 */


#ifndef PA_TEMP_MINOR_ALARM_H_
#define PA_TEMP_MINOR_ALARM_H_

#include "Alarm.h"

namespace Mplane {

class Pa1TempMinorAlarm : public Alarm
{
public:
	Pa1TempMinorAlarm() ;

	virtual ~Pa1TempMinorAlarm() ;

    static const char* NAME;

} ;

class Pa2TempMinorAlarm : public Alarm
{
public:
	Pa2TempMinorAlarm() ;

	virtual ~Pa2TempMinorAlarm() ;

    static const char* NAME;

} ;

class Pa3TempMinorAlarm : public Alarm
{
public:
	Pa3TempMinorAlarm() ;

	virtual ~Pa3TempMinorAlarm() ;

    static const char* NAME;

} ;

class Pa4TempMinorAlarm : public Alarm
{
public:
	Pa4TempMinorAlarm() ;

	virtual ~Pa4TempMinorAlarm() ;

    static const char* NAME;

} ;

}

#endif /* PA_TEMP_MINOR_ALARM_H_ */
