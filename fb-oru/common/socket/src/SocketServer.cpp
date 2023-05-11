/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Socket.cpp
 * \brief     Implementation of a base socket connection handler task.
 *
 *
 * \details   Implementation of a base socket connection handler task.
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "stringfunc.hpp"

#include "Socket.h"
#include "SocketServer.h"
#include "SocketHandler.h"

#include <iostream>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <sys/types.h>

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SocketServer::SocketServer(int hostPort, int maxConnections, int priority ) :
        Task( priority, MEDIUM_STACK, "SocketServer", "AP"),
        mPort(hostPort),
        mConnected(false),
        mHandlerCount(0),
        mMaxConnections(maxConnections)
{

}

//-------------------------------------------------------------------------------------------------------------
SocketServer::SocketServer(const std::string& name, int hostPort, int maxConnections, int priority ) :
        Task( priority, MEDIUM_STACK, name.c_str(), "AP"),
        mPort(hostPort),
        mConnected(false),
        mHandlerCount(0),
        mMaxConnections(maxConnections)
{

}

//-------------------------------------------------------------------------------------------------------------
SocketServer::~SocketServer()
{
    Mutex::Lock lock( mMutex );

    mHandlers.clear();

}

//-------------------------------------------------------------------------------------------------------------
bool SocketServer::addSocketHandlers( std::shared_ptr<SocketHandler> socketHandler)
{
    Mutex::Lock lock( mMutex );

    if ( mHandlerCount < mMaxConnections)
    {
        mHandlerCount++;
        mHandlers.push_back(socketHandler);
        return true;
    }
    return false;
}

//-------------------------------------------------------------------------------------------------------------
int SocketServer::start()
{
    if (!Socket::create())
    {
        throw SocketException("Could not create server socket.");
    }

    Socket::setReuseAddr(true);
    Socket::setKeepAlive(true);
    Socket::setNoDelay(true);

    if (!Socket::bind(mPort))
    {
    	std::string errString = "Could not bind to port - error is ";
    	errString += strError( errno );
        throw SocketException( errString );
    }

    if (!Socket::listen(mMaxConnections))
    {
        throw SocketException("Could not listen to socket.");
    }
    Socket::setNonBlocking( true );
    // now we have our listener socket start accepting new connections
    // in our connection thread, starting new connection handlers
    // for new sockets.
    Task::start();
    return 0;
}

//-------------------------------------------------------------------------------------------------------------
unsigned SocketServer::getMaxConnections() const
{
	return mMaxConnections ;
}


//-------------------------------------------------------------------------------------------------------------
void SocketServer::shutdown()
{
    mConnected = false;
}

//-------------------------------------------------------------------------------------------------------------
void SocketServer::disconnectClients()
{
    Mutex::Lock lock( mMutex );

    std::vector< std::shared_ptr<SocketHandler> >::iterator sockHandlerIterator;

    for ( auto handler : mHandlers )
    {
        // check if the socket handler has a valid socket
        if ( !handler->isValid() )
        	continue ;

        // handler has a valid socket so disconnect
        handler->disconnectClient() ;
    }
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int SocketServer::run()
{
    int newSocket;
    mConnected = true;

    while (mConnected)
    {
        try
        {
            newSocket = Socket::accept();

        	if( newSocket != ERROR )
            {
        		std::shared_ptr<SocketHandler> socketHandler(findAvailableHandler());
                if( socketHandler )
                {
                    if( socketHandler->isRunning() == false )
                    {
                        socketHandler->start( newSocket );
                    }
                }
                else
                {
                    // no available connection handler so close the socket
                    ::close( newSocket );
                }
            }

            // service the task watchdog
			kickSoftwareWatchdog() ;

            msSleep(100);
        } catch (SocketException& e)
        {
            std::cout << " SocketServer exception in accept caught:" << e.description() << std::endl;
            mConnected = false;
        }
    }
    Socket::close();
    return 0;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<SocketHandler> SocketServer::findAvailableHandler()
{
    Mutex::Lock lock( mMutex );

    std::vector< std::shared_ptr<SocketHandler> >::iterator sockHandlerIterator;

    for ( sockHandlerIterator = mHandlers.begin();
            sockHandlerIterator != mHandlers.end();
            ++sockHandlerIterator )
    {

        // check if the socket handler already has a valid socket
        if ( !(*sockHandlerIterator)->isValid() )
        {
            return (*sockHandlerIterator);
        }
    }
    return std::shared_ptr<SocketHandler>(); // no spare handler available.
}
