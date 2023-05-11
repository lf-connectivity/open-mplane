/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsMsgFactory.h
 * \brief     Factory for creating FpgaCommsMsg classes
 *
 *
 * \details   This is actually just a helper class that helps out the real IFpgaMsg::factory() methods
 *
 */


#ifndef FPGACOMMSMSGFACTORY_H_
#define FPGACOMMSMSGFACTORY_H_

#include <memory>

#include "IFpgaMsgTokens.h"
#include "IFpgaMsg.h"
#include "IFpgaPdu.h"

namespace Mplane {

class FpgaCommsMsgFactory {
public:

	/**
	 * Factory from creating new instances
	 *
	 * @param pdu
	 */
	static std::shared_ptr<IFpgaMsg> factory(std::shared_ptr<IFpgaMsgTokens> tokens,
			std::shared_ptr<IFpgaPdu> pdu) ;

	/**
	 * Factory from creating new instances
	 *
	 * @param pdu
	 */
	static std::shared_ptr<IFpgaMsg> factory(std::shared_ptr<IFpgaMsgTokens> tokens,
			const IFpgaPdu& pdu) ;

	/**
	 * Factory from creating new instances
	 *
	 * @param cmd	Command type to create
	 * @param attributes	map of key/value pairs to use with the command
	 * @param varNames	[optional] set of variable names to use with command (used with 'get' command etc)
	 *
	 */
	static std::shared_ptr<IFpgaMsg> factory(std::shared_ptr<IFpgaMsgTokens> tokens,
			const std::string& cmd,
			const std::vector<DataVariant>& attributes = std::vector<DataVariant>{},
			const std::set<std::string>& varNames = std::set<std::string>{}) ;

	/**
	 * Factory from creating new reply instances
	 *
	 * @param msgId		Message ID of the command we're replying to
	 * @param attributes	map of key/value pairs to use with the reply
	 *
	 */
	static std::shared_ptr<IFpgaMsg> factory(std::shared_ptr<IFpgaMsgTokens> tokens,
			unsigned msgId,
			const std::vector<DataVariant>& attributes = std::vector<DataVariant>{}) ;


} ;

}

#endif /* FPGACOMMSMSGFACTORY_H_ */
