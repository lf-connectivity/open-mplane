/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SerialBus.h
 * \brief     Base-level serial bus
 *
 *
 * \details   Base-level serial bus
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "SerialBus.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SerialBus::SerialBus(const std::string &busName, const std::string &busDetails, unsigned baud, std::shared_ptr<IBusLock> busLock,
		std::shared_ptr<IBusReadonlySettings> busSettings) :
	Bus(busName, busDetails, busLock, busSettings),
	mBaudRate(baud)
{
}

//-------------------------------------------------------------------------------------------------------------
SerialBus::~SerialBus()
{
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
unsigned SerialBus::baud() const
{
	return mBaudRate ;
}
