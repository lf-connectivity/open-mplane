/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRxAttenuatorsFactory.cpp
 * \brief     Get the IRxAttenuators singleton
 *
 *
 * \details   We will always use the IRxPort instance so we can make this a common factory for all applications
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "IRxAttenuators.h"
#include "IRxPort.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRxAttenuators> IRxAttenuators::getInstance(unsigned port)
{
	static  std::vector< std::shared_ptr<IRxPort> > rxPorts(IRxPortFactory::getPorts());
	return std::dynamic_pointer_cast<IRxAttenuators>(rxPorts[port]) ;
}
