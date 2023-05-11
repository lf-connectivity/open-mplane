/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OffTargetGpio.cpp
 * \brief     Implementation of the OffTargetGpio class
 *
 *
 * \details   This file contains the implementation of the hardware gpio emulator
 *            class.
 *
 */

// =========================================================
// TODO Update for GPIO application
// [DJ ]Initial version based on SteveP's OffTargetFPGA
// To be modified to emulate GPIO registers
// =========================================================


#ifdef OFF_TARGET

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdlib>
#include <cerrno>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>		// std::back_inserter
#include <algorithm>	// std::copy

#include "OffTargetGpio.h"

using namespace Mplane;

//=============================================================================================================
// TYPES
//=============================================================================================================

//-------------------------------------------------------------------------------------
// A class for containing the information about a field
class OffTargetGpio::FieldInfo
{
public:
	FieldInfo(const std::string& name, const unsigned address, const UINT16 shift = 0, const UINT16 mask = 0xffff, const std::string& record = "") :
		mName(name),
		mAddress(address),
		mShift(shift),
		mMask(mask),
		mRecord(record)
	{};
	~FieldInfo() {} ;

	std::string mName ;
	unsigned mAddress ;
	UINT16 mShift ;
	UINT16 mMask ;
	std::string mRecord ;
};


//-------------------------------------------------------------------------------------
// Class to hold a data source that can be attached to a field
class OffTargetGpio::DataSource
{
public:
	DataSource(const std::vector<UINT16>& values, const DataValuesMode mode = DATAVALUES_ONESHOT) :
		mValues(0),
		mIter(),
		mMode(mode)
	{
		std::copy(values.begin(), values.end(), std::back_inserter(mValues));
		mIter = mValues.begin() ;
	}

	~DataSource() {}

	bool empty()
	{
		if (mIter == mValues.end())
			return true ;
		return false ;
	}

	UINT16 getValue()
	{
		if (mIter == mValues.end())
			return (UINT16)0xdead ;

		UINT16 value = *mIter++ ;

		if ( (mIter == mValues.end()) && (mMode == OffTargetGpio::DATAVALUES_REPEAT) )
		{
			mIter = mValues.begin() ;
		}

		return value ;
	}


private:
	std::vector<UINT16> mValues ;
	std::vector<UINT16>::iterator mIter ;
	OffTargetGpio::DataValuesMode mMode ;
};

//-------------------------------------------------------------------------------------
// Class to hold a check sequence and it's results
class OffTargetGpio::CheckSequence {
public:
	explicit CheckSequence(const std::vector<OffTargetGpio::SequenceCheck>& values) :
		mComplete(false),
		mMismatches(0),
		mValues(values.begin(), values.end()),
		mValuesIter(mValues.begin())
	{
	}

	~CheckSequence() {}

	bool isComplete() { return mComplete; }

	void showSequence(const std::string& info)
	{
		std::cout << "--[ " << info << "]------" << std::endl ;
		std::cout << "Complete.....: " << mComplete << std::endl ;
		std::cout << "Mismatch.....: " << mMismatches << std::endl ;
		bool reached = true ;
		unsigned idx = 0 ;
		for (std::vector<OffTargetGpio::SequenceCheck>::const_iterator iter = mValues.begin(); iter != mValues.end(); ++iter)
		{
			if (iter == mValuesIter)
				reached = false ;

			printf(" [%03u] 0x%05x: 0x%04x / 0x%04x ....%s\n",
				idx++,
				iter->mAddress, iter->mValue, iter->mMask,
				(reached ? "OK" : "X"));
		}
		std::cout << "-------------------------" << std::endl ;
	}

	void updateSequence(const unsigned address, const UINT16 value, const UINT16 mask = 0xFFFF)
	{
		// skip if already done
		if (mComplete)
			return ;
		if (mValues.size() == 0)
			return ;

//std::cerr << "Sequence check: wr addr 0x" << std::hex << address << " seq addr 0x" << mValuesIter->mAddress << std::dec << std::endl ;
		if (address == mValuesIter->mAddress)
		{
			if ((mValuesIter->mType == SEQCHECK_WRITE) || (mValuesIter->mType == SEQCHECK_WRITE_DONTCARE))
			{
				// Does the write match?
				UINT16 writtenVal = (value & mask) & mValuesIter->mMask ;
				UINT16 expectedVal = mValuesIter->mValue & mValuesIter->mMask ;
	//std::cerr << " * Sequence check: wr val 0x" << std::hex << writtenVal << " expected 0x" << expectedVal << std::endl ;
				if ((writtenVal == expectedVal) || (mValuesIter->mType == SEQCHECK_WRITE_DONTCARE))
				{
					++mValuesIter ;
					if (mValuesIter == mValues.end())
						mComplete = true ;
				}
				else
				{
					// Mismatch so start again
					mValuesIter = mValues.begin() ;
					++mMismatches ;
				}
			}
		}
	}

