/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxIfCalHelper.cpp
 * \brief     Provides static utility methods for RxIfCal
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "ICalData.h"
#include "IRxIfCalData.h"

#include "IRxIfCal.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool IRxIfCal::getGain(int path, const FrequencyOffset& freqOffset, Power& gain)
{
	// Get RX IF cal
    std::shared_ptr<IRxIfCalDataContainer> calData(
    	std::dynamic_pointer_cast<IRxIfCalDataContainer>(ICalDataFactory::getInterface())
    );
    if (!calData)
    	return false ;

    std::shared_ptr<IRxIfCalData> rxIfCal(calData->getRxIfCal());
    if (!rxIfCal)
    	return false ;

    // skip if not loaded
    if (!rxIfCal->isLoaded())
    	return false ;

    // skip if no valid RX IF response
    std::shared_ptr<IRxIfResponse> ifResp(rxIfCal->getRxIfResponse(path)) ;
    if (!ifResp)
    	return false ;

	// skip adjustment if can't find a suitable value
    if (!ifResp->getGain(freqOffset, gain))
    	return false ;

    // got a value
    return true ;
}
