/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SerialData.cpp
 * \brief     Serves as a container for data received on serial bus
 *
 *
 * \details   This file is a container for data received on serial bus
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "SerialData.h"

using namespace Mplane;

//=============================================================================================================
// Public functions
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SerialData::SerialData(unsigned int readBlockSize)
{
	mData.clear();
	//Reserve the size that the serial data would need
	mData.reserve(readBlockSize);
}

//-------------------------------------------------------------------------------------------------------------
std::vector<unsigned char> SerialData::getData(void)
{
	return mData;
}

//-------------------------------------------------------------------------------------------------------------
void SerialData::setData(std::vector<unsigned char> data)
{
	mData = data;
}

//-------------------------------------------------------------------------------------------------------------
void SerialData::appendData(std::vector<unsigned char> data)
{
	mData.insert(mData.begin(), data.begin(), data.end());
}

//-------------------------------------------------------------------------------------------------------------
void SerialData::clearData(void)
{
	mData.clear();
}
