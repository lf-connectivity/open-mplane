/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OffTargetFPGA.cpp
 * \brief     Implementation of the OffTargetFPGA class
 *
 *
 * \details   This file contains the implementation of the hardware fpga emulator
 *            class.
 *
 */

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

// BUG#845: debug
//#include "MemMap.hpp"

#include "stringfunc.hpp"
#include "OffTargetFPGA.h"

using namespace Mplane;


//=============================================================================================================
// TYPES
//=============================================================================================================

//-------------------------------------------------------------------------------------
// A class for containing the information about a field
class OffTargetFPGA::FieldInfo
{
public:
	FieldInfo(const std::string& name, const unsigned address, const uint32_t shift = 0, const uint32_t mask = 0xffffffff, const std::string& record = "") :
		mName(name),
		mAddress(address),
		mShift(shift),
		mMask(mask),
		mRecord(record)
	{
	};
	~FieldInfo()
	{
	}

	std::string mName ;
	unsigned mAddress ;
	uint32_t mShift ;
	uint32_t mMask ;
	std::string mRecord ;
};


//-------------------------------------------------------------------------------------
// Class to hold a data source that can be attached to a field
class OffTargetFPGA::DataSource
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

		if ( (mIter == mValues.end()) && (mMode == OffTargetFPGA::DATAVALUES_REPEAT) )
		{
			mIter = mValues.begin() ;
		}

		return value ;
	}


private:
	std::vector<UINT16> mValues ;
	std::vector<UINT16>::iterator mIter ;
	OffTargetFPGA::DataValuesMode mMode ;
};

//-------------------------------------------------------------------------------------
// Class to hold a check sequence and it's results
class OffTargetFPGA::CheckSequence {
public:
	CheckSequence(const std::string& name, const std::vector<OffTargetFPGA::SequenceCheck>& values) :
		mName(name),
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
		for (std::vector<OffTargetFPGA::SequenceCheck>::const_iterator iter = mValues.begin(); iter != mValues.end(); ++iter)
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
		std::cerr <<
				std::hex <<
				"[" << mName << "]"
				" Address 0x" << address <<
				" wr val 0x" << value <<
				" seq addr 0x" << mValuesIter->mAddress <<
				std::dec <<
				" sequence index " << (mValuesIter-mValues.begin()) <<
				" " << (mComplete ? "COMPLETE" : "") <<
				std::endl ;

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

					std::cerr <<
							std::hex <<
							"[" << mName << "]"
							" Sequence check : Address 0x" << address <<
							" wr val 0x" << writtenVal <<
							" expected 0x" << expectedVal <<
							std::dec <<
							" sequence index " << (mValuesIter-mValues.begin()) <<
							" " << (mComplete ? "COMPLETE" : "") <<
							std::endl ;

				}
				else
				{
					std::cerr <<
							std::hex <<
							"[" << mName << "]"
							" ! Sequence check restart: Address 0x" << address <<
							" wr val 0x" << writtenVal <<
							" expected 0x" << expectedVal <<
							std::dec <<
							" sequence index " << (mValuesIter-mValues.begin()) <<
							std::endl ;

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
	std::string mName ;
	bool mComplete ;
	unsigned mMismatches ;
	const std::vector<OffTargetFPGA::SequenceCheck> mValues ;
	std::vector<OffTargetFPGA::SequenceCheck>::const_iterator mValuesIter ;

	// @todo: add vector of actual writes ?
};


//=============================================================================================================
// SINGLETON
//=============================================================================================================

