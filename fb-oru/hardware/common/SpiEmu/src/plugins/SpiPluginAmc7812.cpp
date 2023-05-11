/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SpiPluginAmc7812.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <iomanip>

#include "plugins/Amc7812/Amc7812Temperature.h"
#include "plugins/Amc7812/Amc7812Voltage.h"
#include "plugins/Amc7812/Amc7812Adc.h"
#include "plugins/Amc7812/Amc7812PowerDetect.h"
#include "plugins/SpiPluginAmc7812.h"

using namespace Mplane;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISpiPlugin> SpiPluginAmc7812::factory(unsigned bus, unsigned devId, unsigned devNum, unsigned shift)
{
	return std::make_shared<SpiPluginAmc7812>(bus, devId, devNum, shift) ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SpiPluginAmc7812::SpiPluginAmc7812(unsigned bus, unsigned devId, unsigned devNum, unsigned shift) :
	SpiPluginBase(std::string(
			"SPI" + std::to_string(bus) + "-Amc7812-" + std::to_string(devId) + "-" + std::to_string(devNum)
		), bus, devId, devNum, shift),
	mOp(Amc7812Op::WRITE),
	mAddress(0),
	mHandlers()
{
	// Create handlers
	std::string prefix(getName() + ":") ;

	// Temperature
	//    LT = 0x00, // Internal sensor
	//    D1 = 0x01, // External sensor 1. Board specific.
	//    D2 = 0x02  // External sensor 2. Board specific.
	mHandlers[0x00] = Amc7812Temperature::factory(prefix + "LT", 0.0, 128.0, 23.0, 40.0, 0.1) ;
	mHandlers[0x01] = Amc7812Temperature::factory(prefix + "D1", 0.0, 128.0, 23.0, 40.0, 0.1) ;
	mHandlers[0x02] = Amc7812Temperature::factory(prefix + "D2", 0.0, 128.0, 38.9, 41.0, 0.1) ;

	// ADC-0 RF power detector
	// Values here work out to give approx. 35dBm output
//	mHandlers[0x23] = Amc7812Adc::factory(prefix + "ADC-0", 0.0, 1.0, 1818.0, 1860.0, 0.01) ;
//	// Values here work out to give approx. 24dBm output
//	mHandlers[0x23] = Amc7812Adc::factory(prefix + "ADC-0", 0.0, 1.0, 2222.0, 2250.0, 0.01) ;
	mHandlers[0x23] = Amc7812PowerDetect::factory(prefix + "ADC-0", devNum) ;

	// ADC-1 used for PA presence
	mHandlers[0x24] = Amc7812Adc::factory(prefix + "ADC-1", 0.0, 1.0, 10.0, 11.0, 0.1) ;

	// PA Temperature - ADC-2 .. ADC-5
	float paOffset(4095.0 / 5.0 * 1.8605) ;
	float paFactor(4095.0 / 5.0 * -0.01177) ;
	mHandlers[0x25] = Amc7812Temperature::factory(prefix + "ADC-2", paOffset, paFactor, 23.0, 40.0, 0.1) ;
	mHandlers[0x26] = Amc7812Temperature::factory(prefix + "ADC-3", paOffset, paFactor, 23.0, 40.0, 0.1) ;
	mHandlers[0x27] = Amc7812Temperature::factory(prefix + "ADC-4", paOffset, paFactor, 23.0, 40.0, 0.1) ;
	mHandlers[0x28] = Amc7812Temperature::factory(prefix + "ADC-5", paOffset, paFactor, 23.0, 40.0, 0.1) ;

	// Voltage
	mHandlers[0x2f] = Amc7812Voltage::factory(prefix + "ADC-12", 0.0, 1.0/0.002052, 4.80, 5.20, 0.05) ;
}

//-------------------------------------------------------------------------------------------------------------
SpiPluginAmc7812::~SpiPluginAmc7812()
{
}

//-------------------------------------------------------------------------------------------------------------
bool SpiPluginAmc7812::handleData(unsigned select, unsigned writeData, unsigned writeNumBits, unsigned& readData, unsigned readNumBits)
{
	if (writeNumBits == 0)
		return false ;

	// Get the top 8 bits of the write data - this is the read/write bit + address
	++writeNumBits ;
	unsigned writeTop( (writeData >> (writeNumBits-8)) & 0xff ) ;
	unsigned wdata = writeData & ((1<<(writeNumBits-8))-1) ;

//	unsigned devNum(select & 0x7) ;

	unsigned address(writeTop & 0x7f) ;

	// Get the operation
	std::string phase ;
#if 0
	if (write)
	{
		// Single phase write
		mOp = Amc7812Op::WRITE ;
		mAddress = address ;
	}
	else
	{
		// 2 phase read - first phase sets address, second reads data
		if (mOp == Amc7812Op::WRITE)
		{
			mOp = Amc7812Op::READ1 ;
			mAddress = address ;
		}
		else
		{
			mOp = Amc7812Op::READ2 ;

			// Use address from previous cycle
			std::swap(address, mAddress) ;
		}
	}
#endif

	// The SW currently clears the MSB bit (RnW bit) on phase 2 - which is wrong!
	if (mOp == Amc7812Op::READ1)
	{
		mOp = Amc7812Op::READ2 ;
		phase="READ2" ;

		// Use address from previous cycle
		std::swap(address, mAddress) ;
	}
	else
	{
		mAddress = address ;

	    bool write( (writeTop & 0x80) == 0x00) ;

		if (write)
		{
			// Single phase write
			mOp = Amc7812Op::WRITE ;
			phase="WRITE" ;
		}
		else
		{
			mOp = Amc7812Op::READ1 ;
			phase="READ1" ;
		}
	}

	if (mOp != Amc7812Op::WRITE)
	{
		if (readNumBits == 0)
			return false ;
		++readNumBits ;
	}

	auto entry(mHandlers.find(address)) ;
	if (entry == mHandlers.end())
	{
		logDebugVerbose("[SPI%u:Amc7812-%u:UNKNOWN] ID=%u Phase=%s wdata=0x%04x (num bits=%u) rdata=0x%04x (num bits=%u)",
			getBus(), getDevNum(),
			select, phase.c_str(),
			writeData, writeNumBits,
			readData, readNumBits) ;

		return true ;
	}

	std::shared_ptr<IAmc7812Handler> handler(entry->second) ;

	if (mOp == Amc7812Op::WRITE)
		return handler->writeData(address, wdata) ;

	if (mOp == Amc7812Op::READ2)
		return handler->readData(address, readData) ;

	return true ;
}
