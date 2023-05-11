/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111UsedTestInterface.cpp
 * \brief     Test interface for ZCU111
 *
 *
 * \details   Hand-generated to pull in the correct TIF for the current build
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "Zcu111TestInterface.h"

#ifdef BUILD_IF_CPRI
#include "Zcu111CpriTestHandler.h"
#endif

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111TestInterface::Zcu111TestInterface()
{
#ifdef BUILD_IF_CPRI
	Zcu111CpriTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;
#endif

}

//-------------------------------------------------------------------------------------------------------------
Zcu111TestInterface::~Zcu111TestInterface()
{
}
