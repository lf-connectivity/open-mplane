/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdMsgFactory.cpp
 * \brief     Factory for creating new DPD-specific messages
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sstream>

#include "FpgaCommsMsgFactory.h"
#include "TestTokens.h"

using namespace Mplane;


//=============================================================================================================
// FACTORY
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaMsg> IFpgaMsg::factory(std::shared_ptr<IFpgaPdu> pdu)
{
	std::shared_ptr<IFpgaMsgTokens> tokens(TestTokens::getInterface()) ;
	return FpgaCommsMsgFactory::factory(tokens, pdu) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaMsg> IFpgaMsg::factory(const IFpgaPdu& pdu)
{
	std::shared_ptr<IFpgaMsgTokens> tokens(TestTokens::getInterface()) ;
	return FpgaCommsMsgFactory::factory(tokens, pdu) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaMsg> IFpgaMsg::factory(const std::string& cmd,
		const std::vector<DataVariant>& attributes,
		const std::set<std::string>& varNames)
{
	std::shared_ptr<IFpgaMsgTokens> tokens(TestTokens::getInterface()) ;
//std::cerr << "IFpgaMsg::factory cmd=" << cmd << std::endl ;
//std::cerr << "Attributes:" << std::endl ;
//for (auto attr : attributes)
//{
//	std::cerr << " " << attr.getTypeStr() << " " << attr.getName() << "=" << attr.toString() << std::endl ;
//}
//std::cerr << "Variables:" << std::endl ;
//for (auto var : varNames)
//{
//	std::cerr << " " << var << std::endl ;
//}

	return FpgaCommsMsgFactory::factory(tokens, cmd, attributes, varNames) ;
}
