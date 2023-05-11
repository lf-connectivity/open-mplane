/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      I2cBusMgr.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Path.h"
#include "stringfunc.hpp"

#include "BusSettings.hpp"
#include "BusLock.hpp"

#include "I2cBusMgr.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
I2cBusMgr::I2cBusMgr() :
	mI2cBus(),
	mBusLock(),
	mBusSetting(),
	mNames()
{
}

//-------------------------------------------------------------------------------------------------------------
I2cBusMgr::~I2cBusMgr()
{
}

//-------------------------------------------------------------------------------------------------------------
void I2cBusMgr::registerNames(const std::map<std::string, std::string> &namesMap)
{
	mNames.insert(namesMap.begin(), namesMap.end()) ;
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::string> I2cBusMgr::getRegisteredNames() const
{
	return mNames ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<II2cBus> I2cBusMgr::namedDeviceBus(const std::string &name)
{
	if (mNames.find(name) == mNames.end())
		return std::shared_ptr<II2cBus>() ;

	return deviceBus(mNames[name]) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<II2cBus> I2cBusMgr::deviceBus(const std::string &unifiedDeviceName)
{
	// start by seeing if this device bus is cached
	if (mI2cBus.find(unifiedDeviceName) != mI2cBus.end())
		return mI2cBus[unifiedDeviceName] ;

	// try using all lowercase name
	std::string lower(toLower(unifiedDeviceName)) ;
	if (mI2cBus.find(lower) != mI2cBus.end())
		return mI2cBus[lower] ;

	if (lower[0] != '/')
		return std::shared_ptr<II2cBus>() ;

	// need to create device bus (if possible)

	// extract device name and bus name
	std::size_t pos(lower.find_last_of('/')) ;
	if (pos == std::string::npos)
		return std::shared_ptr<II2cBus>() ;

	std::string busName(lower.substr(0, pos)) ;

	unsigned i2cAddress(stoul(lower.substr(pos+1), nullptr, 0));

	// get top-level bus number
	std::size_t spos(lower.find('/', 1)) ;
	if (spos == std::string::npos)
		return std::shared_ptr<II2cBus>() ;

	unsigned bus(stoul(lower.substr(1, spos-1))) ;
	if (bus >= mBusLock.size())
		return std::shared_ptr<II2cBus>() ;

	// Can now create a new device bus and cache it
	std::shared_ptr<II2cBus> i2c( createBus(busName, i2cAddress, bus, mBusLock[bus], mBusSetting[bus]) ) ;
	mI2cBus[lower] = i2c ;

	return i2c ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<II2cBus> I2cBusMgr::deviceBus(const std::string &unifiedBusName, unsigned i2cAddress)
{
	std::stringstream ss ;
	ss << unifiedBusName << "/0x" << std::hex << std::setw(2) << std::setfill('0') << i2cAddress ;
	return deviceBus(ss.str()) ;
}

//=============================================================================================================
// PROTECTED HOOKS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<II2cBus> I2cBusMgr::createBus(const std::string &unifiedBusName, unsigned i2cAddress, unsigned bus,
		std::shared_ptr<IBusLock> busLock, std::shared_ptr<IBusSettings> busSettings)
{
	return std::shared_ptr<II2cBus>() ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void I2cBusMgr::createBuses(unsigned numBusses)
{
	while( numBusses >= mBusLock.size() )
	{
		mBusLock.push_back( std::make_shared<BusLock>() ) ;
		mBusSetting.push_back( std::make_shared<BusSettings>() ) ;
	}
}
