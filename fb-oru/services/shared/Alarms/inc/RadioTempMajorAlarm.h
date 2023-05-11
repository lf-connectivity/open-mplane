/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioTempMajorAlarm.h
 * \brief     Alarm for Radio Temperature Major faults
 *
 *
 * \details
 *
 */


#ifndef RADIO_TEMP_MAJOR_ALARM_H_
#define RADIO_TEMP_MAJOR_ALARM_H_

#include "AlarmLatched.h"

namespace Mplane {

/**
 * Board level under temperature alarm for the TX1 path
 */
class RadioTempMajorAlarm : public AlarmLatched
{
public:
	RadioTempMajorAlarm() ;

	virtual ~RadioTempMajorAlarm() ;

	static const char* NAME;
} ;

}

#endif /* RADIO_TEMP_MAJOR_ALARM_H_ */
