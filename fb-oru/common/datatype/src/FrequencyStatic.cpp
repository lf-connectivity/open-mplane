/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FrequencyStatic.cpp
 * \brief     Common methods used by FrequencyBase
 *
 *
 * \details   This file contains the implementation common methods used by the template class FrequencyBase
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <math.h>

#include "stringfunc.hpp"
#include "FrequencyBase.hpp"

using namespace Mplane;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const char* FrequencyStatic::unit2Str(FrequencyStatic::Unit value)
{
    switch (value)
    {
    case Hz:
        return "Hz";
    case THz:
        return "THz";
    case HHz:
        return "HHz";
    case KHz:
        return "KHz";
    case TKHz:
        return "TKHz";
    case HKHz:
        return "HKHz";
    case MHz:
        return "MHz";
    case GHz:
        return "GHz";
    default:
        return "unknown";
    }
}

//-------------------------------------------------------------------------------------------------------------
FrequencyStatic::Unit FrequencyStatic::str2unit(const std::string& units)
{
	std::string lowerUnits( toLower(units) ) ;
	if (lowerUnits == "khz")
	{
		return KHz ;
	}
	else if (lowerUnits == "mhz")
	{
		return MHz ;
	}
	else if (lowerUnits == "hz")
	{
		return Hz ;
	}
	else if (lowerUnits == "ghz")
	{
		return GHz ;
	}
	else if (lowerUnits == "thz")
	{
		return THz ;
	}
	else if (lowerUnits == "hhz")
	{
		return HHz ;
	}
	else if (lowerUnits == "tkhz")
	{
		return TKHz ;
	}
	else if (lowerUnits == "hkhz")
	{
		return HKHz ;
	}
	else
	{
		return Hz ;
	}
}
