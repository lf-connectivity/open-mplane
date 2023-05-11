/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Pa1UnderTemperatureFaultMajor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "PaUnderTemperatureFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::Pa1UnderTemperatureFaultMajor::NAME="Pa1UnderTemperatureMajorFault";

const char* Mplane::Pa2UnderTemperatureFaultMajor::NAME="Pa2UnderTemperatureMajorFault";

const char* Mplane::Pa3UnderTemperatureFaultMajor::NAME="Pa3UnderTemperatureMajorFault";

const char* Mplane::Pa4UnderTemperatureFaultMajor::NAME="Pa4UnderTemperatureMajorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa1UnderTemperatureFaultMajor::Pa1UnderTemperatureFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa1UnderTemperatureFaultMajor::~Pa1UnderTemperatureFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa2UnderTemperatureFaultMajor::Pa2UnderTemperatureFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa2UnderTemperatureFaultMajor::~Pa2UnderTemperatureFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa3UnderTemperatureFaultMajor::Pa3UnderTemperatureFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa3UnderTemperatureFaultMajor::~Pa3UnderTemperatureFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa4UnderTemperatureFaultMajor::Pa4UnderTemperatureFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Pa4UnderTemperatureFaultMajor::~Pa4UnderTemperatureFaultMajor()
{
}