	unsigned getMismatches() { return mMismatches; }

	void resetSequence(void)
	{
		// skip if empty
		if (mValues.size() == 0)
			return ;

		// set to start of sequence
		mValuesIter = mValues.begin() ;
		mComplete = false ;
		mMismatches = 0 ;
	}


private:
	bool mComplete ;
	unsigned mMismatches ;
	const std::vector<OffTargetGpio::SequenceCheck> mValues ;
	std::vector<OffTargetGpio::SequenceCheck>::const_iterator mValuesIter ;

	// @todo: add vector of actual writes ?
};


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
OffTargetGpio& OffTargetGpio::getInstance(void)
{
    static OffTargetGpio _instance;
    return _instance;
}

//=============================================================================================================
// MemMap Interface
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
UINT16 OffTargetGpio::readVal(unsigned offset, UINT16 mask)
{
	Mutex::Lock lock( mAccessMutex );  // use the Mutex lock guard here

	writeLog("CMD: read 0x%05x 1", offset) ;

	UINT16 readValue ;
	rawRdReg(offset, &readValue, mask);
	logFieldRead(offset, readValue, mask) ;
	writeLog("REPLY: OK 0x%04x\n", readValue) ;

	return(readValue) ;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 OffTargetGpio::modifyVal(unsigned offset, UINT16 value, UINT16 mask)
{
	Mutex::Lock lock( mAccessMutex );  // use the Mutex lock guard here

	writeLog("CMD: modify 0x%05x 1 0x%04x/0x%04x", offset, value, mask) ;

	UINT16 readValue = rawWrReg(offset, value, mask);
	writeLog("REPLY: OK 0x%04x\n", readValue) ;

	return(readValue) ;
}

//-------------------------------------------------------------------------------------------------------------
void OffTargetGpio::writeVal(unsigned offset, UINT16 value, UINT16 mask)
{
	Mutex::Lock lock( mAccessMutex );  // use the Mutex lock guard here

	writeLog("CMD: write 0x%05x 1 0x%04x/0x%04x", offset, value, mask) ;
	rawWrReg(offset, value, mask);
	writeLog("REPLY: OK 0x%04x\n", value) ;
}


//=============================================================================================================
// Debug Interface
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
void OffTargetGpio::setDebug(const unsigned level)
{
	mDebug = level ;
}

//-------------------------------------------------------------------------------------------------------------
void OffTargetGpio::reset()
{
	reset(mConfigFile) ;
}

//-------------------------------------------------------------------------------------------------------------
void OffTargetGpio::reset(const std::string &configFile)
{
	// reset vars
	mDebug = 0 ;
	mRegData.clear() ;
	mAddressLookup.clear() ;
	mNameLookup.clear() ;
	mDataSources.clear() ;
	mLogFilename = std::string("") ;
	mActualSequence.clear() ;

	// re-initialise
	std::string config(configFile) ;
	expandVars(config) ;
	expandVars(mConfigSearchPath) ;
	initialise(config, mConfigSearchPath) ;

}


//-------------------------------------------------------------------------------------------------------------
void OffTargetGpio::registerDataValues(const std::string &fieldName, const std::vector<UINT16>& values, const DataValuesMode mode)
{
	// Make the name lowercase
	std::string lower(fieldName) ;
	std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower) ;

	Fields_Address_iter iter( mNameLookup.find(lower) ) ;
	if (iter == mNameLookup.end() )
	{
    	writeLog("ERROR: Unable to access field '%s'", fieldName.c_str() ) ;
    	std::cerr << "Unable to access gpio field '" << fieldName << "'" << std::endl ;
		return ;
	}

	registerDataValues(iter->second->mAddress, values, mode) ;

}


//-------------------------------------------------------------------------------------------------------------
void OffTargetGpio::registerDataValues(const unsigned address, const std::vector<UINT16>& values, const DataValuesMode mode)
{
	mDataSources[address] = std::shared_ptr<DataSource>(new DataSource(values, mode)) ;
}



