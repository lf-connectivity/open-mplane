/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranDelaysSingleton.cpp
 * \brief     Oran Delays singleton
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "IOranDelays.h"
#include "OranDelays.h"

using namespace Mplane;

// ====================================================================================================
std::shared_ptr<IOranDelays> IOranDelays::getOranDelaysSingleton(IOranDelays::DelayClock_T delayClock)
{
	static std::shared_ptr<IOranDelays> instance(std::make_shared<OranDelays>(delayClock)) ;
	return instance;
}
