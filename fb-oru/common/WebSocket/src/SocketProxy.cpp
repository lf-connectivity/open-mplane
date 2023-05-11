/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SocketProxy.cpp
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
#include "Socket.h"
#include "SocketProxy.h"

using namespace Mplane;


//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mutex SocketProxy::mCreateMutex ;
int SocketProxy::mProxyPort = 59600 ;

//=============================================================================================================
// CLASSES
//=============================================================================================================
namespace Mplane {

class SocketMaster : public Socket {
public:
	explicit SocketMaster(unsigned port) :
		Socket(),
		mClientFd(-1)
	{
	    if (!create())
	    {
	        throw SocketException("Could not create server socket.");
	    }

	    if (!bind(port))
	    {
	    	std::string errString = "SocketProxy: Master could not bind to port - error is ";
	    	errString += strError( errno );
	        throw SocketException( errString );
	    }

	    if (!listen(1))
	    {
	        throw SocketException("SocketProxy: Master could not listen to socket.");
	    }
	    setNonBlocking( true );
	}

	virtual ~SocketMaster()
	{

	}

	int getClient()
	{
		if (mClientFd > -1)
			return mClientFd ;

		mClientFd = this->accept() ;
		return mClientFd ;
	}

private:
	int mClientFd ;
};

class SocketSlave : public Socket {
public:
	explicit SocketSlave(unsigned port) :
		Socket()
	{
	    if (!create())
	    {
	        throw SocketException("SocketProxy: Slave could not create client socket.");
	    }

	    if (!connect("localhost", port))
	    {
	    	std::string errString = "SocketProxy: Slave could not bind to port - error is ";
	    	errString += strError( errno );
	        throw SocketException( errString );
	    }
	}

	virtual ~SocketSlave()
	{

	}

};

}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SocketProxy::SocketProxy() :
	mSockMaster(),
	mSockSlave(),
	mMutex(),
	mReply("")
{
	// Create the masterand slave sockets
	createSockets() ;

//std::cerr << "SocketProxy NEW : Master [" << mSockMaster->getFd() << "] Slave[" << mSockSlave->getFd() << "]" << std::endl ;

	// start processing
	this->start() ;
}

//-------------------------------------------------------------------------------------------------------------
SocketProxy::~SocketProxy()
{
}

//-------------------------------------------------------------------------------------------------------------
int SocketProxy::getFd() const
{
	return mSockMaster->getClient() ;
}

//-------------------------------------------------------------------------------------------------------------
void SocketProxy::sendMsg(const std::string& msg)
{
	Mutex::Lock lock(mMutex) ;
//std::cerr << "SocketProxy::sendMsg(" << msg << ")" << std::endl ;
	mSockSlave->send(msg) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SocketProxy::getReply()
{
	std::string reply ;
	using std::swap ;

	Mutex::Lock lock(mMutex) ;
	swap(reply, mReply) ;

//if (!reply.empty()) std::cerr << "SocketProxy::getReply(" << reply << ")" << std::endl ;

	return reply ;
}

//-------------------------------------------------------------------------------------------------------------
bool SocketProxy::isValid() const
{
	return mSockMaster->isValid() && mSockSlave->isValid() ;
}

//-------------------------------------------------------------------------------------------------------------
bool SocketProxy::close()
{
//	mSockMaster->close() ;
//	mSockSlave->close() ;
	return true ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int SocketProxy::run()
{
	int sock(mSockSlave->getFd()) ;
	ILoggable::logEventInfo("SocketProxy[%d] connected", sock) ;

	// Handler just reads any data from the remote end and buffers it
	while (true)
	{
        try
        {
        	std::string reply ;
        	mSockSlave->recv(reply) ;
        	if (reply.empty())
        		continue ;

//std::vector<uint8_t> data(reply.begin(), reply.end()) ;
//std::cout << "-- TelnetClient::handler -------" << std::endl ;
//ByteTransfer::dump(data) ;
//std::cout << "--------------------------------\n" << std::endl ;

			// simple telnet strip
			std::string stripped ;
			for (unsigned i=0; i < reply.size(); ++i)
			{
				unsigned cc( static_cast<unsigned>(reply[i]) & 0xff) ;
				if (cc == 0xff)
				{
					i += 2 ;
					continue ;
				}
				stripped += reply[i] ;
			}
			if (stripped.empty())
				continue ;

//			{
//				std::vector<uint8_t> data(stripped.begin(), stripped.end()) ;
//				std::cout << "-- TelnetClient::handler stripped -------" << std::endl ;
//				ByteTransfer::dump(data) ;
//				std::cout << "--------------------------------\n" << std::endl ;
//
//			}


        	Mutex::Lock lock(mMutex) ;
        	mReply += stripped ;
//        	mReply += reply ;

        } catch (SocketException& e)
        {
        	ILoggable::logEventInfo("SocketProxy[%d] disconnected", sock) ;
//			std::cerr << "[TelnetClient::handler] Got socket exception: " << e.description() << std::endl ;
        	return 0 ;
        }
	}

	ILoggable::logEventInfo("SocketProxy[%d] disconnected", sock) ;
	return 0 ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void SocketProxy::createSockets()
{
	Mutex::Lock lock(mCreateMutex) ;

	// Create the master (server) socket
	mSockMaster = std::make_shared<SocketMaster>(mProxyPort) ;

	// Create the slave (client) socket
	mSockSlave = std::make_shared<SocketSlave>(mProxyPort) ;

	// next port number
	++mProxyPort ;
}
