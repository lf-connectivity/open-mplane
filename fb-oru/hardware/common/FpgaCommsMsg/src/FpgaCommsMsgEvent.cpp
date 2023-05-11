/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsMsgEvent.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "stringfunc.hpp"
#include "FpgaCommsMsgEvent.h"

using namespace Mplane;



//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgEvent::FpgaCommsMsgEvent(std::shared_ptr<IFpgaMsgTokens> tokens, std::shared_ptr<IFpgaPdu> pdu) :
	FpgaCommsMsgBase(tokens, pdu)
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgEvent::FpgaCommsMsgEvent(std::shared_ptr<IFpgaMsgTokens> tokens, const IFpgaPdu& pdu) :
	FpgaCommsMsgBase(tokens, pdu)
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgEvent::~FpgaCommsMsgEvent()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string FpgaCommsMsgEvent::toString() const
{
	// Need to convert tokens
	std::string pduData(getPduData()) ;
	unsigned dataPos{0} ;

	// convert the data into a string
	std::string str(toTokenString(pduData, dataPos)) ;
	return trim_right(str) ;
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, DataVariant> FpgaCommsMsgEvent::getAttributes() const
{
	std::string pduData(getPduData()) ;
	unsigned dataPos{0} ;

	return getTokenAttributes(pduData, dataPos) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================


//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
