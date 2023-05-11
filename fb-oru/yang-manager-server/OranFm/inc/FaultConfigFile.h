#ifndef _MPLANE__FAULT_CONFIG_H_
#define _MPLANE__FAULT_CONFIG_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FaultConfigFile.h
 * \brief     Represents FaultConfig.xml
 *
 *
 * \details   Reads in information from FaultConfig.xml and presents it to the rest of the program
 *
 */

#include <memory>
#include <list>
#include <vector>
#include <map>

#include "libtinyxml2/tinyxml2.h"

#include "string.h"
#include "CommonConfigBase.h"
#include "ConfigDownload.h"
#include "Loggable.h"

namespace Mplane
{

class AlarmEntry
{
public:
	/*!
	 * \brief Default constructor sets the fault ID to unknown fault
	 */
	AlarmEntry();

	AlarmEntry(const std::string& radioAlarm, const std::string &description,
			   const std::string &faultId,
			   const std::string &severity, const std::vector<std::string> &objs);

	void setRadioAlarm(std::string radioAlarm);

	std::string getRadioAlarm(void) const;

	void setDescription(std::string Description);

	std::string getDescription(void) const;

	void setFaultId(std::string FaultId);

	std::string getFaultId(void) const;

	void setSeverity(std::string severity);

	std::string getSeverity(void) const;

	std::vector<std::string> getAffectedObjs() const;

    static const std::string name;
    static const std::string RadioAlarmStr;
    static const std::string DescriptionStr;
    static const std::string FaultIdStr;
    static const std::string SeverityStr;
    static const std::string AffectedObjsStr;
    static const std::string ObjStr;

private:
    std::string mRadioAlarm;
    std::string mDescription;
    std::string mFaultId;
    std::string mSeverity;
    std::vector<std::string> mAffectedObjs;
};

class OranAlarmMapping
{
public:
	OranAlarmMapping(const std::string& version, const std::string& country, const std::string& facility, const std::string& theoperator) :
        mVersion( version ),
        mCountry( country ),
        mFacility( facility ),
        mOperator( theoperator )
    {
    }

    void addAlarmTable(std::shared_ptr<AlarmEntry> alarmTable);
    std::shared_ptr<AlarmEntry> getAlarmEntry(const std::string &radioAlarm);

    static const std::string name;

protected:

	std::string mVersion;
	std::string mCountry;
	std::string mFacility;
	std::string mOperator;

    std::list<std::shared_ptr<AlarmEntry>> mAlarmTables;
};

/*!
\brief A class to read in a fault config file
 */
class OranFaultConfigData: public CommonConfigBase
{
public:
    explicit OranFaultConfigData(const char *filePath);


    virtual void show()
    {
    }

    virtual ReturnType::State load();

    std::shared_ptr<OranAlarmMapping> getAlarmMapping( void );


protected:

    bool parseAlarmMap(tinyxml2::XMLElement* node) ;

    bool extractAlarmTable(std::shared_ptr<OranAlarmMapping> alarmMapping, tinyxml2::XMLElement* node) ;

    // Map of attributes
    typedef std::map<std::string, std::string> AttrMap ;
    typedef AttrMap::iterator AttrMapIterator ;

    /**
     * Set to the full path of the config file for this object
     */
    std::string mConfigFilePath;

    std::shared_ptr<OranAlarmMapping> mAlarmMap;

    /**
     * Fill a map with the attributes
     * @param attrMap
     */
    void getAttributeMap(tinyxml2::XMLElement* node, AttrMap& attrMap) const ;
};

}

#endif /* _MPLANE__FAULT_CONFIG_H_ */
