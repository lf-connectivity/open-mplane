/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RrhFreqPolicy.cpp
 * \brief     Frequency policy common to RRH apps
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sstream>

#include "RrhFreqPolicy.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RrhFreqPolicy::RrhFreqPolicy()
{
}

//-------------------------------------------------------------------------------------------------------------
RrhFreqPolicy::~RrhFreqPolicy()
{
}

//-------------------------------------------------------------------------------------------------------------
Frequency RrhFreqPolicy::calcCentre(unsigned port,
		const Frequency& centre, const Frequency& bundleMin,
		const Frequency& bundleMax)
{
	// calc centre of bundle
	Frequency bandwidth(bundleMax - bundleMin) ;
	return bundleMin + (bandwidth/2.0) ;
}

//-------------------------------------------------------------------------------------------------------------
bool RrhFreqPolicy::checkBundle(unsigned port,
		const Frequency& bandMin, const Frequency& bandMax,
		const Frequency& bundleMin, const Frequency& bundleMax,
		std::string& errorString)
{
	// Check against end stops
	if (bundleMax > bandMax)
	{
		std::stringstream ss ;
		ss << "Maximum frequency " << bundleMax << " greater than limit " << bandMax ;
		errorString = ss.str() ;
		return false ;
	}
	if (bundleMin < bandMin)
	{
		std::stringstream ss ;
		ss << "Minimum frequency " << bundleMin << " less than limit " << bandMin ;
		errorString = ss.str() ;
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool RrhFreqPolicy::checkCentre(unsigned port, const Frequency& centre,
		const Frequency& halfBandwidth, const Frequency& bundleMin,
		const Frequency& bundleMax, std::string& errorString)
{
	// check against the centre
	Frequency loMax(centre + halfBandwidth) ;
	if (bundleMax > loMax)
	{
		std::stringstream ss ;
		ss << "Maximum frequency " << bundleMax << " outside LO bandwidth. Max " << loMax ;
		errorString = ss.str() ;
		return false ;
	}

	Frequency loMin(centre - halfBandwidth) ;
	if (bundleMin < loMin)
	{
		std::stringstream ss ;
		ss << "Minimum frequency " << bundleMin << " outside LO bandwidth. Min " << loMin ;
		errorString = ss.str() ;
		return false ;
	}

	return true ;
}
