/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsMsg.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sstream>

#include "FpgaCommsMsgCmd.h"
#include "FpgaCommsMsgReply.h"
#include "FpgaCommsMsgEvent.h"
#include "FpgaCommsMsgLog.h"
#include "FpgaCommsMsgMatlab.h"
#include "FpgaCommsMsgText.h"

#include "IFpgaMsg.h"
#include "FpgaCommsMsgFactory.h"

using namespace Mplane;


//=============================================================================================================
// FACTORY
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaMsg> FpgaCommsMsgFactory::factory(std::shared_ptr<IFpgaMsgTokens> tokens,
		std::shared_ptr<IFpgaPdu> pdu)
{
	return FpgaCommsMsgFactory::factory(tokens, *pdu) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaMsg> FpgaCommsMsgFactory::factory(std::shared_ptr<IFpgaMsgTokens> tokens,
		const IFpgaPdu& pdu)
{
	switch (pdu.getType())
	{
	case IFpgaPdu::PduDataType::PDU_TYPE_CMD :
		return std::make_shared<FpgaCommsMsgCmd>(tokens, pdu) ;
		break ;
	case IFpgaPdu::PduDataType::PDU_TYPE_REPLY :
		return std::make_shared<FpgaCommsMsgReply>(tokens, pdu) ;
		break ;
	case IFpgaPdu::PduDataType::PDU_TYPE_EVENT :
		return std::make_shared<FpgaCommsMsgEvent>(tokens, pdu) ;
		break ;
	case IFpgaPdu::PduDataType::PDU_TYPE_LOG :
		return std::make_shared<FpgaCommsMsgLog>(tokens, pdu) ;
		break ;
	case IFpgaPdu::PduDataType::PDU_TYPE_MATLAB :
		return std::make_shared<FpgaCommsMsgMatlab>(tokens, pdu) ;
		break ;
	case IFpgaPdu::PduDataType::PDU_TYPE_TEXT :
		return std::make_shared<FpgaCommsMsgText>(tokens, pdu) ;
		break ;
	default:
		return std::shared_ptr<IFpgaMsg>() ;
		break ;
	}

	return std::shared_ptr<IFpgaMsg>() ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaMsg> FpgaCommsMsgFactory::factory(std::shared_ptr<IFpgaMsgTokens> tokens,
		const std::string& cmd,
		const std::vector<DataVariant>& attributes,
		const std::set<std::string>& varNames)
{
	return std::make_shared<FpgaCommsMsgCmd>(tokens, cmd, attributes, varNames) ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaMsg> FpgaCommsMsgFactory::factory(std::shared_ptr<IFpgaMsgTokens> tokens,
		unsigned msgId, const std::vector<DataVariant>& attributes)
{
	return std::make_shared<FpgaCommsMsgReply>(tokens, msgId, attributes) ;
}
