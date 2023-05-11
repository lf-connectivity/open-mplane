/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Socket.cpp
 * \brief     Implementation of a basic socket handling wrapper class.
 *
 *
 * \details   Implementation of a basic socket handling wrapper class.
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <errno.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>  // needed for memset

#include <iostream>

#include "Socket.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

// Number of times to retry sending data before aborting
static const unsigned SEND_RETRY_COUNT
{ 3 };

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Socket::Socket() :
        mNonBlocking(false), mSock(ERROR), mBinary(false)
{
    memset(&mAddress, 0, sizeof(mAddress));
}

Socket::Socket(int socket):
        mNonBlocking(false), mSock(socket), mBinary(false)
{
}

//-------------------------------------------------------------------------------------------------------------
Socket::~Socket()
{
    close();
}

//-------------------------------------------------------------------------------------------------------------
bool Socket::isValid() const
{
    return mSock != ERROR;
}

//-------------------------------------------------------------------------------------------------------------
bool Socket::create()
{
    if( isValid() == false  )   // don't create a new one if we already have one
    {
        mSock = socket(AF_INET, SOCK_STREAM, 0);
    }

    if (isValid())
    {
            return true;
    }
    return false;
}

bool Socket::setReuseAddr( bool set )
{
    if (isValid())
    {
        int on = 0;
        if( set )
        {
            on = 1;
        }
        if ( (setsockopt(mSock, SOL_SOCKET, SO_REUSEADDR,
                        (const char*) &on, sizeof(on)) != ERROR) )
        {
            return true;
        }
    }
    return false;
}

bool Socket::setKeepAlive( bool set )
{
    if (isValid())
    {
        int on = 0;
        if( set )
        {
            on = 1;
        }
        if ( (setsockopt(mSock, SOL_SOCKET, SO_KEEPALIVE,
                        (const char*) &on, sizeof(on)) != ERROR) )
        {
            return true;
        }

    }
    return false;
}

bool Socket::setNoDelay( bool set )
{
    if (isValid())
    {
        int on = 0;
        if( set )
        {
            on = 1;
        }
        if ( (setsockopt(mSock, IPPROTO_TCP, TCP_NODELAY,
                        (const char*) &on, sizeof(on)) != ERROR) )
        {
            return true;
        }
    }
    return false;
}

bool Socket::setRecvTimeout( int msecs )
{
    if (isValid())
    {
        struct timeval tv = {0};
        tv.tv_sec = (msecs / 1000);      // msecs to secons
        tv.tv_usec = (msecs % 1000) * 1000;  // take msecs and convert to secs

        if (setsockopt(mSock, SOL_SOCKET, SO_RCVTIMEO,
                           (char *)&tv, sizeof(struct timeval)) != ERROR )
        {
            return true;
        }

    }
    return false;

}

bool Socket::setSendTimeout( int msecs )
{
    if (isValid())
    {
        struct timeval tv = {0};
        tv.tv_sec = (msecs / 1000);      // msecs to secons
        tv.tv_usec = (msecs % 1000) * 1000;  // take msecs and convert to secs

        if (setsockopt(mSock, SOL_SOCKET, SO_SNDTIMEO,
                           (char *)&tv, sizeof(struct timeval)) != ERROR )
        {
            return true;
        }
    }
    return false;
}


//-------------------------------------------------------------------------------------------------------------
bool Socket::bind(const int port)
{
    if (!isValid())
    {
        errno = ENOTSOCK;
        return false;
    }

    mAddress.sin_family = AF_INET;
    mAddress.sin_addr.s_addr = INADDR_ANY;
    mAddress.sin_port = htons(port);

    if (::bind(mSock, (struct sockaddr *) &mAddress, sizeof(mAddress)) == ERROR)
    {
        close();
        return false;
    }

    return true;
}

//-------------------------------------------------------------------------------------------------------------
bool Socket::listen(int maxConnections) const
{
    if (isValid())
    {
        if (::listen(mSock, maxConnections) != ERROR)
        {
            return true;
        }
    }
    return false;
}

//-------------------------------------------------------------------------------------------------------------
int Socket::accept() const
{
    if (isValid())
    {
        int newSocket;
        socklen_t addrLength = sizeof(mAddress);
        if ((newSocket = ::accept(mSock, (sockaddr *) &mAddress, &addrLength))  > 0)
        {
            return newSocket;
        }
    }
    return ERROR;
}

//-------------------------------------------------------------------------------------------------------------
bool Socket::connect(const std::string &host, const int port)
{
    if (isValid())
    {
        mAddress.sin_family = AF_INET;
        mAddress.sin_port = htons(port);
        int result = inet_pton(AF_INET, host.c_str(), &mAddress.sin_addr);
        if (result >= 0)
        {
            if (result == 0)
            {
                if ( errno == EAFNOSUPPORT)
                {
                    return false;
                }
            }
            if (::connect(mSock, (sockaddr *) &mAddress, sizeof(mAddress)) == 0)
            {
                return true;
            }
        }
    }
    close();
    return false;
}

//-------------------------------------------------------------------------------------------------------------
bool Socket::send(const std::string& s)
{
    return send(s.c_str(), s.size());
}

//-------------------------------------------------------------------------------------------------------------
bool Socket::send(const std::vector<uint8_t>& data)
{
    return send(&data[0], data.size());
}

