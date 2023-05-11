/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SpiBusEmu.cpp
 * \brief     SPI bus emulator
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "SpiBusEmu.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

// Timeout = 5ms, so emulate less than this
static const unsigned SPI_TIME_MS{1} ;

static const unsigned SPI_BASE{0x00200} ;
static const unsigned SPI_OFFSET{0x100} ;
static const unsigned SPI_SELECT{0x2} ;


//=============================================================================================================
// LOCAL
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
namespace {

	static unsigned calcSelect(unsigned devId, unsigned devNum, unsigned shift)
	{
		return (devId << shift) + devNum ;
	}
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SpiBusEmu::SpiBusEmu(unsigned index) :
	TaskEvent(Task::PRIORITY_MEDIUM, Task::MEDIUM_STACK, "SpiBusEmu" + std::to_string(index), "SpiEmu"),
	mIndex(index),
	mPrefix("spi" + std::to_string(mIndex)),
	mEmuMutex(),
	mFpga(OffTargetFPGA::getInstance()),
	mStatusField("alarmStatusSpi" + std::to_string(mIndex) + "Done"),
	mSelect(0),
	mPlugins()
{
//	std::cerr << "SpiBusEmu @ " << this << std::endl ;

	unsigned spiBase(SPI_BASE + mIndex*SPI_OFFSET) ;

	// register ourself to handle the memory locations
	mFpga->registerHandler(spiBase+SPI_SELECT, spiBase+SPI_SELECT,
		[this](const UINT32 address, const UINT16 value, const UINT16 mask)->UINT16{
			return writeSelectHandler(address, value, mask) ;
		},
		[this](const UINT32 address, const UINT16 mask)->UINT16{
			return readSelectHandler(address, mask) ;
		}
	) ;
}

//-------------------------------------------------------------------------------------------------------------
SpiBusEmu::~SpiBusEmu()
{
}

//-------------------------------------------------------------------------------------------------------------
bool SpiBusEmu::registerDevice(std::shared_ptr<ISpiPlugin> plugin)
{
	unsigned select(calcSelect(plugin->getDevId(), plugin->getDevNum(), plugin->getShift())) ;
	auto entry(mPlugins.find(select)) ;
	if (entry != mPlugins.end())
		return false ;

	mPlugins[select] = plugin ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool SpiBusEmu::unregisterDevice(unsigned devId, unsigned devNum, unsigned shift)
{
	unsigned select(calcSelect(devId, devNum, shift)) ;
	auto entry(mPlugins.find(select)) ;
	if (entry == mPlugins.end())
		return false ;

	mPlugins.erase(entry) ;
	return true ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool SpiBusEmu::runEvent()
{
//	printf("[SpiBusEmu%u] EVENT \n", mIndex) ;


	// Get all the parameters
	unsigned select(0) ;
	unsigned keep(0) ;
	unsigned writeLen(0) ;
	unsigned readLen(0) ;
	unsigned readData(0) ;
	unsigned writeData(0) ;

	{
		Mutex::Lock lock(mEmuMutex) ;
		select = ( mSelect ) ;

		// Get all the parameters
		keep = ( mFpga->internalReadField(mPrefix + "KeepEnable") ) ;
		writeLen = ( mFpga->internalReadField(mPrefix + "WdataLen") ) ;
		readLen = ( mFpga->internalReadField(mPrefix + "RdataLen") ) ;

		readData = (
			((unsigned)mFpga->internalReadField(mPrefix + "ReadDataHi") << 16) |
			(unsigned)mFpga->internalReadField(mPrefix + "ReadDataLo")
		) ;

		writeData = (
			((unsigned)mFpga->internalReadField(mPrefix + "WriteDataHi") << 16) |
			(unsigned)mFpga->internalReadField(mPrefix + "WriteDataLo")
		) ;
	}

	// Send to plugin if one is registered
	auto entry(mPlugins.find(select)) ;
	if (entry != mPlugins.end())
	{
		// handle
		if ( entry->second->handleData(select, writeData, writeLen, readData, readLen) )
		{
			// Update the read register
			UINT16 hi((readData >> 16) & 0xffff) ;
			UINT16 lo(readData & 0xffff) ;
			mFpga->internalWriteField(mPrefix + "ReadDataHi", hi) ;
			mFpga->internalWriteField(mPrefix + "ReadDataLo", lo) ;
		}
	}
	else
	{
		// Default action
		logDebugVerbose("[SPI%u] UNKNOWN ID=%u keep=%u wlen=%u rlen=%u wdata=0x%04x rdata=0x%04x",
			mIndex, select, keep, writeLen, readLen, writeData, readData) ;
	}
	Task::msSleep(SPI_TIME_MS) ;

	// DONE
	{
		Mutex::Lock lock(mEmuMutex) ;
		logDebugVerbose("[SPI%u] DONE=1", mIndex) ;
		mFpga->internalWriteField(mStatusField, 1) ;
		mFpga->internalWriteField(mPrefix + "CompleteAlarm", 1) ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISpiPlugin> Mplane::SpiBusEmu::getPlugin(const std::string& name) const
{
	for (auto entry : mPlugins)
	{
		if (entry.second->isPlugin(name))
			return entry.second ;
	}
	return std::shared_ptr<ISpiPlugin>() ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISpiPlugin> Mplane::SpiBusEmu::getPlugin(unsigned devId, unsigned devNum, unsigned shift) const
{
	for (auto entry : mPlugins)
	{
		if (entry.second->isPlugin(mIndex, devId, devNum, shift))
			return entry.second ;
	}
	return std::shared_ptr<ISpiPlugin>() ;
}


//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
UINT16 SpiBusEmu::writeSelectHandler(const UINT32 address, const UINT16 value, const UINT16 mask)
{
	{
		Mutex::Lock lock(mEmuMutex) ;

		mSelect &= ~mask ;
		mSelect |= (value & mask) ;

//		printf("[SpiBusEmu%u] WRITE 0x%05x = 0x%04x / 0x%04x (0x%04x)\n",
//				mIndex, address, value, mask, mSelect) ;

		// Clear down DONE bit until we've seen the regs
		logDebugVerbose("[SPI%u] DONE=0", mIndex) ;
		mFpga->internalWriteField(mPrefix + "CompleteAlarm", 0) ;
		mFpga->internalWriteField(mStatusField, 0) ;
	}

	// notify state machine
	event() ;

	return mSelect ;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 SpiBusEmu::readSelectHandler(const UINT32 address, const UINT16 mask)
{
	Mutex::Lock lock(mEmuMutex) ;
	return mSelect & mask ;
}
