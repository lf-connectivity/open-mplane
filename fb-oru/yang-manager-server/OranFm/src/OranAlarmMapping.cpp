/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranAlarmMapping.cpp
 * \brief     Maps ORAN alarms to radio alarms
 *
 *
 * \details   Maps ORAN alarms to radio alarms
 *
 */
#include "OranAlarmMapping.h"

using namespace Mplane;

const std::string OranAlarmMapping::mName = "AlarmMapping";

OranAlarmMapping::OranAlarmMapping(const std::string & version,
                                   const std::string & country,
                                   const std::string & facility,
                                   const std::string & theOperator)
	: mVersion(version)
	, mCountry(country)
	, mFacility(facility)
	, mOperator(theOperator)
{
}

OranAlarmMapping::~OranAlarmMapping()
{
}

void OranAlarmMapping::addAlarmTable(std::shared_ptr<OranAlarmEntry> alarmTable)
{
	mAlarmTables.push_back(alarmTable);
}

std::shared_ptr<OranAlarmEntry> OranAlarmMapping::getAlarmEntry(const std::string & radioAlarm)
{
	for (auto it = mAlarmTables.begin(); it != mAlarmTables.end(); ++it)
	{
		if ((*it)->getRadioAlarm() == radioAlarm)
		{
			return *it;
		}
	}
	return std::make_shared<OranAlarmEntry>();
}