class OffTargetFPGAInst : public OffTargetFPGA {
public:
	OffTargetFPGAInst(OffTargetFPGASize dataSize) : OffTargetFPGA(dataSize) {}
	virtual ~OffTargetFPGAInst() {}
};
//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<OffTargetFPGA> OffTargetFPGA::getInstance(void)
{
	return createInstance(DATA_DEFAULT) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<OffTargetFPGA> OffTargetFPGA::createInstance(OffTargetFPGASize dataSize)
{
    static std::shared_ptr<OffTargetFPGA> _instance(std::make_shared<OffTargetFPGAInst>(dataSize));
    if (dataSize != DATA_DEFAULT)
    	_instance->setDataSize(dataSize) ;
    return _instance;
}


//=============================================================================================================
// MemMap Interface
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
uint32_t OffTargetFPGA::readVal(unsigned offset, uint32_t mask)
{
	Mutex::Lock lock( mAccessMutex );  // use the Mutex lock guard here

	writeLog("CMD: read 0x%05x 1", offset) ;

	uint32_t readValue ;
	rawRdReg(offset, &readValue, mask);
	logFieldRead(offset, readValue, mask) ;
	writeLog("REPLY: OK 0x%08x\n", readValue) ;

	return(readValue) ;
}

//-------------------------------------------------------------------------------------------------------------
uint32_t OffTargetFPGA::modifyVal(unsigned offset, uint32_t value, uint32_t mask)
{
	Mutex::Lock lock( mAccessMutex );  // use the Mutex lock guard here

	writeLog("CMD: modify 0x%05x 1 0x%08x/0x%08x", offset, value, mask) ;

	uint32_t readValue = rawWrReg(offset, value, mask);
	writeLog("REPLY: OK 0x%08x\n", readValue) ;

	return(readValue) ;
}

//-------------------------------------------------------------------------------------------------------------
void OffTargetFPGA::writeVal(unsigned offset, uint32_t value, uint32_t mask)
{
	Mutex::Lock lock( mAccessMutex );  // use the Mutex lock guard here

	writeLog("CMD: write 0x%05x 1 0x%08x/0x%08x", offset, value, mask) ;
	rawWrReg(offset, value, mask);
	writeLog("REPLY: OK 0x%08x\n", value) ;

}


//=============================================================================================================
// Debug Interface
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
void OffTargetFPGA::setDebug(const unsigned level)
{
	mDebug = level ;
}

//-------------------------------------------------------------------------------------------------------------
void OffTargetFPGA::reset()
{
	reset(mConfigFile) ;
}

//-------------------------------------------------------------------------------------------------------------
void OffTargetFPGA::reset(const std::string &configFile)
{
	Mutex::Lock lock( mAccessMutex );  // use the Mutex lock guard here

	// reset vars
	mDebug = 0 ;
	mRegData.clear() ;
	mAddressLookup.clear() ;
	mNameLookup.clear() ;
	mDataSources.clear() ;
	mLogEnable = false ;
	mLogFilename = std::string("") ;
	mActualSequence.clear() ;

	// re-initialise
	std::string config(configFile) ;
	expandVars(config) ;
	expandVars(mConfigSearchPath) ;
	initialise(config, mConfigSearchPath) ;

	std::cerr << ">>> OffTargetFPGA reset <<<" << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
void OffTargetFPGA::writeField(const std::string& name, const UINT16 value)
{
	Mutex::Lock lock( mAccessMutex );  // use the Mutex lock guard here
	internalWriteField(name, value) ;
}

//-------------------------------------------------------------------------------------------------------------
void OffTargetFPGA::internalWriteField(const std::string& name, const UINT16 value)
{
	// Make the name lowercase
	std::string lower(name) ;
	std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower) ;

	Fields_Address_iter iter( mNameLookup.find(lower) ) ;
	if (iter == mNameLookup.end() )
	{
    	writeLog("ERROR: Unable to write field '%s'", name.c_str() ) ;
    	std::cerr << "Unable to write to fpga field '" << lower << "'" << std::endl ;
		return ;
	}

	unsigned address = iter->second->mAddress ;
	UINT16 mask = iter->second->mMask ;
	UINT16 shift = iter->second->mShift ;
	UINT16 wr_value = value & mask ;

	internalWrReg(address, (wr_value << shift), (mask << shift));
}

//-------------------------------------------------------------------------------------------------------------
UINT16 OffTargetFPGA::readField(const std::string& name)
{
	Mutex::Lock lock( mAccessMutex );  // use the Mutex lock guard here
	return internalReadField(name) ;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 OffTargetFPGA::internalReadField(const std::string& name)
{
	// Make the name lowercase
	std::string lower(name) ;
	std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower) ;

	Fields_Address_iter iter( mNameLookup.find(lower) ) ;
	if (iter == mNameLookup.end() )
	{
    	writeLog("ERROR: Unable to read field '%s'", name.c_str() ) ;
    	std::cerr << "Unable to read from fpga field '" << lower << "'" << std::endl ;
		return (UINT16)0 ;
	}

	unsigned address = iter->second->mAddress ;
	UINT16 mask = iter->second->mMask ;
	UINT16 shift = iter->second->mShift ;

	UINT32 regValue ;
	internalRdReg(address, &regValue, (mask << shift));

	regValue = ((regValue) >> shift) & mask ;

	return (UINT16)regValue ;
}



//-------------------------------------------------------------------------------------------------------------
void OffTargetFPGA::registerDataValues(const std::string &fieldName, const std::vector<UINT16>& values, const DataValuesMode mode)
{
	// Make the name lowercase
	std::string lower(fieldName) ;
	std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower) ;

	Fields_Address_iter iter( mNameLookup.find(lower) ) ;
	if (iter == mNameLookup.end() )
	{
    	writeLog("ERROR: Unable to access field '%s'", fieldName.c_str() ) ;
    	std::cerr << "Unable to access fpga field '" << fieldName << "'" << std::endl ;
		return ;
	}

	registerDataValues(iter->second->mAddress, values, mode) ;

}


