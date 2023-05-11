/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranFaultConfigData.cpp
 * \brief     Represents FaultConfig.xml
 *
 *
 * \details   Reads in information from FaultConfig.xml and presents it to the rest of the program
 *
 */
#include "OranFaultConfigData.h"

using namespace Mplane;

OranFaultConfigData::OranFaultConfigData(const char * filePath)
	: CommonConfigBase("FaultConfig", "ORAN")
	, mConfigFilePath(filePath)
{
}

OranFaultConfigData::~OranFaultConfigData()
{
}

void OranFaultConfigData::show()
{
}

ReturnType::State OranFaultConfigData::load()
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

std::shared_ptr<OranAlarmMapping> OranFaultConfigData::getAlarmMapping()
{
	return mAlarmMap;
}

bool OranFaultConfigData::parseAlarmMap(tinyxml2::XMLElement *node)
{
	if (node->Name() == OranAlarmMapping::mName) // Is the first element the correct element?
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

bool OranFaultConfigData::extractAlarmTable(std::shared_ptr<OranAlarmMapping> alarmMapping,
		tinyxml2::XMLElement *node)
{
	if (node->Name() == OranAlarmEntry::mName) // is this an AlarmTable element?
	{
		tinyxml2::XMLElement *ele = node->FirstChildElement();

		if (ele->Name() == OranAlarmEntry::mRadioAlarmStr)
		{
			std::string radioAlarm = ele->GetText();

			ele = ele->NextSiblingElement();

			if (ele->Name() == OranAlarmEntry::mDescriptionStr)
			{
				std::string description = ele->GetText();

				ele = ele->NextSiblingElement();

				if (ele->Name() == OranAlarmEntry::mFaultIdStr)
				{
					std::string faultId = ele->GetText();

					ele = ele->NextSiblingElement();

					if (ele->Name() == OranAlarmEntry::mSeverityStr)
					{
						std::string severity = ele->GetText();

						ele = ele->NextSiblingElement();

						if (ele->Name() == OranAlarmEntry::mAffectedObjsStr)
						{
							// Need to move on to the next node for the objects affected
							tinyxml2::XMLElement *nextNode = ele->FirstChildElement();

							std::vector<std::string> affectedObjs;

							for (unsigned int loop = 0; nextNode != nullptr; loop++)
							{
								if (nextNode->Name() == OranAlarmEntry::mObjStr)
								{
									if (nextNode->GetText() != nullptr)
									{
										affectedObjs.push_back(nextNode->GetText());

										nextNode = nextNode->NextSiblingElement();
									}
								}
							}

							// We have extracted all the elements. Create alarm table and add it to the alarm mapping.
							std::shared_ptr<OranAlarmEntry> alarmTable(
									new OranAlarmEntry(radioAlarm, description, faultId, severity, affectedObjs));

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

void OranFaultConfigData::getAttributeMap(tinyxml2::XMLElement * node,
		AttrMap & attrMap) const
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
