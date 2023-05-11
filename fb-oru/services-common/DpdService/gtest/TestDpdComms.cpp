/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestDpdComms.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IFpgaPdu.h"
#include "IFpgaMsgTokens.h"

#include "DataVariantList.h"
#include "FpgaPdu.h"
#include "FpgaCommsMsgFactory.h"


#include "TestTokens.h"
#include "TestDpdComms.h"

using namespace Mplane;

Mplane::TestDpdComms::TestDpdComms() :
	mHandlers({
		{PduDataType::PDU_TYPE_NONE, 		{}},
		{PduDataType::PDU_TYPE_CMD, 		{}},
		{PduDataType::PDU_TYPE_REPLY, 		{}},
		{PduDataType::PDU_TYPE_EVENT, 		{}},
		{PduDataType::PDU_TYPE_LOG, 		{}},
		{PduDataType::PDU_TYPE_MATLAB,		{}},
		{PduDataType::PDU_TYPE_TEXT, 		{}},
	})
{

}

Mplane::TestDpdComms::~TestDpdComms() {
}

std::shared_ptr<IFpgaMsgTokens> Mplane::TestDpdComms::getTokens() const {
	std::shared_ptr<IFpgaMsgTokens> tokens(std::make_shared<TestTokens>()) ;
	return tokens ;
}

int Mplane::TestDpdComms::enumToInt(const std::string& name) const {
	return -1 ;
}

bool Mplane::TestDpdComms::commandWaitResponse(std::shared_ptr<IFpgaMsg> msg,
		std::shared_ptr<IFpgaMsg>& response, std::string& failReason)
{
	// save last sent command message
	std::vector<UINT8> bytes(msg->getPdu()->getDataBytes()) ;
//	std::vector<UINT8> bytesData(bytes.begin()+2, bytes.end()) ;
	FpgaPdu pdu(msg->getType(), bytes) ;
	mLastCommand = FpgaCommsMsgFactory::factory(getTokens(), pdu) ;

	// should always be a 'set' command - just use it as a dummy response
	response = IFpgaMsg::factory("set") ;
	return true ;
}

bool Mplane::TestDpdComms::commandDontWaitResponse(std::shared_ptr<IFpgaMsg> msg,
		std::string& failReason)
{
	// save last sent command message
	std::vector<UINT8> bytes(msg->getPdu()->getDataBytes()) ;
//	std::vector<UINT8> bytesData(bytes.begin()+2, bytes.end()) ;
	FpgaPdu pdu(msg->getType(), bytes) ;
	mLastCommand = FpgaCommsMsgFactory::factory(getTokens(), pdu) ;

	return true ;
}

bool Mplane::TestDpdComms::checkApiVersion(std::shared_ptr<IFpgaMsg> msg) {
	return false ;
}

unsigned Mplane::TestDpdComms::getApiVersion() {
	return 0 ;
}

bool Mplane::TestDpdComms::command(const IFpgaMsg& msg,
		std::string& failReason) {
	return true ;
}

bool Mplane::TestDpdComms::command(std::shared_ptr<IFpgaMsg> msg,
		std::string& failReason) {
	return false ;
}

std::vector<std::pair<std::string, UINT16> > Mplane::TestDpdComms::statusValues() {
	return std::vector<std::pair<std::string, UINT16> >() ;
}

bool Mplane::TestDpdComms::registerMsgHandler(IFpgaPdu::PduDataType dataType, void* const object,
		MsgHandler handler, MsgCreator creator, std::string& failReason)
{
	if (!handler || !creator)
	{
		throw std::invalid_argument("Must specify valid handler/creator functions") ;
		return false ;
	}

	auto entry(mHandlers[dataType].find(object)) ;
	if (entry != mHandlers[dataType].end())
	{
		entry->second = HandlerStruct(handler, creator) ;
	}
	else
	{
		mHandlers[dataType][object] = HandlerStruct(handler, creator) ;
	}
	return true ;
}

void Mplane::TestDpdComms::unRegisterMsgHandler(IFpgaPdu::PduDataType dataType, void* const object)
{
	auto entry(mHandlers[dataType].find(object)) ;
	if (entry != mHandlers[dataType].end())
		mHandlers[dataType].erase(entry) ;
}

void Mplane::TestDpdComms::setLogging(IFpgaPdu::PduDataType PduDataType,
		bool logEnable) {
}

bool Mplane::TestDpdComms::getLogging(
		IFpgaPdu::PduDataType PduDataType) const {
	return true ;
}

int Mplane::TestDpdComms::start() {
	return 0 ;
}

int Mplane::TestDpdComms::stop() {
	return 0 ;
}

bool Mplane::TestDpdComms::isRunning() {
	return true ;
}

void Mplane::TestDpdComms::show() {
}


//=============================================================================================================
// TEST INTERFACE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Mplane::TestDpdComms::emulateRxMsg(std::shared_ptr<IFpgaMsg> msg)
{
	FpgaPdu::PduDataType dataType( msg->getType() ) ;

	// propogate to handlers
	for (auto entry : mHandlers[dataType])
	{
		entry.second.mHandler( entry.second.mCreator(*(msg->getPdu())) ) ;
	}


}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaMsg> Mplane::TestDpdComms::createMsg(IFpgaPdu::PduDataType type, const std::string& args)
{
	std::shared_ptr<IFpgaMsgTokens> tokens(getTokens()) ;

	// create a dummy command message using the tokens and args
	DataVariantList dvl(args.c_str()) ;
	std::shared_ptr<IFpgaMsg> cmdMsg( FpgaCommsMsgFactory::factory(tokens, "set", dvl.getList()) ) ;

	// get the message PDU bytes and drop the command word (first 2 bytes)
	std::vector<UINT8> bytes(cmdMsg->getPdu()->getDataBytes()) ;
	std::vector<UINT8> bytesData(bytes.begin()+2, bytes.end()) ;

	// create a PDU of the specified type using the bytes
	FpgaPdu pdu(type, bytesData) ;

	// Now create the messsage
	std::shared_ptr<IFpgaMsg> msg(FpgaCommsMsgFactory::factory(tokens, pdu)) ;

	return msg ;
}
