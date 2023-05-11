/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsMsgText.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "FpgaCommsMsgText.h"

using namespace Mplane;



//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgText::FpgaCommsMsgText(std::shared_ptr<IFpgaMsgTokens> tokens, std::shared_ptr<IFpgaPdu> pdu) :
	// Use the text-only variant of the constructor
	FpgaCommsMsgBase(tokens, pdu, true)
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgText::FpgaCommsMsgText(std::shared_ptr<IFpgaMsgTokens> tokens, const IFpgaPdu& pdu) :
	// Use the text-only variant of the constructor
	FpgaCommsMsgBase(tokens, pdu, true)
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgText::~FpgaCommsMsgText()
{
}
