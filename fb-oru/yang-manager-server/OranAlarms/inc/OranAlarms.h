/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranAlarms.h
 * \brief     A file to contain the ORAN alarm handler
 *
 *
 * \brief     This file defines ORAN alarm handler
 *
 */

#ifndef _ORAN_ALARMS_H_
#define _ORAN_ALARMS_H_

// Includes go here, before the namespace
#include <vector>
#include <memory>

#include "IAlarm.h"

namespace Mplane
{
/*! \brief ORAN alarms class.
 *
 * The Alarm class contains all the ORAN alarms and is instantiated
 * during application initialisation.
 */
class OranAlarms
{
public:
	static std::shared_ptr<OranAlarms> getInstance();


	OranAlarms();
	virtual ~OranAlarms();

	// C/U-Plane connectivity alarms
	std::shared_ptr<IAlarm> mCUPlaneConnectivityMajorAlarm;
	std::shared_ptr<IAlarm> mCUPlaneConnectivityMinorAlarm;


};  // end of class OranAlarms

}
#endif /* _ORAN_ALARMS_H_ */
