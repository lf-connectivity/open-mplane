#ifndef _RADIO_HARDWARE_OTFPGA_H_
#define _RADIO_HARDWARE_OTFPGA_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OffTargetFPGA.h
 * \brief     FPGA emulation.
 *
 *
 * \details   This file defines the interface to the fpga emulator.
 *
 */
#include <sys/stat.h>

#include <map>
#include <vector>
#include <list>
#include <string>
#include <functional>
#include <memory>
#include <cstdint>

#include "GlobalTypeDefs.h"
#include "Mutex.h"

namespace Mplane
{

class OffTargetFPGA
{
    /*
     * In an OFF_TARGET build we allow the Test harness to be our friend
     */
    friend class OffTargetFPGATestCase;

public:
    virtual ~OffTargetFPGA();

    /**
     * Size of data storage
     */
    enum OffTargetFPGASize {
    	DATA_DEFAULT,
    	DATA16,
		DATA32,
    };

    /**
     * Reset the internal data size of the emulated FPGA
     */
    virtual void setDataSize(OffTargetFPGASize dataSize) ;


    /*! \brief  Get the singleton instance
     *
     *  Used to get a reference to the single instance of the FPGA emulator
     *  object.
     */
    static std::shared_ptr<OffTargetFPGA> getInstance(void);

    /*! \brief  Create the singleton instance
     *
     *  Used to get a reference to the single instance of the FPGA emulator
     *  object.
     */
    static std::shared_ptr<OffTargetFPGA> createInstance(OffTargetFPGASize dataSize);


    //-- MemMap Interface (size data to allow up to 32 bit access) --

	/**
	 * Read a value
	 * @param offset	Offset (from base address) in bytes
	 * @param mask		Mask value
	 * @return the read value masked
	 */
	uint32_t readVal(unsigned offset, uint32_t mask = static_cast<uint32_t>(-1));

	/**
	 * Read-Modify-Write a value
	 * @param offset	Offset (from base address) in bytes
	 * @param value		Value to write
	 * @param mask		Mask value
	 * @return the modified value
	 */
	uint32_t modifyVal(unsigned offset, uint32_t value, uint32_t mask = static_cast<uint32_t>(-1));

	/**
	 * Write a value
	 * @param offset	Offset (from base address) in bytes
	 * @param value		Value to write
	 * @param mask		Mask value
	 */
	void writeVal(unsigned offset, uint32_t value, uint32_t mask = static_cast<uint32_t>(-1));




    //-- Debug Interface --

    /*! \brief  The initialise method
     *
     *  Method called during system startup, post FPGA image load, to fully
     *  initialise the device and to override any initial settings with
     *  board-specific ones.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise(const std::string& configFile, const std::string& configSearchPath);


    /*!
     * Set the debug level
     */
    void setDebug(const unsigned level) ;

    /*! \brief  Read a register
     *
     * Read a register location
     *
     *  \param   address   register address
     *  \param   value_p   pointer to value to be set by register read
     *  \param   mask      bits to read
     *
     *  \return true if successful, false if register hasn't been set (and sets the value to a preset default)
     */
	bool readReg(const UINT32 address, UINT16 *value_p, const UINT16 mask = 0xffff) ;

    /*! \brief  Write a register
     *
     * Write a register location
     *
     *  \param   address   register address
     *  \param   value     value to write
     *  \param   mask      bits to write
     *
     *  \return true if successful, false if not
     */
	bool writeReg(const UINT32 address, const UINT16 value, const UINT16 mask = 0xffff) ;

	/**
	 * Write to field by name
	 * @param name	field name
	 * @param value	value to write
	 */
	void writeField(const std::string &name, const UINT16 value) ;

	/**
	 * Read from field by name
	 * @param name	field name
	 * @return field value
	 */
	UINT16 readField(const std::string &name) ;

	/**
	 * Write to field by name. Used internally by models etc, does NOT lock the mutex
	 * @param name	field name
	 * @param value	value to write
	 */
	void internalWriteField(const std::string &name, const UINT16 value) ;

