/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonResamplerConfig.cpp
 * \brief     This interface class provides access to the FPGA resampler configuration data
 *
 *
 * \details   This interface class provides access to the FPGA resampler configuration data
 *
 */


#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "CommonResamplerConfig.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================



//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonResamplerConfig::CommonResamplerConfig():
		mResamplers()
{
}

//-------------------------------------------------------------------------------------------------------------
unsigned CommonResamplerConfig::getClockPerSample(std::pair<unsigned, unsigned> resamplerMD, Frequency ibw)
{
	int index = findResamplerIndex(resamplerMD);
	if (index >= 0)
	{
		return mResamplers[index].getClockPerSample(ibw);
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<float> CommonResamplerConfig::getResamplingCoefficients(std::pair<unsigned, unsigned> resamplerMD, Frequency ibw)
{
	int index = findResamplerIndex(resamplerMD);
	if (index >= 0)
	{
		return mResamplers[index].getResamplingCoefficients(ibw);
	}

	return std::vector<float>();
}

//-------------------------------------------------------------------------------------------------------------
void CommonResamplerConfig::Resampler::addIbwData(Frequency ibw, unsigned clocksPerSample, const std::vector<float>& coeff)
{
	mIbwData[ibw] = std::make_tuple(clocksPerSample, coeff);
}

//-------------------------------------------------------------------------------------------------------------
unsigned CommonResamplerConfig::Resampler::getClockPerSample(Frequency ibw)
{
	if (mIbwData.find(ibw) != mIbwData.end())
	{
		auto data = mIbwData[ibw];
		return std::get<0>(data);
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<float> CommonResamplerConfig::Resampler::getResamplingCoefficients(Frequency ibw)
{
	if (mIbwData.find(ibw) != mIbwData.end())
	{
		auto data = mIbwData[ibw];
		return std::get<1>(data);
	}

	return std::vector<float>();
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void CommonResamplerConfig::createResampler(std::pair<unsigned, unsigned> resamplerRatio)
{
	mResamplers.push_back(Resampler(resamplerRatio));
}

//-------------------------------------------------------------------------------------------------------------
void CommonResamplerConfig::addIbwData(std::pair<unsigned, unsigned> resamplerRatio, Frequency ibw,
		unsigned clocksPerSample, const std::vector<float>& coeff)
{
	int index = findResamplerIndex(resamplerRatio);
	if (index >= 0)
	{
		mResamplers[index].addIbwData(ibw, clocksPerSample, coeff);
	}
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int CommonResamplerConfig::findResamplerIndex(std::pair<unsigned, unsigned> resamplerRatio)
{
	int index = 0;
	auto it = mResamplers.begin();
	while (it != mResamplers.end())
	{
		if (resamplerRatio.first == it->resamplerMultiply() &&
				resamplerRatio.second == it->resamplerDivide())
		{
			break;
		}

		 ++it;
		 ++index;
	}

	if (it == mResamplers.end())
		index = -1;

	return index;
}
