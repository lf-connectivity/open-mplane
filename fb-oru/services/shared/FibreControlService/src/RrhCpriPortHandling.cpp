/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      D1tCpriPortHandling.cpp
 * \brief     JDSU-D1T specific Cpri port handler
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "RrhCpriPortHandling.h"

#include "CommonCpriCore.h"
#include "IHardwareSettings.h"

using namespace Mplane;

//=============================================================================================================
// SINGLETONS/FACTORIES
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
// Factory for creating instances if this
std::shared_ptr<ICpriPortHandler> RrhCpriPortHandler::factory(unsigned port, std::shared_ptr<ICpriSfpControlLogic> sfpLogic)
{
	return std::shared_ptr<ICpriPortHandler>( new RrhCpriPortHandler(port, sfpLogic) ) ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RrhCpriPortHandler::~RrhCpriPortHandler()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void RrhCpriPortHandler::setupAutoNeg()
{
	setupDefaults() ;

    // This setup only applies to a slave port

    // Special for RRH - Restrict rates
    mPortControl.allowableRates = getAllowableRates() ;

    // Program the preferred line rates to the core register
    mCore->setPortParameters(mPortControl);
}

//-------------------------------------------------------------------------------------------------------------
ICpriCore::LineRateCapability RrhCpriPortHandler::getAllowableRates()
{
    ICpriCore::LineRateCapability allowableRates ;

    allowableRates.capableOfRate9830_4 = true;  // CPRI rate 7

    return allowableRates ;
}


//-------------------------------------------------------------------------------------------------------------
RrhCpriPortHandler::RrhCpriPortHandler(UINT32 port, std::shared_ptr<ICpriSfpControlLogic> sfpLogic) :
	CpriPortHandler(port, sfpLogic)
{
}
