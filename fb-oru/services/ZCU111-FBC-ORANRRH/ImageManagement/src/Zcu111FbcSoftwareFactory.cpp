/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcSoftwareFactory.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "SoftwareSlotMgr.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISoftwareSlotMgr> ISoftwareSlotMgr::singleton()
{
	// Allow for 8 slots
	static std::shared_ptr<ISoftwareSlotMgr> instance(std::make_shared<SoftwareSlotMgr>(8)) ;
	return instance ;
}
