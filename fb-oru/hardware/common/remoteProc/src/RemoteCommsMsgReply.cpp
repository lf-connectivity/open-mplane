/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RemoteCommsMsgReply.cpp
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
#include "RemoteCommsMsgReply.h"

using namespace Mplane;



//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RemoteCommsMsgReply::RemoteCommsMsgReply(std::shared_ptr<IFpgaMsgTokens> tokens, std::shared_ptr<IFpgaPdu> pdu) :
	RemoteCommsMsgBase(tokens, pdu)
{
	setAck( ackFromPdu(*pdu) ) ;
}

//-------------------------------------------------------------------------------------------------------------
RemoteCommsMsgReply::RemoteCommsMsgReply(std::shared_ptr<IFpgaMsgTokens> tokens, const IFpgaPdu& pdu) :
	RemoteCommsMsgBase(tokens, pdu)
{
	setAck( ackFromPdu(pdu) ) ;
}

//-------------------------------------------------------------------------------------------------------------
RemoteCommsMsgReply::RemoteCommsMsgReply(std::shared_ptr<IFpgaMsgTokens> tokens,
		unsigned msgId,
		const std::vector<DataVariant>& attributes) :
	RemoteCommsMsgBase(tokens, msgId, attributes)
{
	setAck( ackFromPdu( *getPdu() ) ) ;
}

//-------------------------------------------------------------------------------------------------------------
RemoteCommsMsgReply::~RemoteCommsMsgReply()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string RemoteCommsMsgReply::toString() const
{
	// Need to convert tokens
	std::string pduData(getPduData()) ;
	unsigned dataPos{0} ;

	// convert the data into a string
	std::string str(toTokenString(pduData, dataPos)) ;
	return trim_right(str) ;
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, DataVariant> RemoteCommsMsgReply::getAttributes() const
{
	std::string pduData(getPduData()) ;
	unsigned dataPos{0} ;

	return getTokenAttributes(pduData, dataPos) ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool RemoteCommsMsgReply::ackFromPdu(const IFpgaPdu& pdu)
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
