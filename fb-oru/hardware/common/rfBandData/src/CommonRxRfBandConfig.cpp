/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRxRfBandConfig.cpp
 * \brief     This interface class provides access to the radios Rx RF band constants
 *
 *
 * \details   This interface class provides access to the radios Rx RF band constants
 *
 */


#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "CommonRxRfBandConfig.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================



//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonRxRfBandConfig::CommonRxRfBandConfig():
		CommonRfBandConfig()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void CommonRxRfBandConfig::addRxRfBand(Frequency centerMin, Frequency centerMax, Frequency edgeMin, Frequency edgeMax,
    			   Frequency sampling, unsigned nyquistZone, unsigned decimation,
				   std::pair<unsigned, unsigned> mmcmRatio, std::pair<unsigned, unsigned> resamplerRatio)
{
	addRfBand(centerMin, centerMax, edgeMin, edgeMax, sampling, nyquistZone, decimation, 1, mmcmRatio, resamplerRatio);
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================