//-------------------------------------------------------------------------------------------------------------
int Socket::recv(std::string& s)
{
    // ensure max TCP packet will fit (MTU 1500)

    s = "";

    memset(mBuf, 0, mMaxRecBuf );

    int status = ::recv(mSock, mBuf, mMaxRecBuf, 0);

    // if there is an error, we need to check that if we are non-blocking check for acceptable errors.
    if (status == ERROR)
    {
        // catch known potential error conditions
        if (mNonBlocking )
        {
            if((errno == EAGAIN) || (errno == EWOULDBLOCK))
            {
//                fprintf(stderr, "Socket::recv(%d) on NON-BLOCKING socket has handled error=%d so ignore\n",mSock, errno) ;
                return 0;
            }
            fprintf(stderr, "Socket::recv(%d) on NON-BLOCKING socket has unhandled error=%d\n",mSock, errno) ;
        }
        else
        {
            if( (errno == EINTR) || (errno == EAGAIN) )
            {
//                fprintf(stderr, "Socket::recv(%d) on BLOCKING socket handled error=%d, so ignore\n", mSock, errno) ;
                return 0;
            }
            fprintf(stderr, "Socket::recv(%d) on BLOCKING socket has unhandled error=%d\n", mSock, errno) ;
        }
    }

    if (status > 0) // did we receive any characters
    {
        if (mBinary)
        {
            // Use range constructor to ensure binary data (e.g. telnet control sequences) get copied across
            // properly (otherwise 0 will terminate the string prematurely)
            s = std::string(mBuf, mBuf + status);
        }
        else
        {
            // text copy
            s = mBuf;
        }
        return status;  // return the socket status
    }
    return Socket::ERROR;  // return the socket status
}

//-------------------------------------------------------------------------------------------------------------
int Socket::recv(std::vector<uint8_t>& data)
{
    // Allocate a receive buffer dynamically when it's first needed
    int maxRecBuf { 8192 };
    if (mRxBuff.empty())
    {
        mRxBuff.reserve(maxRecBuf);
        mRxBuff.resize(maxRecBuf, 0);
    }

    int status = ::recv(mSock, &mRxBuff[0], maxRecBuf, 0);

    if (status == ERROR)
    {
        // catch known potential error conditions
        if (mNonBlocking )
        {
            if((errno == EAGAIN) || (errno == EWOULDBLOCK))
            {
                // non-blocking
                return 0;
            }
            fprintf(stderr, "Socket::recv(%d) to vector on NON-BLOCKING socket has unhandled error=%d\n", mSock, errno) ;
        }
        else
        {
            if( errno == EINTR || errno == EAGAIN )
            {
                return 0;
            }
            fprintf(stderr, "Socket::recv(%d) to vector on BLOCKING socket has unhandled error=%d\n", mSock, errno) ;
        }
    }

    if (status > 0)
    {
        data.insert(data.end(), mRxBuff.begin(), mRxBuff.begin() + status);
    }
    return status;
}

//-------------------------------------------------------------------------------------------------------------
void Socket::setNonBlocking(const bool b, int timeout)
{
    int opts = fcntl(mSock, F_GETFL);

    if (opts > 0)
    {
        mNonBlocking = b;
        if (b)
        {
            // we want a non-blocking socket so
            // set SO_RCVTIMEO to timeout.
//            struct timeval tv = {0};
//            tv.tv_sec = 0;
//            tv.tv_usec = timeout * 1000;
//            setsockopt(mSock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(struct timeval));

            opts = (opts | O_NONBLOCK);
        }
        else
        {
            opts = (opts & ~O_NONBLOCK);
        }
        fcntl(mSock, F_SETFL, opts);
    }
}

//-------------------------------------------------------------------------------------------------------------
void Socket::setBinary(const bool binary)
{
    mBinary = binary;
}

//-------------------------------------------------------------------------------------------------------------
bool Socket::isBinary() const
{
	return mBinary ;
}

//-------------------------------------------------------------------------------------------------------------
bool Socket::close()
{
    if (isValid())
    {
        ::close(mSock);
        mSock = ERROR;
        return true;
    }
    return false;
}

//-------------------------------------------------------------------------------------------------------------
SocketException::SocketException(std::string str) :
        mString(str)
{
}

//-------------------------------------------------------------------------------------------------------------
SocketException::~SocketException()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string SocketException::description()
{
    return mString;
}

//-------------------------------------------------------------------------------------------------------------
std::string Socket::getIpAddress()
{
    // Get the connection IP
    std::string connection("");
    char ip[INET_ADDRSTRLEN];
    if (::inet_ntop(AF_INET, &this->mAddress.sin_addr, ip, sizeof(ip)) != NULL)
        connection = ip;

    return connection;
}

//-------------------------------------------------------------------------------------------------------------
int Socket::getFd() const
{
    return mSock;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Socket::send(const void* data, unsigned size) const
{
    // Send the data - if we get the EAGAIN error then try resending a few times before bailing
    unsigned retryCount(SEND_RETRY_COUNT);
    while (retryCount > 0)
    {
        if (::send(mSock, data, size, MSG_NOSIGNAL) != ERROR)
        {
            return true;
        }

        if ((errno != EAGAIN) && (errno != EWOULDBLOCK))
        {
			fprintf(stderr, "Socket::send(%d) counter=%u error=%d\n", mSock, retryCount, errno) ;
            return false;
        }
        else
        {
            fprintf(stderr, "Socket::send(%d) unhandled error=%d\n", mSock, errno) ;
        }

        if (--retryCount == 0)
        {
            fprintf(stderr, "Socket::send(%d) retry count 0, error=%d\n", mSock, errno) ;
            return false;
        }
        // Pause briefly
        struct timespec ts { 0, 1000 };
        nanosleep(&ts, (struct timespec *) 0);
        fprintf(stderr, "Socket::send(%d) retry %d\n", mSock,  retryCount) ;
    }
    fprintf(stderr, "Socket::send(%d) impossible condition retCount < 0, error=%d\n",mSock,  errno) ;
    return false;
}