//-------------------------------------------------------------------------------------------------------------
void OffTargetGpio::addSequenceCheck(const std::string& seqName, const std::vector<SequenceCheck>& values)
{
	mCheckSequences[seqName] = std::shared_ptr<CheckSequence>(new CheckSequence(values)) ;
}

//-------------------------------------------------------------------------------------------------------------
void OffTargetGpio::addSequenceCheck(const std::string& seqName, const std::vector<FieldSequenceCheck>& values, SequenceMode seqMode)
{
	// convert the field accesses into a sequence of register accesses
	unsigned last_address = 0 ;
	std::vector<SequenceCheck> seqValues ;
	for (std::vector<FieldSequenceCheck>::const_iterator iter(values.begin()); iter != values.end(); ++iter)
	{
		// Get register information

		std::string lower(iter->mField) ;
		std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower) ;

		Fields_Address_iter field_iter( mNameLookup.find(lower) ) ;
		if (field_iter == mNameLookup.end() )
		{
	    	writeLog("ERROR: Unable to access field '%s'", iter->mField.c_str() ) ;
	    	std::cerr << "Unable to access gpio field '" << iter->mField << "'" << std::endl ;
			return ;
		}

		unsigned address = field_iter->second->mAddress ;
		UINT16 mask = field_iter->second->mMask ;
		UINT16 shift = field_iter->second->mShift ;

		mask <<= shift ;
		UINT16 value = iter->mValue << shift ;

		if (seqMode == SEQMODE_ADDRMERGE)
		{
			// see if this address is the same as the last entry - if so then combine
			if (!seqValues.empty() && (address == last_address))
			{
				// combine
				SequenceCheck& last( seqValues.back() ) ;
				last.mMask |= mask ;
				last.mValue |= value ;
			}
			else
			{
				// add new value
				seqValues.push_back(SequenceCheck(address, value, mask, iter->mType)) ;
			}
		}
		else
		{
			// add new value
			seqValues.push_back(SequenceCheck(address, value, mask, iter->mType)) ;
		}

		// track latest value
		last_address = address ;
	}
	mCheckSequences[seqName] = std::shared_ptr<CheckSequence>(new CheckSequence(seqValues)) ;
}

//-------------------------------------------------------------------------------------------------------------
bool OffTargetGpio::isSequenceCheckComplete(const std::string& seqName)
{
	CheckSequenceMap_iter iter( mCheckSequences.find(seqName) ) ;
	if (iter == mCheckSequences.end() )
	{
    	writeLog("ERROR: Check Sequence '%s' is not registered", seqName.c_str() ) ;
    	std::cerr << "Check Sequence '" << seqName << "' is not registered" << std::endl ;
		return false ;
	}

	return 	iter->second->isComplete() ;
}

//-------------------------------------------------------------------------------------------------------------
void OffTargetGpio::delSequenceCheck(const std::string& seqName)
{
	CheckSequenceMap_iter iter( mCheckSequences.find(seqName) ) ;
	if (iter == mCheckSequences.end() )
	{
    	writeLog("ERROR: Check Sequence '%s' is not registered", seqName.c_str() ) ;
    	std::cerr << "Check Sequence '" << seqName << "' is not registered" << std::endl ;
		return ;
	}

	mCheckSequences.erase(iter) ;
}

//-------------------------------------------------------------------------------------------------------------
void OffTargetGpio::restartSequenceCheck(const std::string& seqName)
{
	CheckSequenceMap_iter iter( mCheckSequences.find(seqName) ) ;
	if (iter == mCheckSequences.end() )
	{
    	writeLog("ERROR: Check Sequence '%s' is not registered", seqName.c_str() ) ;
    	std::cerr << "Check Sequence '" << seqName << "' is not registered" << std::endl ;
		return ;
	}

	iter->second->resetSequence() ;
}

