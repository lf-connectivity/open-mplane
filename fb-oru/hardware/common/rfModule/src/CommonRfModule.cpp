/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRfModule.cpp
 * \brief     Implementation of methods defined in the CommonRfModule class
 *
 *
 * \details   Implementation of methods defined in the CommonRfModule class
 *
 */

#include <string.h>

#include "GlobalTypeDefs.h"
#include "CommonRfModule.h"
#include "Loggable.h"

namespace Mplane
{

//-------------------------------------------------------------------------------------------------------------
bool Mplane::CommonRfModule::setSwitch(unsigned sw, bool enable)
{
	throw( std::out_of_range("setSwitch() not implemented in base class") );
	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::CommonRfModule::getSwitch(unsigned sw)
{
	throw( std::out_of_range("getSwitch() not implemented in base class") );
	return false;
}

}
