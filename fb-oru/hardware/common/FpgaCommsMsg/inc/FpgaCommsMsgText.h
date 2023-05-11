/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsMsgText.h
 * \brief     A FpgaCommsMsg specifically handling LOG types
 *
 *
 * \details
 *
 */


#ifndef FpgaCommsMSGTEXT_H_
#define FpgaCommsMSGTEXT_H_


#include "FpgaCommsMsgBase.h"

namespace Mplane {

class FpgaCommsMsgText : public FpgaCommsMsgBase
{
public:
	/**
	 * Construct a message from a log/event/response PDU. Converts all token values into token strings
	 *
	 * @param pdu
	 */
	FpgaCommsMsgText(std::shared_ptr<IFpgaMsgTokens> tokens, std::shared_ptr<IFpgaPdu> pdu) ;

	/**
	 * Construct a message from a log/event/response PDU. Converts all token values into token strings
	 *
	 * @param pdu
	 */
	FpgaCommsMsgText(std::shared_ptr<IFpgaMsgTokens> tokens, const IFpgaPdu& pdu) ;

	/**
	 * Destructor
	 */
	virtual ~FpgaCommsMsgText() ;

private:
	/**
	 * Construct a message from a command and a map of attribute key/value pairs
	 *
	 * @param cmd	Command type to create
	 * @param attributes	map of key/value pairs to use with the command
	 * @param varNames	[optional] set of variable names to use with command (used with 'get' command etc)
	 *
	 */
	FpgaCommsMsgText(std::shared_ptr<IFpgaMsgTokens> tokens,
			const std::string& cmd,
			const std::map<std::string, int>& attributes = std::map<std::string, int>{},
			const std::set<std::string>& varNames = std::set<std::string>()) ;

} ;

}

#endif /* FpgaCommsMSGTEXT_H_ */
