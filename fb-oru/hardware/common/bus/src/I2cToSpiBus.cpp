/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      I2cToSpiBus.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>
#include "ByteTransfer.hpp"

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <unistd.h>

#include "BusLock.hpp"
#include "I2cToSpiBus.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
I2cToSpiBus::I2cToSpiBus(std::shared_ptr<II2cBus> i2c, std::shared_ptr<IBusReadonlySettings> busSettings, unsigned spiSelect) :
	SpiBus("I2c->SPI", i2c->busName() + " " + i2c->busDetails(), std::make_shared<NullBusLock>(), busSettings),
	mI2c(i2c),
	mOffset(1 << spiSelect)
{
}

//-------------------------------------------------------------------------------------------------------------
I2cToSpiBus::~I2cToSpiBus()
{
}

//=============================================================================================================
// PROTECTED HOOKS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool I2cToSpiBus::doWriteData(const std::vector<uint8_t> &bytes)
{
	// Expects data bytes to be MS byte first
	if (mI2c->writeData(mOffset, bytes))
		return true ;

	return setError(mI2c->error()) ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cToSpiBus::doReadData(std::vector<uint8_t> &bytes, unsigned numBytes)
{
	// Expects data bytes to be MS byte first
	if (mI2c->readData(bytes, numBytes) )
		return true ;

	return setError(mI2c->error()) ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cToSpiBus::doWriteByte(uint32_t offset, uint8_t byte)
{
	std::vector<uint8_t> bytes ;
	bytes.push_back(byte) ;
	return doWriteData(writeBytes(offset, bytes)) ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cToSpiBus::doWriteShort(uint32_t offset, uint16_t shortVal)
{
	std::vector<uint8_t> bytes ;

	if (settings()->isBigEndian())
	{
		// MS first
		bytes.push_back( ((uint8_t)(shortVal >> 8) & 0xff) ) ;
		bytes.push_back( ((uint8_t)(shortVal) & 0xff) ) ;
	}
	else
	{
		// LS first
		bytes.push_back( ((uint8_t)(shortVal) & 0xff) ) ;
		bytes.push_back( ((uint8_t)(shortVal >> 8) & 0xff) ) ;
	}

	return doWriteData(writeBytes(offset, bytes)) ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cToSpiBus::doWriteWord(uint32_t offset, uint32_t word)
{
	std::vector<uint8_t> bytes ;

	if (settings()->isBigEndian())
	{
		// MS first
		bytes.push_back( ((uint8_t)(word >> 24) & 0xff) ) ;
		bytes.push_back( ((uint8_t)(word >> 16) & 0xff) ) ;
		bytes.push_back( ((uint8_t)(word >> 8) & 0xff) ) ;
		bytes.push_back( ((uint8_t)(word) & 0xff) ) ;
	}
	else
	{
		// LS first
		bytes.push_back( ((uint8_t)(word) & 0xff) ) ;
		bytes.push_back( ((uint8_t)(word >> 8) & 0xff) ) ;
		bytes.push_back( ((uint8_t)(word >> 16) & 0xff) ) ;
		bytes.push_back( ((uint8_t)(word >> 24) & 0xff) ) ;
	}

	return doWriteData(writeBytes(offset, bytes)) ;
}


//-------------------------------------------------------------------------------------------------------------
bool I2cToSpiBus::doReadByte(uint32_t offset, uint8_t &byte)
{
	// send the read command and enough dummy bytes (value = 0) to clock in the data output
	// NOTE: Don't need any size because we know the shift register size
	if (!doWriteData(readBytes(offset)))
		return false ;

	std::vector<uint8_t> bytes ;
	if (!doReadData(bytes, 1))
		return false ;

	// get the LSB
	byte = bytes[bytes.size()-1] ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cToSpiBus::doReadShort(uint32_t offset, uint16_t &shortVal)
{
	// send the read command and enough dummy bytes (value = 0) to clock in the data output
	// NOTE: Don't need any size because we know the shift register size
	std::vector<uint8_t> dummyBytes(readBytes(offset)) ;

	if (!doWriteData(dummyBytes))
		return false ;

	// nasty, hardcoded delay - but we seem to need it!
	usleep(10000) ;

	std::vector<uint8_t> bytes ;
	if (!doReadData(bytes, dummyBytes.size()))
		return false ;

	if (settings()->isBigEndian())
	{
		// get the LS 2 bytes
		shortVal = ((uint16_t)bytes[bytes.size()-2] << 8) | (uint16_t)bytes[bytes.size()-1] ;
	}
	else
	{
		// Get the last 2 bytes (first bytes are command/control)
		shortVal = ((uint16_t)bytes[bytes.size()-1] << 8) | (uint16_t)bytes[bytes.size()-2] ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cToSpiBus::doReadWord(uint32_t offset, uint32_t &word)
{
	// send the read command and enough dummy bytes (value = 0) to clock in the data output
	// NOTE: Don't need any size because we know the shift register size
	std::vector<uint8_t> dummyBytes(readBytes(offset)) ;

	if (!doWriteData(dummyBytes))
		return false ;

	// nasty, hardcoded delay - but we seem to need it!
	usleep(10000) ;

	std::vector<uint8_t> bytes ;
	if (!doReadData(bytes, dummyBytes.size()))
		return false ;

	if (settings()->isBigEndian())
	{
		// get the LS 4 bytes
		word =  ((uint32_t)bytes[bytes.size()-4] << 24) |
				((uint32_t)bytes[bytes.size()-3] << 16) |
				((uint32_t)bytes[bytes.size()-2] << 8) |
				 (uint32_t)bytes[bytes.size()-1] ;
	}
	else
	{
		// Get the last 4 bytes (first bytes are command/control)
		word =  ((uint32_t)bytes[bytes.size()-1] << 24) |
				((uint32_t)bytes[bytes.size()-2] << 16) |
				((uint32_t)bytes[bytes.size()-3] << 8) |
				 (uint32_t)bytes[bytes.size()-4] ;
	}
	return true ;
}
