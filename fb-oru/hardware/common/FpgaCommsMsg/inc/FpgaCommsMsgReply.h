/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsMsgReply.h
 * \brief     A FpgaCommsMsg specifically handling REPLY types
 *
 *
 * \details
 *
 */


#ifndef FpgaCommsMSGREPLY_H_
#define FpgaCommsMSGREPLY_H_

#include "FpgaCommsMsgBase.h"

namespace Mplane {

class FpgaCommsMsgReply : public FpgaCommsMsgBase
{
public:
	/**
	 * Construct a message from a log/event/response PDU. Converts all token values into token strings
	 *
	 * @param pdu
	 */
	FpgaCommsMsgReply(std::shared_ptr<IFpgaMsgTokens> tokens, std::shared_ptr<IFpgaPdu> pdu) ;

	/**
	 * Construct a message from a log/event/response PDU. Converts all token values into token strings
	 *
	 * @param pdu
	 */
	FpgaCommsMsgReply(std::shared_ptr<IFpgaMsgTokens> tokens, const IFpgaPdu& pdu) ;

	/**
	 * Construct a new reply message
	 *
	 * @param msgId		Message ID of the command we're replying to
	 * @param attributes	map of key/value pairs to use with the reply
	 *
	 */
	FpgaCommsMsgReply(std::shared_ptr<IFpgaMsgTokens> tokens,
			unsigned msgId,
			const std::vector<DataVariant>& attributes = std::vector<DataVariant>{}) ;

	/**
	 * Destructor
	 */
	virtual ~FpgaCommsMsgReply() ;

	/**
	 * Converts the message data into a string. For response types this converts any token values into strings
	 * and any enumerated type values into enumerations.
	 *
	 * @return string representation of message
	 */
	virtual std::string toString() const override ;

	/**
	 * Extract the var=value pairs from the message
	 * @return map of var=value pairs
	 */
	virtual std::map<std::string, DataVariant> getAttributes() const override ;


private:
	bool ackFromPdu(const IFpgaPdu& pdu) ;

	/**
	 * Construct a message from a command and a map of attribute key/value pairs
	 *
	 * @param cmd	Command type to create
	 * @param attributes	map of key/value pairs to use with the command
	 * @param varNames	[optional] set of variable names to use with command (used with 'get' command etc)
	 *
	 */
	FpgaCommsMsgReply(std::shared_ptr<IFpgaMsgTokens> tokens,
			const std::string& cmd,
			const std::map<std::string, int>& attributes = std::map<std::string, int>{},
			const std::set<std::string>& varNames = std::set<std::string>()) ;

} ;

}

#endif /* FpgaCommsMSGREPLY_H_ */
