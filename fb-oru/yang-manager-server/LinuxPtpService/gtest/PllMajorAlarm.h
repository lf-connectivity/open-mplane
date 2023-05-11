/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PllMajorAlarm.h
 * \brief     PLL Major Alarms
 *
 *
 * \details
 *
 */


#ifndef CLOCKALARM_H_
#define CLOCKALARM_H_

#include "Alarm.h"

namespace Mplane {

class PllMajorAlarm : public Alarm
{
public:
	PllMajorAlarm() ;

	virtual ~PllMajorAlarm() ;

    static const char* NAME;

} ;

}

#endif /* CLOCKALARM_H_ */
