#ifndef _AA_COMMON_SOCKETCLIENT_H_
#define _AA_COMMON_SOCKETCLIENT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SocketClient.h
 * \brief     Base class for creating a IP socket class that runs as a task
 *
 *
 * \details   Base class for creating a IP socket class that runs as a task
 *
 */

#include "Task.h"
#include "Socket.h"

namespace Mplane
{

/**
 * The SocketClient provides a base class that can be used to create a socket
 * and open a connection to a socket server. After be created, the user calls
 * the start() method to establish the connection and run the thread used to service
 * the connection. On completion the super class returns from the handler() method,
 * the connection is closed thread terminates. The object can then be re-used to re-establish the
 * connection or be deleted.
 */
class SocketClient: public Task, public Socket
{
public:
    /**
     * Unit test set as friend to allow access to protected and private data and methods.
     */
    friend class SocketsTestCase;

    /**
     * Create a socket client that will attached to the given host address and port.
     * A priority can be set for the thread that will handle the open connection communications.
     *
     * @see Task for details of available priorities.
     *
     * @param hostName  servers computer name, i.e. "localhost"
     * @param port number to connect to
     * @param priority of thread to handle connection
     */
    SocketClient ( const char* hostName, int port, int priority = 0 );

    /**
     * Destructor
     */
    virtual ~SocketClient();

    /**
     * Operator allows the use of << to send string data out on the socket.
     * @param string data to send
     * @return reference to he socket client
     */
    SocketClient& operator <<(const std::string&) ;
    /**
     * Operator allows the use of >> to retrieve string data received on the socket.
     * @param string data to receive new data
     * @return reference to he socket client
     */
    SocketClient& operator >>(std::string&) ;

    /**
     * Method used to open the connection and start the thread that calls
     * the handler(O) method to implement communications with hte server.
     * @return 0 if succesful otherwise ERROR
     */
    virtual int start();

protected:

    /**
     * Method called in the context of the new thread created as a result of a call to the start
     * method.
     *
     * This method in turn calls the handler method implemented by the super class.
     *
     * On return the method cleans up, closing the socket.
     * @return the handler exit status
     */
    virtual int run();

    /**
     * This pure virtual method must be implemented by the the SocketClient super class.
     * @return exit status value.
     */
    virtual int handler() = 0;

private:
    /**
     * Holds the host name for the socket connection
     */
    const char* mHostName;
    /**
     * Holds the port number for the connection.
     */
    int         mPort;
};

}

#endif /* _AA_COMMON_SOCKETCLIENT_H_ */
