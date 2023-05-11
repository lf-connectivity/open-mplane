/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      I2cBusLinux.cpp
 * \brief     PC simulation version
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
#include <algorithm>
#include <fstream>
#include <sstream>

#include "Benchmark.h"
#include "Path.h"
#include "I2cBusLinux.h"

using namespace Mplane;


//=============================================================================================================
// LOCAL
//=============================================================================================================

const unsigned MAX_READ_BUFF(32) ;

namespace {

	std::fstream simfile ;
	std::map<std::string, std::vector<std::vector<uint8_t>>> simRegs ;

	//---------------------------------------------------------------------------------------------------------
	void initSim()
	{
		static bool initialised(false) ;

		if (initialised)
			return ;

		std::string user(::getenv("USER")) ;
		if (user.empty())
			user = "test" ;
		std::string simfilePath("/tmp/" + user + "/i2c") ;
		Path::mkpath(simfilePath) ;

		std::string simfileName(simfilePath + "/i2c.log") ;
		simfile.open(simfileName, std::fstream::out | std::fstream::trunc) ;
		std::cerr << "** I2C SIM: Check log file at " << simfileName << " **" << std::endl ;

		initialised = true ;
	}

	//---------------------------------------------------------------------------------------------------------
	void initSimRegs(const std::string& devpath)
	{
		if (simRegs.find(devpath) != simRegs.end())
			return ;

		simRegs[devpath] = std::vector<std::vector<uint8_t>>() ;
		for (unsigned i=0; i < 256; i++)
		{
			simRegs[devpath].push_back( std::vector<uint8_t>(256, 0) ) ;
		}
	}

	//---------------------------------------------------------------------------------------------------------
	std::string logBytes(const std::vector<uint8_t>& bytes)
	{
		std::stringstream ss ;
		ss << " [ " ;
		for (auto byte : bytes)
		{
			ss << std::hex << std::setw(2) << std::setfill('0') << (unsigned)byte << std::dec << " " ;
		}
		ss << "]" ;
		return ss.str() ;
	}

	//---------------------------------------------------------------------------------------------------------
	std::string logVal(uint8_t val)
	{
		std::stringstream ss ;
		ss << " val=0x" << std::hex << (unsigned)val << std::dec ;
		return ss.str() ;
	}

	//---------------------------------------------------------------------------------------------------------
	std::string logVal(uint16_t val)
	{
		std::stringstream ss ;
		ss << " val=0x" << std::hex << val << std::dec ;
		return ss.str() ;
	}

