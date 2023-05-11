/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRfBandConfig.cpp
 * \brief     This interface class provides access to the radios RF band constants
 *
 *
 * \details   This interface class provides access to the radios RF band constants
 *
 */


#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "CommonRfBandConfig.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================



//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonRfBandConfig::CommonRfBandConfig():
		mRfBands()
{
}

//-------------------------------------------------------------------------------------------------------------
Frequency CommonRfBandConfig::getRfBandCenterMinFreq(Frequency freq)
{
	int index = findRfBandIndex(freq);
	if (index >= 0)
	{
		return mRfBands[index].centerMin();
	}

	return 0.0;
}

//-------------------------------------------------------------------------------------------------------------
Frequency CommonRfBandConfig::getRfBandCenterMaxFreq(Frequency freq)
{
	int index = findRfBandIndex(freq);
	if (index >= 0)
	{
		return mRfBands[index].centerMax();
	}

	return 0.0;
}

//-------------------------------------------------------------------------------------------------------------
Frequency CommonRfBandConfig::getRfBandEdgeMinFreq(Frequency freq)
{
	int index = findRfBandIndex(freq);
	if (index >= 0)
	{
		return mRfBands[index].edgeMin();
	}

	return 0.0;
}

//-------------------------------------------------------------------------------------------------------------
Frequency CommonRfBandConfig::getRfBandEdgeMaxFreq(Frequency freq)
{
	int index = findRfBandIndex(freq);
	if (index >= 0)
	{
		return mRfBands[index].edgeMax();
	}

	return 0.0;
}

//-------------------------------------------------------------------------------------------------------------
Frequency CommonRfBandConfig::getRfBandSamplingFreq(Frequency freq)
{
	int index = findRfBandIndex(freq);
	if (index >= 0)
	{
		return mRfBands[index].sampling();
	}

	return 0.0;
}

//-------------------------------------------------------------------------------------------------------------
unsigned CommonRfBandConfig::getRfBandNyquistZone(Frequency freq)
{
	int index = findRfBandIndex(freq);
	if (index >= 0)
	{
		return mRfBands[index].nyquistZone();
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------------------
unsigned CommonRfBandConfig::getRfBandDecimationFactor(Frequency freq)
{
	int index = findRfBandIndex(freq);
	if (index >= 0)
	{
		return mRfBands[index].decimation();
	}

	return 1;
}

//-------------------------------------------------------------------------------------------------------------
unsigned CommonRfBandConfig::getRfBandInterpolationFactor(Frequency freq)
{
	int index = findRfBandIndex(freq);
	if (index >= 0)
	{
		return mRfBands[index].interpolation();
	}

	return 1;
}

//-------------------------------------------------------------------------------------------------------------
std::pair<unsigned, unsigned> CommonRfBandConfig::getRfBandMmcmRatio(Frequency freq)
{
	int index = findRfBandIndex(freq);
	if (index >= 0)
	{
		return std::make_pair(mRfBands[index].mmcmMultiply(), mRfBands[index].mmcmDivide());
	}

	return std::make_pair(0,0);
}

//-------------------------------------------------------------------------------------------------------------
std::pair<unsigned, unsigned> CommonRfBandConfig::getRfBandResamplerRatio(Frequency freq)
{
	int index = findRfBandIndex(freq);
	if (index >= 0)
	{
		return std::make_pair(mRfBands[index].resamplerMultiply(), mRfBands[index].resamplerDivide());
	}

	return std::make_pair(0,0);
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void CommonRfBandConfig::addRfBand(Frequency centerMin, Frequency centerMax, Frequency edgeMin, Frequency edgeMax,
    			   Frequency sampling, unsigned nyquistZone, unsigned decimation, unsigned interpolation,
				   std::pair<unsigned, unsigned> mmcmRatio, std::pair<unsigned, unsigned> resamplerRatio)
{
	mRfBands.push_back(RfBand(centerMin, centerMax, edgeMin, edgeMax, sampling,
			nyquistZone, decimation, interpolation, mmcmRatio, resamplerRatio));
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int CommonRfBandConfig::findRfBandIndex(Frequency freq)
{
	int index = 0;
	auto it = mRfBands.begin();
	while (it != mRfBands.end())
	{

		if (freq >= it->centerMin() &&
			freq <= it->centerMax())
		{
			break;
		}

		 ++it;
		 ++index;
	}

	if (it == mRfBands.end())
		index = -1;

	return index;
}
