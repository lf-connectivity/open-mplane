/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AtlasUsedTestInterface.cpp
 * \brief     Test interface for Atlas
 *
 *
 * \details   Hand-generated to pull in the correct TIF for the current build
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "AtlasTestInterface.h"

#ifdef BUILD_IF_CPRI
#include "AtlasCpriTestHandler.h"
#endif

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
AtlasTestInterface::AtlasTestInterface()
{
#ifdef BUILD_IF_CPRI
	AtlasCpriTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;
#endif

}

//-------------------------------------------------------------------------------------------------------------
AtlasTestInterface::~AtlasTestInterface()
{
}
