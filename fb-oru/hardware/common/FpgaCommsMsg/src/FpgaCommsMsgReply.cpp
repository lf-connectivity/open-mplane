/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsMsgReply.cpp
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
#include "FpgaCommsMsgReply.h"

using namespace Mplane;



//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgReply::FpgaCommsMsgReply(std::shared_ptr<IFpgaMsgTokens> tokens, std::shared_ptr<IFpgaPdu> pdu) :
	FpgaCommsMsgBase(tokens, pdu)
{
	setAck( ackFromPdu(*pdu) ) ;
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgReply::FpgaCommsMsgReply(std::shared_ptr<IFpgaMsgTokens> tokens, const IFpgaPdu& pdu) :
	FpgaCommsMsgBase(tokens, pdu)
{
	setAck( ackFromPdu(pdu) ) ;
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgReply::FpgaCommsMsgReply(std::shared_ptr<IFpgaMsgTokens> tokens,
		unsigned msgId,
		const std::vector<DataVariant>& attributes) :
	FpgaCommsMsgBase(tokens, msgId, attributes)
{
	setAck( ackFromPdu( *getPdu() ) ) ;
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgReply::~FpgaCommsMsgReply()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string FpgaCommsMsgReply::toString() const
{
	// Need to convert tokens
	std::string pduData(getPduData()) ;
	unsigned dataPos{0} ;

	// convert the data into a string
	std::string str(toTokenString(pduData, dataPos)) ;
	return trim_right(str) ;
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, DataVariant> FpgaCommsMsgReply::getAttributes() const
{
	std::string pduData(getPduData()) ;
	unsigned dataPos{0} ;

	return getTokenAttributes(pduData, dataPos) ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsMsgReply::ackFromPdu(const IFpgaPdu& pdu)
{
	// Find response and see if it's ack
	std::string pduData(getPduData()) ;
	try {
		unsigned dataPos{0} ;
		std::map<std::string, DataVariant> attributes(getTokenAttributes(pduData, dataPos)) ;
		if (attributes.find("response") == attributes.end())
			return false ;

		if (attributes["response"].toString() == "ACK")
			return true ;

	} catch(...) {
		return false ;
	}

	return false ;
}
