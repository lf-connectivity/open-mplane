/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PaTempMajorAlarm.h
 * \brief     Alarm for all Pa  Temperature Major faults
 *
 *
 * \details
 *
 */


#ifndef PA_TEMP_MAJOR_ALARM_H_
#define PA_TEMP_MAJOR_ALARM_H_

#include "AlarmLatched.h"

namespace Mplane {

class Pa1TempMajorAlarm : public AlarmLatched
{
public:
	Pa1TempMajorAlarm() ;

	virtual ~Pa1TempMajorAlarm() ;

    static const char* NAME;

} ;

class Pa2TempMajorAlarm : public AlarmLatched
{
public:
	Pa2TempMajorAlarm() ;

	virtual ~Pa2TempMajorAlarm() ;

    static const char* NAME;

} ;

class Pa3TempMajorAlarm : public AlarmLatched
{
public:
	Pa3TempMajorAlarm() ;

	virtual ~Pa3TempMajorAlarm() ;

    static const char* NAME;

} ;

class Pa4TempMajorAlarm : public AlarmLatched
{
public:
	Pa4TempMajorAlarm() ;

	virtual ~Pa4TempMajorAlarm() ;

    static const char* NAME;

} ;

}

#endif /* PA_TEMP_MAJOR_ALARM_H_ */
