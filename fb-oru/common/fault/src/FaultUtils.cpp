/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FaultUtils.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "FaultUtils.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool FaultUtils::setUnderTemperatureFault(std::shared_ptr<IFault> fault,
		float temperature, float tripThreshold, float clearThreshold)
{
    if( temperature <= tripThreshold)
    {
        fault->setStatus( true );
        return true ;
    }

    if( temperature >= clearThreshold)
    {
        fault->setStatus( false );
        return false ;
    }

    // return current status
    return fault->isFaultPresent() ;
}

//-------------------------------------------------------------------------------------------------------------
bool FaultUtils::setOverTemperatureFault(std::shared_ptr<IFault> fault,
		float temperature, float tripThreshold, float clearThreshold)
{
    if( temperature >= tripThreshold)
    {
        fault->setStatus( true );
        return true ;
    }

    if( temperature <= clearThreshold)
    {
        fault->setStatus( false );
        return false ;
    }

    // return current status
    return fault->isFaultPresent() ;
}
