/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsEmulator.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Tokeniser.h"
#include "ByteTransfer.hpp"

#include "ToUblazeEmu.h"
#include "FromUblazeEmu.h"
#include "FpgaCommsEmulator.h"

using namespace Mplane;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<FpgaCommsEmulator> Mplane::FpgaCommsEmulator::getInstance()
{
	// used for testing
	static std::shared_ptr<FpgaCommsEmulator> instance(new FpgaCommsEmulator(0xa00, 0x80/2, 0xa80, 0x160/2)) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaCommsEmulator::~FpgaCommsEmulator()
{
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsEmulator::bufferMsgs(bool buffer)
{
	mToUblaze->bufferMsgs(buffer) ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<CommsEmuMsg> Mplane::FpgaCommsEmulator::getMsgs()
{
	return mToUblaze->getMsgs() ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::FpgaCommsEmulator::sendMsg(const CommsEmuMsg& msg)
{
	return mFromUblaze->sendMsg(msg) ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::FpgaCommsEmulator::sendMsgs(const std::vector<CommsEmuMsg>& msgs)
{
	return mFromUblaze->sendMsgs(msgs) ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::FpgaCommsEmulator::sendInvalidPtr(UINT16 ptr)
{
	return mFromUblaze->sendInvalidPtr(ptr) ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::FpgaCommsEmulator::scheduleResponse(UINT16 command, const CommsEmuMsg& msg)
{
	Mutex::Lock lock(mMutex) ;
	if (mScheduledResponses.find(command) == mScheduledResponses.end())
		mScheduledResponses[command] = std::vector<CommsEmuMsg>() ;
	mScheduledResponses[command].push_back(msg) ;
	return true ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::FpgaCommsEmulator::FpgaCommsEmulator(unsigned toUblazeAddr, unsigned toUblazeLen,
		unsigned fromUblazeAddr, unsigned fromUblazeLen) :
	mToUblaze(new ToUblazeEmu(toUblazeAddr, toUblazeLen)),
	mFromUblaze(new FromUblazeEmu(fromUblazeAddr, fromUblazeLen))
{
	mToUblaze->start() ;
	mFromUblaze->start() ;

	// register handlers
	mToUblaze->setCallback([this](const CommsEmuMsg& msg){toUblazeMsgHandler(msg);}) ;

	std::cerr << "COMMS EMU created" << std::endl ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Mplane::FpgaCommsEmulator::toUblazeMsgHandler(const CommsEmuMsg& msg)
{
	// first word of PDU is command
	FpgaPdu pdu(msg.getPdu()) ;
	std::string msgStr(pdu.getData()) ;

	std::cerr << "FpgaCommsEmulator PPC -> uBlaze:" << std::endl ;
	ByteTransfer::dump(pdu.getDataBytes(), std::cerr) ;

	if (msgStr.size() < 2)
		return ;

	UINT16 command(
		((static_cast<UINT16>(msgStr[0]) & 0xff) << 8) |
		(static_cast<UINT16>(msgStr[1]) & 0xff)
	) ;

	Mutex::Lock lock(mMutex) ;
	auto entry(mScheduledResponses.find(command)) ;
	if (entry == mScheduledResponses.end())
		return ;

	if (mScheduledResponses[command].empty())
		return ;

	CommsEmuMsg responseMsg(mScheduledResponses[command].front()) ;
//std::cerr << "toUblazeMsgHandler: Scheduled response='" << responseMsg.getPdu().getData() << "' " << std::endl ;
	mFromUblaze->sendMsg(responseMsg) ;
	mScheduledResponses[command].erase( mScheduledResponses[command].begin() ) ;

	if (mScheduledResponses[command].empty())
		mScheduledResponses.erase(command) ;
}
