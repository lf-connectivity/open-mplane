/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaSpiBus.cpp
 * \brief     Base-level FPGA SPI bus
 *
 *
 * \details   FPGA SPI bus access implementation
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <string.h>
#include <iostream>
#include "ByteTransfer.hpp"
#include "FpgaSpiBus.h"
#include "Task.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================

// 5ms timeout
static const unsigned SPI_DONE_TIMEOUT_MS{5} ;

const uint8_t FpgaSpiBus::CLOCK_DIV(1);
const uint8_t FpgaSpiBus::READ_OPPOSITE_EDGE(0);

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaSpiBus::FpgaSpiBus(const std::string& busName, const std::string& busDetails, std::shared_ptr<IBusLock> busLock,
		std::shared_ptr<ISpiBusReadonlySettings> busSettings) :
		SpiBus(busName, busDetails, busLock, busSettings)
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaSpiBus::~FpgaSpiBus()
{
}


//=============================================================================================================
// PROTECTED HOOKS
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
bool FpgaSpiBus::doWriteByte(uint32_t offset, uint8_t byte)
{
	/// Create a vector of bytes to write and fill up the offset bytes in it
	uint8_t numOffsetBytes= 0;
	std::vector<uint8_t> bytes;

	fillWriteData(offset, bytes, numOffsetBytes);

	/// Append the data to the vector
	bytes.push_back(byte);

	/// Write the data to the bus
	return doWriteData(bytes);
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaSpiBus::doWriteShort(uint32_t offset, uint16_t shortVal)
{
	/// Create a vector of bytes to write and fill up the offset bytes in it
	uint8_t numOffsetBytes= 0;
	std::vector<uint8_t> bytes;

	fillWriteData(offset, bytes, numOffsetBytes);

	/// Append the data to the vector
	bytes.push_back(shortVal & 0xFF);
	bytes.push_back((shortVal & 0xFF00) >> 8);

	/// Write the data to the bus
	return doWriteData(bytes);
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaSpiBus::doReadByte(uint32_t offset, uint8_t &byte)
{
	/// Create a vector of bytes to write and fill up the offset bytes in it
	uint8_t numOffsetBytes= 0;
	std::vector<uint8_t> bytes;

	fillWriteData(offset, bytes, numOffsetBytes);

	/// Write the data to the bus
	if (!executeRequest(bytes, 1))
	{
		return false;
	}

	/// Read the data from the bus
	unsigned rawData;
	readData(rawData);

	/// Copy the data to the reference variable
	byte = rawData & 0xFF;

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaSpiBus::doReadShort(uint32_t offset, uint16_t &shortVal)
{
	/// Create a vector of bytes to write and fill up the offset bytes in it
	uint8_t numOffsetBytes= 0;
	std::vector<uint8_t> bytes;

	fillWriteData(offset, bytes, numOffsetBytes);

	/// Write the data to the bus
	if (!executeRequest(bytes, 2))
	{
		return false;
	}

	/// Read the data from the bus
	unsigned rawData;
	readData(rawData);

	/// Copy the data to the reference variable
	shortVal = rawData & 0xFFFF;

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaSpiBus::doWriteData(const std::vector<uint8_t> &bytes)
{
	return (executeRequest(bytes, 0));
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaSpiBus::doReadData(std::vector<uint8_t> &bytes, unsigned numBytes)
{
	/// Cannot read more than 4 bytes on FPGA SPI bus in a single transaction
	if (numBytes > 4)
	{
		return setError("Cannot read more than 4 bytes on FPGA SPI bus in a single transaction");
	}

	/// Create a blank vector
	std::vector<uint8_t> writebytes;

	/// Write the data to the bus
	if (!executeRequest(writebytes, numBytes))
	{
		return false;
	}

	/// Read the data from the bus
	unsigned rawData;
	readData(rawData);

	/// Copy the data to the vector
	for (uint8_t index = 0; index < numBytes; index++)
	{
		bytes.push_back(rawData & 0xFF);
		rawData = rawData >> 8;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaSpiBus::doWriteData(uint32_t offset, const std::vector<uint8_t> &bytes)
{
	/// Create a vector of bytes to write and fill up the offset bytes in it
	uint8_t numOffsetBytes= 0;
	std::vector<uint8_t> targetBytes;

	fillWriteData(offset, targetBytes, numOffsetBytes);

	/// Append the data to the vector
	for (unsigned index = 0; index < bytes.size(); index++)
	{
		targetBytes.push_back(bytes[index]);
	}

	/// Write the data to the bus
	return doWriteData(targetBytes);
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaSpiBus::doReadData(uint32_t offset, std::vector<uint8_t> &bytes, unsigned numBytes)
{
	/// Cannot read more than 4 bytes on FPGA SPI bus in a single transaction
	if (numBytes > 4)
	{
		return setError("Cannot read more than 4 bytes on FPGA SPI bus in a single transaction");
	}

	/// Create a vector of bytes to write and fill up the offset bytes in it
	uint8_t numOffsetBytes= 0;
	std::vector<uint8_t> writeBytes;

	fillWriteData(offset, writeBytes, numOffsetBytes);

	/// Write the data to the bus
	if (!executeRequest(writeBytes, numBytes))
	{
		return false;
	}

	/// Read the data from the bus
	unsigned rawData;
	readData(rawData);

	/// Copy the data to the vector
	for (uint8_t index = 0; index < numBytes; index++)
	{
		bytes.push_back(rawData & 0xFF);
		rawData = rawData >> 8;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaSpiBus::isTransactionSuccessful(void)
{
    unsigned timeMs = 0;

	do
	{
		// check whether the access is complete
		if (isTransactionComplete())
		{
			return true;
		}

		// Sleep for 1ms
		Task::msSleep(1) ;
		timeMs++;

	} while (timeMs <= SPI_DONE_TIMEOUT_MS) ;

	// If SPI transaction is not complete within the timeout, then return false
    return false;
}


//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void FpgaSpiBus::fillWriteData(uint32_t offset, std::vector<uint8_t> &bytes, uint8_t& numOffsetBytes)
{
	/// Get the number of bits used in the offset parameter
	uint8_t offsetLen = settings()->getOffsetNumBits();

	/// Mask the offset parameter as per the number of bits
	offset &= ((1 << offsetLen) - 1);

	/// Calculate the number of bytes required by the offset parameter and the number of bytes to write
	numOffsetBytes = (offsetLen + 7)/8;

	/// Write the offset
	for (uint8_t index = 0; index < numOffsetBytes; index++)
	{
		bytes.push_back(offset & 0xFF);
		offset = offset >> 8;
	}
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaSpiBus::executeRequest(std::vector<uint8_t> bytes, uint8_t numBytesToRead)
{
	unsigned numBytes = bytes.size();

	/// Cannot write more than 4 bytes on FPGA SPI bus in a single transaction
	if (numBytes > 4)
	{
		return setError("Cannot write more than 4 bytes on FPGA SPI bus in a single transaction");
	}

	ISpiBusReadonlySettings::SpiMode modeNum = std::dynamic_pointer_cast<ISpiBusReadonlySettings>(settings())->mode();
	uint8_t cPha, cPol;
	cPha = modeNum & 0x01;
	cPol = (modeNum & 0x10) >> 1;

	/// Calculate number of bits to read and write
	uint8_t readBits = numBytesToRead * 8;
	uint8_t writeBits = numBytes * 8;

	if (writeBits > 0)
	{
		writeBits--;
	}

	/// Setup control registers
	setControlReg1(readBits, writeBits, cPol, READ_OPPOSITE_EDGE);

	setControlReg2(CLOCK_DIV, cPha, false);

	/// Setup the data to write
	uint32_t dataToWrite = 0;

	for (unsigned index = 0; index < numBytes; index++)
	{
		dataToWrite = dataToWrite << 8;
		dataToWrite |= bytes[index];
	}

	setupWriteData(dataToWrite & 0xFFFF, (dataToWrite & 0xFFFF0000) >> 16);

	/// Start the SPI transaction
	startSpiTransaction();

	/// Check if transaction is successful
	if ( !isTransactionSuccessful())
	{
		return setError("FPGA SPI transfer failed");
	}

	return true ;
}
