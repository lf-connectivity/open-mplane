/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TcpPortIo.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TcpPortIoHandler.h"
#include "TcpPortIo.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TcpPortIo::TcpPortIo(ITcpPortIoTypes::TcpPortType type, unsigned port, unsigned maxConnections) :
	SocketServer(
		std::string("TcpPort")+std::to_string(port),
		port,
		maxConnections)
{
	for (unsigned instance=1; instance <= maxConnections; ++instance)
	{
		addSocketHandlers( std::shared_ptr<TcpPortIoHandler>(new TcpPortIoHandler(type, port, instance, maxConnections)) );
	}
}

//-------------------------------------------------------------------------------------------------------------
TcpPortIo::~TcpPortIo()
{
}

//-------------------------------------------------------------------------------------------------------------
void TcpPortIo::setBinary(const bool binary)
{
	this->SocketServer::setBinary(binary) ;
	for (auto handler : mHandlers)
	{
		std::shared_ptr<TcpPortIoHandler> tcpHandler(std::dynamic_pointer_cast<TcpPortIoHandler>(handler)) ;
		tcpHandler->setBinary(binary) ;
	}

}

//-------------------------------------------------------------------------------------------------------------
bool TcpPortIo::send(const std::string& msg)
{
	for (auto handler : mHandlers)
	{
		std::shared_ptr<TcpPortIoHandler> tcpHandler(std::dynamic_pointer_cast<TcpPortIoHandler>(handler)) ;
		tcpHandler->send(msg) ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool TcpPortIo::send(const std::vector<uint8_t>& msg)
{
	for (auto handler : mHandlers)
	{
		std::shared_ptr<TcpPortIoHandler> tcpHandler(std::dynamic_pointer_cast<TcpPortIoHandler>(handler)) ;
		tcpHandler->send(msg) ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool TcpPortIo::receive(std::vector<uint8_t>& data, unsigned expectedSize, unsigned timeoutSecs)
{
	// For receivers should only have one active connection
	if (mHandlers.size() != 1)
		return true ;

	// Use the single connection
	std::shared_ptr<TcpPortIoHandler> tcpHandler(std::dynamic_pointer_cast<TcpPortIoHandler>(mHandlers[0])) ;
	if (!tcpHandler->receive(data, expectedSize, timeoutSecs))
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool TcpPortIo::receive(ITcpPortIoTypes::ReceiveCallback callback, unsigned expectedSize, unsigned timeoutSecs)
{
	// For receivers should only have one active connection
	if (mHandlers.size() != 1)
		return true ;

	// Use the single connection
	std::shared_ptr<TcpPortIoHandler> tcpHandler(std::dynamic_pointer_cast<TcpPortIoHandler>(mHandlers[0])) ;
	if (!tcpHandler->receive(callback, expectedSize, timeoutSecs))
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void TcpPortIo::show(std::ostream& os)
{
	for (auto handler : mHandlers)
	{
		std::shared_ptr<TcpPortIoHandler> tcpHandler(std::dynamic_pointer_cast<TcpPortIoHandler>(handler)) ;
		tcpHandler->show(os) ;
	}
}

//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void TcpPortIo::showFormat(std::ostream& os,
		const std::string& portStr, const std::string& typeStr,
		const std::string& instanceStr, const std::string& connectionStr)
{
	TcpPortIoHandler::showFormat(os, portStr, typeStr, instanceStr, connectionStr) ;
}