//-------------------------------------------------------------------------------------------------------------
void OffTargetGpio::showSequenceCheck(const std::string& seqName)
{
	CheckSequenceMap_iter iter( mCheckSequences.find(seqName) ) ;
	if (iter == mCheckSequences.end() )
	{
    	writeLog("ERROR: Check Sequence '%s' is not registered", seqName.c_str() ) ;
    	std::cerr << "Check Sequence '" << seqName << "' is not registered" << std::endl ;
		return ;
	}

	std::cout << "SEQUENCE" << std::endl ;
	iter->second->showSequence(seqName) ;


	std::cout << "ACTUAL" << std::endl ;
	unsigned idx = 0 ;
	for (std::vector<OffTargetGpio::SequenceCheck>::const_iterator iter = mActualSequence.begin(); iter != mActualSequence.end(); ++iter)
	{
		printf(" [%03u] 0x%05x: 0x%04x / 0x%04x\n",
			idx++,
			iter->mAddress, iter->mValue, iter->mMask);
	}
	std::cout << "-------------------------" << std::endl ;

}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
OffTargetGpio::OffTargetGpio(const std::string& config_file, const std::string& config_search_path, const UINT16 default_value) :
	mConfigFile(config_file),
	mConfigSearchPath(config_search_path),
	mDefaultValue(default_value),
	mAccessMutex(),
	mDebug(0),
	mRegData(),
	mAddressLookup(),
	mNameLookup(),
	mDataSources(),
	mLogFilename(""),
	mLastLogFilename(""),
	mActualSequence(0)
{
	expandVars(mConfigFile) ;
	expandVars(mConfigSearchPath) ;
	initialise(mConfigFile, mConfigSearchPath) ;
}


//-------------------------------------------------------------------------------------------------------------
OffTargetGpio::~OffTargetGpio()
{
	// clear out hashes
	mAddressLookup.clear() ;
	mNameLookup.clear() ;
	mRegData.clear() ;
	mLogFilename.clear();
	mLastLogFilename.clear();
    mActualSequence.clear() ;
    mDataSources.clear() ;
    mConfigFile.clear() ;
    mConfigSearchPath.clear() ;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State OffTargetGpio::initialise(const std::string& configFile, const std::string& configSearchPath)
{
	std::ifstream infile;
	std::string configPath( openFileViaSearchPath(configFile, configSearchPath, infile) ) ;

	if (mDebug) printf("read <%s>\n", configPath.c_str()) ;

//std::cerr << "initialise() path=" << configPath << " open? " << infile.is_open() << std::endl ;

	std::string linebuff ;
	if (infile.is_open())
	{
		while(infile.good())
		{
			// get the line text string
			std::getline(infile, linebuff);


			if (mDebug >= 2) printf("line=<%s>\n", linebuff.c_str()) ;

			// Skip comments (#) and look for lines of the form:
			// address=0x40a value=0xffff

			std::string::size_type pos = linebuff.find("#") ;
			if (pos != std::string::npos)
				linebuff.erase(pos, std::string::npos) ;
			if (linebuff.length() == 0)
				continue ;

			std::string cmd_var, cmd_val ;
			pos = var_val(linebuff, 0, cmd_var, cmd_val) ;
			if ((cmd_var.length() == 0) || (cmd_val.length() == 0))
				continue ;

			// address
			if (cmd_var.compare("address") == 0)
			{
				std::string value_var, value_val ;

				pos = var_val(linebuff, pos, value_var, value_val) ;

				if ((value_var.length() == 0) || (value_val.length() == 0) || (value_var.compare("value") != 0))
					continue ;

				unsigned address = (unsigned)strtoul(cmd_val.c_str(), NULL, 0) ;
				unsigned value = (unsigned)strtoul(value_val.c_str(), NULL, 0) ;
				UINT16 word = value & 0xffff ;

				if (mDebug) printf("LOAD: 0x%05x = 0x%04x\n", address, word) ;
				writeReg(address, word) ;
			}

			// field
			if (cmd_var.compare("field") == 0)
			{
				std::string value_var, value_val ;

				pos = var_val(linebuff, pos, value_var, value_val) ;

				if ((value_var.length() == 0) || (value_val.length() == 0) || (value_var.compare("value") != 0))
					continue ;


				// Make the name lowercase
				std::string lower(cmd_val) ;
				std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower) ;

				Fields_Address_iter iter( mNameLookup.find(lower) ) ;
				if (iter == mNameLookup.end() )
				{
			    	writeLog("INFO: Unable to find field '%s'", cmd_val.c_str() ) ;
			    	std::cerr << "INFO: Unable to find gpio field '" << cmd_val << "'" << std::endl ;
			    	continue ;
				}

				unsigned address = iter->second->mAddress ;
				UINT16 mask = iter->second->mMask ;
				UINT16 shift = iter->second->mShift ;
				unsigned value = (unsigned)strtoul(value_val.c_str(), NULL, 0) ;
				UINT16 wr_value = value & mask ;

				rawWrReg(address, (wr_value << shift), (mask << shift));

				if (mDebug) printf("LOAD: 0x%05x = 0x%04x\n", address, wr_value) ;
			}

			// emu.debug
			else if (cmd_var.compare("emu.debug") == 0)
			{
				mDebug = (unsigned)strtoul(cmd_val.c_str(), NULL, 0) ;
			}

			// emu.log
			else if (cmd_var.compare("emu.log") == 0)
			{
				mLogFilename = cmd_val ;
				startLog() ;
			}

			// emu.names
			else if (cmd_var.compare("emu.names") == 0)
			{
				// expand any environment vars
				expandVars(cmd_val) ;

				// Process the field names config file
				processFieldNames(cmd_val, mConfigSearchPath) ;
			}
		}
	}
    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 OffTargetGpio::defaultValue(void) const
{
	return mDefaultValue ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::OffTargetGpio::writeField(const std::string& name, const UINT16 value)
{
	// Make the name lowercase
	std::string lower(name) ;
	std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower) ;

	Fields_Address_iter iter( mNameLookup.find(lower) ) ;
	if (iter == mNameLookup.end() )
	{
    	writeLog("ERROR: Unable to write field '%s'", name.c_str() ) ;
    	std::cerr << "Unable to write to gpio field '" << lower << "'" << std::endl ;
		return ;
	}

	unsigned address = iter->second->mAddress ;
	UINT16 mask = iter->second->mMask ;
	UINT16 shift = iter->second->mShift ;
	UINT16 wr_value = value & mask ;

	rawWrReg(address, (wr_value << shift), (mask << shift));
}

//-------------------------------------------------------------------------------------------------------------
UINT16 Mplane::OffTargetGpio::readField(const std::string& name)
{
	// Make the name lowercase
	std::string lower(name) ;
	std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower) ;

	Fields_Address_iter iter( mNameLookup.find(lower) ) ;
	if (iter == mNameLookup.end() )
	{
    	writeLog("ERROR: Unable to read field '%s'", name.c_str() ) ;
    	std::cerr << "Unable to read from gpio field '" << lower << "'" << std::endl ;
		return (UINT16)0 ;
	}

	unsigned address = iter->second->mAddress ;
	UINT16 mask = iter->second->mMask ;
	UINT16 shift = iter->second->mShift ;

	UINT16 regValue ;
	rawRdReg(address, &regValue, (mask << shift));

	regValue = ((regValue) >> shift) & mask ;

	return regValue ;
}



