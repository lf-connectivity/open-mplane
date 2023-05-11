/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioTempMinorAlarm.h
 * \brief     Alarm for Radio Temperature Minor faults
 *
 *
 * \details
 *
 */


#ifndef RADIO_TEMP_MINOR_ALARM_H_
#define RADIO_TEMP_MINOR_ALARM_H_

#include "Alarm.h"

namespace Mplane {

class RadioTempMinorAlarm : public Alarm
{
public:
	RadioTempMinorAlarm() ;

	virtual ~RadioTempMinorAlarm() ;

    static const char* NAME;

} ;

}

#endif /* RADIO_TEMP_MINOR_ALARM_H_ */
