#ifndef _AA_COMMON_SOCKETSERVER_H_
#define _AA_COMMON_SOCKETSERVER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Socket.h
 * \brief     Defines a base class used to listen for incoming socket connections
 *
 *
 * \details   Defines a base class used to listen for incoming socket connections
 *
 */

#include <vector>
#include <memory>

#include "Task.h"
#include "Socket.h"
#include "Mutex.h"

namespace Mplane
{

class SocketHandler;

/**
 * This class provides a simple socket connection server. It will bind to an address
 * and accept new incoming connections. Each new connection is passed to a SocketHandler
 * class for processing. This class, once started will run in its own thread.
 */
class SocketServer: public Task, public Socket
{
public:
    /**
     * Allows unit test to access private and protected data.
     */
    friend class SocketsTestCase;

    /**
     * Create an instance of a connection server on a given port with a set size of
     * listener queue. The priority of the thread that accepts new connections can be
     * set in the constructor.
     * @see Task for priority ranges
     * @param port to bind to
     * @param maxConnections maximum listen queue size
     * @param priority of thread that accepts connections.
     */
    SocketServer( int port, int maxConnections, int priority = 0 );

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
    SocketServer( const std::string& name, int port, int maxConnections, int priority = 0 );

    /**
     * Simple destructor.
     * @note the destructor must not be called while the main thread remains
     * active, use shutdown to terminate the main thread loop and close the base socket.
     */
    virtual ~SocketServer();

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
    virtual bool addSocketHandlers( std::shared_ptr<SocketHandler> socketHandler );

    /**
     * This method will attempt to open the socket and connect to the
     * given IP address and port. If the connection is successful, the
     * run() method is called to start a thread that accepts new socket connections.
     *
     * The the socket cannot be created or  opened the error code is return.
     *
     * @return the socket error code, or zero if successful.
     */
    virtual int start();

    /**
     * Method used to force the main thread to exit and close the base socket connection.
     */
    virtual void shutdown();

    /**
     * Get the maximum number of connections for this server
     */
    virtual unsigned getMaxConnections() const ;

	/**
	 * Disconnect all clients for all servers (e.g. when interface goes down)
	 */
	virtual void disconnectClients() ;



protected:

    /**
     * Method called from the start() method as a result of a good connection.
     * This method will sit on the open socket and wait for new connections,
     * using the Socket::accept() method. New connection are passed to the
     * next available connection handler.
     *
     * If the shutdown() method is called the run loop will terminate and
     * the base socket will be closed.
     *
     * @return If the connection is closed the exit error code is returned.
     */
    virtual int run();

    /**
     * When a new incoming connection is accepted, this method is used to return a
     * pointer to an available socket handler. If none are free zero ((SocketHandler*)0)
     * is returned
     *
     * @return available socket handler pointer, or none if not available.
     */
    virtual std::shared_ptr<SocketHandler> findAvailableHandler();

protected:
    /**
     * The port number to which the server is bound
     */
    int mPort;
    /**
     * USed to indicate we are in the main run loop.
     */
    bool mConnected;
    /**
     * Counts the number of socket handlers added to the server.
     */
    int mHandlerCount;
    /**
     * maximum number of socket handlers/connections the server will handle
     */
    int mMaxConnections;
    /**
     * List of socket handlers
     */
    std::vector<std::shared_ptr<SocketHandler>> mHandlers;
    /**
     * Mutex used for thread safe access, where necessary.
     */
    Mutex mMutex;
};

}

#endif /* _AA_COMMON_SOCKETSERVER_H_ */