//-------------------------------------------------------------------------------------------------------------
void OffTargetFPGA::registerDataValues(const unsigned address, const std::vector<UINT16>& values, const DataValuesMode mode)
{
	mDataSources[address] = std::shared_ptr<DataSource>(new DataSource(values, mode)) ;
}



//-------------------------------------------------------------------------------------------------------------
void OffTargetFPGA::addSequenceCheck(const std::string& seqName, const std::vector<SequenceCheck>& values)
{
	mCheckSequences[seqName] = std::shared_ptr<CheckSequence>(new CheckSequence(seqName, values)) ;
}

//-------------------------------------------------------------------------------------------------------------
void OffTargetFPGA::addSequenceCheck(const std::string& seqName, const std::vector<FieldSequenceCheck>& values, SequenceMode seqMode)
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
	    	std::cerr << "Unable to access fpga field '" << iter->mField << "'" << std::endl ;
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
	mCheckSequences[seqName] = std::shared_ptr<CheckSequence>(new CheckSequence(seqName, seqValues)) ;
}

//-------------------------------------------------------------------------------------------------------------
bool OffTargetFPGA::isSequenceCheckComplete(const std::string& seqName)
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
void OffTargetFPGA::delSequenceCheck(const std::string& seqName)
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
void OffTargetFPGA::restartSequenceCheck(const std::string& seqName)
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
void OffTargetFPGA::showSequenceCheck(const std::string& seqName)
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
	for (std::vector<OffTargetFPGA::SequenceCheck>::const_iterator iter = mActualSequence.begin(); iter != mActualSequence.end(); ++iter)
	{
		printf(" [%03u] 0x%05x: 0x%04x / 0x%04x\n",
			idx++,
			iter->mAddress, iter->mValue, iter->mMask);
	}
	std::cout << "-------------------------" << std::endl ;

}

//-------------------------------------------------------------------------------------------------------------
void OffTargetFPGA::showSequenceCheckTestcode(const std::string& seqName, const std::string& testName)
{
	CheckSequenceMap_iter iter( mCheckSequences.find(seqName) ) ;
	if (iter == mCheckSequences.end() )
	{
    	writeLog("ERROR: Check Sequence '%s' is not registered", seqName.c_str() ) ;
    	std::cerr << "Check Sequence '" << seqName << "' is not registered" << std::endl ;
		return ;
	}


//	static const OffTargetFPGA::SequenceCheck gatherSeqData[] = {
//
//			// This is a sequence guaranteed NOT to appear - used to gather the actual sequence
//			OffTargetFPGA::SequenceCheck(0xFFFFF, 0x1010),
//	} ;
//	#define NUM_GATHER_DATA	(sizeof(gatherSeqData) / sizeof(OffTargetFPGA::SequenceCheck))

	std::string TEST_NAME(toUpper(testName)) ;
	std::cout << "static const OffTargetFPGA::SequenceCheck " << testName <<  "SeqData[] = {" << std::endl ;
	for (std::vector<OffTargetFPGA::SequenceCheck>::const_iterator iter = mActualSequence.begin(); iter != mActualSequence.end(); ++iter)
	{
		printf("\tOffTargetFPGA::SequenceCheck(0x%05x, 0x%04x, 0x%04x),\n",
			iter->mAddress, iter->mValue, iter->mMask);
	}
	std::cout << "} ;" << std::endl ;
	std::cout << "#define NUM_" << TEST_NAME << "_DATA	(sizeof(" <<
			testName << "SeqData) / sizeof(OffTargetFPGA::SequenceCheck))" << std::endl ;

}


