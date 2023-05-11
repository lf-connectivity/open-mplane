/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      EcbEuropaSystemClockInputSingleton.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TestSystemClockInput.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISystemClockInput> ISystemClockInput::getInstance()
{
	// Default on EUROPA is set to select fibre
	static std::shared_ptr<ISystemClockInput> instance(std::make_shared<TestSystemClockInput>(ISystemClockInput::CLKIN_FIBRE)) ;
	return instance ;
}
