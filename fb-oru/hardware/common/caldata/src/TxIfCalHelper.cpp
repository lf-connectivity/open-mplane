/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxIfCalHelper.cpp
 * \brief     Provides static utility methods for TxIfCal
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "ICalData.h"
#include "ITxIfCalData.h"

#include "ITxIfCal.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool ITxIfCal::getGain(int path, const FrequencyOffset& freqOffset, Power& gain)
{
	// Get RX IF cal
    std::shared_ptr<ITxIfCalDataContainer> calData(
    	std::dynamic_pointer_cast<ITxIfCalDataContainer>(ICalDataFactory::getInterface())
    );
    if (!calData)
    	return false ;

    std::shared_ptr<ITxIfCalData> txIfCal(calData->getTxIfCal());
    if (!txIfCal)
    	return false ;

    // skip if not loaded
    if (!txIfCal->isLoaded())
    	return false ;

    // skip if no valid RX IF response
    std::shared_ptr<ITxIfResponse> ifResp(txIfCal->getTxIfResponse(path)) ;
    if (!ifResp)
    	return false ;

	// skip adjustment if can't find a suitable value
    if (!ifResp->getGain(freqOffset, gain))
    	return false ;

    // got a value
    return true ;
}
