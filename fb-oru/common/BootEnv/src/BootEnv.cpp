/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BootEnv.cpp
 * \brief     Manages access to the u-boot environment
 *
 *
 * \details   The u-boot environment is stored in 2 NOR flash partitions (access in Linux as 2 devices). One is marked
 *            as the active bank, the other the inactive bank. Every time a change is made, it is written to the inactive
 *            bank and the banks swapped
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <fstream>

#include "stringfunc.hpp"
#include "BootEnvDevice.h"
#include "BootEnv.h"

using namespace Mplane;

//=============================================================================================================
// MACROS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
//#define TEST_MTD_PARSE

#ifdef TEST_MTD_PARSE
#else
#ifdef OFF_TARGET
#define SIM_MTD
#endif
#endif

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
class BootEnvInst : public BootEnv
{
public:
	// Default instance (used by radios) limits the environment to 16K
	BootEnvInst() : BootEnv(16 * 1024) {}
	virtual ~BootEnvInst() {}
};

std::shared_ptr<BootEnv> BootEnv::getInstance()
{
	static std::shared_ptr<BootEnv> instance(std::make_shared<BootEnvInst>()) ;
	return instance ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
BootEnv::~BootEnv()
{
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnv::isValid() const
{
	Mutex::Lock lock(mMutex) ;

	if (!checkState())
		return false ;

	return mActiveEnv->isValid() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string BootEnv::getError()
{
	Mutex::Lock lock(mMutex) ;

	std::string error("") ;
	std::swap(error, mError) ;
	return error ;
}


//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::string> BootEnv::getVars() const
{
	Mutex::Lock lock(mMutex) ;

	if (!checkState())
		return std::map<std::string, std::string>() ;

	return mActiveEnv->getVars() ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnv::isVar(const std::string& var) const
{
	Mutex::Lock lock(mMutex) ;

	if (!checkState())
		return false ;

	return mActiveEnv->isVar(var) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string BootEnv::getVar(const std::string& var) const
{
	Mutex::Lock lock(mMutex) ;

	if (!checkState())
		return "" ;

	return mActiveEnv->getVar(var) ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnv::setVar(const std::string& var, const std::string& value)
{
	return setVar(std::map<std::string, std::string>{{var, value}}) ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnv::setVar(const std::map<std::string, std::string>& vars)
{
	Mutex::Lock lock(mMutex) ;

	if (!checkState())
		return false ;

	// get active environment
	std::map<std::string, std::string> env(mActiveEnv->getVars()) ;

	// change specified vars
	for (auto varVal : vars)
	{
		env[varVal.first] = varVal.second ;
	}

	// write new environment to inactive bank and swap banks
	return writeEnv(env) ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnv::deleteVar(const std::string& var)
{
	return deleteVar(std::vector<std::string>{var}) ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnv::deleteVar(const std::vector<std::string>& vars)
{
	Mutex::Lock lock(mMutex) ;

	if (!checkState())
		return false ;

	// get active environment
	std::map<std::string, std::string> env(mActiveEnv->getVars()) ;

	// delete specified vars
	for (auto var : vars)
	{
		env.erase(var) ;
	}

	// write new environment to inactive bank and swap banks
	return writeEnv(env) ;

}

//-------------------------------------------------------------------------------------------------------------
bool BootEnv::resetVars(const std::map<std::string, std::string>& vars)
{
	Mutex::Lock lock(mMutex) ;

	if (!checkState())
		return false ;

	return writeEnv(vars) ;
}



//-------------------------------------------------------------------------------------------------------------
unsigned BootEnv::getIndex() const
{
	Mutex::Lock lock(mMutex) ;

	if (!checkState())
		return false ;

	return mActiveEnv->getIndex() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string BootEnv::getDeviceName() const
{
	Mutex::Lock lock(mMutex) ;

	if (!checkState())
		return "" ;

	return mActiveEnv->getDeviceName() ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnv::isActive() const
{
	Mutex::Lock lock(mMutex) ;

	if (!checkState())
		return false ;

	return mActiveEnv->isActive() ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnv::read()
{
	Mutex::Lock lock(mMutex) ;

	// For this "manager" object, do a complete refresh
	return init() ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnv::write()
{
	// For this "manager" object, does nothing
	return true ;
}


#ifdef OFF_TARGET
//=============================================================================================================
// TEST INTERFACE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void BootEnv::reset(const std::map<std::string, std::string>& env)
{
	Mutex::Lock lock(mMutex) ;

	std::map<std::string, std::string> vars(env) ;
	if (vars.empty())
	{
		vars["bootargs"] = "root=/dev/ram rw console=ttyS0,115200";
		vars["boot1"] = "bootm 0xff800000 - 0xfff90000";
		vars["boot2"] = "bootm 0xffbc0000 - 0xfff80000";
		vars["bootcmd"] = "run boot1";
		vars["activeos"] = "1";
		vars["bootdelay"] = "5";
		vars["baudrate"] = "115200";
		vars["loads_echo"] = "";
//		vars["ipaddr"] = "172.16.3.224";
//		vars["serverip"] = "192.168.10.1";
		vars["preboot"] = "echo Axis Ltd";
		vars["hostname"] = "art-016";
		vars["ateid"] = "ate-swin-2620";
		vars["ethact"] = "ppc_4xx_eth0";
		vars["ethaddr"] = "00:24:24:25:17:e7";
		vars["ethaddr1"] = "00:24:24:25:17:e0";
		vars["ethaddr2"] = "00:24:24:25:17:e1";
		vars["ethaddr3"] = "00:24:24:25:17:e2";
		vars["ethaddr4"] = "00:24:24:25:17:e3";
		vars["ethaddr5"] = "00:24:24:25:17:e4";
		vars["ethaddr6"] = "00:24:24:25:17:e5";
		vars["ethaddr7"] = "00:24:24:25:17:e6";
		vars["productCode"] = "310-00112-001-FTU-HW-Phoenix";
		vars["linerate"] = "4";
		vars["radioLowFreq"] = "700000";
		vars["radioHighFreq"] = "2700000";
		vars["force"] = "1";
		vars["booturl"] = "";
	}

	// reset the data
	for (auto dev : mEnvDevices)
	{
		std::dynamic_pointer_cast<BootEnvDevice>(dev)->reset(vars) ;
	}

	// re-load
	init() ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::shared_ptr<IBootEnvDevice>> BootEnv::getDevices() const
{
	Mutex::Lock lock(mMutex) ;

	return mEnvDevices ;
}

#endif

//=============================================================================================================
// PROTECTED CONSTRUCTOR
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
BootEnv::BootEnv(unsigned maxEnvSize, bool flagSupported, bool deferInit) :
	Loggable("BootEnv", "BootEnv"),
	mFlagSupported(flagSupported),
	mMaxEnvSize(maxEnvSize),
	mMutex(),
	mEnvDevices(),
	mActiveEnv(),
	mInactiveEnv(),
	mError(),
	mMinNumBanks(2)
{
	Mutex::Lock lock(mMutex) ;

	// if we are NOT delaying initialisation (i.e. derived object wants to init later) then
	// go ahead and init now
	if (!deferInit)
		init() ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnv::init()
{
	// clear
	mEnvDevices.clear() ;
	mActiveEnv.reset() ;
	mInactiveEnv.reset() ;
	mError.clear() ;

	// Now populate data
	std::map<unsigned, BootEnv::PartitionInfo> devices(getDeviceList()) ;
	for (auto entry : devices)
	{
		std::shared_ptr<IBootEnvDevice> envDevice(
			std::make_shared<BootEnvDevice>(entry.first, entry.second.name, mFlagSupported, entry.second.size)
		) ;
		if (!envDevice->isValid())
			continue ;

		// save valid device
		mEnvDevices.push_back(envDevice) ;

		// find the active device
		if (envDevice->isActive())
		{
			if (!mActiveEnv)
			{
				mActiveEnv = envDevice ;
				continue ;
			}

			// Already found an active device, so deactivate this one
			envDevice->setActiveFlag(false) ;
			envDevice->write() ;
		}

		// Keep track of any inactive
		if (!envDevice->isActive())
			mInactiveEnv = envDevice ;

	}

	// Must have at least N valid devices
	if (mEnvDevices.size() < mMinNumBanks)
	{
		mError = "Found only " + std::to_string(mEnvDevices.size()) + " valid devices (need at least " + std::to_string(mMinNumBanks) + ")" ;
		return false ;
	}

	// if none active then choose first
	if (mActiveEnv)
		return false ;

	// Select the first to be active
	mActiveEnv = mEnvDevices[0] ;
	mActiveEnv->setActiveFlag(true) ;
	mActiveEnv->write() ;

	return true ;
}


//=============================================================================================================
// PROTECTED UTILS
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
std::map<unsigned, BootEnv::PartitionInfo> BootEnv::getDeviceList()
{
	std::map<unsigned, BootEnv::PartitionInfo> devices ;

#ifdef SIM_MTD
	devices = getSimDeviceList() ;
#else
    /*
     * Read /proc/mtd, which should be of the form:
     *
     * dev:    size   erasesize  name
     * mtd0: 00790000 00010000 "kernel"
     * mtd1: 00010000 00010000 "dtb"
     * mtd2: 00010000 00010000 "ubenv2"
     * mtd3: 00010000 00010000 "ubenv1"
     * mtd4: 00040000 00010000 "u-boot"
     * mtd5: 02000000 00004000 "NAND 32MiB 3,3V 8-bit"
     * mtd6: 02000000 00004000 "filesystem"
     */

#ifdef TEST_MTD_PARSE
	std::vector<std::string> exampleMtd{
	     "dev:    size   erasesize  name",
	     "mtd0: 00790000 00010000 \"kernel\"",
	     "mtd1: 00010000 00010000 \"dtb\"",
	     "mtd2: 00010000 00008000 \"ubenv2\"",
	     "mtd3: 00010000 00004000 \"ubenv1\"",
	     "mtd4: 00040000 00010000 \"u-boot\"",
	     "mtd5: 02000000 00004000 \"NAND 32MiB 3,3V 8-bit\"",
	     "mtd6: 02000000 00004000 \"filesystem\"",

	} ;

	for (auto linebuff : exampleMtd)
	{
#else
	std::string linebuff ;
	std::ifstream infile;
	infile.open("/proc/mtd");
	if (!infile.is_open())
	{
		mError = "Unable to read /proc/mtd" ;
		return std::map<unsigned, BootEnv::PartitionInfo>() ;
	}

	while(infile.good())
	{
		// get the line text string
		std::getline(infile, linebuff);

#endif
		// process the line
		unsigned index ;
		if (!processDeviceLine(linebuff, index))
			continue ;

		// get the device name
		std::size_t pos(linebuff.find(":")) ;
		if (pos == std::string::npos)
			continue ;
		std::string devName("/dev/" + linebuff.substr(0, pos)) ;

		std::size_t sizepos(linebuff.find_first_not_of(" ", pos+1)) ;
		if (sizepos == std::string::npos)
			continue ;
		unsigned size( (unsigned)strtoul(linebuff.substr(sizepos).c_str(), nullptr, 16) ) ;

		std::size_t sizeendpos(linebuff.find_first_of(" ", sizepos)) ;
		if (sizeendpos == std::string::npos)
			continue ;

		std::size_t erasepos(linebuff.find_first_not_of(" ", sizeendpos+1)) ;
		if (erasepos == std::string::npos)
			continue ;
		unsigned eraseSize( (unsigned)strtoul(linebuff.substr(erasepos).c_str(), nullptr, 16) ) ;

		// If max size is set then limit size to this maximum
		if ( (mMaxEnvSize > 0 ) && (size > mMaxEnvSize) )
			size = mMaxEnvSize ;

		devices[index] = { devName, size, eraseSize } ;

		logDebugVerbose("Found ubenv%d device %s CRC size %u Erase size %u", index, devName.c_str(), size, eraseSize) ;
	}
#endif

	return devices ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnv::checkState() const
{
	// Must have at least N valid devices
	if (mEnvDevices.size() < mMinNumBanks)
	{
		mError = "Found only " +
				std::to_string(mEnvDevices.size()) +
				" valid devices (need at least " +
				std::to_string(mMinNumBanks) +
				")";
//		std::cerr << "BootEnv::checkState error: " << mError << std::endl ;
		return false ;
	}

	if (!mActiveEnv)
	{
		mError = "No active environment";
//		std::cerr << "BootEnv::checkState error: " << mError << std::endl ;
		return false ;
	}

	if (mMinNumBanks < 2)
		return true ;

	if (!mInactiveEnv)
	{
		mError = "No inactive environment";
//		std::cerr << "BootEnv::checkState error: " << mError << std::endl ;
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnv::writeInactive(const std::map<std::string, std::string>& newEnv)
{
//	std::cerr << "BootEnv::writeInactive" << std::endl ;

	if (!checkState())
		return false ;

	if (!mActiveEnv->setActiveFlag(false))
	{
//		std::cerr << "BootEnv::writeInactive - error setting active flag (active->inactive)" << std::endl ;
		mError = mActiveEnv->getError() ;
		return false ;
	}
	if (!mActiveEnv->write())
	{
//		std::cerr << "BootEnv::writeInactive - error writing" << std::endl ;
		mError = mActiveEnv->getError() ;
		return false ;
	}

	if (mMinNumBanks < 2)
		return true ;

	if (!mInactiveEnv->setActiveFlag(true))
	{
//		std::cerr << "BootEnv::writeInactive - error setting active flag (inactive->active)" << std::endl ;
		mError = mInactiveEnv->getError() ;
		return false ;
	}
	if (!mInactiveEnv->resetVars(newEnv))
	{
//		std::cerr << "BootEnv::writeInactive - error resetting vars" << std::endl ;
		mError = mInactiveEnv->getError() ;
		return false ;
	}
	if (!mInactiveEnv->write())
	{
//		std::cerr << "BootEnv::writeInactive - error writing vars to previous inactive bank" << std::endl ;
		mError = mInactiveEnv->getError() ;
		return false ;
	}

	std::swap(mActiveEnv, mInactiveEnv) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnv::writeActive(const std::map<std::string, std::string>& newEnv)
{
	if (!checkState())
		return false ;

	if (!mActiveEnv->resetVars(newEnv))
	{
		mError = mActiveEnv->getError() ;
		return false ;
	}
	if (!mActiveEnv->write())
	{
		mError = mActiveEnv->getError() ;
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void BootEnv::setMinBanks(unsigned numBanks)
{
	if (numBanks < 1)
		return ;
	mMinNumBanks = numBanks ;
}


//=============================================================================================================
// PROTECTED HOOKS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool BootEnv::processDeviceLine(const std::string& line, unsigned & index)
{
    /*
     * Default action is to find lines like ubenvXX
     *
     * dev:    size   erasesize  name
     * mtd0: 00790000 00010000 "kernel"
     * mtd1: 00010000 00010000 "dtb"
     * mtd2: 00010000 00010000 "ubenv2"
     * mtd3: 00010000 00010000 "ubenv1"
     * mtd4: 00040000 00010000 "u-boot"
     * mtd5: 02000000 00004000 "NAND 32MiB 3,3V 8-bit"
     * mtd6: 02000000 00004000 "filesystem"
     */

	// Simply look for any string with "ubenvXX" and get the index
	std::size_t spos(line.find("\"ubenv")) ;
	if (spos == std::string::npos)
		return false ;
	bool ok(true) ;
	unsigned ubenv(extractUnsigned(line, ok, spos)) ;
	if (!ok || (ubenv == 0))
		return false ;

	index = ubenv ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootEnv::writeEnv(const std::map<std::string, std::string>& newEnv)
{
	// Default behaviour is to write to the inactive bank and switch
	return writeInactive(newEnv) ;
}

#ifdef OFF_TARGET
//-------------------------------------------------------------------------------------------------------------
std::map<unsigned, BootEnv::PartitionInfo> BootEnv::getSimDeviceList()
{
	std::map<unsigned, BootEnv::PartitionInfo> devices ;
	devices[1] = { "/dev/mtd5", 0x10000, 0x10000 } ;
	devices[2] = { "/dev/mtd4", 0x10000, 0x10000 } ;
	return devices ;
}
#endif
