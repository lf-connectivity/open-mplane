/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SpiPluginAd9122.cpp
 * \brief     AD9122
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "SpiPluginAd9122.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const unsigned REG_FIFO_LEVEL{0x19} ;

//=============================================================================================================
// FACTORY
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISpiPlugin> SpiPluginAd9122::factory(unsigned bus, unsigned devId, unsigned devNum, unsigned shift)
{
	return std::make_shared<SpiPluginAd9122>(bus, devId, devNum, shift) ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SpiPluginAd9122::SpiPluginAd9122(unsigned bus, unsigned devId, unsigned devNum, unsigned shift) :
	SpiPluginBase(std::string(
			"SPI" + std::to_string(bus) + "-Ad9122-" + std::to_string(devId) + "-" + std::to_string(devNum)
		), bus, devId, devNum, shift),
	mRegs(128, 0)
{
}

//-------------------------------------------------------------------------------------------------------------
SpiPluginAd9122::~SpiPluginAd9122()
{
}

//-------------------------------------------------------------------------------------------------------------
bool SpiPluginAd9122::handleData(unsigned select, unsigned writeData,
		unsigned writeNumBits, unsigned & readData, unsigned readNumBits)
{
	logDebugNormal("[SPI%u:Ad9122-%u] ID=%u wdata=0x%04x (num bits=%u) rdata=0x%04x (num bits=%u)",
		getBus(), getDevNum(),
		select, writeData, writeNumBits,
		readData, readNumBits
	) ;

	if (writeNumBits == 0)
		return false ;

	// Get the top 8 bits of the write data - this is the read/write bit + address
	++writeNumBits ;
	unsigned writeTop( (writeData >> (writeNumBits-8)) & 0xff ) ;
	unsigned wdata = writeData & ((1<<(writeNumBits-8))-1) ;

//	unsigned devNum(select & 0x7) ;
	bool write( (writeTop & 0x80) == 0x00) ;
	unsigned address(writeTop & 0x7f) ;

	// error check
	if (address >= mRegs.size())
	{
		eventError("[SPI%u:Ad9122-%u] ID=%u Phase=%s wdata=0x%04x (num bits=%u) rdata=0x%04x (num bits=%u) : Invalid register read",
				getBus(), getDevNum(),
				select, (write ? "WRITE" : "READ"),
				writeData, writeNumBits,
				readData, readNumBits) ;
		return false ;
	}

	// WRITE
	if (write)
	{
		mRegs[address] = static_cast<UINT8>(wdata & 0xff) ;
		return true ;
	}

	// Handle special regs
	if (address == REG_FIFO_LEVEL)
	{
		// Ramp up fifo level every time we read it - used for debug
		++mRegs[address] ;
	}

	// READ
	if (readNumBits == 0)
		return false ;
	++readNumBits ;

	readData = static_cast<unsigned>(mRegs[address]) ;

	// Simulate the AD9122 returning the control byte
	readData |= (writeTop << 8) ;

	logDebugNormal("[SPI%u:Ad9122-%u] ID=%u READ Reg=0x%02x Data=0x%08x",
		getBus(), getDevNum(),
		select, address,
		readData
	) ;

	return true ;
}
