/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranAlarmMapping.h
 * \brief     Maps ORAN alarms to radio alarms
 *
 *
 * \details   Maps ORAN alarms to radio alarms
 *
 */
#ifndef _ORANFM_ORANALARMMAPPING_H_
#define _ORANFM_ORANALARMMAPPING_H_

#include <memory>
#include <string>
#include <list>
#include <vector>
#include <iostream>

#include "OranAlarmMapping.h"
#include "OranAlarmEntry.h"

namespace Mplane
{

class OranAlarmMapping
{
public:
	OranAlarmMapping(const std::string & version,
	                 const std::string & country,
	                 const std::string & facility,
	                 const std::string & theOperator);
	~OranAlarmMapping();

	void addAlarmTable(std::shared_ptr<OranAlarmEntry> alarmTable);
	std::shared_ptr<OranAlarmEntry> getAlarmEntry(const std::string & radioAlarm);

	static const std::string mName;

protected:

	std::string mVersion;
	std::string mCountry;
	std::string mFacility;
	std::string mOperator;

	std::list<std::shared_ptr<OranAlarmEntry>> mAlarmTables;
};

}

#endif /* _ORANFM_ORANALARMMAPPING_H_ */
