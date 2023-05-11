/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AisgCommand.cpp
 * \brief     Stores details regarding a particular Aisg command
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "AisgCommand.h"


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::AisgCommand::AisgCommand(unsigned char id, unsigned long timeout, respCallback cb) :
	mId(id),
	mTimeout(timeout),
	mRespCb(cb)
{
}

//-------------------------------------------------------------------------------------------------------------
unsigned char Mplane::AisgCommand::getCommndId(void)
{
	return mId;
}

//-------------------------------------------------------------------------------------------------------------
unsigned long Mplane::AisgCommand::getCommandTimeout(void)
{
	return mTimeout;
}

//-------------------------------------------------------------------------------------------------------------
Mplane::AisgCommand::respCallback Mplane::AisgCommand::getResponseCallback(void)
{
	return mRespCb;
}
