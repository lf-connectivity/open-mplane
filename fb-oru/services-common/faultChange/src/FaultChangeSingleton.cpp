/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FaultChangeSingleton.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "IFaultChange.h"
#include "FaultChange.h"


using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFaultChange> IFaultChange::getInstance( void )
{
	static std::shared_ptr<IFaultChange> instance(new FaultChange()) ;

	return instance ;
}
