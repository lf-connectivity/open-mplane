#ifndef _RRH_ALARMS_H_
#define _RRH_ALARMS_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RrhAlarms.h
 * \brief     A file to contain the RRH radio alarm handler
 *
 *
 * \brief     This file defines RRH radio alarm handler
 *
 */

// Includes go here, before the namespace
#include <vector>
#include <memory>

#include "IAlarm.h"

namespace Mplane
{
/*! \brief A RRH radio application alarm class.
 *
 * The Alarm class defines a single alarm, its associated data and related
 * interfaces.
 *
 * Each Alarm object in the system is instantiated during application initialisation.
 */
class RrhAlarms
{
public:

	static std::shared_ptr<RrhAlarms> getInstance();


	RrhAlarms();
	virtual ~RrhAlarms();

	// PLL major alarm
	std::shared_ptr<IAlarm> mPllMajorAlarm;

	// CPRI0 major alarm
	std::shared_ptr<IAlarm> mCpri0MajorAlarm;

	// Radio temperature alarms
	std::shared_ptr<IAlarm> mRadioTempMajorAlarm;
	std::shared_ptr<IAlarm> mRadioTempMinorAlarm;

	// Rx major alarms vector
	std::vector<std::shared_ptr<IAlarm>> mRxMajorAlarm;

	// PA alarms vectors
	std::vector<std::shared_ptr<IAlarm>> mPaTempMajorAlarm;
	std::vector<std::shared_ptr<IAlarm>> mPaTempMinorAlarm;

	// Tx shutdown alarms vector
	std::vector<std::shared_ptr<IAlarm>> mTxShutdownAlarm;

	// Tx degraded alarms vector
	std::vector<std::shared_ptr<IAlarm>> mTxDegradedAlarm;

	// VSWR alarms vector
	std::vector<std::shared_ptr<IAlarm>> mVswrTxAlarm;

	// Tx baseband IQ alarms vector
	std::vector<std::shared_ptr<IAlarm>> mTxBbIqAlarm;

	// Heartbeat alarm
	std::shared_ptr<IAlarm> mHeartBeatAlarm;

	// Tx DPD minor alarms vector
	std::vector<std::shared_ptr<IAlarm>> mTxDpdMinorAlarm;


};  // end of class RrhAlarm

}
#endif /* _RRH_ALARMS_H_ */
