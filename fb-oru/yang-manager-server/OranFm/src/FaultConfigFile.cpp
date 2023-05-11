/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FaultConfigFile.cpp
 * \brief     Represents FaultConfig.xml
 *
 *
 * \details   Reads in information from FaultConfig.xml and presents it to the rest of the program
 *
 */

#include "IConfigDownloadManagement.h"
#include <map>
#include <memory>

#include <iostream>
#include "FaultConfigFile.h"

using namespace Mplane;

AlarmEntry::AlarmEntry()
	: mDescription("Unknown Fault")
	, mFaultId("1000")					// ID number for unknown fault
	, mSeverity("MINOR")
{}

AlarmEntry::AlarmEntry(const std::string& radioAlarm, const std::string &description,
		   const std::string &faultId,
		   const std::string &severity, const std::vector<std::string> &objs) :
    mRadioAlarm(radioAlarm),
    mDescription(description),
	mFaultId(faultId),
    mSeverity(severity),
	mAffectedObjs(objs)
{}

void AlarmEntry::setRadioAlarm(std::string radioAlarm)
{
	mRadioAlarm = radioAlarm;
}

std::string AlarmEntry::getRadioAlarm(void) const
{
	return mRadioAlarm;
}

void AlarmEntry::setDescription(std::string Description)
{
	mDescription = Description;
}

std::string AlarmEntry::getDescription(void) const
{
	return mDescription;
}

void AlarmEntry::setFaultId(std::string FaultId)
{
	mFaultId = FaultId;
}

std::string AlarmEntry::getFaultId(void) const
{
	return mFaultId;
}

void AlarmEntry::setSeverity(std::string severity)
{
	mSeverity = severity;
}

std::string AlarmEntry::getSeverity(void) const
{
	return mSeverity;
}

std::vector<std::string> AlarmEntry::getAffectedObjs() const
{
	return mAffectedObjs;
}



const std::string AlarmEntry::name = "Alarm";
const std::string AlarmEntry::RadioAlarmStr = "RadioAlarm";
const std::string AlarmEntry::DescriptionStr = "Description";
const std::string AlarmEntry::FaultIdStr = "FaultId";
const std::string AlarmEntry::SeverityStr = "Severity";
const std::string AlarmEntry::AffectedObjsStr = "AffectedObjs";
const std::string AlarmEntry::ObjStr = "Obj";

const std::string OranAlarmMapping::name = "AlarmMapping";

void Mplane::OranAlarmMapping::addAlarmTable(std::shared_ptr<AlarmEntry> alarmTable)
{
	mAlarmTables.push_back(alarmTable);
}

Mplane::OranFaultConfigData::OranFaultConfigData(const char *filePath) :
	CommonConfigBase("FaultConfig", "ORAN"),
	mConfigFilePath(filePath)
{
}

ReturnType::State Mplane::OranFaultConfigData::load()
{
	ReturnType::State status = ReturnType::RT_OK;

	if (isLoaded() != true)
	{
		// Parse the final expanded file
		tinyxml2::XMLDocument doc;
		if (doc.LoadFile(mConfigFilePath.c_str()) != tinyxml2::XML_NO_ERROR)
		{
			eventError("Could not parse file %s", mConfigFilePath.c_str());
			return ReturnType::RT_NOT_FOUND;
		}

		tinyxml2::XMLElement *root_element = doc.RootElement();
		if (root_element == NULL)
		{
			eventError("Invalid xml format in file %s ", mConfigFilePath.c_str());
			return ReturnType::RT_NOT_FOUND;
		}

		if (!parseAlarmMap(root_element))
		{
			eventError("Syntax error in config file %s ", mConfigFilePath.c_str());
			return ReturnType::RT_SYNTAX_ERROR;
		}
		setLoaded(true);
	}
	return status;
}

bool Mplane::OranFaultConfigData::parseAlarmMap(tinyxml2::XMLElement *node)
{
	if (node->Name() == OranAlarmMapping::name) // is the first element the correct element?
	{
		AttrMap attributes;
		attributes["version"] = "";
		attributes["country"] = "";
		attributes["facility"] = "";
		attributes["operator"] = "";
		getAttributeMap(node, attributes);

		std::shared_ptr<OranAlarmMapping> alarmMap(new OranAlarmMapping(attributes["version"], attributes["country"],
				attributes["facility"], attributes["operator"]));

		mAlarmMap = alarmMap;

		for (tinyxml2::XMLElement *cur_node = node->FirstChildElement();
				cur_node; cur_node = cur_node->NextSiblingElement())
		{
			// Get the device definition inside board
			if (!extractAlarmTable(mAlarmMap, cur_node))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool Mplane::OranFaultConfigData::extractAlarmTable(std::shared_ptr<OranAlarmMapping> alarmMapping,
		tinyxml2::XMLElement *node)
{
	if (node->Name() == AlarmEntry::name) // is this a AlarmTable element?
	{
		tinyxml2::XMLElement *ele = node->FirstChildElement();

		if (ele->Name() == AlarmEntry::RadioAlarmStr)
		{
			std::string radioAlarm = ele->GetText();

			ele = ele->NextSiblingElement();

			if (ele->Name() == AlarmEntry::DescriptionStr)
			{
				std::string description = ele->GetText();

				ele = ele->NextSiblingElement();

				if (ele->Name() == AlarmEntry::FaultIdStr)
				{
					std::string faultId = ele->GetText();

					ele = ele->NextSiblingElement();

					if (ele->Name() == AlarmEntry::SeverityStr)
					{
						std::string severity = ele->GetText();

						ele = ele->NextSiblingElement();

						if (ele->Name() == AlarmEntry::AffectedObjsStr)
						{
							// Need to move on to the next node for the objects affected
							tinyxml2::XMLElement *nextNode = ele->FirstChildElement();

							std::vector<std::string> affectedObjs;

							for (unsigned int loop = 0; nextNode != nullptr; loop++)
							{
								if (nextNode->Name() == AlarmEntry::ObjStr)
								{
									if (nextNode->GetText() != nullptr)
									{
										affectedObjs.push_back(nextNode->GetText());

										nextNode = nextNode->NextSiblingElement();
									}
								}
							}

							// We have extracted all the elements. Create alarm table and add it to the alarm mapping.
							std::shared_ptr<AlarmEntry> alarmTable(
									new AlarmEntry(radioAlarm, description, faultId, severity, affectedObjs));

							alarmMapping->addAlarmTable(alarmTable);
						}
					}
				}
			}
		}
		return true;
	}
	return false;
}

std::shared_ptr<OranAlarmMapping> Mplane::OranFaultConfigData::getAlarmMapping(void)
{
	return mAlarmMap;
}

void Mplane::OranFaultConfigData::getAttributeMap(tinyxml2::XMLElement *node,
		AttrMap &attrMap) const
{
	for (AttrMapIterator iter(attrMap.begin()); iter != attrMap.end(); ++iter)
	{
		const char *attr(node->Attribute(iter->first.c_str()));
		if (attr)
		{
			iter->second = std::string(attr);
		}
	}
}

std::shared_ptr<AlarmEntry> Mplane::OranAlarmMapping::getAlarmEntry(const std::string &radioAlarm)
{
	for (auto it = mAlarmTables.begin(); it != mAlarmTables.end(); ++it)
	{
		if ((*it)->getRadioAlarm() == radioAlarm)
		{
			return *it;
		}
	}
	return std::make_shared<AlarmEntry>();
}
