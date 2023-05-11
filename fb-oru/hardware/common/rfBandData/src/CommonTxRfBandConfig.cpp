/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonTxRfBandConfig.cpp
 * \brief     This interface class provides access to the radios Tx RF band constants
 *
 *
 * \details   This interface class provides access to the radios Tx RF band constants
 *
 */


#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "CommonTxRfBandConfig.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================



//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonTxRfBandConfig::CommonTxRfBandConfig():
		CommonRfBandConfig()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void CommonTxRfBandConfig::addTxRfBand(Frequency centerMin, Frequency centerMax, Frequency edgeMin, Frequency edgeMax,
    			   Frequency sampling, unsigned nyquistZone, unsigned interpolation,
				   std::pair<unsigned, unsigned> mmcmRatio, std::pair<unsigned, unsigned> resamplerRatio)
{
	addRfBand(centerMin, centerMax, edgeMin, edgeMax, sampling, nyquistZone, 1, interpolation, mmcmRatio, resamplerRatio);
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================
