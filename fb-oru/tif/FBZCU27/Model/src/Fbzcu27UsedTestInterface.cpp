/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Fbzcu27UsedTestInterface.cpp
 * \brief     Test interface for Fbzcu27
 *
 *
 * \details   Hand-generated to pull in the correct TIF for the current build
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "Fbzcu27TestInterface.h"

#ifdef BUILD_IF_CPRI
#include "Fbzcu27CpriTestHandler.h"
#endif

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Fbzcu27TestInterface::Fbzcu27TestInterface()
{
#ifdef BUILD_IF_CPRI
	Fbzcu27CpriTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;
#endif

}

//-------------------------------------------------------------------------------------------------------------
Fbzcu27TestInterface::~Fbzcu27TestInterface()
{
}
