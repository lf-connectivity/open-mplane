/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsMsgMatlab.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "FpgaCommsMsgMatlab.h"

using namespace Mplane;



//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgMatlab::FpgaCommsMsgMatlab(std::shared_ptr<IFpgaMsgTokens> tokens, std::shared_ptr<IFpgaPdu> pdu) :
	// Use the text-only variant of the constructor
	FpgaCommsMsgBase(tokens, pdu, true)
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgMatlab::FpgaCommsMsgMatlab(std::shared_ptr<IFpgaMsgTokens> tokens, const IFpgaPdu& pdu) :
	// Use the text-only variant of the constructor
	FpgaCommsMsgBase(tokens, pdu, true)
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgMatlab::~FpgaCommsMsgMatlab()
{
}
