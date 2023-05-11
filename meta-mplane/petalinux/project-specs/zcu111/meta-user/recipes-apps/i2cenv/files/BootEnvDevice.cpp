/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BootEnvDevice.cpp
 * \brief     u-boot environment device class
 *
 *
 * \details   Manages access to one of the u-boot environment devices.
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
//#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <error.h>
#include <unistd.h>
//#include <string.h>
#include <stdlib.h>

#ifdef OFF_TARGET
#include "IAppSettings.h"
#include "IAppSettingsFactory.h"
#include "AppSettings.h"
#include "Path.h"
#else
#include <sys/types.h>
#include <sys/ioctl.h>
//#include <ctype.h>
//#include <sys/time.h>
#include <mtd/mtd-user.h>
#endif

//#include "GlobalTypeDefs.h"
#include "Crc.h"
#include "stringfunc.hpp"
#include "ByteTransfer.hpp"
#include "BootEnvDevice.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------

/**
 * U-boot env data is stored as (with flag support):
 *
 * +----+----+----+----+
 * | CRC (32 bits)     |
 * +----+----+----+----+
 * |FLAG|
 * +----+----+----+----+
 * | DATA....          |
 * | ...               |
 * | ...               |
 * | ...               |
 * +----+----+----+----+
 *
 * or (without flag support):
 *
 * +----+----+----+----+
 * | CRC (32 bits)     |
 * +----+----+----+----+
 * | DATA....          |
 * | ...               |
 * | ...               |
 * | ...               |
 * +----+----+----+----+
 *
 */
static const unsigned NOR_CRC_OFFSET{0} ;
static const unsigned NOR_CRC_SIZE{4} ;
static const unsigned NOR_FLAG_SIZE{1} ;

//=============================================================================================================
// OFF TARGET EMULATION
//=============================================================================================================

#ifdef OFF_TARGET

//-------------------------------------------------------------------------------------------------------------
static const std::string EnvFileDir("bootenv") ;

namespace {

	//-------------------------------------------------------------------------------------------------------------
	std::string getEnvFilepath(const std::string& devName, unsigned envSize)
	{
		std::string user(::getenv("USER")) ;
		if (user.empty())
			user = "test" ;

		std::shared_ptr<IAppSettings> appSettings(IAppSettingsFactory::getInterface());

		std::string tmpPath(
			"/tmp/" + user + "/" + EnvFileDir + "/" +
			appSettings->getBoardString() + "-" +
			appSettings->getCustomerString() + "-" +
			appSettings->getAppString()
		) ;

		// Ensure test path is created
		Path::mkpath(tmpPath);
		Path::mkpath(tmpPath+"/dev");

		std::string filePath(tmpPath + devName) ;

		// if file exists but is the wrong size then reset data
		if (Path::exists(filePath) && (Path::fileSize(filePath) != envSize))
			Path::remove(filePath) ;

		return filePath ;
	}

}

#endif


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
BootEnvDevice::BootEnvDevice(unsigned index, const std::string& devName, bool flagSupported, unsigned envSize) :
	Loggable("BootEnvDev" + std::to_string(index), "BootEnv"),
	mFlagSupported(flagSupported),
	mEnvSize(envSize),
	mValid(false),
	mIndex(index),
	mDevName(devName),
	mCrc(0),
	mActive(false),
	mEnv(),
	mError("")
{
#ifdef OFF_TARGET
	// create a dummy device name - use a real file for emulation
    // cppcheck-suppress useInitializationList
	mDevName = getEnvFilepath(devName, mEnvSize) ;

	// If file doesn't exist then create a default
	if (!Path::exists(mDevName))
		reset() ;

#endif

	// load in the data
	mValid = read() ;
}

