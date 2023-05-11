/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AlarmPackage.h
 * \brief     Package up creation of IAlarm and registering the alarm with fault(s)
 *
 *
 * \details
 *
 */


#ifndef ALARMPACKAGE_H_
#define ALARMPACKAGE_H_

#include "IAlarm.h"
#include "IAlarmPackage.h"

namespace Mplane {

class AlarmPackage : public IAlarmPackage
{
public:
	AlarmPackage() ;
	virtual ~AlarmPackage() ;

protected:
	/**
	 * Derived objects use this method to associate faults with the new IAlarm object
	 * @param alarm
	 */
	virtual void addAlarm(std::shared_ptr<IAlarm> alarm, const std::set<std::string>& names) override ;
} ;

}

#endif /* ALARMPACKAGE_H_ */
