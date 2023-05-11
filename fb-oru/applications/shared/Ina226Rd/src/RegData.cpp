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

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "RegData.h"
#include "ILoggable.h"


using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RegData::RegData()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State RegData::getRegisterData(std::string driverName, std::vector< std::pair< uint32_t, uint32_t> > & regData )
{
	return ReturnType::RT_NOT_FOUND;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State RegData::getRegisterData(std::string driverName, std::vector< uint32_t > & regData )
{
	return ReturnType::RT_NOT_FOUND;
}
