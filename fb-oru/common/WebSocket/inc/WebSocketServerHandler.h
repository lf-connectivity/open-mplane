/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WebSocketHandler.h
 * \brief     SocketHandler for WebSocketServer
 *
 *
 * \details   This is a SocketHandler class that provides WebSocket support for a generic SocketHandler. It transparently
 * 				wraps the original handler, stripping off any WebSocket-specific data (and handling that itself)
 *
 */


#ifndef WEBSOCKETSERVERHANDLER_H_
#define WEBSOCKETSERVERHANDLER_H_

#include "Socket.h"
#include "SocketProxy.h"
#include "SocketHandler.h"

namespace Mplane {

class WebSocketServerHandler : public SocketHandler {
public:
	explicit WebSocketServerHandler(std::shared_ptr<SocketHandler> handler) ;
	virtual ~WebSocketServerHandler() ;

protected:
    /**
     * This method MUST be implemented as the receive/send loop
     * of the super class socket handler.
     * @return error indicator
     */
    virtual int handler() override ;

private:
    std::string handleInit(bool& init) ;
    std::string handleWs() ;

private:
    bool mInit ;
    bool mIsConnected ;
    std::shared_ptr<SocketHandler> mChild ;
    std::shared_ptr<SocketProxy> mChildSock ;
    std::string mCmd ;
} ;

}

#endif /* WEBSOCKETSERVERHANDLER_H_ */
