#ifndef COMMON_MEMORY_INC_COMMONIDEEPROM_H_
#define COMMON_MEMORY_INC_COMMONIDEEPROM_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonIdEeprom.h
 * \brief     A file to define common implementation of an ID EEPROM
 *
 *
 * \details   A file to define common implementation of an ID EEPROM
 *
 */

// Includes go here, before the namespace
#include "GlobalTypeDefs.h"
#include "IIdEeprom.h"
#include "libtinyxml2/tinyxml2.h"
#include "Loggable.h"
#include <memory>
#include <list>

namespace Mplane
{

class ModuleFeatures
{
public:

	ModuleFeatures();

	virtual ~ModuleFeatures();
};

class ModuleConfig
{
public:

	ModuleConfig();

	virtual ~ModuleConfig();
};

class HwModule
{
public:

	/*! \brief Module types enum.
	 *
	 */
	typedef enum
	{
		POWER_SUPPLY = 0,
		PA_FINAL_DRIVER,
		PA_PRE_FINAL_DRIVER,
		PA_INTERFACE,
		LED_8_INTERFACE,
		EXTERNAL_PA,
		EXTERNAL_FILTER,
		TYPE_UNKNOWN
	} moduleTypes_T;

    /**
     * Convert type into a string
     * @param module type
     * @return string representation of type
     */
    static std::string moduleTypeToStr(HwModule::moduleTypes_T type);

    /**
     * Convert type string into a type
     * @param string representation of module type
     * @return module type
     */
    static moduleTypes_T strToModuleType(const std::string& typeStr) ;

	HwModule(const std::string& date, const std::string& name, const std::string& type, const std::string& desc,
			const std::string& manu, const std::string& productCode, const std::string& aaProductCode,
			const std::string& swVer, const std::string& hwVer, const std::string serialNum);

    virtual ~HwModule();

    /**
     * Getter - get Features
     */
    virtual std::shared_ptr<ModuleFeatures> getFeatures(void);

    /**
     * Setter - add Features
     */
    virtual void addFeatures( std::shared_ptr<ModuleFeatures> features );

    /**
     * Getter - get Config
     */
    virtual std::shared_ptr<ModuleConfig> getConfig(void);

    /**
     * Setter - add Config
     */
    virtual void addConfig( std::shared_ptr<ModuleConfig> config );

public:

    static const std::string name;
    static const std::string nameStr;
    static const std::string typeStr;
    static const std::string dateStr;
    static const std::string descriptionStr;
    static const std::string manufacturerStr;
    static const std::string productCodeStr;
    static const std::string aaProductCodeStr;
    static const std::string softwareVerStr;
    static const std::string hardwareVerStr;
    static const std::string serialNumStr;
    static const std::string featureStr;
    static const std::string configItemsStr;

protected:
	std::string mDate;
	std::string mName;
	moduleTypes_T mType;
	std::string mDescription;
	std::string mManufacturer;
	std::string mProductCode;
	std::string mAAProductCode;
	std::string mSoftwareVer;
	std::string mHardwareVer;
	std::string mSerialNum;
	std::list<std::shared_ptr<ModuleFeatures>> mFeatures;
	std::list<std::shared_ptr<ModuleConfig>> mConfig;

};

class ModuleDescription
{
public:
	ModuleDescription(const std::string& version, const std::string& country, const std::string& facility, const std::string& theoperator);

    virtual ~ModuleDescription();

    /**
     * Getter - get a Module
     */
    virtual std::shared_ptr<HwModule> getModule(void);

    /**
     * Setter - add a Module
     */
    virtual void addModule( std::shared_ptr<HwModule> module );

    /**
     * Get version string
     * @return
     */
    virtual std::string getVersion() const ;

    /**
     * Get country string
     * @return
     */
    virtual std::string getCountry() const ;

    /**
     * Get facility string
     * @return
     */
    virtual std::string getFacility() const ;

    /**
     * Get operator string
     * @return
     */
    virtual std::string getOperator() const ;

public:

    static const std::string name;
    static const std::string versionStr;
    static const std::string countryStr;
    static const std::string facilityStr;
    static const std::string operatorStr;

protected:

	std::string mVersion;
	std::string mCountry;
	std::string mFacility;
	std::string mOperator;

