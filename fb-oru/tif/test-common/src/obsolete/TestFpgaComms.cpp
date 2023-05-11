/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestFpgaComms.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "TestFpgaMsgTokens.h"

#include "TestFpgaComms.h"

using namespace Mplane;

Mplane::TestFpgaComms::TestFpgaComms() {
}

Mplane::TestFpgaComms::~TestFpgaComms() {
}

std::shared_ptr<IFpgaMsgTokens> Mplane::TestFpgaComms::getTokens() const {
	std::shared_ptr<IFpgaMsgTokens> tokens(std::make_shared<TestFpgaMsgTokens>()) ;
	return tokens ;
}

int Mplane::TestFpgaComms::enumToInt(const std::string& name) const {
	return -1 ;
}

bool Mplane::TestFpgaComms::commandWaitResponse(std::shared_ptr<IFpgaMsg> msg,
		std::shared_ptr<IFpgaMsg>& response, std::string& failReason) {
	response = IFpgaMsg::factory("dummy") ;
	return false ;
}

bool Mplane::TestFpgaComms::commandDontWaitResponse(std::shared_ptr<IFpgaMsg> msg,
		std::string& failReason) {
	return false ;
}

bool Mplane::TestFpgaComms::checkApiVersion(std::shared_ptr<IFpgaMsg> msg) {
	return false ;
}

unsigned Mplane::TestFpgaComms::getApiVersion() {
	return 0 ;
}

bool Mplane::TestFpgaComms::command(const IFpgaMsg& msg,
		std::string& failReason) {
	return true ;
}

bool Mplane::TestFpgaComms::command(std::shared_ptr<IFpgaMsg> msg,
		std::string& failReason) {
	return false ;
}

std::vector<std::pair<std::string, UINT16> > Mplane::TestFpgaComms::statusValues() {
	return std::vector<std::pair<std::string, UINT16> >() ;
}

bool Mplane::TestFpgaComms::registerMsgHandler(
		IFpgaPdu::PduDataType PduDataType, void* const object,
		MsgHandler handler, MsgCreator creator, std::string& failReason) {
	return true ;
}

void Mplane::TestFpgaComms::unRegisterMsgHandler(
		IFpgaPdu::PduDataType PduDataType, void* const object) {
}

void Mplane::TestFpgaComms::setLogging(IFpgaPdu::PduDataType PduDataType,
		bool logEnable) {
}

bool Mplane::TestFpgaComms::getLogging(
		IFpgaPdu::PduDataType PduDataType) const {
	return true ;
}

int Mplane::TestFpgaComms::start() {
	return 0 ;
}

int Mplane::TestFpgaComms::stop() {
	return 0 ;
}

bool Mplane::TestFpgaComms::isRunning() {
	return true ;
}

void Mplane::TestFpgaComms::show() {
}
//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
