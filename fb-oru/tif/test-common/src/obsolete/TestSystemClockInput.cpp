/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestSystemClockInput.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <iostream>
#include <map>
#include "TestSystemClockInput.h"

using namespace Mplane;

//=============================================================================================================
// STATIC
//=============================================================================================================

static const std::map<ISystemClockInput::ClkSource, std::string> ClockSourceLookup{
	{ ISystemClockInput::CLKIN_NONE,  "NONE"},
	{ ISystemClockInput::CLKIN_10MHZ, "External 10MHz"},
	{ ISystemClockInput::CLKIN_FIBRE, "FIBRE"},
} ;

//-------------------------------------------------------------------------------------------------------------
std::string ISystemClockInput::clkinToStr(ISystemClockInput::ClkSource clkInput)
{
	return ClockSourceLookup.at(clkInput) ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TestSystemClockInput::TestSystemClockInput(ISystemClockInput::ClkSource clkInput) :
	mClkSource(clkInput)
{
}

//-------------------------------------------------------------------------------------------------------------
TestSystemClockInput::~TestSystemClockInput()
{
}

//-------------------------------------------------------------------------------------------------------------
bool TestSystemClockInput::setClockInput(ClkSource clkInput)
{
	if (mClkSource != clkInput)
	{
		// TODO: Re-run radio init
		std::cerr << "Re-initialise radio with clock input: " << clkinToStr(clkInput) << std::endl ;
	}

	mClkSource = clkInput ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
ISystemClockInput::ClkSource TestSystemClockInput::getClockInput()
{
	return mClkSource ;
}
