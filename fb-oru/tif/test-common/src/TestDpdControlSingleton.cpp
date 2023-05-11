/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestDpdControlSingleton.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <IDpdControl.h>
#include <memory>
#include "TestDpdControl.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IDpdControl> IDpdControl::getInterface()
{
static std::shared_ptr<IDpdControl> interface(std::make_shared<TestDpdControl>());

	return interface ;
}
