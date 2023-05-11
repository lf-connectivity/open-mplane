/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxAgcCalData.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <algorithm>

#include "RxAgcCal.h"
#include "RxAgcCalData.h"

using namespace Mplane;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RxAgcCalData::RxAgcCalData(std::shared_ptr<ICalDownload> calDownLoad) :
	RxCalData(calDownLoad)
{
}

//-------------------------------------------------------------------------------------------------------------
RxAgcCalData::~RxAgcCalData()
{
}

//-------------------------------------------------------------------------------------------------------------
std::vector<Power> RxAgcCalData::getCgSteps(int path, unsigned int numLevels,
		double attenuationStep)
{
	std::vector<Power> cgSteps;

	// Construct the CG levels as per the step size and the number of levels
	for (unsigned int level = 0; level < numLevels; level++)
	{
		cgSteps.push_back(level * attenuationStep);
	}

	return cgSteps ;

}

//-------------------------------------------------------------------------------------------------------------
std::vector<Power> RxAgcCalData::getCgSteps(int path)
{
	// Once upon a time the rx calibration file only had the following entries. Then, as time went on,
	// the calibration file blossomed into a beautiful complete file. Unfortunately the big bad AGC
	// was forgotten about and wasn't taken on the same beautiful fairy tale journey. Sadly the result
	// was that the big bad AGC didn't work any more and was not discovered for quite a few years.
	// To make this work now, we just define the AGC steps (RF DSA) because that was all it needed all
	// those years ago. And they all live happily ever after. The End.

	std::vector<Power> cgSteps = {1,4,10,16,22};

	return cgSteps;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<RxCal> RxAgcCalData::createRxAgcCal(
		const std::string& version, const std::string& country,
		const std::string& facility, const std::string& theoperator)
{
	return std::make_shared<RxAgcCal>(version, country, facility, theoperator) ;
}