//-------------------------------------------------------------------------------------------------------------
BootEnvDevice::~BootEnvDevice()
{
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnvDevice::setActiveFlag(bool active)
{
	mActive = active ;
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool BootEnvDevice::isValid() const
{
	return mValid ;
}

//-------------------------------------------------------------------------------------------------------------
std::string BootEnvDevice::getError()
{
	std::string error("") ;
	std::swap(error, mError) ;
	return error ;
}


//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::string> BootEnvDevice::getVars() const
{
	return mEnv ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnvDevice::isVar(const std::string& var) const
{
	auto entry(mEnv.find(var)) ;
	return entry != mEnv.end() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string BootEnvDevice::getVar(const std::string& var) const
{
	auto entry(mEnv.find(var)) ;
	if (entry == mEnv.end())
		return "" ;

	return entry->second ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnvDevice::setVar(const std::string& var, const std::string& value)
{
	return setVar(std::map<std::string, std::string>{{var, value}}) ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnvDevice::setVar(const std::map<std::string, std::string>& vars)
{
	for (auto varVal : vars)
	{
		mEnv[varVal.first] = varVal.second ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnvDevice::deleteVar(const std::string& var)
{
	return deleteVar(std::vector<std::string>{var}) ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnvDevice::deleteVar(const std::vector<std::string>& vars)
{
	for (auto var : vars)
	{
		mEnv.erase(var) ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnvDevice::resetVars(const std::map<std::string, std::string>& vars)
{
	mEnv.clear() ;
	mEnv = vars ;
	return true ;
}



//-------------------------------------------------------------------------------------------------------------
unsigned BootEnvDevice::getIndex() const
{
	return mIndex ;
}

//-------------------------------------------------------------------------------------------------------------
std::string BootEnvDevice::getDeviceName() const
{
	return mDevName ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnvDevice::isActive() const
{
	return mActive ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnvDevice::read()
{
	std::vector<uint8_t> data(mEnvSize, 0xff) ;
	auto dataStart(data.cbegin()) ;
	auto dataEnd(data.cend()) ;

	// Read data
	int fd = ::open(mDevName.c_str(), O_RDONLY) ;
	if (fd < 0)
	{
		setError("Unable to open device " + mDevName + " " + strError(errno));
		return false ;
	}

	int read = ::read(fd, &data[0], data.size()) ;
	::close(fd) ;
	if (read < 0)
	{
		setError("Error reading environment from device " + mDevName + " " + strError(errno));
		return false ;
	}
	if (static_cast<unsigned>(read) < data.size())
	{
		setError("Failed to read complete environment from device " + mDevName);
		return false ;
	}

//	// debug
//	ByteTransfer::dump(data) ;

	// ** Extract data **
	unsigned dataOffset(NOR_CRC_OFFSET+NOR_CRC_SIZE) ;
	if (mFlagSupported)
		dataOffset += NOR_FLAG_SIZE ;

	unsigned dataSize = mEnvSize - dataOffset ;

	// CRC
#ifdef IS_BIG_ENDIAN
//	std::cerr << mDevName<< " Big Endian" << std::endl ;
	uint32_t crc = ByteTransfer::readWord(dataStart, dataEnd) ;
#else
//	std::cerr << mDevName<< " Little Endian" << std::endl ;
	uint32_t crc = ByteTransfer::readWordLE(dataStart, dataEnd) ;
#endif
	uint32_t crcReal = Crc32::calc(&data[dataOffset], dataSize) ;
	mValid = (crc == crcReal) ;
	if (!mValid)
	{
//		setError("CRC mismatch on device " + mDevName);
//		return false ;
		std::cerr << mDevName<< " CRC Error: Got 0x" << std::hex << crc << " expected 0x" << crcReal << std::dec <<
				" " << dataSize << " bytes starting at offset " << dataOffset <<
				std::endl ;
	}
#if 0
else
{
	std::cerr << mDevName<< " CRC OK: Got 0x" << std::hex << crc << " expected 0x" << crcReal << std::dec <<
			" " << dataSize << " bytes starting at offset " << dataOffset <<
			std::endl ;
}

uint32_t crcOver16k = Crc32::calc(&data[dataOffset], (16*1024) - dataOffset) ;
std::cerr << mDevName<< " CRC over 16K: 0x" << std::hex << crcOver16k << std::dec <<
		std::endl ;

#endif

	// Flag
	mActive = true ;
	if (mFlagSupported)
	{
		uint8_t flag = ByteTransfer::readByte(dataStart, dataEnd) ;
		mActive = (flag > 0) ;
	}

	// Environment
	std::string envStr ;
	while ( !(envStr = ByteTransfer::readString(dataStart, dataEnd)).empty() )
	{
		// only process strings of the form var=value
		std::size_t pos(envStr.find("=")) ;
		if (pos == std::string::npos)
			continue ;

		mEnv[envStr.substr(0, pos)] = envStr.substr(pos+1) ;
	}

	if (isDebug(Loggable::LOG_DEBUG_VERBOSE))
	{
		logDebugVerbose("%s: Environment:", mDevName.c_str());
		for (auto entry : mEnv)
		{
			logDebugVerbose("  '%s' = '%s'", entry.first.c_str(), entry.second.c_str()) ;
		}
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnvDevice::write()
{
	std::vector<uint8_t> data(mEnvSize, 0xff) ;
	auto dataStart(data.begin()) ;
	auto dataEnd(data.end()) ;

	// CRC - write dummy
	ByteTransfer::writeWord(dataStart, dataEnd, 0xffffffff) ;

	// Flag
	if (mFlagSupported)
		ByteTransfer::writeByte(dataStart, dataEnd, (mActive ? 0x01 : 0x00) ) ;

	// Environment
	for (auto entry : mEnv)
	{
		std::string envStr(entry.first + "=" + entry.second) ;
		ByteTransfer::writeString(dataStart, dataEnd, envStr) ;
	}

	// Add extra terminating NULL
	ByteTransfer::writeByte(dataStart, dataEnd, 0x00 ) ;


	// Calculate the CRC
	unsigned dataOffset(NOR_CRC_OFFSET+NOR_CRC_SIZE) ;
	if (mFlagSupported)
		dataOffset += NOR_FLAG_SIZE ;

	unsigned dataSize = mEnvSize - dataOffset ;

	uint32_t crc = Crc32::calc(&data[dataOffset], dataSize) ;

	// CRC - write real value
	dataStart = data.begin() ;
#ifdef IS_BIG_ENDIAN
	ByteTransfer::writeWord(dataStart, dataEnd, crc) ;
#else
	ByteTransfer::writeWordLE(dataStart, dataEnd, crc) ;
#endif

	// Erase flash
	if (!eraseFlash())
		return false ;

	// Write data
	int fd = ::open(mDevName.c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) ;
	if (fd < 0)
	{
		setError("Unable to open device " + mDevName + " " + strError(errno));
		return false ;
	}

	int written = ::write(fd, &data[0], data.size()) ;
	if (written < 0)
	{
		setError("Error writing environment to device " + mDevName + " " + strError(errno));
		return false ;
	}
	if (static_cast<unsigned>(written) < data.size())
	{
		setError("Failed to write complete environment to device " + mDevName);
		return false ;
	}
	::close(fd) ;

//	// debug
//	ByteTransfer::dump(data) ;

	return true ;
}

#ifdef OFF_TARGET
//-------------------------------------------------------------------------------------------------------------
void BootEnvDevice::reset(const std::map<std::string, std::string>& env)
{
	mValid = true ;
	mError.clear() ;

	mActive = false ;
	if (mIndex == 1)
		mActive = true ;

	std::cerr << "[BootEnvDevice:" << mDevName << "] reset() - Active=" << mActive << std::endl ;

	resetVars(env) ;
	write() ;
}

//-------------------------------------------------------------------------------------------------------------
void BootEnvDevice::show()
{
	std::cerr << "[BootEnvDevice:" << mDevName << "] show() Valid=" << mValid << " Active=" << mActive << std::endl ;
	std::cerr << "--contents-------" << std::endl ;
	for (auto entry : mEnv)
	{
		std::cerr << "  " << entry.first << "=" << entry.second << std::endl ;
	}
	std::cerr << "-----------------" << std::endl ;
}
#endif

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void BootEnvDevice::setError(const std::string& error)
{
	logDebugVerbose("%s: ERROR: %s", mDevName.c_str(), error.c_str());

	if (!mError.empty())
		mError += "\n" ;
	mError += error ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnvDevice::eraseFlash()
{
#ifndef OFF_TARGET

	int fd = ::open(mDevName.c_str(), O_RDWR) ;
	if (fd < 0)
	{
		setError("Unable to open device " + mDevName + " " + strError(errno));
		return false ;
	}

    int nblocks;
	if (::ioctl(fd, MEMGETREGIONCOUNT, &nblocks) != 0)
    {
		::close(fd) ;
    	setError("Failed to erase, unable to get region count " + strError(errno)) ;
    	return false ;
    }

	logDebugVerbose("%s: found regioncount of %d", mDevName.c_str(), nblocks) ;

    mtd_info_t meminfo;
    if (::ioctl(fd, MEMGETINFO, &meminfo) != 0)
    {
		::close(fd) ;
    	setError("Failed to erase, unable to get region info " + strError(errno)) ;
    	return false ;
    }

    int nerase = meminfo.size / meminfo.erasesize;

	logDebugVerbose("%s: mtd size=%d erasesize=%d writesize=%d flags=0x%x nerase=%d",
		mDevName.c_str(),
		meminfo.size,
		meminfo.erasesize,
		meminfo.writesize,
		meminfo.flags,
		nerase
	) ;

	int pos = 0;
	for (pos = 0; pos < nerase; pos++)
	{
	    erase_info_t erase;
	    erase.start = pos * meminfo.erasesize;
	    erase.length = meminfo.erasesize;

/** The xilinx linux version of MTD spi-nor.c keeps the device unlocked and then barfs every time you try to unlock it
 * (rather than silently allow it)!
	    if (::ioctl(fd, MEMUNLOCK, &erase) != 0)
	    {
	    	if (errno != EOPNOTSUPP)
	    	{
	    		::close(fd) ;
	        	setError("Failed to erase, unlock failed") ;
	        	return false ;
	    	}
	    }
 */

	    if (::ioctl(fd, MEMERASE, &erase) != 0)
	    {
    		::close(fd) ;
        	setError("Erase failed") ;
        	return false ;
	    }
	}
	::close(fd) ;
#endif
	return true ;
}

