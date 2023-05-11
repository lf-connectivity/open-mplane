/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HeartBeatAlarm.h
 * \brief     Heart Beat Major Alarms
 *
 *
 * \details
 *
 */


#ifndef HEART_BEAT_ALARM_H_
#define HEART_BEAT_ALARM_H_

#include "Alarm.h"

namespace Mplane {

class HeartBeatAlarm : public Alarm
{
public:
	HeartBeatAlarm() ;

	virtual ~HeartBeatAlarm() ;

    static const char* NAME;

} ;

}

#endif /* HEART_BEAT_ALARM_H_ */
