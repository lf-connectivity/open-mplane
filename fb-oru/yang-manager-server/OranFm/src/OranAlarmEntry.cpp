/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranAlarmEntry.cpp
 * \brief
 *
 *
 * \details
 *
 */

#include "OranAlarmEntry.h"

using namespace Mplane;

const std::string OranAlarmEntry::mName = "Alarm";
const std::string OranAlarmEntry::mRadioAlarmStr = "RadioAlarm";
const std::string OranAlarmEntry::mDescriptionStr = "Description";
const std::string OranAlarmEntry::mFaultIdStr = "FaultId";
const std::string OranAlarmEntry::mSeverityStr = "Severity";
const std::string OranAlarmEntry::mAffectedObjsStr = "AffectedObjs";
const std::string OranAlarmEntry::mObjStr = "Obj";

OranAlarmEntry::OranAlarmEntry()
	: mDescription("Unknown Fault")
	, mFaultId("1000")					// ID number for unknown fault
	, mSeverity("MINOR")
{
}

OranAlarmEntry::OranAlarmEntry(const std::string & radioAlarm,
                       const std::string & description,
                       const std::string & faultId,
                       const std::string & severity,
                       const std::vector<std::string> & objs)
	: mRadioAlarm(radioAlarm)
	, mDescription(description)
	, mFaultId(faultId)
	, mSeverity(severity)
	, mAffectedObjs(objs)
{
}

void OranAlarmEntry::setRadioAlarm(std::string radioAlarm)
{
	mRadioAlarm = radioAlarm;
}

std::string OranAlarmEntry::getRadioAlarm(void) const
{
	return mRadioAlarm;
}

void OranAlarmEntry::setDescription(std::string description)
{
	mDescription = description;
}

std::string OranAlarmEntry::getDescription(void) const
{
	return mDescription;
}

void OranAlarmEntry::setFaultId(std::string faultId)
{
	mFaultId = faultId;
}

std::string OranAlarmEntry::getFaultId(void) const
{
	return mFaultId;
}

void OranAlarmEntry::setSeverity(std::string severity)
{
	mSeverity = severity;
}

std::string OranAlarmEntry::getSeverity(void) const
{
	return mSeverity;
}

std::vector<std::string> OranAlarmEntry::getAffectedObjs() const
{
	return mAffectedObjs;
}

void OranAlarmEntry::show(std::ostream & os)
{
	os << "Alarm:  " << getRadioAlarm() << std::endl;
	os << "  " << "Description : " << getDescription() << std::endl;
	os << "  " << "FaultId     : " << getFaultId() << std::endl;
	os << "  " << "Severity    : " << getSeverity() << std::endl;
}
