/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CUPlaneConnectivityMajorAlarm.h
 * \brief     ORAN C/U-Plane Connectivity major alarm
 *
 *
 * \details
 *
 */


#ifndef ALARM_CUPLANE_CONNECTIVITY_MAJOR_H_
#define ALARM_CUPLANE_CONNECTIVITY_MAJOR_H_

#include "Alarm.h"

namespace Mplane {

class CUPlaneConnectivityMajorAlarm : public Alarm
{
public:
	CUPlaneConnectivityMajorAlarm() ;

	virtual ~CUPlaneConnectivityMajorAlarm() ;

	static const char* NAME;

} ;

}

#endif /* ALARM_CUPLANE_CONNECTIVITY_MAJOR_H_ */
