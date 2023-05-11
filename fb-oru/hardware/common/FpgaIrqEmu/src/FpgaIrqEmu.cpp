/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaIrqEmu.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <exception>

#include "FpgaIrqDevice.h"
#include "FpgaIrqEmu.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const unsigned NUM_DEVICES{16} ;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaIrqEmu> IFpgaIrqEmu::getInstance()
{
	static std::shared_ptr<IFpgaIrqEmu> instance(std::make_shared<FpgaIrqEmu>()) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaIrqEmu::FpgaIrqEmu() :
	mDevices(),
	mDeviceMap()
{
	for (unsigned bitNum=0; bitNum < NUM_DEVICES; ++bitNum)
	{
		mDevices.push_back(std::make_shared<FpgaIrqDevice>(bitNum)) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
FpgaIrqEmu::~FpgaIrqEmu()
{
}

//-------------------------------------------------------------------------------------------------------------
int FpgaIrqEmu::open(const char* pathname, int flags)
{
	// Expect name of the form "/dev/fpga-irq.0"
	std::string name(pathname) ;
	std::size_t pos(name.find_last_of('.')) ;

	if (pos == std::string::npos)
		// invalid name
		return -1 ;

	// Get bit number - throws exception of failure
	unsigned bitNum(std::stoul(name.substr(pos+1))) ;
	if (bitNum >= mDevices.size())
		return -1 ;

	// Pass open down to appropriate device
	int fd = mDevices[bitNum]->open(pathname, flags) ;
	if (fd < 0)
		return fd ;

	// Track this fd
	mDeviceMap[fd] = mDevices[bitNum] ;

	return fd ;
}

//-------------------------------------------------------------------------------------------------------------
int FpgaIrqEmu::close(int fd)
{
	// See if this fd is valid
	auto entry(mDeviceMap.find(fd)) ;
	if (entry == mDeviceMap.end())
		return -1 ;

	// remove this entry
	std::shared_ptr<FpgaIrqDevice> dev(entry->second) ;
	mDeviceMap.erase(entry) ;

	// pass close to device
	return dev->close(fd) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaIrqEmu::raiseIrq(unsigned irqBit)
{
	if (irqBit >= mDevices.size())
		return false ;

	mDevices[irqBit]->raiseIrq() ;
	return true ;
}
