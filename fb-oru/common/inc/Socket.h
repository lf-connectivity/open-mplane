#ifndef _AA_COMMON_SOCKET_H_
#define _AA_COMMON_SOCKET_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Socket.h
 * \brief     Basic C++ socket wrapper class
 *
 *
 * \details   Basic C++ socket wrapper class
 *
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <cstdint>
#include <string>
#include <vector>


namespace Mplane
{

/**
 * This class acts as a basic C++ wrapper for the fundamental socket functionality.
 * It is intended to be used by higher level class to provide some basic functionality
 * around the socket.
 */
class Socket
{
public:
    /**
     * To allow the unit test environment to access protected and private data.
     */
    friend class SocketsTestCase;

    /**
     * Basic constructor
     */
    Socket();

    /**
     * Basic constructor
     */
    Socket(int socket);

    /**
     * Basic destructor
     */
    virtual ~Socket();

    /**
     * This method is used to create a basic AF_INET socket type.
     * @return true if created OK otherwise false
     */
    virtual bool create();
    /**
     * Method used in socket server implementations to bind the socket to a given port
     * @param port  port number to bind to
     * @return true if bound OK, otherwise false
     */
    virtual bool bind(const int port);
    /**
     * Method used in socket server implementations to set up the socket listener queue from which
     * new connections are accepted
     * @param maxConnections maximum queue for incoming connections
     * @return true if OK, otherwise
     */
    virtual bool listen( int maxConnections ) const;
    /**
     * Method used in socket server implementations to accept new socket connections and return a new socket
     * file descriptor for that connection. If the socket is set as blocking a call to this method will
     * not return until a new connection is received. If the base socket is set to non-blocking
     * it will return immediately, the return value will be -1 (ERROR) unless a new connection is
     * available.
     * @return a new socket file descriptor, or -1 for non-blocking socket
     */
    virtual int accept() const;

    /**
     * Method used in socket client implementations to connect to a given server and port.
     * @param host name of the host, ie "localhost"
     * @param port the port number to connect to.
     * @return
     */
    virtual bool connect(const std::string &host, const int port);

    /**
     * Method used to send a string out on the currently open socket.
     * @param reference to a string to send
     * @return true if sent OK otherwise false.
     */
    virtual bool send(const std::string& data) ;

    /**
     * Method used to send a vector of bytes out on the currently open socket.
     * @param reference to the bytes to send
     * @return true if sent OK otherwise false.
     */
    virtual bool send(const std::vector<uint8_t>& data) ;

    /**
     * Method used to receive a string on the currently open port.
     * @param reference to string to populate
     * @return number of characters received
     */
    virtual int recv(std::string& data) ;

    /**
     * Receive binary data (regardless of current binary mode setting) into specified buffer. The buffer
     * will have the received data *appended* to, so if you want the buffer to only contain data received
     * during this call then you need to empty it first.
     *
     * @param reference to vector to append to
     * @return number of characters received
     */
    virtual int recv(std::vector<uint8_t>& data) ;

    /**
     * Method used to change the blocking status of the socket.
     * @param true sets socket as non-blocking, false set blocking
     * @param receive timeout in millseconds, default to 100ms
     */
    virtual void setNonBlocking(const bool, int recvTimeout = 100);

    virtual bool setReuseAddr( bool set );

    virtual bool setKeepAlive( bool set );

    virtual bool setNoDelay( bool set );

    virtual bool setRecvTimeout( int msecs );

    virtual bool setSendTimeout( int msecs );


    /**
     * Method used to change the binary of the socket.
     * @param true sets socket as binary which handles binary messages (including NUL chars); false
     * treats messages as text terminating on NUL
     */
    virtual void setBinary(const bool binary);

    /**
     * See if this is a binary socket
     */
    virtual bool isBinary() const ;

    /**
     * Method checks the status of the socket, ie it has a valid socket file
     * descriptor number
     * @return false, socket is closed, true socket is valid.
     */
    virtual bool isValid() const;

    /**
     * Method used to close the currently open socket and set the file descriptor invalid (-1=ERROR)
     * @return
     */
    virtual bool close();

    /**
     * Convert the socket address into an IPv4 address
     *
     * @return ip address or empty string if unable to convert
     */
    virtual std::string getIpAddress();

    /**
     * Get the underlying socket file descriptor used by this socket
     */
    virtual int getFd() const ;

    /**
     * Value used to define an error or invalid socket file descriptor
     */
    static const int ERROR=-1;

protected:
    /**
     * Method used to send a string out on the currently open socket.
     * @param data pointer to raw bytes to be sent
     * @param size number of bytes
     * @return true if sent OK otherwise false.
     */
    virtual bool send(const void* data, unsigned size) const;

    bool mNonBlocking;

protected:
    /**
     * This Socket objects socket file descriptor
     */
    int mSock;

    /**
     * The address associated with socket, defined during creation.
     */
    sockaddr_in mAddress;

    /**
     * Binary mode
     */
    bool mBinary ;

    /**
     * Buffer used for binary receive transfers. Only created when necessary
     */
    std::vector <uint8_t> mRxBuff ;

    int mMaxRecBuf = 8192;
    char mBuf[8192];


};

/**
 * This a simple exception class that is thrown by higher level classes when any Socket method call
 * fails.
 */
class SocketException
{
public:
    /**
     * Constructor
     * @param str describes the exception
     */
	explicit SocketException(std::string str);
    /**
     * Desctructor
     */
    ~SocketException();

    /**
     * Method used to retrieve the description associated with the exception
     * @return
     */
    std::string description();

private:

    /**
     * String that describes the exception
     */
    std::string mString;

};

}

#endif /* _SOCKET_H_ */
