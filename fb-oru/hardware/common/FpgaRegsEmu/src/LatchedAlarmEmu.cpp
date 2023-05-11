/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LatchedAlarmEmu.cpp
 * \brief     Latched alarm register (at 0x24)
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "LatchedAlarmEmu.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
LatchedAlarmEmu::LatchedAlarmEmu() :
	W1Clear(0x00024, 0, 16)
{
}

LatchedAlarmEmu::~LatchedAlarmEmu()
{
}