	/**
	 * Read from field by name. Used internally by models etc, does NOT lock the mutex
	 * @param name	field name
	 * @return field value
	 */
	UINT16 internalReadField(const std::string &name) ;


	enum DataValuesMode {
		DATAVALUES_ONESHOT	= 0,
		DATAVALUES_REPEAT	= 1,
	};

	/**
	 * Attach a set of data values to the address of a field, such that reads will access this data
	 * @param fieldName
	 * @param values
	 * @param mode
	 */
    void registerDataValues(const std::string &fieldName, const std::vector<UINT16>& values, const DataValuesMode mode = DATAVALUES_ONESHOT) ;

	/**
	 * Attach a set of data values to an address, such that reads will access this data
	 * @param address
	 * @param values
	 * @param mode
	 */
	void registerDataValues(const unsigned address, const std::vector<UINT16>& values, const DataValuesMode mode = DATAVALUES_ONESHOT) ;

	/**
	 * Emulates a device reset. Clears all registers and re-reads the config file to re-apply any default register
	 * settings
	 */
	void reset(void) ;

	/**
	 * Emulates a device reset. Clears all registers and re-reads the config file to re-apply any default register
	 * settings
	 *
	 * @param config path to new config file to read
	 */
	void reset(const std::string &config) ;


	// Write sequence checking

	enum SequenceCheckType {
		SEQCHECK_WRITE 			= 0,		//<! Check write access
		SEQCHECK_READ 			= 1,		//<! Check read access
		SEQCHECK_WRITE_DONTCARE = 2,		//<! Check a write of any value to this field
		SEQCHECK_READ_DONTCARE 	= 3			//<! Check a read of any value from this field
	};
	struct SequenceCheck {

		SequenceCheck(unsigned address, UINT16 value, UINT16 mask = 0xFFFF, SequenceCheckType type = SEQCHECK_WRITE) :
			mType(type),
			mAddress(address),
			mValue(value),
			mMask(mask)
		{}

		SequenceCheck() :
			mType(SEQCHECK_WRITE),
			mAddress(0),
			mValue(0),
			mMask(0)
		{}

		SequenceCheckType mType ;
		unsigned mAddress ;
		UINT16 mValue ;
		UINT16 mMask ;
	};

	enum SequenceMode {
		SEQMODE_ADDRSEP,	//!< Keep sequence entries with same address as separate entries
		SEQMODE_ADDRMERGE,	//!< For sequential sequence entries with same address merge them into a single entry
	};

	/**
	 * Registers a sequence of register writes to check the actual register writes against. If the sequence successfully
	 * completes, with all writes matching the sequence then isSequenceCheckComplete() will return true
	 * @param seqName	Name to access this sequence
	 * @param values	Vector of values to check sequence against
	 */
	void addSequenceCheck(const std::string& seqName, const std::vector<SequenceCheck>& values) ;

	struct FieldSequenceCheck {

		FieldSequenceCheck(const std::string& field, UINT16 value, SequenceCheckType type = SEQCHECK_WRITE) :
			mType(type),
			mField(field),
			mValue(value)
		{}

		explicit FieldSequenceCheck(const std::string& field) :
			mType(SEQCHECK_WRITE_DONTCARE),
			mField(field),
			mValue(0)
		{}

		SequenceCheckType mType ;
		std::string mField ;
		UINT16 mValue ;
	};

	/**
	 * Registers a sequence of field writes to check the actual register writes against. If the sequence successfully
	 * completes, with all writes matching the sequence then isSequenceCheckComplete() will return true
	 * @param seqName	Name to access this sequence
	 * @param values	Vector of field values to check sequence against
	 */
	void addSequenceCheck(const std::string& seqName, const std::vector<FieldSequenceCheck>& values, SequenceMode seqMode = SEQMODE_ADDRSEP) ;

