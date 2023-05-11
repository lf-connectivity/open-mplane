/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TcpPortIoHandler.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "stringfunc.hpp"

#include "TcpPortIoHandler.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TcpPortIoHandler::TcpPortIoHandler(ITcpPortIoTypes::TcpPortType type,
		unsigned port, unsigned instance, unsigned maxConnections) :
	SocketHandler("TCP"+std::to_string(port), "TIF"),

	mType(type),
	mPort(port),
	mInstance(instance),
	mMaxConnections(maxConnections),
	mQueue(std::string("TcpQueue")+std::to_string(port), "TCP",  [this](const std::string& msg){sendData(msg);}),

	mConnection(""),

    mInMutex(),
    mInSize(0),
    mReceivedBytes(0),
    mCallback(),
    mInDoneSignal()
{
//std::cerr << "new TcpPortIoHandler " << mPort << " @ " << this << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
TcpPortIoHandler::~TcpPortIoHandler()
{
//std::cerr << "del TcpPortIoHandler " << mPort << " @ " << this << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
bool TcpPortIoHandler::send(const std::string& msg)
{
	if (mType == ITcpPortIoTypes::TCP_PORT_IN)
		return false ;

	if (!isConnected())
		return false ;

	std::string msgCopy(msg) ;

	if (!isBinary())
	{
		// Ensure we have a trailing CR LF
		std::size_t pos(msgCopy.find('\n')) ;
		if (pos == std::string::npos)
		{
			msgCopy.append("\r\n") ;
		}
		else
		{
			while (pos != std::string::npos)
			{
				msgCopy.insert(pos, "\r") ;
				pos = msgCopy.find('\n', pos+2) ;
			}
		}
	}

	// Send it (via queue buffer)
	mQueue.add(msgCopy) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool TcpPortIoHandler::send(const std::vector<uint8_t>& msg)
{
	if (mType == ITcpPortIoTypes::TCP_PORT_IN)
		return false ;

	if (!isConnected())
		return false ;

	// Send it immediately
    try
    {
    	this->super::send(msg) ;
    }
    catch (SocketException& e)
    {
        logDebugNormal("Client closed connection (exception)") ;
        this->close();
    }

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool TcpPortIoHandler::receive(std::vector<uint8_t>& data, unsigned expectedSize, unsigned timeoutSecs)
{
	return receive([this, &data](const std::vector<uint8_t>& datain)->bool {
			data.insert(data.end(), datain.cbegin(), datain.cend()) ;
			return true ;
		},
		expectedSize, timeoutSecs
	) ;
}


//-------------------------------------------------------------------------------------------------------------
bool TcpPortIoHandler::receive(ITcpPortIoTypes::ReceiveCallback callback,
		unsigned expectedSize,
		unsigned timeoutSecs)
{
	if (mType == ITcpPortIoTypes::TCP_PORT_OUT)
		return false ;

	if (!isConnected())
		return false ;

//std::cerr  << "RECEIVE: START - size=" << expectedSize << std::endl ;

	// Set up parameters
	{
		Mutex::Lock lock(mInMutex) ;

		// can't continue if already waiting for input
		if (mCallback)
			return false ;

		mCallback = callback;
		mInSize = expectedSize ;
		mReceivedBytes =0 ;
	}

	// Wait for data
	bool timeout(false) ;
	if (!mInDoneSignal.wait(timeoutSecs * 1000))
		timeout = true ;

	// Tidy up
	receiveEnd() ;

//std::cerr  << "RECEIVE: END - buff size=" << mReceivedBytes << " timeout=" << timeout << std::endl ;

	return !timeout ;
}


//-------------------------------------------------------------------------------------------------------------
void TcpPortIoHandler::show(std::ostream& os)
{
	// @TODO: Update this
	std::string typeStr("OUT") ;
	if (mType == ITcpPortIoTypes::TCP_PORT_IN)
		typeStr = "IN" ;
	if (mType == ITcpPortIoTypes::TCP_PORT_INOUT)
		typeStr = "INOUT" ;

	std::string instanceStr( std::to_string(mInstance) + "/" + std::to_string(mMaxConnections)) ;

	std::string connection(mConnection) ;
	if (connection.empty())
		connection = "---" ;

	showFormat(os, std::to_string(mPort), typeStr, instanceStr, connection) ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int TcpPortIoHandler::handler()
{
//std::cerr << "New connection on port " << mPort << std::endl ;

	// Get the connection IP
	mConnection = getIpAddress() ;
	if (mConnection.empty())
    	mConnection = "<connected>" ;

    logDebugNormal("New connection on socket: %d (ip %s)", this->mSock, mConnection.c_str()) ;

    // ensure socket is in binary mode
//    setBinary(true) ;

	std::vector<uint8_t> data ;
    while (isConnected())
    {
        try
        {
        	// get any data
        	data.clear() ;
        	int numBytes( recv(data) ) ;
//std::cerr  << "RX: # bytes=" << numBytes << std::endl ;
			if (numBytes == 0)
			{
				// connection closed
	            logDebugNormal("Client closed connection") ;
	            this->close();
	            break ;
			}
        	if (numBytes <= 0)
        	{
        		std::cerr << "RX: recv error=" << numBytes << std::endl ;
        		continue ;
        	}


        	// for output only ports just ditch the input
        	if (mType == ITcpPortIoTypes::TCP_PORT_OUT)
        		continue ;

        	// See if we're currently receiving
        	bool done(false) ;
        	{
        		Mutex::Lock lock(mInMutex) ;

        		// skip if not receiving
        		if (!mCallback)
        			continue ;

//int remaining = (int)mInSize - (int)mReceivedBytes ;
//std::cerr  << "RX: current buff size=" << mReceivedBytes << " expect=" << mInSize << " remaining=" << remaining << std::endl ;

        		// skip if already reached size
        		if (mReceivedBytes >= mInSize)
        			continue ;

        		// truncate if too much
        		if (numBytes+mReceivedBytes > mInSize)
        		{
        			numBytes = mInSize - mReceivedBytes ;
        			data.resize(numBytes) ;
        		}
        		mReceivedBytes += numBytes ;

        		// copy data and flag end
        		if (!mCallback(data))
        			done = true ;

        		if (mReceivedBytes >= mInSize)
        			done = true ;
        	}

        	// send signal that we've done
        	if (done)
        	{
//std::cerr  << "RX: DONE" << std::endl ;
        		Conditional::Lock lock(mInDoneSignal) ;
        		mInDoneSignal.signal() ;
        	}
        }
        catch (SocketException& e)
        {
            logDebugNormal("Client closed connection (exception)") ;
            this->close();
            break ;
        }
    }


    // Tidy up
    mConnection.clear() ;
    receiveEnd() ;

//std::cerr << "Connection closed on port " << 	mPort << std::endl ;

    return 0 ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void TcpPortIoHandler::sendData(const std::string& msg)
{
	// Send it
    try
    {
    	*this << msg ;
    }
    catch (SocketException& e)
    {
        logDebugNormal("Client closed connection (exception)") ;
        this->close();
    }
}

//-------------------------------------------------------------------------------------------------------------
void TcpPortIoHandler::receiveEnd()
{
	Mutex::Lock lock(mInMutex) ;
	mCallback = ITcpPortIoTypes::ReceiveCallback() ;
	mReceivedBytes = 0 ;
	mInSize = 0 ;
}

//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void TcpPortIoHandler::showFormat(std::ostream& os,
		const std::string& portStr, const std::string& typeStr,
		const std::string& instanceStr, const std::string& connectionStr)
{
	os <<
		padLeft(portStr, 7) <<
		padLeft(typeStr, 7) <<
		padLeft(instanceStr, 7) <<
		connectionStr << std::endl ;
}
