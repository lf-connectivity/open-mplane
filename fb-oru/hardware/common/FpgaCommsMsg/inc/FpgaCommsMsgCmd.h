/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsMsgCmd.h
 * \brief     A FpgaCommsMsg specifically handling RESPONSE types
 *
 *
 * \details
 *
 */


#ifndef FpgaCommsMSGCMD_H_
#define FpgaCommsMSGCMD_H_

#include "FpgaCommsMsgBase.h"

namespace Mplane {

class FpgaCommsMsgCmd : public FpgaCommsMsgBase
{
public:
	/**
	 * Construct a message from a command and a map of attribute key/value pairs
	 *
	 * @param cmd	Command type to create
	 * @param attributes	map of key/value pairs to use with the command
	 * @param varNames	[optional] set of variable names to use with command (used with 'get' command etc)
	 *
	 */
	FpgaCommsMsgCmd(std::shared_ptr<IFpgaMsgTokens> tokens,
			const std::string& cmd,
			const std::vector<DataVariant>& attributes = std::vector<DataVariant>{},
			const std::set<std::string>& varNames = std::set<std::string>()) ;


	/**
	 * Construct a message from a log/event/response PDU. Converts all token values into token strings
	 *
	 * @param pdu
	 */
	FpgaCommsMsgCmd(std::shared_ptr<IFpgaMsgTokens> tokens, std::shared_ptr<IFpgaPdu> pdu) ;

	/**
	 * Construct a message from a log/event/response PDU. Converts all token values into token strings
	 *
	 * @param pdu
	 */
	FpgaCommsMsgCmd(std::shared_ptr<IFpgaMsgTokens> tokens, const IFpgaPdu& pdu) ;

	/**
	 * Destructor
	 */
	virtual ~FpgaCommsMsgCmd() ;

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

} ;

}

#endif /* FpgaCommsMSGCMD_H_ */
