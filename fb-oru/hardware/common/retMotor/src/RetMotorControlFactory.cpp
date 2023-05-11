/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RetMotorControlFactory.cpp
 * \brief     Factory for creating singleton instance of Motor control
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IRetMotorControl.h"
#include <memory>

#include "RetMotorControl.h"

using namespace Mplane;

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRetMotorControl> IRetMotorControl::getInstance(void)
{
    static std::shared_ptr<IRetMotorControl> _instance =
    		std::dynamic_pointer_cast<IRetMotorControl>(std::make_shared<RetMotorControl>());

	return _instance;
}
