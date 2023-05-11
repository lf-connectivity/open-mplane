/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WebSocketServerHandler.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "ByteTransfer.hpp"
#include "Sha1.h"
#include "stringfunc.hpp"
#include "Base64.h"

#include "ILoggable.h"
#include "WebSocketPacket.h"

#include "WebSocketServerHandler.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
WebSocketServerHandler::WebSocketServerHandler(std::shared_ptr<SocketHandler> handler) :
	SocketHandler(),
	mInit(true),
	mIsConnected(false),
	mChild(handler),
	mChildSock(),
	mCmd("")
{
//	std::cerr << "WebSocketServerHandler NEW" << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
WebSocketServerHandler::~WebSocketServerHandler()
{
//	std::cerr << "WebSocketServerHandler DESTROY" << std::endl ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int WebSocketServerHandler::handler()
{
	int sock(mSock) ;
	ILoggable::logEventInfo("WS Handler[%d] connected %s", sock, getIpAddress().c_str()) ;

	// make sure that this connection is set to binary mode
	this->setBinary(true) ;

//std::cerr << "[WebSocketServerHandler::handler] Running WS handler " << sock << " " <<  getIpAddress() << std::endl;

	mInit = true ;
	mIsConnected = true ;
	mCmd.clear() ;
	while (mIsConnected)
	{
		try
		{
			// Handle either connection negotiation or WebSocket data
			std::string reply ;
			if (mInit)
			{
				reply = handleInit(mInit) ;
			}
			else
			{
				reply = handleWs() ;
			}

			// process any reply strings
			if (!reply.empty())
			{
//std::cerr << "[handler WS reply] " << reply << std::endl;
//std::vector<uint8_t> data(reply.begin(), reply.end()) ;
//ByteTransfer::dump(data) ;
				*this << reply ;
			}
		}
		catch (SocketException& e)
		{
			mIsConnected = false;
//			std::cerr << "[WebSocketServerHandler::handler] Got socket exception: " << e.description() << std::endl ;
		}
	}


	// shut everything down
	this->close();
	if (mChildSock && mChildSock->isValid())
	{
		// expect this to also close the child handler
		mChildSock->close() ;
		mChildSock.reset() ;
	}
	mInit = true ;
	mCmd.clear() ;

	// switch to blocking server
	this->setNonBlocking(false) ;


//std::cerr << "[WebSocketServerHandler::handler] Exit WS handler" << std::endl;
	ILoggable::logEventInfo("WS Handler[%d] disconnected", sock) ;

	return 0;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================
const std::string KeyName{"Sec-WebSocket-Key:"} ;
const std::string MAGIC{"258EAFA5-E914-47DA-95CA-C5AB0DC85B11"} ;

//-------------------------------------------------------------------------------------------------------------
std::string WebSocketServerHandler::handleInit(bool& init)
{
	// Keep going until we've got an empty line
	std::string cmd ;
	std::string buff ;
	while (cmd.find("\r\n\r\n") == std::string::npos && this->isValid())
	{
		*this >> buff ;
		if (buff.empty())
		{
			Task::msSleep(100) ;
			continue ;
		}
		cmd += buff ;
	}

	std::size_t pos(cmd.find(KeyName)) ;
	if (pos == std::string::npos)
		return "" ;
	std::size_t hostPos(cmd.find("GET /")) ;
	if (hostPos == std::string::npos)
		return "" ;

	// hostPos += 5 ; CppCheck - Variable 'hostPos' is assigned a value that is never used.

	// manage WebSocket negotiation
	init = false ;
	pos += KeyName.size() ;

	std::size_t nl(cmd.find("\r", pos)) ;
	std::string key(trim(cmd.substr(pos, nl-pos))) ;

	key += MAGIC ;
	// std::string sha1Str(Sha1::getHashString(key)) ; CppCheck - Variable 'sha1Str' is assigned a value that is never used.
	std::vector<uint8_t> sha1(Sha1::getHash(key)) ;

	std::string reply(
		std::string("HTTP/1.1 101 Web Socket Protocol Handshake\r\n"
		"Upgrade: websocket\r\n"
		"Connection: Upgrade\r\n"
		"Sec-WebSocket-Accept: ") + Base64::encode(sha1) + "\r\n" +
		"\r\n"
	) ;

	// switch to non-blocking server
	this->setNonBlocking(true) ;
	mCmd.clear() ;

//std::cerr << "[WebSocketServerHandler::handleInit] start child handler.." << std::endl ;

	// Use an ephemeral port
	mChildSock = std::make_shared<SocketProxy>() ;

	// Start child handler
	mChild->start(mChildSock->getFd()) ;

	return reply ;
}

//-------------------------------------------------------------------------------------------------------------
std::string WebSocketServerHandler::handleWs()
{
	if (!mChildSock || !mChildSock->isValid())
        throw SocketException("Socket disconnected");

//std::cerr << "[WebSocketServerHandler::handleWs]" << std::endl ;

	bool active(false) ;

	// TX
	std::string buff ;
	*this >> buff ;
	if (!buff.empty())
	{
		active = true ;
		WebSocketPacket packet ;
		packet.setPacketData(buff) ;
		WebSocketPacket::WsOpcode opcode(packet.getOpcode()) ;
		if (opcode == WebSocketPacket::CONNECTION_CLOSE)
		{
			mIsConnected = false ;
			return "" ;
		}
		if (opcode != WebSocketPacket::TEXT_FRAME)
			return "" ;

		mCmd += packet.getPayload() ;
//std::cerr << " so far cmd='" << mCmd << "'" << std::endl ;
//std::vector<uint8_t> data(mCmd.begin(), mCmd.end()) ;
//ByteTransfer::dump(data) ;

		// Only send when we have a terminating NL
		if (mCmd.find('\n') != std::string::npos)
		{
			// for debugging, allow comments starting with # but then strip off the comment
			std::size_t pos(mCmd.find('#')) ;
			if (pos != std::string::npos)
			{
				mCmd = mCmd.substr(0, pos) + '\n' ;
			}

//			std::cerr << " SENT cmd='" << mCmd << "'" << std::endl ;
//			std::vector<uint8_t> data(mCmd.begin(), mCmd.end()) ;
//			ByteTransfer::dump(data) ;

			// send it
			mChildSock->sendMsg(mCmd) ;
			mCmd.clear() ;
		}
	}

	// RX
	std::string reply(mChildSock->getReply()) ;
	if (!reply.empty())
	{
		active = true ;
		WebSocketPacket packet ;
		packet.setPayloadData(reply) ;
		reply = packet.getPacketData() ;
	}

	if (!active)
		Task::msSleep(10) ;

	return reply ;
}
