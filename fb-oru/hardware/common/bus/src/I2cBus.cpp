/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      I2cBus.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "I2cBus.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
I2cBus::I2cBus(const std::string &busName, const std::string &busDetails, unsigned i2cAddress, std::shared_ptr<IBusLock> busLock,
		std::shared_ptr<IBusReadonlySettings> busSettings) :
	Bus(busName, busDetails, busLock, busSettings),
	mI2cAddress(i2cAddress & 0xff)
{
}

//-------------------------------------------------------------------------------------------------------------
I2cBus::~I2cBus()
{
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
unsigned I2cBus::i2cAddress() const
{
	return mI2cAddress ;
}
