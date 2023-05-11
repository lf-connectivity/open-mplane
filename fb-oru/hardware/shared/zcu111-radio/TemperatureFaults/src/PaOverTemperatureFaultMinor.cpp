/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PaOverTemperatureFaultMinor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "PaOverTemperatureFaultMinor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::Pa1OverTemperatureFaultMinor::NAME="Pa1OverTemperatureMinorFault";

const char* Mplane::Pa2OverTemperatureFaultMinor::NAME="Pa2OverTemperatureMinorFault";

const char* Mplane::Pa3OverTemperatureFaultMinor::NAME="Pa3OverTemperatureMinorFault";

const char* Mplane::Pa4OverTemperatureFaultMinor::NAME="Pa4OverTemperatureMinorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa1OverTemperatureFaultMinor::Pa1OverTemperatureFaultMinor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa1OverTemperatureFaultMinor::~Pa1OverTemperatureFaultMinor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa2OverTemperatureFaultMinor::Pa2OverTemperatureFaultMinor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa2OverTemperatureFaultMinor::~Pa2OverTemperatureFaultMinor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa3OverTemperatureFaultMinor::Pa3OverTemperatureFaultMinor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa3OverTemperatureFaultMinor::~Pa3OverTemperatureFaultMinor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa4OverTemperatureFaultMinor::Pa4OverTemperatureFaultMinor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa4OverTemperatureFaultMinor::~Pa4OverTemperatureFaultMinor()
{
}
