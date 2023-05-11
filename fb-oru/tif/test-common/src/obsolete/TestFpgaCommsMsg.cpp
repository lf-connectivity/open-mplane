/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestFpgaCommsMsg.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TestFpgaCommsMsg.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::TestFpgaCommsMsg::TestFpgaCommsMsg() :
	mCmd(""),
	mAttributes(),
	mVarNames()
{
}

Mplane::TestFpgaCommsMsg::~TestFpgaCommsMsg() {
}

IFpgaPdu::PduDataType Mplane::TestFpgaCommsMsg::getType() const {
	return IFpgaPdu::PDU_TYPE_NONE ;
}

std::shared_ptr<IFpgaPdu> Mplane::TestFpgaCommsMsg::getPdu() const {
	return std::shared_ptr<IFpgaPdu>() ;
}

std::string Mplane::TestFpgaCommsMsg::getPduData() const {
	return "" ;
}

void Mplane::TestFpgaCommsMsg::show(std::ostream& os) const {
}

unsigned Mplane::TestFpgaCommsMsg::getId() const {
	return 0 ;
}

bool Mplane::TestFpgaCommsMsg::isError() const {
	return false ;
}

std::string Mplane::TestFpgaCommsMsg::errorReason() const {
	return "" ;
}

std::string Mplane::TestFpgaCommsMsg::toString() const {
	std::string str(mCmd) ;
	if (!str.empty())
		str += " " ;
	for (auto attr : mAttributes)
	{
		str += attr.getNameValuePair() + " " ;
	}

	return str ;
}

bool Mplane::TestFpgaCommsMsg::isIdMatch(
		std::shared_ptr<IFpgaMsg>& msg) const {
	return true ;
}

std::string Mplane::TestFpgaCommsMsg::getStr() const {
	return "" ;
}

bool Mplane::TestFpgaCommsMsg::getAck() const {
	return true ;
}

std::map<std::string, DataVariant> Mplane::TestFpgaCommsMsg::getAttributes() const {
	std::map<std::string, DataVariant> attributes ;
	for (auto attr : mAttributes)
	{
		attributes[attr.getName()] = attr ;
	}
	return attributes ;
}

Mplane::TestFpgaCommsMsg::TestFpgaCommsMsg(const std::string& cmd,
		const std::vector<DataVariant>& attributes,
		const std::set<std::string>& varNames) :
	mCmd(cmd),
	mAttributes(attributes),
	mVarNames(varNames)
{
}
