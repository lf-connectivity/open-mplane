/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DummyRemoteMsgHandler.cpp
 * \brief     Used when feature DPD2=NONE
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "IRemoteMsgHandler.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRemoteMsgHandler> IRemoteMsgHandler::factory(unsigned remoteId)
{
	return std::shared_ptr<IRemoteMsgHandler>() ;
}