	std::list<std::shared_ptr<HwModule> > mModuleData;
};

/*! \brief  Common implementation of ID EEPROM
 *
 *  A virtual interface base class defining an interface to ID EEPROM
 *  The interface contains configuration and control aspects.
 */
class CommonIdEeprom: public IIdEeprom, public Loggable
{
public:

    /*! \brief Constructor
     *
     */
	CommonIdEeprom(UINT32 capacity = CommonIdEeprom::IdEepromMaxSize);

    /*! \brief  Read the ID EEPROM. This will lock the bus and perform the read
     *
     *  Do the read from the chip.
     *
     *  \param byteAddress is the start address.
     *  \param numberOfBytesToRead  The number of bytes that we wish to read
     *  \param bufferPtrToWriteTo   The buffer that we wish the data to be written to
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State readAtomic( UINT32 byteAddress, UINT8  numberOfBytesToRead,
                                    UINT8* bufferPtrToWriteTo ) ;

    /*! \brief  Write to the ID EEPROM. This will lock the bus and perform the write
     *
     *  Do the write to the chip.
     *
     *  \param byteAddress is the start address.
     *  \param dataLen is the number of words to write.
     *  \param dataPtr is the buffer containing the data to write.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State writeAtomic(UINT32 byteAddress, UINT16 dataLen, UINT8* dataPtr) ;

    /*! \brief  Read the ID EEPROM. This does not lock the bus
     *
     *  Do the read from the chip.
     *
     *  \param numberOfBytesToRead  The number of bytes that we wish to read
     *  \param bufferPtrToWriteTo   The buffer that we wish the data to be written to
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State read( UINT8  numberOfBytesToRead,
                                    UINT8* bufferPtrToWriteTo ) ;

    /*! \brief  Write to the ID EEPROM. This does not lock the bus
     *
     *  Do the write to the chip.
     *
     *  \param byteAddress is the address where writing should start.
     *  \param dataLen is the number of words to write.
     *  \param dataPtr is the buffer containing the data to write.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write(UINT32 byteAddress, UINT16 dataLen, UINT8* dataPtr) ;

    /*! \brief  Load the ID EEPROM contents
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State load();

    /*! \brief  Check whether ID EEPROM data is read and parsed
     *
     *  \return true/false
     */
    virtual bool isLoaded(void);

    /*! \brief  Get the pointer to module description
     *
     *  \return pointer to module description
     */
    virtual std::shared_ptr<ModuleDescription> getModuleDescription(void);

    /*! \brief Destructor
     *
     */
    virtual ~CommonIdEeprom();

public:
    static const UINT32 IdEepromMaxSize;
    static const UINT8 ReadSize;

protected:
    bool parseModuleDescription(tinyxml2::XMLElement* node);
    bool extractHwModule(std::shared_ptr<ModuleDescription> mModuleDesc, tinyxml2::XMLElement* a_node) ;
    virtual bool extractFeatures(std::shared_ptr<HwModule> module, tinyxml2::XMLElement* a_node) ;
    virtual bool extractConfig(std::shared_ptr<HwModule> module, tinyxml2::XMLElement* a_node) ;

    virtual std::shared_ptr<ModuleDescription> createModuleDesc(const std::string& version, const std::string& country,
    		const std::string& facility, const std::string& theoperator) ;

    virtual std::shared_ptr<HwModule> createHwModule(const std::string& date, const std::string& name, const std::string& type,
    		const std::string& desc, const std::string& manu, const std::string& productCode, const std::string& aaProductCode,
			const std::string& swVer, const std::string& hwVer, const std::string serialNum);


    // Map of attributes
    using AttrMap = std::map<std::string, std::string> ;

    /**
     * Fill a map with the attributes
     * @param attrMap
     */
    void getAttributeMap(tinyxml2::XMLElement* node, AttrMap& attrMap) const ;

protected:

    /*!
     * Size of EEPROM
     */
    UINT32 mCapacity;

    /*!
     * Reference to module description object
     */
    std::shared_ptr<ModuleDescription> mModuleDesc;

    /*!
     * Flag to indicate whether EEPROM data is read and parsed
     */
    bool mEepromDataLoaded;
};

} /* namespace Mplane */


#endif /* COMMON_MEMORY_INC_COMMONIDEEPROM_H_ */
