/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranAlarmEntry.h
 * \brief
 *
 *
 * \details
 *
 */
#ifndef _ORANFM_ORANALARMENTRY_H_
#define _ORANFM_ORANALARMENTRY_H_

#include <memory>
#include <string>
#include <vector>
#include <iostream>

namespace Mplane
{

class OranAlarmEntry
{
public:
	/*!
	 * \brief Default constructor sets the fault ID to unknown fault
	 */
	OranAlarmEntry();

	OranAlarmEntry(const std::string & radioAlarm,
	               const std::string & description,
	               const std::string & faultId,
	               const std::string & severity,
	               const std::vector<std::string> & objs);

	void setRadioAlarm(std::string radioAlarm);

	std::string getRadioAlarm(void) const;

	void setDescription(std::string description);

	std::string getDescription(void) const;

	void setFaultId(std::string faultId);

	std::string getFaultId(void) const;

	void setSeverity(std::string severity);

	std::string getSeverity(void) const;

	std::vector<std::string> getAffectedObjs() const;

	void show(std::ostream & os = std::cout);

	static const std::string mName;
	static const std::string mRadioAlarmStr;
	static const std::string mDescriptionStr;
	static const std::string mFaultIdStr;
	static const std::string mSeverityStr;
	static const std::string mAffectedObjsStr;
	static const std::string mObjStr;

private:

	std::string mRadioAlarm;
	std::string mDescription;
	std::string mFaultId;
	std::string mSeverity;
	std::vector<std::string> mAffectedObjs;
};

}

#endif /* _ORANFM_ORANALARMENTRY_H_ */
