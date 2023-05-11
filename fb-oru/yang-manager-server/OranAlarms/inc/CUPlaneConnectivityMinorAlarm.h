/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CUPlaneConnectivityMinorAlarm.h
 * \brief     ORAN C/U-Plane Connectivity minor alarm
 *
 *
 * \details
 *
 */


#ifndef ALARM_CUPLANE_CONNECTIVITY_MINOR_H_
#define ALARM_CUPLANE_CONNECTIVITY_MINOR_H_

#include "Alarm.h"

namespace Mplane {

class CUPlaneConnectivityMinorAlarm : public Alarm
{
public:
	CUPlaneConnectivityMinorAlarm() ;

	virtual ~CUPlaneConnectivityMinorAlarm() ;

	static const char* NAME;

} ;

}

#endif /* ALARM_CUPLANE_CONNECTIVITY_MINOR_H_ */
