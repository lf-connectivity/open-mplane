/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SynthClockFault.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "SynthClockFault.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::SynthClockFault::NAME="BasebandSynthClockFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::SynthClockFault::SynthClockFault() :
	Fault(10, 3, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::SynthClockFault::~SynthClockFault()
{
}