//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string::size_type OffTargetGpio::var_val(const std::string &str, const std::string::size_type &startpos,
        std::string &var, std::string &val)
{
	std::string::size_type pos(startpos) ;

	// Skip any space seperated words at start of string
	static std::string delimeq = "\t =" ;
	static std::string delim = "\t " ;

	std::string::size_type var_start(std::string::npos) ;
	std::string::size_type var_end(std::string::npos) ;
	std::string::size_type val_start(std::string::npos) ;

	while(startpos < str.length())
	{
		// Given a string and a start position, finds pairs of the format:
		// var = val
		//
		var_start = str.find_first_not_of(delimeq, pos) ;
		if (var_start == std::string::npos)
			return std::string::npos ;

		var_end = str.find_first_of(delimeq, var_start) ;
		if (var_end == std::string::npos)
			return std::string::npos ;

		val_start = str.find_first_not_of(delimeq, var_end) ;
		if (val_start == std::string::npos)
			return std::string::npos ;

		// check for = following variable name
		std::string sep = str.substr(var_end, val_start-var_end) ;
		if (sep.find("=") != std::string::npos)
			break ;

		// not found "var=" yet so skip this word
		pos = var_end+1 ;

	}

	if (pos >= str.length())
		return std::string::npos ;


	// found "var=.." so find end of value
	std::string::size_type val_end = str.find_first_of(delim, val_start) ;
	if (val_end == std::string::npos)
		val_end = str.length() ;

	// save
	var = str.substr(var_start, var_end-var_start) ;
	val = str.substr(val_start, val_end-val_start) ;

	if (++val_end >= str.length())
		return std::string::npos ;

	return val_end ;
}

//-------------------------------------------------------------------------------------------------------------
// This is a debug method
bool OffTargetGpio::readReg(const UINT32 address, UINT16 *value_p, const UINT16 mask)
{
	Mutex::Lock lock( mAccessMutex );  // use the Mutex lock guard here

	UINT16 data ;
	bool stat = rawRdReg(address, &data, (mask)) ;

	*value_p = (data) ;
	return stat ;
}

