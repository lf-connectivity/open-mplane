/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AlarmBuilder.h
 * \brief     Creates and stores IAlarm objects (creating the alarms for the application)
 *
 *
 * \details
 *
 */


#ifndef ALARMBUILDER_H_
#define ALARMBUILDER_H_

#include <memory>

#include "IAlarmPackage.h"
#include "IAlarmBuilder.h"

namespace Mplane {

class AlarmBuilder : public IAlarmBuilder
{
public:
	AlarmBuilder() ;
	virtual ~AlarmBuilder() ;

protected:
	/**
	 * Derived objects use this method to create and store new IAlarmPackage objects
	 */
	virtual void addAlarmPackage(std::shared_ptr<IAlarmPackage> package) override ;
} ;

}

#endif /* ALARMBUILDER_H_ */
