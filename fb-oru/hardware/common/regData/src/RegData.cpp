/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RegData.cpp
 * \brief     Implements IRegData interface to retrieve initialisation data for all supported drivers
 *
 *
 * \details   Implements IRegData interface to retrieve initialisation data for all supported drivers
 *
 */

#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "ILoggable.h"

#include "RegData.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RegData::RegData():
		mRegValues(),
		mRegAddrValues()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State RegData::getRegisterData(std::string driverName, std::vector< std::pair< uint32_t, uint32_t> > & regData )
{
	if (mRegAddrValues.find(driverName) != mRegAddrValues.end())
	{
		regData = mRegAddrValues[driverName];
	}
	else
	{
		return ReturnType::RT_NOT_FOUND;
	}

	return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State RegData::getRegisterData(std::string driverName, std::vector< uint32_t > & regData )
{
    std::cerr << "getRegisterData " << driverName << std::endl ;

	if (mRegValues.find(driverName) != mRegValues.end())
	{
		regData = mRegValues[driverName];
	}
	else
	{
		return ReturnType::RT_NOT_FOUND;
	}

	return ReturnType::RT_OK;
}