	/**
	 * If the sequence successfully completes, with all writes matching the sequence then this will return true
	 * @param seqName	Name to access the sequence
	 * @return true if sequence has completed
	 */
	bool isSequenceCheckComplete(const std::string& seqName) ;

	/**
	 * Delete the sequence
	 * @param seqName	Name to access the sequence
	 */
	void delSequenceCheck(const std::string& seqName) ;

	/**
	 * Restart the sequence checking from the beginning of the sequence
	 * @param seqName	Name to access the sequence
	 */
	void restartSequenceCheck(const std::string& seqName) ;

	/**
	 * Debug prints the sequence
	 * @param seqName	Name to access the sequence
	 */
	void showSequenceCheck(const std::string& seqName) ;

	/**
	 * Debug prints the sequence in a format that you can cut'n'paste into your test code
	 * @param seqName	Name to access the sequence
	 */
	void showSequenceCheckTestcode(const std::string& seqName, const std::string& testName) ;


	/**
	 * Register handler functions for an address or range of addresses. Normally these functions would actually
	 * be methods in a handler object
	 *
	 */
	using ReadHandlerFunction = std::function< UINT16(const UINT32 address, const UINT16 mask) > ;
	using WriteHandlerFunction = std::function< UINT16(const UINT32 address, const UINT16 value, const UINT16 mask) > ;

	/**
	 * Register handlers for a single address
	 * @return true if handelr's registered ok
	 */
	bool registerHandler(const UINT32 address, WriteHandlerFunction writeHandler, ReadHandlerFunction readHandler) ;

	/**
	 * Register handlers for a range of addresses
	 * @return true if handelr's registered ok
	 */
	bool registerHandler(const UINT32 addressStart, const UINT32 addressEnd, WriteHandlerFunction writeHandler, ReadHandlerFunction readHandler) ;

	/**
	 * Un-Register handlers for a single address
	 * @return true if handelr's registered ok
	 */
	bool unRegisterHandler(const UINT32 address) ;

	/**
	 * Un-Register handlers for a range of addresses
	 * @return true if handelr's registered ok
	 */
	bool unRegisterHandler(const UINT32 addressStart, const UINT32 addressEnd) ;


    /*
     * Protected methods to allow friend classes access to the FPGA emulator
     */
protected:

    /*! \brief  Constructor
     *
     */
    OffTargetFPGA(
    	OffTargetFPGASize dataSize = DATA16,
    	const std::string& config_file = "fpga-emu.cfg",
    	const std::string& config_search_path = ".:$OFFTARGET_CFG_DIR:../../../hardware/common/fpga/cfg",
    	uint32_t default_value = 0xDEADDEAD);

    /*! \brief  Get the default value
     *
     *  Returns the default value that will be returned on a read to a register that hasn't been initialised
     *  or wrotten to yet.
     */
    uint32_t defaultValue(void) const ;

private:
    /*! \brief  Split string into var=val pairs
     *
     * Processes a string looking for "var = val" pairs (with or without whitespace around the =)
     * Returns the next start position after finding this pair so that multiple pairs can be processed
     * from a string. If no pairs found returns std::string::npos
     *
     *  \param   str   input string
     *  \param   startpos   starting position within string (1st time start at 0)
     *  \param   var   reference to string to hold variable name
     *  \param   val   reference to string to hold value
     *
     *  \return true if successful, false if register hasn't been set (and sets the value to a preset default)
     */
    std::string::size_type var_val(const std::string &str, const std::string::size_type &startpos,
            std::string &var, std::string &val) ;


    /*! \brief  Low level register read - provides adjustment from 16bit interface to internal data width
     *
     * Performs read of a register location but without any mutex protection (caller must lock the mutex)
     *
     *  \param   address   register address
     *  \param   value_p   pointer to value to be set by register read
     *  \param   mask      bits to read
     *
     *  \return true if successful, false if register hasn't been set (and sets the value to a preset default)
     */
	bool internalRdReg(const UINT32 address, uint32_t *value_p, const uint32_t mask = 0xffffffff);

