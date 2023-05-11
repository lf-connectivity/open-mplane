#ifndef _AA_COMMON_SOCKETHANDLER_H_
#define _AA_COMMON_SOCKETHANDLER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SocketHandler.h
 * \brief     Base class used to handle the processing of new socket connection
 *
 *
 * \details   Base class used to handle the processing of new socket connection
 *
 */

#include "Task.h"
#include "Socket.h"

namespace Mplane
{

/**
 * This base class is used to provide a foundation class that must be used
 * to provide a multi-threaded socket connection handler for the SocketServer
 * class.
 *
 * The intention is for the super class to implement the pure virtual handler()
 * method to proved a receive/transmit loop for the socket that it has been
 * associated with through its start() method.
 *
 *
 * If the handler loop terminates, the socket is closed and the thread stops running,
 * the socket handler can then be used for the next incoming connection.
 *
 */
class SocketHandler: public Task, public Socket
{
public:
    /**
     *
     */
    friend class SocketsTestCase;

    /**
     * Socket handler constructor. The priority of the thread can be set by the constructor.
     *
     * @see The Task class for details of available priorities.
     *
     * @param priority
     */
    explicit SocketHandler(int priority = Task::PRIORITY_MEDIUM);

    /**
     * Socket handler constructor. The priority of the thread can be set by the constructor.
     *
     * @see The Task class for details of available priorities.
     *
     * @param priority
     * @param instanceName Name of instance (for logging)
     * @param instanceName Name of group (for logging)
     */
    SocketHandler(const std::string& instanceName, const std::string& groupName, int priority = Task::PRIORITY_MEDIUM);

    /**
     * Socket handler destructor
     */
    virtual ~SocketHandler();

    /**
     * The start() method is called by the socket server (SocketServer) when a new connection
     * is accepted. The server passes the handler the new socket file descriptor to be handler.
     * @param socket file descriptor for the new coinnection
     */
    virtual void start( int socket );

    /**
     * Method used to check that a socket handler remains
     * connected.
     * @return true is connected otherwise false
     */
    bool isConnected();

    /**
     * Operator overload provides << syntax to allow a strings data to be sent out
     * on the socket
     * @param string data to send
     * @return reference to the socket handler
     */
    const SocketHandler& operator <<(const std::string&) ;
    /**
     * Operator overload provides >> syntax to allow a strings data to be received
     * from the socket
     * @param string data to to get new data
     * @return reference to the socket handler
     */
    const SocketHandler& operator >>(std::string&) ;

    /**
     * Disconnect the client
     */
    virtual void disconnectClient() ;

protected:

    /**
     * Implements the main task thread, calls the handler and cleans up on return,
     * ie closes the socket associated with the handler.
     *
     * @return the return code from the end handler implementation
     */
    virtual int run();

    /**
     * This method MUST be implemented as the receive/send loop
     * of the super class socket handler.
     * @return error indicator
     */
    virtual int handler() = 0;

private:
    /**
     * Used to indicate the socket remains connected, as returned by isConnected() method.
     */
    bool mIsConnected;

};

}

#endif /* _SOCKETHANDLER_H_ */
