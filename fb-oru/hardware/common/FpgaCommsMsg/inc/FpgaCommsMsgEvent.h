/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsMsgEvent.h
 * \brief     A FpgaCommsMsg specifically handling EVENT types
 *
 *
 * \details
 *
 */


#ifndef FpgaCommsMSGEVENT_H_
#define FpgaCommsMSGEVENT_H_

#include "FpgaCommsMsgBase.h"

namespace Mplane {

class FpgaCommsMsgEvent : public FpgaCommsMsgBase
{
public:
	/**
	 * Construct a message from a log/event/response PDU. Converts all token values into token strings
	 *
	 * @param pdu
	 */
	FpgaCommsMsgEvent(std::shared_ptr<IFpgaMsgTokens> tokens, std::shared_ptr<IFpgaPdu> pdu) ;

	/**
	 * Construct a message from a log/event/response PDU. Converts all token values into token strings
	 *
	 * @param pdu
	 */
	FpgaCommsMsgEvent(std::shared_ptr<IFpgaMsgTokens> tokens, const IFpgaPdu& pdu) ;

	/**
	 * Destructor
	 */
	virtual ~FpgaCommsMsgEvent() ;

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
	/**
	 * Construct a message from a command and a map of attribute key/value pairs
	 *
	 * @param cmd	Command type to create
	 * @param attributes	map of key/value pairs to use with the command
	 * @param varNames	[optional] set of variable names to use with command (used with 'get' command etc)
	 *
	 */
	FpgaCommsMsgEvent(std::shared_ptr<IFpgaMsgTokens> tokens,
			const std::string& cmd,
			const std::map<std::string, int>& attributes = std::map<std::string, int>{},
			const std::set<std::string>& varNames = std::set<std::string>()) ;

} ;

}

#endif /* FpgaCommsMSGEVENT_H_ */