//-------------------------------------------------------------------------------------------------------------
// This is a debug method
bool OffTargetGpio::writeReg(const UINT32 address, const UINT16 value, const UINT16 mask)
{
	Mutex::Lock lock( mAccessMutex );  // use the Mutex lock guard here

	rawWrReg(address, (value), (mask)) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
// NOTE: Data is stored in "correct" order
bool OffTargetGpio::rawRdReg(const UINT32 address, UINT16 *value_p, const UINT16 mask)
{
	Fields_Data_iter diter( mDataSources.find(address) ) ;
	if (diter != mDataSources.end())
	{
		// found a data source
		if (diter->second.get())
		{
			if (diter->second->empty())
			{
				// replace empty data with a NULL
				mDataSources[address] = std::shared_ptr<DataSource>() ;
			}
			else
			{
				// use the data source
				*value_p = (diter->second->getValue()) & mask ;
				return true ;
			}

		}
	}

	Data_const_iter iter( mRegData.find(address) ) ;
	if (iter == mRegData.end())
	{
		// not found
		*value_p = (mDefaultValue) & mask ;
		return false ;
	}

	*value_p = (iter->second) & mask ;

	if (mDebug >= 2)
		std::cerr << std::dec << "OffTargetGpio::rawRdReg(0x" <<
		std::hex << address << ") = 0x" <<
		std::hex << iter->second << " [stored=0x" << mRegData[address] << "]" <<
		std::dec <<
		std::endl ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
// NOTE: Data is stored in "correct" order
UINT16 OffTargetGpio::rawWrReg(const UINT32 address, const UINT16 value, const UINT16 mask)
{

	UINT16 new_value = (value) ;
	UINT16 new_mask = (mask) ;

	logFieldWrite(address, new_value, new_mask) ;

	if (new_mask != 0xffff)
	{
		UINT16 readValue ;
		if (!rawRdReg(address, &readValue, 0xffff))
			readValue = 0 ; // reg not access yet, so use 0 as start value (rather than the dummy value)

		// turn on or off the required bit(s)
		new_value = ((readValue) & ~new_mask) | (new_value & new_mask);
	}

    mRegData[address] = new_value ;

    // Sequence Checking
    if (!mCheckSequences.empty())
    {
    	// Update all sequences
    	for (CheckSequenceMap_iter iter = mCheckSequences.begin(); iter != mCheckSequences.end(); ++iter)
    	{
    		iter->second->updateSequence(address, new_value, new_mask) ;
    	}

        // Keep list of actual writes
    	mActualSequence.push_back(SequenceCheck(address, new_value, new_mask)) ;
    }

	if (mDebug >= 2)
		std::cerr << std::dec << "OffTargetGpio::rawWrReg(0x" <<
		std::hex << address << ") = 0x" <<
		std::hex << value << " / 0x" << mask << " [stored=0x" << mRegData[address] << "]" <<
		std::dec <<
		std::endl ;

	return (new_value) ;
}

//-------------------------------------------------------------------------------------------------------------
void OffTargetGpio::startLog(void)
{
	if (mLogFilename.empty())
		return ;

	std::string::size_type sep = mLogFilename.find_last_of("/") ;
	if (sep != std::string::npos)
	{
		std::string path = mLogFilename.substr(0, sep) ;
		mkpath(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) ;
	}

	// if already opened this filename then we're just resetting
	if (mLogFilename == mLastLogFilename)
	{
		// mark the restart
		writeLog("#-- RESTART ---------------------------------\n");
	}
	else
	{
		// create file
		std::ofstream ofile ;
		ofile.open(mLogFilename.c_str(), std::ios::out | std::ios::trunc) ;
		if (ofile.is_open())
		{
			ofile.close() ;
		}
		else
		{
			// can't write to log file, so clear filename
			mLogFilename = "" ;
		}
	}

	// save latest log file setting
	mLastLogFilename = mLogFilename ;
}

//-------------------------------------------------------------------------------------------------------------
void OffTargetGpio::writeLog(const char *fmt, ...)
{
	if (mLogFilename.empty())
		return ;


	// open file
	FILE *ofile = fopen(mLogFilename.c_str(), "a") ;
	if (!ofile)
	{
		// can't write to log file, so clear filename
		mLogFilename = "" ;
		return ;

	}

	// calc timestamp
	struct timespec t ;
	if (clock_gettime(CLOCK_REALTIME, &t) == 0)
	{
		struct tm result ;
		struct tm  *ts = localtime_r(&t.tv_sec, &result);
		char buf[80];

		strftime(buf, sizeof(buf), "%H:%M:%S", ts);

		int us = (int)(t.tv_nsec / 1000L) ;
		fprintf(ofile, "[%s.%06d] [%d] ", buf, us, getpid()) ;
	}


	// print message
    va_list args;

    va_start(args, fmt);
    vfprintf(ofile, fmt, args) ;
    va_end(args) ;
    fprintf(ofile, "\n") ;

	fclose(ofile) ;
}

//-------------------------------------------------------------------------------------------------------------
void OffTargetGpio::logFieldWrite(const unsigned address, const UINT16 value, const UINT16 mask)
{
	// Look up address for any lookup table entry
	Address_Fields_iter iter(mAddressLookup.find(address));
	if (iter == mAddressLookup.end())
		return ;

	for (Field_const_iter field_iter(iter->second.begin()); field_iter != iter->second.end(); ++field_iter)
	{
		// each entry has a field name, mask, and shift
		std::shared_ptr<FieldInfo> entry( *field_iter ) ;
		unsigned field_mask = entry->mMask << entry->mShift ;

		// output if any of the write mask bits overlap with this field
		if (mask & field_mask)
		{
			// get value
			UINT16 field_val = (value & field_mask) >> entry->mShift ;

			// do we have a record?
			if (entry->mRecord.empty())
			{
				writeLog(" + WRITING: %s = 0x%04x", entry->mName.c_str(), field_val) ;
			}
			else
			{
				writeLog(" + WRITING: %s.%s = 0x%04x", entry->mRecord.c_str(), entry->mName.c_str(), field_val) ;
			}
		}
	}

}

//-------------------------------------------------------------------------------------------------------------
void OffTargetGpio::logFieldRead(unsigned address, const UINT16 value, const UINT16 mask)
{
	// Look up address for any lookup table entry
	Address_Fields_iter iter(mAddressLookup.find(address));
	if (iter == mAddressLookup.end())
		return ;

	for (Field_const_iter field_iter(iter->second.begin()); field_iter != iter->second.end(); ++field_iter)
	{
		// each entry has a field name, mask, and shift
		std::shared_ptr<FieldInfo> entry( *field_iter ) ;
		unsigned field_mask = entry->mMask << entry->mShift ;

		// output if any of the write mask bits overlap with this field
		if (mask & field_mask)
		{
			// get value
			UINT16 field_val = (value & field_mask) >> entry->mShift ;

			// do we have a record?
			if (entry->mRecord.empty())
			{
				writeLog(" + READING: %s = 0x%04x", entry->mName.c_str(), field_val) ;
			}
			else
			{
				writeLog(" + READING: %s.%s = 0x%04x", entry->mRecord.c_str(), entry->mName.c_str(), field_val) ;
			}
		}
	}

}




//-------------------------------------------------------------------------------------------------------------
void OffTargetGpio::processFieldNames(const std::string &filename, const std::string& configSearchPath)
{
	std::ifstream infile;
	std::string filepath( openFileViaSearchPath(filename, configSearchPath, infile) ) ;

	if (mDebug) printf("process field names config <%s>\n", filepath.c_str()) ;
//std::cerr << "processFieldNames() path=" << filepath << " open? " << infile.is_open() << std::endl ;

	std::string linebuff ;
	if (infile.is_open())
	{
		while(infile.good())
		{
			// get the line text string
			std::getline(infile, linebuff);


			if (mDebug >= 2) printf("line=<%s>\n", linebuff.c_str()) ;

			// Skip comments (#) and look for lines of the form:
			// name=m1_TxRules1	type=int	perm=rw	position=0x41800	mask=0xffff	shift=0	value=0	record=Wcdma_power_active_struct

			std::string::size_type pos = linebuff.find("#") ;
			if (pos != std::string::npos)
				linebuff.erase(pos, std::string::npos) ;
			if (linebuff.length() == 0)
				continue ;

			// parse line collecting usable parameters
			std::map<std::string, std::string> attributes ;
			std::string var, val ;

			pos = 0 ;
			while(pos != std::string::npos)
			{
				pos = var_val(linebuff, pos, var, val) ;
				if ((var.length() == 0) || (val.length() == 0))
					continue ;

				attributes[var] = val ;
			}

			//-- check we have all the necessary parts --
			typedef std::map<std::string, std::string>::const_iterator Attribs_const_iter ;

			// position (and not set to "none")
			Attribs_const_iter iter( attributes.find("position") ) ;
			if (iter == attributes.end())
				continue ;

			if (iter->second.compare("none") == 0)
				continue ;

			UINT32 address = (unsigned)strtoul(iter->second.c_str(), NULL, 0) ;

			// name
			iter = attributes.find("name") ;
			if (iter == attributes.end())
				continue ;
			std::string name(iter->second) ;

			// (optional) shift
			UINT16 shift = 0 ;
			iter = attributes.find("shift") ;
			if (iter != attributes.end())
			{
				shift = (unsigned)strtoul(iter->second.c_str(), NULL, 0) ;
			}

			// (optional) mask
			UINT16 mask = 0xffff ;
			iter = attributes.find("mask") ;
			if (iter != attributes.end())
			{
				mask = (unsigned)strtoul(iter->second.c_str(), NULL, 0) ;
			}

			// (optional) record
			std::string record("") ;
			iter = attributes.find("record") ;
			if (iter != attributes.end())
			{
				record = iter->second ;
			}

			// Make the name lowercase
			std::string lower(name) ;
			std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower) ;

			if (mDebug >= 2) printf(" + Set field \"%s\" (\"%s\") address 0x%05x bit %d mask 0x%04x\n",
					name.c_str(), lower.c_str(), address, shift, mask) ;

			// Create a new entry
			std::shared_ptr<FieldInfo>entry(new FieldInfo(name, address, shift, mask, record)) ;

			// Add to address lookup
			mAddressLookup[address].push_back(entry) ;

			// Add to name lookup
			mNameLookup[lower] = entry ;
		}
	}
}


//-------------------------------------------------------------------------------------------------------------
int OffTargetGpio::mkpath(const std::string& dirpath, const mode_t mode)
{

    std::string path(dirpath) ;
    if (path[path.size()-1] != '/')
    {
        // force trailing / so we can handle everything in loop
        path += '/';
    }

    int mdret=0;

    size_t pre(0) ;
    size_t pos;
    while( (pos=path.find_first_of('/', pre)) != std::string::npos)
    {
        std::string dir( path.substr(0, pos++) );
        pre = pos;

        if (dir.size()==0)
        	continue; // if leading / first time is 0 length

        if ( (mdret=mkdir(dir.c_str(), mode)) && (errno != EEXIST) )
        {
            return mdret;
        }
    }
    return mdret;
}

//-------------------------------------------------------------------------------------------------------------
void OffTargetGpio::expandVars(std::string& str)
{
	static const std::string VARIABLE_NAME = "abcdefghijklmnopqrstuvwxyz_0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" ;

//std::cerr << "expandVars(" << str << ")" << std::endl ;

	// Currently only supports:
	//
	// ~ = ENV{HOME}
	//
	std::size_t pos = str.find_first_of("~") ;
	if (pos != std::string::npos)
	{
		std::string home( getenv("HOME") );
		str.replace(pos, 1, home) ;
	}

//std::cerr << " + replaced ~ " << str << std::endl ;

	// Add support for replacing $VAR
	size_t start = 0;
	while ((start = str.find('$', start)) != std::string::npos)
	{
		size_t end = str.find_first_not_of(VARIABLE_NAME, start+1) ;
		if (end == std::string::npos)
			end = str.length() ;

		std::string envVar(str.substr(start+1, end-start-1)) ;
//std::cerr << " + + env var = " << envVar << std::endl ;

		char *cvar = getenv(envVar.c_str()) ;
		if (cvar)
		{
			std::string var( cvar ) ;
//std::cerr << " + + var = " << var << std::endl ;
			str.replace(start, end-start, var) ;
//std::cerr << " + + str = = " << str << std::endl ;
		}
		start = end ;
	}
}

//-------------------------------------------------------------------------------------------------------------
std::string OffTargetGpio::openFileViaSearchPath(const std::string& file, const std::string& configSearchPath, std::ifstream& infile)
{
	// If search path is ':' separated list, then try each path
	std::string configPath ;
	size_t start = 0, end = 0;
	while ((end = configSearchPath.find(':', start)) != std::string::npos)
	{
		configPath = configSearchPath.substr(start, end - start) + '/' + file ;
		start = end + 1;

		// try to open file
		infile.open(configPath.c_str());
		if (infile.is_open())
		{
			break ;
		}
	}

	if (!infile.is_open())
	{
		// try remaining
		configPath = configSearchPath.substr(start) + '/' + file ;

		// try to open file
		infile.open(configPath.c_str());
	}

	return configPath ;
}

//=============================================================================================================
// END
//=============================================================================================================

#endif