	//---------------------------------------------------------------------------------------------------------
	void writeLog(const std::string& method, const std::string& rdwr,
			const std::string& busName, const std::string& busDetails,
			unsigned i2cAddress,
			uint32_t offset, const std::vector<uint8_t>& bytes,
			const std::string& valstr = "")
	{
		simfile << "[" << Benchmark::getInstance()->timestamp() << "]" <<
				" < " << busName << " : " << busDetails << " >" <<
				" I2cBusLinux::" << method << " " << rdwr <<
				" a=0x" <<
				std::hex << i2cAddress << std::dec <<
				" off=0x" << std::hex << offset << std::dec <<
				valstr <<
				logBytes(bytes) <<
				std::endl ;

	}
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
I2cBusLinux::I2cBusLinux(const std::string &devicePath, unsigned i2cAddr, std::shared_ptr<IBusLock> busLock,
		std::shared_ptr<IBusReadonlySettings> busSettings) :
	I2cBus("Linux I2C", devicePath + " addr=" + std::to_string(i2cAddr), i2cAddr, busLock, busSettings),
	mDevicePath(devicePath),
	mFd(-1),
	mSmbWriteByteData(true),
	mSmbReadByteData(true),
	mSmbWriteWordData(true),
	mSmbReadWordData(true),
	mSmbWriteBlockData(true),
	mSmbReadBlockData(true)
{
	initSim() ;
	initSimRegs(devicePath) ;
}

//-------------------------------------------------------------------------------------------------------------
I2cBusLinux::~I2cBusLinux()
{
}


//=============================================================================================================
// PROTECTED HOOKS
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
bool I2cBusLinux::doWriteByte(uint32_t offset, uint8_t byte)
{
	writeLog("doWriteByte", "wr", busName(), busDetails(), i2cAddress(), offset, std::vector<uint8_t>{byte}, logVal(byte)) ;
	simRegs[ mDevicePath ][ i2cAddress() & 0xff ][ offset & 0xff ] = byte ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cBusLinux::doWriteShort(uint32_t offset, uint16_t shortVal)
{
	uint8_t ms( (shortVal >> 8) & 0xff ) ;
	uint8_t ls( shortVal & 0xff ) ;

	if (settings()->isLittleEndian())
		std::swap(ms, ls) ;

	writeLog("doWriteShort", "wr", busName(), busDetails(), i2cAddress(), offset, std::vector<uint8_t>{ms, ls}, logVal(shortVal)) ;

	uint8_t index(offset & 0xff) ;
	simRegs[ mDevicePath ][ i2cAddress() & 0xff ][ index ] = ms ;
	simRegs[ mDevicePath ][ i2cAddress() & 0xff ][ index+1 ] = ls ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cBusLinux::doReadByte(uint32_t offset, uint8_t &byte)
{
	byte = simRegs[ mDevicePath ][ i2cAddress() & 0xff ][ offset & 0xff ] ;

	writeLog("doReadByte", "rd", busName(), busDetails(), i2cAddress(), offset, std::vector<uint8_t>{byte}, logVal(byte)) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cBusLinux::doReadShort(uint32_t offset, uint16_t &shortVal)
{
	uint8_t index(offset & 0xff) ;
	uint8_t ms = simRegs[ mDevicePath ][ i2cAddress() & 0xff ][ index ] ;
	uint8_t ls = simRegs[ mDevicePath ][ i2cAddress() & 0xff ][ index+1 ] ;

	shortVal = ( (uint16_t)ms << 8) | (uint16_t)ls ;
	if (settings()->isLittleEndian())
	{
		shortVal = ( (uint16_t)ls << 8) | (uint16_t)ms ;
	}

	writeLog("doReadShort", "rd", busName(), busDetails(), i2cAddress(), offset, std::vector<uint8_t>{ms, ls}, logVal(shortVal)) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cBusLinux::doWriteData(const std::vector<uint8_t> &bytes)
{
	return doWriteData(0, bytes) ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cBusLinux::doReadData(std::vector<uint8_t> &bytes, unsigned numBytes)
{
	return doReadData(0, bytes, numBytes) ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cBusLinux::doWriteData(uint32_t offset, const std::vector<uint8_t> &bytes)
{
	unsigned totalBytesToWrite(bytes.size()) ;
	const uint8_t* bp(&bytes[0]) ;
	unsigned part(1) ;
	while (totalBytesToWrite > 0)
	{
		unsigned bytesToWrite(totalBytesToWrite) ;
		if (bytesToWrite > MAX_READ_BUFF)
			bytesToWrite = MAX_READ_BUFF ;
		totalBytesToWrite -= bytesToWrite ;

		std::vector<uint8_t> block ;
		for (unsigned i=0; i < bytesToWrite; ++i)
		{
			simRegs[ mDevicePath ][i2cAddress() & 0xff][ (offset&0xff) + i ] = *(bp + i) ;
			block.push_back( *(bp + i) ) ;
		}
		writeLog("doWriteData{" + std::to_string(part) + "}", "wr", busName(), busDetails(), i2cAddress(), offset, block) ;

		bp += bytesToWrite ;
		offset += bytesToWrite ;
		++part ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cBusLinux::doReadData(uint32_t offset, std::vector<uint8_t> &bytes, unsigned numBytes)
{
	unsigned totalBytesToRead(numBytes) ;
	if (totalBytesToRead == 0)
		totalBytesToRead = MAX_READ_BUFF ;

	unsigned part(1) ;
	while (totalBytesToRead > 0)
	{
		unsigned bytesToRead(totalBytesToRead) ;
		if (bytesToRead > MAX_READ_BUFF)
			bytesToRead = MAX_READ_BUFF ;
		totalBytesToRead -= bytesToRead ;

		std::vector<uint8_t> block ;
		for (unsigned i=0; i < bytesToRead; ++i)
		{
			block.push_back( simRegs[ mDevicePath ][i2cAddress() & 0xff][ (offset&0xff) + i ] ) ;
		}
		writeLog("doReadData{" + std::to_string(part) + "}", "rd", busName(), busDetails(), i2cAddress(), offset, block) ;

		bytes.insert(bytes.end(), block.begin(), block.end()) ;
		offset += bytesToRead ;
		++part ;
	}

	return true ;
}
