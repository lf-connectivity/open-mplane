/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WebSocketServer.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "WebSocketServer.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
unsigned WebSocketServer::DEFAULT_PORT{49400} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
WebSocketServer::WebSocketServer(int port, int maxConnections, int priority) :
	SocketServer(port, maxConnections, priority)
{
//	std::cerr << "WebSocketServer NEW : port=" << port << " #connections=" << maxConnections << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
WebSocketServer::WebSocketServer(const std::string& name, int port, int maxConnections, int priority) :
	SocketServer(name, port, maxConnections, priority)
{
//	std::cerr << "WebSocketServer NEW : " << name << " port=" << port << " #connections=" << maxConnections << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
WebSocketServer::~WebSocketServer()
{
//	std::cerr << "WebSocketServer DESTROY" << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
bool WebSocketServer::addSocketHandlers(std::shared_ptr<SocketHandler> socketHandler)
{
	std::shared_ptr<WebSocketServerHandler> handler(std::make_shared<WebSocketServerHandler>(socketHandler)) ;
	return this->super::addSocketHandlers(handler) ;
}

//-------------------------------------------------------------------------------------------------------------
int WebSocketServer::start()
{
	return this->super::start() ;
}

//-------------------------------------------------------------------------------------------------------------
void WebSocketServer::shutdown()
{
	return this->super::shutdown() ;
}
