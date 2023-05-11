/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RrhCpriPortHandlerFactory.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "RrhCpriPortHandling.h"
#include "CpriController.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
// Factory for port handlers
std::shared_ptr<ICpriPortHandler> ICpriPortHandler::factory(unsigned port, std::shared_ptr<ICpriSfpControlLogic> sfpLogic)
{
	// use the common port handling factory
	return RrhCpriPortHandler::factory(port, sfpLogic) ;
}

//-------------------------------------------------------------------------------------------------------------
// Common CPRI controller singleton
std::shared_ptr<ICpriController> ICpriController::getInterface()
{
    return CpriController::getInterface();
}
