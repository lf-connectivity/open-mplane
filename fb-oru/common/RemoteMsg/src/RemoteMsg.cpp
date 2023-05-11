/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RemoteMsg.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "RemoteMsg.h"


//=============================================================================================================
// PUBLIC
//=============================================================================================================
std::mutex RemoteMsgHeader::mCountMutex ;
uint32_t RemoteMsgHeader::mCount = 0 ;

//-------------------------------------------------------------------------------------------------------------
uint32_t RemoteMsgHeader::newMsgCount()
{
	std::unique_lock<std::mutex> lock(RemoteMsgHeader::mCountMutex) ;
	return RemoteMsgHeader::mCount++ ;
}


