/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonIdEeprom.cpp
 * \brief     A file to define common implementation of an ID EEPROM
 *
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "GlobalTypeDefs.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "CommonIdEeprom.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

const UINT32 CommonIdEeprom::IdEepromMaxSize(32768);
const UINT8 CommonIdEeprom::ReadSize(64);

const std::string ModuleDescription::name = "ModuleDescription";
const std::string ModuleDescription::versionStr("version");
const std::string ModuleDescription::countryStr("country");
const std::string ModuleDescription::facilityStr("facility");
const std::string ModuleDescription::operatorStr("operator");

const std::string HwModule::name("Module");
const std::string HwModule::nameStr("Name");
const std::string HwModule::typeStr("Type") ;
const std::string HwModule::dateStr("Date") ;
const std::string HwModule::descriptionStr("Description") ;
const std::string HwModule::manufacturerStr("Manufacturer");
const std::string HwModule::productCodeStr("ProductCode");
const std::string HwModule::aaProductCodeStr("AAProductCode");
const std::string HwModule::softwareVerStr("SoftwareVer");
const std::string HwModule::hardwareVerStr("HardwareVer");
const std::string HwModule::serialNumStr("SerialNum");
const std::string HwModule::featureStr("Features");
const std::string HwModule::configItemsStr("ConfigurationItems");

//=============================================================================================================
// ModuleConfig
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::ModuleConfig::ModuleConfig()
{
}

Mplane::ModuleConfig::~ModuleConfig()
{
}

//=============================================================================================================
// ModuleFeatures
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::ModuleFeatures::ModuleFeatures()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::ModuleFeatures::~ModuleFeatures()
{
}


//=============================================================================================================
// HwModule
//=============================================================================================================

static const std::vector<std::string> HwModuleTypes
{
	"PowerSupply",
	"PaFinalDriver",
	"PaPreFinalDriver",
	"PaInterface",
	"8LedInterface",
	"ExternalPa",
	"ExternalFilter",
	"Unknown"
};

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::HwModule::moduleTypeToStr(HwModule::moduleTypes_T type)
{
	return HwModuleTypes[type];
}

//-------------------------------------------------------------------------------------------------------------
HwModule::moduleTypes_T Mplane::HwModule::strToModuleType(const std::string& typeStr)
{
	auto entry(std::find(HwModuleTypes.begin(), HwModuleTypes.end(), typeStr)) ;
	if (entry == HwModuleTypes.end())
		return HwModule::TYPE_UNKNOWN ;

	return static_cast<HwModule::moduleTypes_T>(std::distance(HwModuleTypes.begin(), entry)) ;
}

//-------------------------------------------------------------------------------------------------------------
Mplane::HwModule::HwModule(const std::string& date, const std::string& name, const std::string& type,
		const std::string& desc, const std::string& manu, const std::string& productCode,
		const std::string& aaProductCode, const std::string& swVer, const std::string& hwVer,
		const std::string serialNum) :
	mDate(date),
	mName(name),
	mType(TYPE_UNKNOWN),
	mDescription(desc),
	mManufacturer(manu),
	mProductCode(productCode),
	mAAProductCode(aaProductCode),
	mSoftwareVer(swVer),
	mHardwareVer(hwVer),
	mSerialNum(serialNum),
	mFeatures(),
	mConfig()
{
	mType = strToModuleType(type);
}

