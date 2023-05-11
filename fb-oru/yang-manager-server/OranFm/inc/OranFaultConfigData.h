/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranFaultConfigData.h
 * \brief     Represents FaultConfig.xml
 *
 *
 * \details   Reads in information from FaultConfig.xml and presents it to the rest of the program
 *
 */
#ifndef _ORANFM_FAULTCONFIGFILE_H_
#define _ORANFM_FAULTCONFIGFILE_H_

#include <memory>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <iostream>

#include "libtinyxml2/tinyxml2.h"

#include "CommonConfigBase.h"
#include "OranAlarmEntry.h"
#include "OranAlarmMapping.h"


namespace Mplane
{

/*!
\brief A class to read in a fault configuration file
 */
class OranFaultConfigData: public CommonConfigBase
{
public:
	explicit OranFaultConfigData(const char * filePath);
	~OranFaultConfigData();

	virtual void show();

	virtual ReturnType::State load();

	std::shared_ptr<OranAlarmMapping> getAlarmMapping();


protected:

	bool parseAlarmMap(tinyxml2::XMLElement * node);

	bool extractAlarmTable(std::shared_ptr<OranAlarmMapping> alarmMapping, tinyxml2::XMLElement * node);

	// Map of attributes
	typedef std::map<std::string, std::string> AttrMap;
	typedef AttrMap::iterator AttrMapIterator;

	/**
	 * Set to the full path of the config file for this object
	 */
	std::string mConfigFilePath;

	std::shared_ptr<OranAlarmMapping> mAlarmMap;

	/**
	 * Fill a map with the attributes
	 * @param attrMap
	 */
	void getAttributeMap(tinyxml2::XMLElement * node, AttrMap & attrMap) const;
};

}

#endif /* _ORANFM_FAULTCONFIGFILE_H_ */
