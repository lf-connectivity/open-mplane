#ifndef _RADIO_HARDWARE_OTGPIO_H_
#define _RADIO_HARDWARE_OTGPIO_H_
#ifdef OFF_TARGET

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OffTargetGpio.h
 * \brief     Gpio emulation.
 *
 *
 * \details   This file defines the interface to the gpio emulator.
 *
 */

// =========================================================
// TODO Update for GPIO application
// [DJ ]Initial version based on SteveP's OffTargetFPGA
// To be modified to emulate GPIO registers
// =========================================================

#include <sys/stat.h>
#include <map>
#include <vector>
#include <list>
#include <string>

#include <memory>
#include "GlobalTypeDefs.h"
#include "Mutex.h"
#include "IGpio.h"		// for gpio device driver info

namespace Mplane
{

class OffTargetGpio
{
    /*
     * In an OFF_TARGET build we allow the Test harness to be our friend
     */
//    friend class OffTargetGpioTestCase;

public:

    /*! \brief  Get the singleton instance
     *
     *  Used to get a reference to the single instance of the gpio emulator
     *  object.
     */
    static OffTargetGpio& getInstance(void);


    //-- MemMap Interface --

	/**
	 * Read a value
	 * @param offset	Offset (from base address) in bytes
	 * @param mask		Mask value
	 * @return the read value masked
	 */
	UINT16 readVal(unsigned offset, UINT16 mask = static_cast<UINT16>(-1));

	/**
	 * Read-Modify-Write a value
	 * @param offset	Offset (from base address) in bytes
	 * @param value		Value to write
	 * @param mask		Mask value
	 * @return the modified value
	 */
	UINT16 modifyVal(unsigned offset, UINT16 value, UINT16 mask = static_cast<UINT16>(-1));

	/**
	 * Write a value
	 * @param offset	Offset (from base address) in bytes
	 * @param value		Value to write
	 * @param mask		Mask value
	 */
	void writeVal(unsigned offset, UINT16 value, UINT16 mask = static_cast<UINT16>(-1));


    //-- Debug Interface --

    /*! \brief  The initialise method
     *
     *  Method called during system startup, to fully
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


    /*
     * Protected methods to allow friend classes access to the gpio emulator
     */
protected:

    /*! \brief  Constructor
     *
     */
    OffTargetGpio(
    	const std::string& config_file = "gpio-emu.cfg",
    	const std::string& config_search_path = ".:$OFFTARGET_CFG_DIR:../../../hardware/common/gpio/cfg:$HOME/git/hardware/common/gpio/cfg",
    	const UINT16 default_value = 0xDEAD);

    /*! Destructor
     *
     *  Destructor
     */
    virtual ~OffTargetGpio();

    /*! \brief  Get the default value
     *
     *  Returns the default value that will be returned on a read to a register that hasn't been initialised
     *  or written to yet.
     */
    UINT16 defaultValue(void) const ;

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

    /*! \brief  Low level register read
     *
     * Performs read of a register location but without any mutex protection (caller must lock the mutex)
     *
     *  \param   address   register address
     *  \param   value_p   pointer to value to be set by register read
     *  \param   mask      bits to read
     *
     *  \return true if successful, false if register hasn't been set (and sets the value to a preset default)
     */
	bool rawRdReg(const UINT32 address, UINT16 *value_p, const UINT16 mask = 0xffff);

    /*! \brief  Low level register write
     *
     * Performs write of a register location but without any mutex protection (caller must lock the mutex)
     *
     *  \param   address   register address
     *  \param   value     value to write
     *  \param   mask      bits to write
     *
     *  \return final write value
     */
	UINT16 rawWrReg(const UINT32 address, const UINT16 value, const UINT16 mask = 0xffff);


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
	void logFieldWrite(const unsigned address, const UINT16 value, const UINT16 mask) ;

    /*! \brief  Log a read access
     *
     * Given the address/mask sees if there is a corresponding field name for this address/bits
     * and writes the information to the log if so
     *
     */
	void logFieldRead(const unsigned address, const UINT16 value, const UINT16 mask) ;

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


private:

    std::string mConfigFile ;
    std::string mConfigSearchPath ;
    UINT16 mDefaultValue ;


    /*!
     *  Mutex used to protect the "register store" since multiple threads may be
     *  trying to access the gpio at once.
     */
    Mutex mAccessMutex ;

    /*!
     *  Debug level
     */
    unsigned mDebug ;

    /*!
     *  Map to hold the register data at each address
     */
	typedef std::map<UINT32, UINT16> Model_data_type ;
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
     *  Log filename - if set then gpio accesses get logged to this file
     */
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


};


} /* namespace Mplane */

#endif
#endif /* _RADIO_HARDWARE_OTGPIO_H_ */
