/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WebSocketServer.h
 * \brief     SocketServer that handles WebSockets
 *
 *
 * \details
 *
 */


#ifndef WEBSOCKETSERVER_H_
#define WEBSOCKETSERVER_H_

#include <vector>
#include <string>
#include <memory>

#include "WebSocketServerHandler.h"
#include "SocketServer.h"

namespace Mplane {

class WebSocketServer : public SocketServer {
public:
	using super = SocketServer ;

	static unsigned DEFAULT_PORT ;

    /**
     * Create an instance of a connection server on a given port with a set size of
     * listener queue. The priority of the thread that accepts new connections can be
     * set in the constructor.
     * @see Task for priority ranges
     * @param port to bind to
     * @param maxConnections maximum listen queue size
     * @param priority of thread that accepts connections.
     */
	WebSocketServer( int port, int maxConnections, int priority = 0 );

    /**
     * Create an instance of a connection server on a given port with a set size of
     * listener queue. The priority of the thread that accepts new connections can be
     * set in the constructor.
     * @see Task for priority ranges
     * @param name to use for logging
     * @param port to bind to
     * @param maxConnections maximum listen queue size
     * @param priority of thread that accepts connections.
     */
	WebSocketServer( const std::string& name, int port, int maxConnections, int priority = 0 );

    /**
     * Simple destructor.
     * @note the destructor must not be called while the main thread remains
     * active, use shutdown to terminate the main thread loop and close the base socket.
     */
    virtual ~WebSocketServer();

    /**
     * This method is used by the server implementation to add
     * application specific connection handlers to the server,  this will
     * deal with new connection and read/write data to the socket.
     *
     * The number of handlers that can be added is limited to the maximum
     * number of connections the server can handle.
     *
     * @param socketHandler a pointer to a SocketHandler class, this must be a super class implementation
     * @return true if handler added, false if it failed.
     */
    virtual bool addSocketHandlers( std::shared_ptr<SocketHandler> socketHandler ) override ;

    /**
     * This method will attempt to open the socket and connect to the
     * given IP address and port. If the connection is successful, the
     * run() method is called to start a thread that accepts new socket connections.
     *
     * The the socket cannot be created or  opened the error code is return.
     *
     * @return the socket error code, or zero if successful.
     */
    virtual int start() override ;

    /**
     * Method used to force the main thread to exit and close the base socket connection.
     */
    virtual void shutdown() override ;

private:
    std::vector<std::shared_ptr<WebSocketServerHandler>> mWebSockHandlers ;
} ;

}

#endif /* WEBSOCKETSERVER_H_ */