    /*! \brief  Low level register write - provides adjustment from 16bit interface to internal data width
     *
     * Performs write of a register location but without any mutex protection (caller must lock the mutex)
     *
     *  \param   address   register address
     *  \param   value     value to write
     *  \param   mask      bits to write
     *
     *  \return final write value
     */
	uint32_t internalWrReg(const UINT32 address, const uint32_t value, const uint32_t mask = 0xffffffff);



    /*! \brief  Low level register read - Directly reads from data store using the specified address and
     * mask, returning the value direct from the data store
     *
     * Performs read of a register location but without any mutex protection (caller must lock the mutex)
     *
     *  \param   address   register address
     *  \param   value_p   pointer to value to be set by register read
     *  \param   mask      bits to read
     *
     *  \return true if successful, false if register hasn't been set (and sets the value to a preset default)
     */
	bool rawRdReg(const UINT32 address, uint32_t *value_p, const uint32_t mask = 0xffffffff);

    /*! \brief  Low level register write - writes directly to data store
     *
     * Performs write of a register location but without any mutex protection (caller must lock the mutex)
     *
     *  \param   address   register address
     *  \param   value     value to write
     *  \param   mask      bits to write
     *
     *  \return final write value
     */
	uint32_t rawWrReg(const UINT32 address, const uint32_t value, const uint32_t mask = 0xffffffff);



    /*! \brief  Start logging
     *
     * Create/truncate the log file. Clears the logfile string on error
     *
     */
	void startLog(void);

    /*! \brief  Write a log line
     *
     * If the logfile string is set then write a timestamped log line to the file
     *
     */
	void writeLog(const char *fmt, ...)
		__attribute__ ((format (printf, 2, 3)));

    /*! \brief  Log a write access
     *
     * Given the address/mask/data sees if there is a corresponding field name for this address/bits
     * and writes the information to the log if so
     *
     */
	void logFieldWrite(const unsigned address, const uint32_t value, const uint32_t mask) ;

    /*! \brief  Log a read access
     *
     * Given the address/mask sees if there is a corresponding field name for this address/bits
     * and writes the information to the log if so
     *
     */
	void logFieldRead(const unsigned address, const uint32_t value, const uint32_t mask) ;

    /*! \brief  Parse field names
     *
     * Read the config file and create the address to field names lookup (as well as the field name to address lookup)
     *
     */
	void processFieldNames(const std::string &filename, const std::string& configSearchPath) ;

	/**
	 * Open a file using the search path to find it in
	 * @param file	base filename to open
	 * @param configSearchPath	list of ':' separated directories to search
	 * @param infile	ref to file stream to open
	 * @return found path string
	 */
	std::string openFileViaSearchPath(const std::string& file, const std::string& configSearchPath, std::ifstream& infile) ;

	/**
	 * Create a directory path, making any non-existing directories in the path
	 * @param path	directory path to create
	 * @param mode	directory mode
	 * @return 0 on success
	 */
	int mkpath(const std::string& path, const mode_t mode) ;

	/**
	 * Expand any environment variables in string
	 * @param str	String to expand (will be modified in-place)
	 */
	void expandVars(std::string& str) ;

	// Various environment variable utilities
	void processEnvironmentVars() ;
	bool isEnvSet(const std::string& name) const ;
	std::string getEnvStr(const std::string& name) const ;
	unsigned getEnvUint(const std::string& name) const ;
	bool getEnvBool(const std::string& name) const ;


	// initialise the data width functions
	void initFuncs() ;

	// get mask depending on data width
	using DefaultMaskFunc = std::function<uint32_t(void)> ;
	uint32_t defaultMask32() const ;
	uint32_t defaultMask16() const ;