//-------------------------------------------------------------------------------------------------------------
bool OffTargetFPGA::registerHandler(const UINT32 address,
		WriteHandlerFunction writeHandler, ReadHandlerFunction readHandler)
{
	return registerHandler(address, address, writeHandler, readHandler) ;
}

//-------------------------------------------------------------------------------------------------------------
bool OffTargetFPGA::registerHandler(const UINT32 addressStart,
		const UINT32 addressEnd, WriteHandlerFunction writeHandler,
		ReadHandlerFunction readHandler)
{
	unsigned start(addressStart) ;
	unsigned end(addressEnd) ;
	if (end < start)
		std::swap(start, end) ;
//std::cerr << "OffTargetFPGA::registerHandler 0x" << std::hex << start << " .. 0x" << end << std::dec << std::endl ;

	for (unsigned addr=start; addr <= end; addr+=2)
	{
		// shouldn't be anything already registered
		if (mAddressHandlers.find(addr) != mAddressHandlers.end())
		{
			std::cerr << "Off Target FPGA ERROR: Attempting to register handler address that is already being handled 0x" << std::hex << addr << std::dec << std::endl ;
			return false ;
		}

		// set this entry
		mAddressHandlers[addr] = make_pair(writeHandler, readHandler) ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool OffTargetFPGA::unRegisterHandler(const UINT32 address)
{
	return unRegisterHandler(address, address) ;
}

//-------------------------------------------------------------------------------------------------------------
bool OffTargetFPGA::unRegisterHandler(const UINT32 addressStart, const UINT32 addressEnd)
{
	unsigned start(addressStart) ;
	unsigned end(addressEnd) ;
	if (end < start)
		std::swap(start, end) ;
//std::cerr << "OffTargetFPGA::unRegisterHandler 0x" << std::hex << start << " .. 0x" << end << std::dec << std::endl ;

	for (unsigned addr=start; addr <= end; addr+=2)
	{
		// remove any registered handler
		auto entry( mAddressHandlers.find(addr) ) ;
		if (entry != mAddressHandlers.end())
			mAddressHandlers.erase(entry) ;
	}
	return true ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
OffTargetFPGA::OffTargetFPGA(OffTargetFPGASize dataSize, const std::string& config_file,
		const std::string& config_search_path, uint32_t default_value) :
	mDataSize(DATA16),
	mConfigFile(config_file),
	mConfigSearchPath(config_search_path),
	mRequestedDefaultValue(default_value),
	mDefaultValue(default_value),
	mAccessMutex(),
	mDebug(0),
	mRegData(),
	mAddressLookup(),
	mNameLookup(),
	mDataSources(),
	mLogEnable(false),
	mLogFilename(""),
	mLastLogFilename(""),
	mActualSequence(0),

	mDefaultMaskFunc(),
	mAdjustAddressFunc(),
	mAdjustWrDataFunc(),
	mAdjustRdDataFunc()

{
	std::cout << "Before : " << mConfigFile << "," << mConfigSearchPath << std::endl;
	setDataSize(dataSize) ;

	expandVars(mConfigFile) ;
	expandVars(mConfigSearchPath) ;

	std::cout << "After : " << mConfigFile << "," << mConfigSearchPath << std::endl;

	initialise(mConfigFile, mConfigSearchPath) ;
}


//-------------------------------------------------------------------------------------------------------------
OffTargetFPGA::~OffTargetFPGA()
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
void OffTargetFPGA::setDataSize(OffTargetFPGASize dataSize)
{
	if (dataSize != DATA_DEFAULT)
		mDataSize = dataSize ;

	initFuncs() ;
	mDefaultValue = mRequestedDefaultValue & mDefaultMaskFunc() ;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State OffTargetFPGA::initialise(const std::string& configFile, const std::string& configSearchPath)
{
	// First get any environment variable settings and apply them
	processEnvironmentVars() ;

	// Start initialisation
	std::ifstream infile;
	std::string configPath( openFileViaSearchPath(configFile, configSearchPath, infile) ) ;

	std::cout << "Config Path - " << configPath.c_str() << std::endl;
	if (mDebug) printf("read <%s>\n", configPath.c_str()) ;

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
				internalWrReg(address, word) ;
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
			    	std::cerr << "INFO: Unable to find fpga field '" << cmd_val << "'" << std::endl ;
			    	continue ;
				}

				unsigned address = iter->second->mAddress ;
				UINT16 mask = iter->second->mMask ;
				UINT16 shift = iter->second->mShift ;
				unsigned value = (unsigned)strtoul(value_val.c_str(), NULL, 0) ;
				UINT16 wr_value = value & mask ;

				internalWrReg(address, (wr_value << shift), (mask << shift));

				if (mDebug) printf("LOAD: 0x%05x = 0x%04x / 0x%04x\n", address, (wr_value << shift), (mask << shift)) ;
			}

			// emu.debug
			else if (cmd_var.compare("emu.debug") == 0)
			{
				mDebug = (unsigned)strtoul(cmd_val.c_str(), NULL, 0) ;
				std::cerr << "FPGA EMU: Debug level " << mDebug << std::endl ;
			}

			// emu.log
			else if (cmd_var.compare("emu.log") == 0)
			{
				mLogFilename = cmd_val ;
				std::cerr << "FPGA EMU: Log file " << mLogFilename << std::endl ;
				startLog() ;
			}

			// emu.logEnable
			else if (cmd_var.compare("emu.logEnable") == 0)
			{
				if (toLower(cmd_val) == "true")
					mLogEnable = true ;
				else
					mLogEnable = (strtoul(cmd_val.c_str(), NULL, 0) > 0 ? true : false) ;
				std::cerr << "FPGA EMU: Logging " << (mLogEnable ? "ENABLED" : "DISABLED") << std::endl ;
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

	if (mDebug)
		std::cerr << "OffTargetFPGA: initialise() path=" << configPath <<
				" search=" << configSearchPath <<
				std::endl ;


    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
void OffTargetFPGA::processEnvironmentVars()
{
	// Environment variables
	static const std::string ENV_LOG_FILE{"OFFTARGET_LOG_FILE"} ;
	static const std::string ENV_LOG_ENABLE{"OFFTARGET_LOG_ENABLE"} ;
	static const std::string ENV_DEBUG{"OFFTARGET_DEBUG"} ;

	if (isEnvSet(ENV_LOG_FILE))
	{
		mLogFilename = getEnvStr(ENV_LOG_FILE) ;
		startLog() ;
	}

	if (isEnvSet(ENV_LOG_ENABLE))
	{
		mLogEnable = getEnvBool(ENV_LOG_ENABLE) ;
		startLog() ;
	}

	if (isEnvSet(ENV_DEBUG))
	{
		mDebug = getEnvUint(ENV_DEBUG) ;
	}
}



//-------------------------------------------------------------------------------------------------------------
uint32_t OffTargetFPGA::defaultValue(void) const
{
	return mDefaultValue ;
}


//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string::size_type OffTargetFPGA::var_val(const std::string &str, const std::string::size_type &startpos,
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
bool OffTargetFPGA::readReg(const UINT32 address, UINT16 *value_p, const UINT16 mask)
{
	Mutex::Lock lock( mAccessMutex );  // use the Mutex lock guard here

	uint32_t data ;
	bool stat = internalRdReg(address, &data, (uint32_t)mask) ;

	*value_p = (UINT16)(data) ;
	return stat ;
}

//-------------------------------------------------------------------------------------------------------------
// This is a debug method
bool OffTargetFPGA::writeReg(const UINT32 address, const UINT16 value, const UINT16 mask)
{
	Mutex::Lock lock( mAccessMutex );  // use the Mutex lock guard here

	internalWrReg(address, (uint32_t)(value), (uint32_t)(mask)) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
// NOTE: Data is stored in "correct" order
bool OffTargetFPGA::internalRdReg(const UINT32 address, uint32_t *value_p, const uint32_t mask)
{
	UINT32 addr(address) ;
	uint32_t adjMask(mask) ;
	mAdjustAddressFunc(addr) ;
	mAdjustWrDataFunc(address, adjMask) ;

	uint32_t data ;
	bool ok(rawRdReg(addr, &data, adjMask));

	*value_p = mAdjustRdDataFunc(address, data) ;
	return ok ;
}


//-------------------------------------------------------------------------------------------------------------
// NOTE: Data is stored in "correct" order
uint32_t OffTargetFPGA::internalWrReg(const UINT32 address, const uint32_t value, const uint32_t mask)
{
	uint32_t new_value(value) ;
	uint32_t new_mask(mask) ;

	if (address == 0x50812)
	{
		std::cerr << "Write 0x50812" << std::endl ;
	}

	UINT32 addr(address) ;
	mAdjustAddressFunc(addr) ;
	mAdjustWrDataFunc(address, new_value) ;
	mAdjustWrDataFunc(address, new_mask) ;

	uint32_t data(rawWrReg(addr, new_value, new_mask)) ;
	return mAdjustRdDataFunc(address, data) ;
}



//-------------------------------------------------------------------------------------------------------------
// NOTE: Data is stored in "correct" order
bool OffTargetFPGA::rawRdReg(const UINT32 address, uint32_t *value_p, const uint32_t mask)
{
	// - If we have a handler for this address then pass control over -
	auto entry(mAddressHandlers.find(address)) ;
	if (entry != mAddressHandlers.end())
	{
		*value_p = entry->second.second(address, mask) ;
		return true ;
	}

	// - Otherwise handle as normal -
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
		std::cerr << std::dec << "OffTargetFPGA::internalRdReg(0x" <<
		std::hex << address << ") = 0x" <<
		std::hex << iter->second << " [stored=0x" << mRegData[address] << "]" <<
		std::dec <<
		std::endl ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
// NOTE: Data is stored in "correct" order
uint32_t OffTargetFPGA::rawWrReg(const UINT32 address, const uint32_t value, const uint32_t mask)
{
	uint32_t new_value(value) ;
	uint32_t new_mask(mask) ;

	logFieldWrite(address, new_value, new_mask) ;

	// - If we have a handler for this address then pass control over -
	auto entry(mAddressHandlers.find(address)) ;
	if (entry != mAddressHandlers.end())
		return entry->second.first(address, value, mask) ;


	// - Otherwise handle as normal -
	if (new_mask != mDefaultMaskFunc())
	{
		uint32_t readValue ;
		if (!internalRdReg(address, &readValue, mDefaultMaskFunc()))
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
		std::cerr << std::dec << "OffTargetFPGA::internalWrReg(0x" <<
		std::hex << address << ") = 0x" <<
		std::hex << value << " / 0x" << mask << " [stored=0x" << mRegData[address] << "]" <<
		std::dec <<
		std::endl ;

	return (new_value) ;
}

//-------------------------------------------------------------------------------------------------------------
void OffTargetFPGA::startLog(void)
{
	if (mLogFilename.empty())
		return ;

	if (!mLogEnable)
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
void OffTargetFPGA::writeLog(const char *fmt, ...)
{
	if (mLogFilename.empty())
		return ;

	if (!mLogEnable)
		return ;


	// open file
	FILE *ofile = fopen(mLogFilename.c_str(), "a") ;
	if (!ofile)
	{
		std::cerr << "** OffTargetFPGA::writeLog unable to write to " << mLogFilename << std::endl ;

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
void OffTargetFPGA::logFieldWrite(const unsigned address, const uint32_t value, const uint32_t mask)
{
	// Look up address for any lookup table entry
	Address_Fields_iter iter(mAddressLookup.find(address));
	if (iter == mAddressLookup.end())
		return ;

	for(auto entry : iter->second)
	{
		unsigned field_mask = entry->mMask << entry->mShift ;

		// output if any of the write mask bits overlap with this field
		if (mask & field_mask)
		{
			// get value
			uint32_t field_val = (value & field_mask) >> entry->mShift ;

			// do we have a record?
			if (entry->mRecord.empty())
			{
				writeLog(" + WRITING: %s = 0x%08x", entry->mName.c_str(), field_val) ;
			}
			else
			{
				writeLog(" + WRITING: %s.%s = 0x%08x", entry->mRecord.c_str(), entry->mName.c_str(), field_val) ;
			}
		}
	}

}

//-------------------------------------------------------------------------------------------------------------
void OffTargetFPGA::logFieldRead(unsigned address, const uint32_t value, const uint32_t mask)
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
			uint32_t field_val = (value & field_mask) >> entry->mShift ;

			// do we have a record?
			if (entry->mRecord.empty())
			{
				writeLog(" + READING: %s = 0x%08x", entry->mName.c_str(), field_val) ;
			}
			else
			{
				writeLog(" + READING: %s.%s = 0x%08x", entry->mRecord.c_str(), entry->mName.c_str(), field_val) ;
			}
		}
	}

}




//-------------------------------------------------------------------------------------------------------------
void OffTargetFPGA::processFieldNames(const std::string &filename, const std::string& configSearchPath)
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
			uint32_t shift = 0 ;
			iter = attributes.find("shift") ;
			if (iter != attributes.end())
			{
				shift = (unsigned)strtoul(iter->second.c_str(), NULL, 0) ;
			}

			// (optional) mask
			uint32_t mask = 0xffffffff ;
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

			if (mDebug >= 2) printf(" + Set field \"%s\" (\"%s\") address 0x%05x bit %d mask 0x%08x\n",
					name.c_str(), lower.c_str(), address, shift, mask) ;

			// Create a new entry
			std::shared_ptr<FieldInfo>entry(new FieldInfo(name, address, shift, mask, record)) ;

			// Add to address lookup
			mAddressLookup[ address ].push_back(entry) ;

			// Add to name lookup
			mNameLookup[lower] = entry ;
		}
	}
}


//-------------------------------------------------------------------------------------------------------------
int OffTargetFPGA::mkpath(const std::string& dirpath, const mode_t mode)
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
void OffTargetFPGA::expandVars(std::string& str)
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

		char *cvar = ::getenv(envVar.c_str()) ;
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
std::string OffTargetFPGA::openFileViaSearchPath(const std::string& file, const std::string& configSearchPath, std::ifstream& infile)
{
	std::string searchPath(configSearchPath) ;

	std::cout << "Search Path : " << searchPath << std::endl;

// If OFFTARGET_CFG_DIR	was defined during compilation, then append it to the path
#ifdef OFFTARGET_CFG_DIR
	searchPath += ":" + std::string( OFFTARGET_CFG_DIR ) ;
#endif

	std::cout << "Search Path now : " << searchPath << std::endl;

//	std::cerr << "OffTargetFPGA: openFileViaSearchPath(" << file <<") search=" << searchPath << std::endl ;

	// If search path is ':' separated list, then try each path
	std::string configPath ;
	size_t start = 0, end = 0;
	bool found(false) ;
	while (!found && ((end = searchPath.find(':', start)) != std::string::npos) )
	{
		configPath = searchPath.substr(start, end - start) + '/' + file ;
		start = end + 1;

std::cerr << "OFFTARGET FPGA: init - try config " << configPath << std::endl ;
		// try to open file
		infile.open(configPath.c_str());
		if (infile.is_open())
		{
			std::cerr << "OFFTARGET FPGA: init - config opened " << configPath << std::endl ;
			found = true ;
			break ;
		}
	}

	if (!infile.is_open())
	{
		// try remaining
		configPath = searchPath.substr(start) + '/' + file ;

		// try to open file
		infile.open(configPath.c_str());
	}

	std::cerr << "OFFTARGET FPGA: config=" << configPath << std::endl ;
	return configPath ;
}

//-------------------------------------------------------------------------------------------------------------
std::string OffTargetFPGA::getEnvStr(const std::string& name) const
{
	char *cvar = ::getenv(name.c_str()) ;
	if (cvar)
		return std::string(cvar) ;

	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
bool OffTargetFPGA::isEnvSet(const std::string& name) const
{
	std::string val(getEnvStr(name)) ;
	if (val.empty())
		return false ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned OffTargetFPGA::getEnvUint(const std::string& name) const
{
	std::string val(getEnvStr(name)) ;
	if (val.empty())
		return 0 ;

	return (unsigned)strtoul(val.c_str(), NULL, 0) ;
}

//-------------------------------------------------------------------------------------------------------------
bool OffTargetFPGA::getEnvBool(const std::string& name) const
{
	std::string val(getEnvStr(name)) ;
	if (val.empty())
		return false ;

	std::string lower(toLower(val)) ;
	if (lower == "yes")
		return true ;
	if (lower == "on")
		return true ;
	if (lower == "enable")
		return true ;
	if (lower == "1")
		return true ;

	return false ;
}

//-------------------------------------------------------------------------------------------------------------
void OffTargetFPGA::initFuncs()
{
	switch (mDataSize)
	{
	case DATA16:
		mDefaultMaskFunc = [this](){ return defaultMask16(); } ;
		mAdjustAddressFunc = [this](uint32_t& address){ return adjustAddress16(address); } ;
		mAdjustWrDataFunc = [this](uint32_t address, uint32_t& data){ return adjustWrData16(address, data); } ;
		mAdjustRdDataFunc = [this](uint32_t address, uint32_t& data){ return adjustRdData16(address, data); } ;
		break ;

	case DATA32:
		mDefaultMaskFunc = [this](){ return defaultMask32(); } ;
		mAdjustAddressFunc = [this](uint32_t& address){ return adjustAddress32(address); } ;
		mAdjustWrDataFunc = [this](uint32_t address, uint32_t& data){ return adjustWrData32(address, data); } ;
		mAdjustRdDataFunc = [this](uint32_t address, uint32_t& data){ return adjustRdData32(address, data); } ;
		break ;

	default:
		break ;
	}
}

//-------------------------------------------------------------------------------------------------------------
uint32_t OffTargetFPGA::defaultMask32() const
{
	return static_cast<uint32_t>(-1) ;
}

//-------------------------------------------------------------------------------------------------------------
uint32_t OffTargetFPGA::defaultMask16() const
{
	return static_cast<uint32_t>( static_cast<uint16_t>(-1) ) ;
}

//-------------------------------------------------------------------------------------------------------------
uint32_t OffTargetFPGA::adjustAddress16(uint32_t &address) const
{
	return address ;
}

//-------------------------------------------------------------------------------------------------------------
uint32_t OffTargetFPGA::adjustAddress32(uint32_t &address) const
{
	address &= 0xfffffffc;  // adjust to 32-bit boundary
	return address ;
}

//-------------------------------------------------------------------------------------------------------------
uint32_t OffTargetFPGA::adjustWrData16(uint32_t address, uint32_t &data) const
{
	return data ;
}

//-------------------------------------------------------------------------------------------------------------
uint32_t OffTargetFPGA::adjustWrData32(uint32_t address, uint32_t &data) const
{
	if (address & 0x3) // odd 16-bit address
	{
		// high short - appears on MS of 32-bit bus
		data <<= 16;
	}

	return data ;
}

//-------------------------------------------------------------------------------------------------------------
uint32_t OffTargetFPGA::adjustRdData16(uint32_t address, uint32_t &data) const
{
	return data ;
}

//-------------------------------------------------------------------------------------------------------------
uint32_t OffTargetFPGA::adjustRdData32(uint32_t address, uint32_t &data) const
{
	if (address & 0x3) // odd 16-bit address
	{
		// high short - appears on MS of 32-bit bus
		data >>= 16 ;
	}

	return data ;
}

//=============================================================================================================
// END
//=============================================================================================================
