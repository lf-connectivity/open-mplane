/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestDataBus.cpp
 * \brief     Base-level serial bus
 *
 *
 * \details   Base-level serial bus
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <string.h>
#include <cctype>
#include <algorithm>
#include <string.h>
#include <sstream>
#include <iomanip>
#include "TestDataBus.h"
#include "stringfunc.hpp"
#include "ILoggable.h"

using namespace Mplane;

const std::string TestDataBus::TestDataPath("/tmp/TestDataBus.inf");
const std::string TestDataBus::WriteResult("Wr");
const std::string TestDataBus::ReadResult("Rd");
const std::string TestDataBus::ReadData("RxData");
//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TestDataBus::TestDataBus(const std::string& busName, const std::string& busDetails, std::shared_ptr<IBusLock> busLock,
		std::shared_ptr<IBusReadonlySettings> busSettings) :
	Bus(busName, busDetails, busLock, busSettings)
{
	mFileMap = std::make_shared<FileMap>(TestDataPath);
	mRead = false;
}

//-------------------------------------------------------------------------------------------------------------
TestDataBus::~TestDataBus()
{
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool TestDataBus::doWriteData(const std::vector<uint8_t>& bytes)
{
	mFileMap->setPath(TestDataPath);
	std::string wrResult = toLower(mFileMap->value(WriteResult));

	mRead = true;
	return (wrResult == "true" ? true : false);
}

//-------------------------------------------------------------------------------------------------------------
bool TestDataBus::doReadData(std::vector<uint8_t>& bytes, unsigned numBytes)
{
	mFileMap->setPath(TestDataPath);
	std::string rdResult = toLower(mFileMap->value(ReadResult));

	if (mRead)
	{
		std::string rxData = removeSpaces(mFileMap->value(ReadData));

		unsigned int index = 0;
		if (numBytes == 0)
		{
			numBytes = rxData.size()/2;
		}

		if (bytes.size() < numBytes)
		{
			bytes.resize(numBytes);
		}
		for (unsigned int i = 0; i < rxData.size(); i += 2) {
			if (i + 1 < rxData.size())
			{
				std::string byteString = rxData.substr(i, 2);
				unsigned char byte = (char) strtol(byteString.c_str(), NULL, 16);
				bytes[index++] = byte;
			}

			if (index >= numBytes)
			{
				break;
			}
		}
		mRead = false;
	}
	return (rdResult == "true" ? true : false);
}
