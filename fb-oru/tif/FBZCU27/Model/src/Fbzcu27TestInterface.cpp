/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Fbzcu27TestInterface.cpp
 * \brief     Test interface for Fbzcu27
 *
 *
 * \details   Auto-generated by gentool. Contains test interface definitions.
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "Fbzcu27TestInterface.h"

#include "Fbzcu27CpriTestHandler.h"


using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Fbzcu27TestInterface::Fbzcu27TestInterface()
{
	Fbzcu27CpriTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;


}

//-------------------------------------------------------------------------------------------------------------
Fbzcu27TestInterface::~Fbzcu27TestInterface()
{
}
