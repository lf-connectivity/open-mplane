/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DelaysMgrSingleton.hpp
 * \brief     Convenience header
 *
 *
 * \details   Creates the singleton for IDelaysMgr using DelaysMgr - use in testbenches
 *
 */


#ifndef DELAYSMGRSINGLETON_H_
#define DELAYSMGRSINGLETON_H_

#include "DelaysMgr.h"

using namespace Mplane ;

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IDelaysMgr> IDelaysMgr::getInterface()
{
	return DelaysMgr::getInstance() ;
}


#endif /* DELAYSMGRSINGLETON_H_ */