	// Interface is 16bit, so adjust to data width
	using AdjustAddressFunc = std::function<uint32_t(uint32_t&)> ;
	using AdjustWrDataFunc = std::function<uint32_t(uint32_t, uint32_t&)> ;
	using AdjustRdDataFunc = std::function<uint32_t(uint32_t, uint32_t&)> ;
	uint32_t adjustAddress16(uint32_t& address) const ;
	uint32_t adjustAddress32(uint32_t& address) const ;
	uint32_t adjustWrData16(uint32_t address, uint32_t& data) const ;
	uint32_t adjustWrData32(uint32_t address, uint32_t& data) const ;
	uint32_t adjustRdData16(uint32_t address, uint32_t& data) const ;
	uint32_t adjustRdData32(uint32_t address, uint32_t& data) const ;


private:
	OffTargetFPGASize mDataSize ;
    std::string mConfigFile ;
    std::string mConfigSearchPath ;
    uint32_t mRequestedDefaultValue ;
    uint32_t mDefaultValue ;


    /*!
     *  Mutex used to protect the "register store" since multiple threads may be
     *  trying to access the fpga at once.
     */
    Mutex mAccessMutex ;

    /*!
     *  Debug level
     */
    unsigned mDebug ;

    /*!
     *  Map to hold the register data at each address
     */
	typedef std::map<UINT32, uint32_t> Model_data_type ;
	typedef Model_data_type::iterator Data_iter ;
	typedef Model_data_type::const_iterator Data_const_iter ;
	Model_data_type mRegData ;

    /*!
     *  Map address to field names
     */
	class FieldInfo ;
	typedef std::list< std::shared_ptr<FieldInfo> > Field_info_list ;
	typedef Field_info_list::iterator Field_iter ;
	typedef Field_info_list::const_iterator Field_const_iter ;
	typedef std::map<UINT32, Field_info_list> Address_Fields_type ;
	typedef Address_Fields_type::iterator Address_Fields_iter ;
	typedef Address_Fields_type::const_iterator Address_Fields_const_iter ;
	Address_Fields_type mAddressLookup ;

    /*!
     *  Map field names to addresses
     */
	typedef std::map<std::string, std::shared_ptr<FieldInfo> > Fields_Address_type ;
	typedef Fields_Address_type::iterator Fields_Address_iter ;
	typedef Fields_Address_type::const_iterator Fields_Address_const_iter ;
	Fields_Address_type mNameLookup ;

	/**
	 * Keep a map of addresses to data sources
	 */
	class DataSource ;
	typedef std::map<unsigned, std::shared_ptr<DataSource> > Fields_Data_type ;
	typedef Fields_Data_type::iterator Fields_Data_iter ;
	Fields_Data_type mDataSources ;

    /*!
     *  Log filename - if set then fpga accesses get logged to this file
     */
	bool mLogEnable ;
	std::string mLogFilename ;
	std::string mLastLogFilename ;

	/**
	 * Sequence checking
	 */
	class CheckSequence ;
	typedef std::map<std::string, std::shared_ptr<CheckSequence> > CheckSequenceMap ;
	typedef CheckSequenceMap::iterator CheckSequenceMap_iter ;
	CheckSequenceMap mCheckSequences ;

	/**
	 * Keep actual sequence of writes
	 */
	std::vector<SequenceCheck> mActualSequence ;

    /*!
     *  Map of address handlers
     */
	typedef std::pair<WriteHandlerFunction, ReadHandlerFunction> AddressHandlersEntry ;
	typedef std::map<UINT32, AddressHandlersEntry> AddressHandlersMap ;
	typedef AddressHandlersMap::iterator AddressHandlers_iter ;
	typedef AddressHandlersMap::const_iterator AddressHandlers_const_iter ;
	AddressHandlersMap mAddressHandlers ;

	/**
	 * Functions adjusted to match the current data width
	 */
	DefaultMaskFunc mDefaultMaskFunc ;
	AdjustAddressFunc mAdjustAddressFunc ;
	AdjustWrDataFunc mAdjustWrDataFunc ;
	AdjustRdDataFunc mAdjustRdDataFunc ;

};


} /* namespace Mplane */

#endif /* _RADIO_HARDWARE_OTFPGA_H_ */
