/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PaOverTemperatureFaultMajor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "PaOverTemperatureFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::Pa1OverTemperatureFaultMajor::NAME="Pa1OverTemperatureMajorFault";

const char* Mplane::Pa2OverTemperatureFaultMajor::NAME="Pa2OverTemperatureMajorFault";

const char* Mplane::Pa3OverTemperatureFaultMajor::NAME="Pa3OverTemperatureMajorFault";

const char* Mplane::Pa4OverTemperatureFaultMajor::NAME="Pa4OverTemperatureMajorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa1OverTemperatureFaultMajor::Pa1OverTemperatureFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa1OverTemperatureFaultMajor::~Pa1OverTemperatureFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa2OverTemperatureFaultMajor::Pa2OverTemperatureFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa2OverTemperatureFaultMajor::~Pa2OverTemperatureFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa3OverTemperatureFaultMajor::Pa3OverTemperatureFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa3OverTemperatureFaultMajor::~Pa3OverTemperatureFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa4OverTemperatureFaultMajor::Pa4OverTemperatureFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa4OverTemperatureFaultMajor::~Pa4OverTemperatureFaultMajor()
{
}
