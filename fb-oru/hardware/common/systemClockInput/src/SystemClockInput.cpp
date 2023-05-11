/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SystemClockInput.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <map>
#include "stringfunc.hpp"
#include "IRadio.h"
#include "SystemClockInput.h"

using namespace Mplane;

//=============================================================================================================
// STATIC
//=============================================================================================================

static const std::map<ISystemClockInput::ClkSource, std::string> ClockSourceLookup{
	{ ISystemClockInput::CLKIN_NONE, 		"NONE"},
	{ ISystemClockInput::CLKIN_INTERNAL, 	"Internal"},
	{ ISystemClockInput::CLKIN_10MHZ, 		"External_10MHz"},
	{ ISystemClockInput::CLKIN_FIBRE, 		"FIBRE"},
	{ ISystemClockInput::CLKIN_10G_SYNCE, 	"10G_SYNCE"},
	{ ISystemClockInput::CLKIN_25G_SYNCE, 	"25G_SYNCE"},
} ;

#if 0
//-------------------------------------------------------------------------------------------------------------
ISystemClockInput::ClkSource ISystemClockInput::strToClkin(const std::string& source)
{
	std::string srcLower(toLower(source)) ;
	for (auto entry : ClockSourceLookup)
	{
		if (toLower(entry.second).find(srcLower) == std::string::npos)
			continue ;

		return entry.first ;
	}
	return ISystemClockInput::CLKIN_NONE ;
}
#endif

//-------------------------------------------------------------------------------------------------------------
std::string ISystemClockInput::clkinToStr(ISystemClockInput::ClkSource clkInput)
{
	return ClockSourceLookup.at(clkInput) ;
}

//-------------------------------------------------------------------------------------------------------------
ISystemClockInput::ClkSource ISystemClockInput::clkStrToEnum(const std::string& clkInput)
{
	ISystemClockInput::ClkSource src = ISystemClockInput::CLKIN_NONE;
	for (auto & elem : ClockSourceLookup)
	{
		if (elem.second == clkInput)
		{
			src = elem.first;
			break;
		}
	}

	return src;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SystemClockInput::SystemClockInput(ISystemClockInput::ClkSource clkInput) :
	mClkSource(clkInput)
{
}

//-------------------------------------------------------------------------------------------------------------
SystemClockInput::~SystemClockInput()
{
}

//-------------------------------------------------------------------------------------------------------------
bool SystemClockInput::setClockInput(ClkSource clkInput)
{
	if (mClkSource == ISystemClockInput::CLKIN_NONE)
	{
		return false;
	}

	if (mClkSource != clkInput)
	{
		ClkSource savedClkSource(mClkSource) ;
		mClkSource = clkInput ;

		// Run radio initialisation
		std::shared_ptr<IRadio> radio(IRadioFactory::getInterface()) ;
		if (radio->initialise() != ReturnType::RT_OK)
		{
			mClkSource = savedClkSource ;
			return false ;
		}
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
ISystemClockInput::ClkSource SystemClockInput::getClockInput()
{
	return mClkSource ;
}
