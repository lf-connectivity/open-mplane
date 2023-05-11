/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LatchedAntennaAlarmEmu.cpp
 * \brief     Latched alarm register (at 0x24)
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "LatchedAntennaAlarmEmu.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
LatchedAntennaAlarmEmu::LatchedAntennaAlarmEmu(unsigned antenna) :
	W1Clear(0x50250 + (0x01000 * antenna), 0, 16)
{
}

LatchedAntennaAlarmEmu::~LatchedAntennaAlarmEmu()
{
}
