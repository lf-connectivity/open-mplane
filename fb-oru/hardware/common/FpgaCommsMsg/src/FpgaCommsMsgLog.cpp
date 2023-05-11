/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsMsgLog.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "FpgaCommsMsgLog.h"

using namespace Mplane;



//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgLog::FpgaCommsMsgLog(std::shared_ptr<IFpgaMsgTokens> tokens, std::shared_ptr<IFpgaPdu> pdu) :
	// Use the text-only variant of the constructor
	FpgaCommsMsgBase(tokens, pdu, true)
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgLog::FpgaCommsMsgLog(std::shared_ptr<IFpgaMsgTokens> tokens, const IFpgaPdu& pdu) :
	// Use the text-only variant of the constructor
	FpgaCommsMsgBase(tokens, pdu, true)
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgLog::~FpgaCommsMsgLog()
{
}
