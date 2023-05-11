/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BootEnvSingleton.cpp
 * \brief     u-boot environment for testing
 *
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "BootEnv.h"

using namespace Mplane;


//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IBootEnv> IBootEnv::getInstance()
{
	return BootEnv::getInstance() ;
}
