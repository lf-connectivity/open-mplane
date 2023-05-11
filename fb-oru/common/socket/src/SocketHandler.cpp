/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SocketHandler.cpp
 * \brief     Implement the socket handler base class
 *
 *
 * \details   Implement the socket handler base class
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================


#include "SocketHandler.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SocketHandler::SocketHandler( int priority ):
    Task( priority, MEDIUM_STACK, "SocketHandler", "SY"),
    mIsConnected(false)
{
}

//-------------------------------------------------------------------------------------------------------------
SocketHandler::SocketHandler(const std::string& instanceName, const std::string& groupName, int priority) :
	Task( priority, MEDIUM_STACK, instanceName.c_str(), groupName.c_str()),
	mIsConnected(false)
{
}

//-------------------------------------------------------------------------------------------------------------
SocketHandler::~SocketHandler()
{
}

//-------------------------------------------------------------------------------------------------------------
void SocketHandler::start(int socket)
{
    this->mSock = socket;
    // only start the task thread if the socket we've been given is valid.
    if( isValid() )
    {
        mIsConnected = true;
        fprintf(stderr, "SocketHandler(%d) starting\n",Socket::getFd()) ;
        Task::start();
    }
}

//-------------------------------------------------------------------------------------------------------------
bool SocketHandler::isConnected()
{
    return mIsConnected;
}


//-------------------------------------------------------------------------------------------------------------
const SocketHandler& SocketHandler::operator <<( const std::string& s)
{

    if (!Socket::send(s))
    {
        throw SocketException("Handler could not write to socket.");
    }

    return *this;
}

//-------------------------------------------------------------------------------------------------------------
const SocketHandler& SocketHandler::operator >>( std::string& s)
{
    s.clear();
    if (Socket::recv(s) == Socket::ERROR)
    {
        throw SocketException("Handler could not read from socket.");
    }

    return *this;
}

//-------------------------------------------------------------------------------------------------------------
void SocketHandler::disconnectClient()
{
    Socket::close();
    mIsConnected = false;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int SocketHandler::run()
{
    int result = handler();
    fprintf(stderr, "SocketHandler(%d) exit - result %d\n",Socket::getFd(), result) ;
    Socket::close();
    mIsConnected = false;
    return result;
}
