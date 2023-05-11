/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestFpgaCommsMsgFactory.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "IFpgaMsg.h"
#include "TestFpgaCommsMsg.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaMsg> IFpgaMsg::factory(std::shared_ptr<IFpgaPdu> pdu)
{
	return std::make_shared<TestFpgaCommsMsg>() ;
}

std::shared_ptr<IFpgaMsg> IFpgaMsg::factory(const IFpgaPdu& pdu)
{
	return std::make_shared<TestFpgaCommsMsg>() ;
}

std::shared_ptr<IFpgaMsg> IFpgaMsg::factory(const std::string& cmd,
		const std::vector<DataVariant>& attributes,
		const std::set<std::string>& varNames)
{
	return std::make_shared<TestFpgaCommsMsg>() ;
}

std::shared_ptr<IFpgaMsg> IFpgaMsg::factory(unsigned msgId, const std::vector<DataVariant>& attributes)
{
	return std::make_shared<TestFpgaCommsMsg>() ;
}