//-------------------------------------------------------------------------------------------------------------
Mplane::HwModule::~HwModule()
{
	mFeatures.clear();
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::HwModule::addFeatures( std::shared_ptr<ModuleFeatures> features )
{
	mFeatures.push_back( features );
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ModuleFeatures> Mplane::HwModule::getFeatures( void )
{
	return mFeatures.front();
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::HwModule::addConfig( std::shared_ptr<ModuleConfig> config )
{
	mConfig.push_back( config );
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ModuleConfig> Mplane::HwModule::getConfig( void )
{
	return mConfig.front();
}


//=============================================================================================================
// ModuleDescription
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::ModuleDescription::ModuleDescription(const std::string& version, const std::string& country,
		const std::string& facility, const std::string& theoperator):
				mVersion( version ), mCountry( country ),
				mFacility( facility ), mOperator( theoperator),
				mModuleData()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::ModuleDescription::~ModuleDescription()
{
	mModuleData.clear();
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<HwModule> Mplane::ModuleDescription::getModule(void)
{
	//It is expected, that there is information for a single module in the ID EEPROM xml file
	return mModuleData.front();
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::ModuleDescription::addModule( std::shared_ptr<HwModule> module )
{
	mModuleData.push_back(module);
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::ModuleDescription::getVersion() const
{
	return mVersion ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::ModuleDescription::getCountry() const
{
	return mCountry ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::ModuleDescription::getFacility() const
{
	return mFacility ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::ModuleDescription::getOperator() const
{
	return mOperator ;
}

//=============================================================================================================
// CommonIdEeprom
//=============================================================================================================

Mplane::CommonIdEeprom::CommonIdEeprom(UINT32 capacity) :
		Loggable( "IDEeprom", "HW" ),
		mCapacity(capacity),
		mModuleDesc(),
		mEepromDataLoaded(false)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::CommonIdEeprom::~CommonIdEeprom()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::CommonIdEeprom::readAtomic(UINT32 byteAddress, UINT8  numberOfBytesToRead, UINT8* bufferPtrToWriteTo )
{
	return (ReturnType::RT_OK);
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::CommonIdEeprom::writeAtomic(UINT32 byteAddress, UINT16 dataLen, UINT8* dataPtr)
{
	return (ReturnType::RT_OK);
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::CommonIdEeprom::read( UINT8  numberOfBytesToRead, UINT8* bufferPtrToWriteTo )
{
	return (ReturnType::RT_OK);
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::CommonIdEeprom::write(UINT32 byteAddress, UINT16 dataLen, UINT8* dataPtr)
{
	return (ReturnType::RT_OK);
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::CommonIdEeprom::load(void)
{
	mEepromDataLoaded = false;

	ReturnType::State status = ReturnType::RT_OK;

	UINT32 numBytes = 0;

	std::vector<UINT8> eepromData;
	eepromData.resize(CommonIdEeprom::ReadSize);

	std::string readBuffer;

	std::ofstream outFile;
	outFile.open("/tmp/ideeprom.xml", std::ios_base::out | std::ios_base::trunc);

	if (!outFile.is_open())
		return ReturnType::RT_OPERATION_FAILED ;

	//Read the file till either a null terminator is found or all the EEPROM is read
	while (numBytes < CommonIdEeprom::IdEepromMaxSize)
	{
		//Read the ID EEPROM contents into a buffer
		ReturnType::State readStatus = read(CommonIdEeprom::ReadSize, eepromData.data());
		if (readStatus != ReturnType::RT_OK)
		{
			return readStatus;
		}
		numBytes += CommonIdEeprom::ReadSize;

		//Check if null terminator is present
		auto pos = std::find(eepromData.begin(), eepromData.end(), '\0');

		if (pos == eepromData.end())
		{
			pos = std::find(eepromData.begin(), eepromData.end(), 0xFF);
		}

		//Copy the data into a string
		if (pos != eepromData.end())
		{
			readBuffer.assign(eepromData.begin(), pos);
		}
		else
		{
			readBuffer.assign(eepromData.begin(), eepromData.end());
		}

		//Copy the contents into output file
		outFile << readBuffer;

		//If null terminator is found, then stop reading EEPROM
		if (pos != eepromData.end())
			break;
	}
	//Close file
	outFile.close();


	//Parse xml file read from ID EEPROM
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile("/tmp/ideeprom.xml") != tinyxml2::XML_NO_ERROR)
	{
		eventError("Could not parse file /tmp/ideeprom.xml");
		return ReturnType::RT_NOT_FOUND;
	}

	//Check if xml format is correct
	tinyxml2::XMLElement *root_element = doc.RootElement();
	if (root_element == NULL)
	{
		eventError("Invalid xml format in ID EEPROM");
		return ReturnType::RT_NOT_FOUND;
	}

	//Parse buffer to populate Module information
	if (!parseModuleDescription(root_element))
	{
		eventError("Syntax error in ID EEPROM");
		return ReturnType::RT_SYNTAX_ERROR;
	}

	mEepromDataLoaded = true;

	return status;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::CommonIdEeprom::isLoaded(void)
{
	return mEepromDataLoaded;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ModuleDescription> Mplane::CommonIdEeprom::getModuleDescription(void)
{
	return mModuleDesc;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::CommonIdEeprom::parseModuleDescription(tinyxml2::XMLElement* node)
{
	if (node->Name() != ModuleDescription::name) // is the first element the correct element?
		return false ;

	AttrMap attributes;
	attributes[ModuleDescription::versionStr] = "";
	attributes[ModuleDescription::countryStr] = "";
	attributes[ModuleDescription::facilityStr] = "";
	attributes[ModuleDescription::operatorStr] = "";
	getAttributeMap(node, attributes);

	mModuleDesc = createModuleDesc(attributes["version"], attributes["country"],
					attributes["facility"], attributes["operator"]);

	for (tinyxml2::XMLElement* cur_node = node->FirstChildElement();
			cur_node; cur_node = cur_node->NextSiblingElement())
	{
		// Get the device definition inside board
		if (!extractHwModule(mModuleDesc, cur_node))
			return false;
	}
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::CommonIdEeprom::extractHwModule(std::shared_ptr<ModuleDescription> mModuleDesc, tinyxml2::XMLElement* node)
{
	if (node->Name() != HwModule::name)    // is the the Module element?
		return false ;

	tinyxml2::XMLElement* ele = node->FirstChildElement();

	//Parse the date
	if (ele->Name() != HwModule::dateStr)
		return false ;
	std::string date = "";
	date = ele->GetText();

	//Parse the name
	ele = ele->NextSiblingElement();
	if (ele->Name() != HwModule::nameStr)
		return false ;
	std::string name = "";
	name = ele->GetText();

	//Parse the type
	ele = ele->NextSiblingElement();
	if (ele->Name() != HwModule::typeStr)
		return false ;
	std::string type = "";
	type = ele->GetText();

	//Parse the description
	ele = ele->NextSiblingElement();
	if (ele->Name() != HwModule::descriptionStr)
		return false ;
	std::string desc = "";
	desc = ele->GetText();

	//Parse the manufacturer
	ele = ele->NextSiblingElement();
	if (ele->Name() != HwModule::manufacturerStr)
		return false ;
	std::string manu = "";
	manu = ele->GetText();

	//Parse the product code
	ele = ele->NextSiblingElement();
	if (ele->Name() != HwModule::productCodeStr)
		return false ;
	std::string productCode = "";
	productCode = ele->GetText();

	//Parse the AA product code
	ele = ele->NextSiblingElement();
	if (ele->Name() != HwModule::aaProductCodeStr)
		return false ;
	std::string aaProductCode = "";
	aaProductCode = ele->GetText();

	//Parse the software version
	ele = ele->NextSiblingElement();
	if (ele->Name() != HwModule::softwareVerStr)
		return false ;
	std::string swVer = "";
	swVer = ele->GetText();

	//Parse the hardware version
	ele = ele->NextSiblingElement();
	if (ele->Name() != HwModule::hardwareVerStr)
		return false ;
	std::string hwVer = "";
	hwVer = ele->GetText();

	//Parse the serial number
	ele = ele->NextSiblingElement();
	if (ele->Name() != HwModule::serialNumStr)
		return false ;
	std::string serialNum = "";
	serialNum = ele->GetText();

	std::shared_ptr<HwModule> hwModule = createHwModule(date, name, type, desc, manu, productCode, aaProductCode,
			swVer, hwVer, serialNum);
	mModuleDesc->addModule(hwModule);

	// now we have a list (of one?) parameter objects to create
	for (tinyxml2::XMLElement* cur_node =
			ele->NextSiblingElement(); cur_node; cur_node =
			cur_node->NextSiblingElement())
	{
		// Get the device definition inside board
		if (cur_node->Name() == HwModule::featureStr)
		{
			if (!extractFeatures(hwModule, cur_node))
				return false;
		}
		else if (cur_node->Name() == HwModule::configItemsStr)
		{
			if (!extractConfig(hwModule, cur_node))
				return false;
		}
	}
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::CommonIdEeprom::extractFeatures(std::shared_ptr<HwModule> module, tinyxml2::XMLElement* node)
{
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::CommonIdEeprom::extractConfig(std::shared_ptr<HwModule> module, tinyxml2::XMLElement* node)
{
	return true;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::CommonIdEeprom::getAttributeMap(tinyxml2::XMLElement* node, AttrMap& attrMap) const
{
	for (auto& entry : attrMap)
	{
		const char* attr(node->Attribute(entry.first.c_str()));
		if (attr)
			entry.second = std::string(attr);
	}
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ModuleDescription> Mplane::CommonIdEeprom::createModuleDesc(
		const std::string& version, const std::string& country,
		const std::string& facility, const std::string& theoperator)
{
	return std::make_shared<ModuleDescription>(version, country, facility, theoperator) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<HwModule> Mplane::CommonIdEeprom::createHwModule(const std::string& date, const std::string& name,
		const std::string& type, const std::string& desc, const std::string& manu, const std::string& productCode,
		const std::string& aaProductCode, const std::string& swVer, const std::string& hwVer, const std::string serialNum)
{
	return std::make_shared<HwModule>(date, name, type, desc, manu, productCode, aaProductCode, swVer, hwVer, serialNum) ;
}
