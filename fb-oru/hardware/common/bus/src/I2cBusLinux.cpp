/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      I2cBusLinux.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <string.h>
#include <iostream>
#include "ByteTransfer.hpp"

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>

#include <algorithm>

#include "I2cBusLinux.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
// cannot read more than 32 bytes at a time
const unsigned MAX_READ_BUFF(32) ;

//#define READDATABLOCK_EMULATE	1

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
I2cBusLinux::I2cBusLinux(const std::string &devicePath, unsigned i2cAddr, std::shared_ptr<IBusLock> busLock,
		std::shared_ptr<IBusReadonlySettings> busSettings) :
	I2cBus("Linux I2C", devicePath + " addr=" + std::to_string(i2cAddr), i2cAddr, busLock, busSettings),
	mDevicePath(devicePath),
	mFd(-1),
	mSmbWriteByteData(false),
	mSmbReadByteData(false),
	mSmbWriteWordData(false),
	mSmbReadWordData(false),
	mSmbWriteBlockData(false),
	mSmbReadBlockData(false)
{
	mFd = open(mDevicePath.c_str(), O_RDWR) ;
	if (mFd < 0)
		throw std::runtime_error("Unable to open I2C device " + mDevicePath) ;

	if (ioctl(mFd, I2C_SLAVE, i2cAddress()) < 0)
	{
		throw std::runtime_error("Unable to set address for I2C device " + mDevicePath + " " + std::to_string(i2cAddress()) + " Error - " + std::to_string(errno) + "," + strerror(errno) ) ;
	}

	unsigned long funcs ;
	if (ioctl(mFd, I2C_FUNCS, &funcs) < 0)
	{
		throw std::runtime_error("Unable to get functions for I2C device " + mDevicePath) ;
	}

	// process available functions into flags
	mSmbWriteByteData = funcs & I2C_FUNC_SMBUS_WRITE_BYTE_DATA ;
	mSmbReadByteData = funcs & I2C_FUNC_SMBUS_READ_BYTE_DATA ;
	mSmbWriteWordData = funcs & I2C_FUNC_SMBUS_WRITE_WORD_DATA ; // NB: "word" = short
	mSmbReadWordData = funcs & I2C_FUNC_SMBUS_READ_WORD_DATA ; // NB: "word" = short
//	mSmbWriteBlockData = funcs & I2C_FUNC_SMBUS_WRITE_BLOCK_DATA ;
	mSmbWriteBlockData = funcs & I2C_FUNC_SMBUS_WRITE_I2C_BLOCK ;
//	mSmbReadBlockData = funcs & I2C_FUNC_SMBUS_READ_BLOCK_DATA ;
	mSmbReadBlockData = funcs & I2C_FUNC_SMBUS_READ_I2C_BLOCK ;

//std::cerr << devicePath << " FUNCS 0x" << std::hex << funcs << std::dec << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
I2cBusLinux::~I2cBusLinux()
{
	if (mFd >= 0)
		close(mFd) ;
}


//=============================================================================================================
// PROTECTED HOOKS
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
bool I2cBusLinux::doWriteByte(uint32_t offset, uint8_t byte)
{
	if (!mSmbWriteByteData)
		return setError("I2cBusLinux::doWriteByte not supported on this device") ;

	if (mFd < 0)
		return setError("I2c device not open") ;

	if (i2c_smbus_write_byte_data(mFd, (uint8_t)(offset & 0xff), byte) < 0)
		return setError("Error writing byte to I2c device " + std::to_string(errno)) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cBusLinux::doWriteShort(uint32_t offset, uint16_t shortVal)
{
	if (!mSmbWriteWordData)
		return setError("I2cBusLinux::doWriteShort not supported on this device") ;

	if (mFd < 0)
		return setError("I2c device not open") ;

	if (i2c_smbus_write_word_data(mFd, (uint8_t)(offset & 0xff), shortVal) < 0)
		return setError("Error writing short to I2c device " + std::to_string(errno)) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cBusLinux::doReadByte(uint32_t offset, uint8_t &byte)
{
	if (!mSmbReadByteData)
		return setError("I2cBusLinux::doReadByte not supported on this device") ;

	if (mFd < 0)
		return setError("I2c device not open") ;

	int32_t ret = i2c_smbus_read_byte_data(mFd, (uint8_t)(offset & 0xff)) ;
	if (ret < 0)
		return setError("Error reading byte from I2c device " + std::to_string(errno)) ;

	byte = (uint8_t)(ret & 0xff) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cBusLinux::doReadShort(uint32_t offset, uint16_t &shortVal)
{
	if (!mSmbReadWordData)
		return setError("I2cBusLinux::doReadShort not supported on this device") ;

	if (mFd < 0)
		return setError("I2c device not open") ;

	int32_t ret = i2c_smbus_read_word_data(mFd, (uint8_t)(offset & 0xff)) ;
	if (ret < 0)
		return setError("Error reading short from I2c device " + std::to_string(errno)) ;

	shortVal = (uint16_t)(ret & 0xffff) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cBusLinux::doWriteData(const std::vector<uint8_t> &bytes)
{
	if (mFd < 0)
		return setError("I2c device not open") ;

	unsigned totalBytesToWrite(bytes.size()) ;
	const uint8_t* bp(&bytes[0]) ;
	while (totalBytesToWrite > 0)
	{
		unsigned bytesToWrite(totalBytesToWrite) ;
		if (bytesToWrite > MAX_READ_BUFF)
			bytesToWrite = MAX_READ_BUFF ;
		totalBytesToWrite -= bytesToWrite ;

		if (write(mFd, bp, bytesToWrite) < 0)
			return setError("Unable to write block to I2c device " + std::to_string(errno)) ;

		bp += bytesToWrite ;
	}


	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cBusLinux::doReadData(std::vector<uint8_t> &bytes, unsigned numBytes)
{
	if (mFd < 0)
		return setError("I2c device not open") ;

	uint8_t buff[MAX_READ_BUFF] ;

	unsigned totalBytesToRead(numBytes) ;
	if (totalBytesToRead == 0)
		totalBytesToRead = MAX_READ_BUFF ;

	while (totalBytesToRead > 0)
	{
		unsigned bytesToRead(totalBytesToRead) ;
		if (bytesToRead > MAX_READ_BUFF)
			bytesToRead = MAX_READ_BUFF ;
		totalBytesToRead -= bytesToRead ;

		int numRead = read(mFd, buff, bytesToRead) ;

		if (debug())
			std::cerr << "I2cBusLinux::doReadData" << " numRead=" << numRead << " errno=" << errno << std::endl ;

		if (numRead < 0)
			return setError("Unable to read bytes from I2c device " + std::to_string(errno)) ;

		if ((numBytes > 0) && (numRead != (int32_t)bytesToRead) )
			return setError("Incorrect number of bytes read from I2c device") ;

		bytes.insert(bytes.end(), buff, buff + numRead) ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cBusLinux::doWriteData(uint32_t offset, const std::vector<uint8_t> &bytes)
{
//	std::cerr << "I2cBusLinux::doWriteData " << busName() << " : " << busDetails() << " : 0x" << std::hex << i2cAddress() << std::dec << std::endl ;
//	std::cerr << "I2cBusLinux::doWriteData offset=0x" << std::hex << offset << std::dec << " " << bytes.size() << " bytes" << std::endl ;

	if (!mSmbWriteBlockData)
		return setError("I2cBusLinux::doWriteData (offset) not supported on this device") ;

	if (mFd < 0)
		return setError("I2c device not open") ;

	unsigned totalBytesToWrite(bytes.size()) ;
	const uint8_t* bp(&bytes[0]) ;
	while (totalBytesToWrite > 0)
	{
		unsigned bytesToWrite(totalBytesToWrite) ;
		if (bytesToWrite > MAX_READ_BUFF)
			bytesToWrite = MAX_READ_BUFF ;
		totalBytesToWrite -= bytesToWrite ;

//		std::cerr << " * doWriteData offset=0x" << std::hex << offset << std::dec << " " << bytesToWrite << " bytes" << std::endl ;

		if (i2c_smbus_write_i2c_block_data(mFd, (uint8_t)(offset & 0xff), bytesToWrite, bp) < 0)
		{
			std::cerr << " * doWriteData FAILED offset=0x" << std::hex << offset << std::dec << " " << bytesToWrite << " bytes, errno=" << errno << std::endl ;
			return setError("Unable to write block to I2c device " + std::to_string(errno)) ;
		}

		bp += bytesToWrite ;
		offset += bytesToWrite ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cBusLinux::doReadData(uint32_t offset, std::vector<uint8_t> &bytes, unsigned numBytes)
{
	if (debug())
		std::cerr << "I2cBusLinux::doReadData" << " offset=" << offset << " numBytes=" << numBytes << std::endl ;

	if (!mSmbReadBlockData)
		return setError("I2cBusLinux::doReadData (offset) not supported on this device") ;

	if (mFd < 0)
		return setError("I2c device not open") ;

	uint8_t buff[MAX_READ_BUFF] ;

	unsigned totalBytesToRead(numBytes) ;
	if (totalBytesToRead == 0)
		totalBytesToRead = MAX_READ_BUFF ;

	while (totalBytesToRead > 0)
	{
		unsigned bytesToRead(totalBytesToRead) ;
		if (bytesToRead > MAX_READ_BUFF)
			bytesToRead = MAX_READ_BUFF ;
		totalBytesToRead -= bytesToRead ;

		int32_t numRead = i2c_smbus_read_i2c_block_data(mFd, (uint8_t)(offset & 0xff), bytesToRead, buff) ;

		if (debug())
			std::cerr << "I2cBusLinux::doReadData" << " numRead=" << numRead << " errno=" << errno << std::endl ;

		if (numRead < 0)
			return setError("Unable to read bytes from I2c device " + std::to_string(errno)) ;

		if ((numBytes > 0) && (numRead != (int32_t)bytesToRead) )
			return setError("Incorrect number of bytes read from I2c device") ;

		bytes.insert(bytes.end(), buff, buff + numRead) ;
		offset += bytesToRead ;
	}

	return true ;
}
