/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AlarmCUPlaneConnectivityMajor.h
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

class AlarmCUPlaneConnectivityMajor : public Alarm
{
public:
	AlarmCUPlaneConnectivityMajor() ;

	virtual ~AlarmCUPlaneConnectivityMajor() ;

	static const char* NAME;

	static const char* DESCRIPTION;

} ;

}

#endif /* ALARM_CUPLANE_CONNECTIVITY_MAJOR_H_ */
