/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SocketClient.cpp
 * \brief     Implementation of the SocketClient base class
 *
 *
 * \details   Implementation of the SocketClient base class
 *
 */

#include <string.h>
#include <errno.h>

#include "stringfunc.hpp"
#include "SocketClient.h"

using namespace Mplane;

Mplane::SocketClient::SocketClient(const char * host, int port, int priority) :
               Task( priority, MEDIUM_STACK, "SocketClient", "SY"),
               mHostName(host), mPort(port)
{
}

Mplane::SocketClient::~SocketClient()
{
}

SocketClient& Mplane::SocketClient::operator <<( const std::string& s)
{

    if (!Socket::send(s))
    {
        throw SocketException("Client could not write to socket.");
    }

    return *this;
}

SocketClient& Mplane::SocketClient::operator >>( std::string& s)
{
    s.clear();
    if (Socket::recv(s) == Socket::ERROR)
    {
        throw SocketException("Client could not read from socket.");
    }

    return *this;
}

int Mplane::SocketClient::start()
{
    if (!Socket::create())
    {
    	if( mSock != ERROR )
    	{
    		Socket::close( );
    	}
        throw SocketException("Client could not create client socket.");
    }

    Socket::setReuseAddr(true);
    Socket::setKeepAlive(true);
    Socket::setNoDelay(true);

    if (!Socket::connect(mHostName, mPort))
    {
    	if( mSock != ERROR )
    	{
    		Socket::close( );
    	}
    	std::string errString = "Could not bind to port - error is ";
    	errString += strError( errno );
    	errString += " (" + std::to_string( errno ) + ")";
        throw SocketException( errString );
    }
    Task::start();
    return 0;
}

int Mplane::SocketClient::run()
{
    int result = handler();
    Socket::close();
    return result;
}
