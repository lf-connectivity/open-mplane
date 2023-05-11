/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      system_unittest.cpp
 * \brief     Unit tests for the system TIF class
 *
 *
 * \details   Unit tests for the system TIF class
 *
 */
#include "gtest/gtest.h"

#include <regex.h>

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include "stringfunc.hpp"
#include "model_fixture.h"

#include "ILoggable.h"

using namespace Mplane ;
using namespace std ;

//===================================================================================================================
// CLASSES

//-------------------------------------------------------------------------------------------------------------------
class TestSocketClient: public SocketClient
{
public:
    TestSocketClient( int port, const std::string& name);
    ~TestSocketClient();

    bool doSend();
    bool replyRevd();
    bool checkReply();
    bool doClose();

protected:

    virtual int handler();

    bool mDoSend;
    bool mReplyRecvd;
    bool mReplyOk;
    bool mConnected;
    bool mThereWasAnException;
    std::string mName;
};


//-------------------------------------------------------------------------------------------------------------------
class TcpModelTests : public ModelTests
{
public:
	std::shared_ptr<TestSocketClient> startClientError(unsigned port, const std::string& name)
	{
		std::cerr << "Create client on port " << port << " '" << name << "'" << std::endl ;
	    std::shared_ptr<TestSocketClient> client( new TestSocketClient(port, name) ) ;

	    // connect the first client
	    try
	    {
	        client->start();

	    } catch (SocketException& e)
	    {
	        std::cout << name << " client->start() - Expected Exception caught:" << e.description() << std::endl;
	        return std::shared_ptr<TestSocketClient>() ;
	    }
	    catch (...)
	    {
	        std::cout << name << " client->start() - Expected Exception caught" << std::endl;
	        return std::shared_ptr<TestSocketClient>() ;
	    }

        EXPECT_TRUE(false);    // should throw an exception
		return client ;
	}

	std::shared_ptr<TestSocketClient> startClient(unsigned port, const std::string& name)
	{
		std::cerr << "Create client on port " << port << " '" << name << "'" << std::endl ;
	    std::shared_ptr<TestSocketClient> client( new TestSocketClient(port, name) ) ;

	    // connect the first client
	    try
	    {
	        client->start();

	    } catch (SocketException& e)
	    {
	        std::cout << name << " client->start() - Exception caught:" << e.description() << std::endl;
	        EXPECT_TRUE(false);    // should not throw an exception
	        return std::shared_ptr<TestSocketClient>() ;
	    }
	    catch (...)
	    {
	        std::cout << name << " client->start() - Exception caught" << std::endl;
	        EXPECT_TRUE(false);    // should not throw an exception
	        return std::shared_ptr<TestSocketClient>() ;
	    }

	    usleep(200 * 1000); // a small delay to allow the thread to start
	    EXPECT_TRUE(client->isRunning());
	    EXPECT_TRUE(client->isValid());

		return client ;
	}

};

//===================================================================================================================
/*
 * Unit tests
 */
// global data used during the off target tests.
// they are global so that they remain active between the tests.

//-------------------------------------------------------------------------------------------------------------------
TEST_F(TcpModelTests, Open)
{
	ILoggable::setLogConsole(true) ;
	ILoggable::setLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE) ;

    std::string result;

    result = runCmdOk(".system.tcp.close 49510");

    result = runCmdOk(".system.tcp.open 49510");
    result = runCmdOk(".system.tcp.open 49511");
    result = runCmdOk(".system.tcp.open 49512 OUT 3");
    result = runCmdOk(".system.tcp.open 49513 IN");

    result = runCmdOk(".system.tcp.show");
    EXPECT_TRUE(result.find("49510  OUT    1/1    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49511  OUT    1/1    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    1/3    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    2/3    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    3/3    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49513  IN     1/1    ---") != std::string::npos) ;

    result = runCmdOk(".system.tcp.close 49510");
    result = runCmdOk(".system.tcp.close 49511");
    result = runCmdOk(".system.tcp.close 49512");
    result = runCmdOk(".system.tcp.close 49513");

}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(TcpModelTests, OpenError)
{
	ILoggable::setLogConsole(true) ;
	ILoggable::setLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE) ;

    std::string result;

    result = runCmdOk(".system.tcp.open 49510");
    result = runCmdOk(".system.tcp.open 49511");
    result = runCmdOk(".system.tcp.open 49512 OUT 3");

    result = runCmdError(".system.tcp.open 49514 IN 3");

    result = runCmdOk(".system.tcp.show");
    EXPECT_TRUE(result.find("49510  OUT    1/1    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49511  OUT    1/1    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    1/3    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    2/3    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    3/3    ---") != std::string::npos) ;

    result = runCmdError(".system.tcp.open 49510");
    EXPECT_TRUE(result.find("TCP Port already opened") != std::string::npos) ;

    result = runCmdError(".system.tcp.open 5");
    EXPECT_TRUE(result.find("Status=ERROR Message=\"Function: open - port less than minimum 1024\"") != std::string::npos) ;

    result = runCmdOk(".system.tcp.close 49510");
    result = runCmdOk(".system.tcp.close 49511");
    result = runCmdOk(".system.tcp.close 49512");
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(TcpModelTests, Close)
{
	ILoggable::setLogConsole(true) ;
	ILoggable::setLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE) ;

    std::string result;

    result = runCmdOk(".system.tcp.open 49510");
    result = runCmdOk(".system.tcp.open 49511");
    result = runCmdOk(".system.tcp.open 49512 OUT 3");

    result = runCmdOk(".system.tcp.show");
    EXPECT_TRUE(result.find("49510  OUT    1/1    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49511  OUT    1/1    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    1/3    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    2/3    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    3/3    ---") != std::string::npos) ;

    result = runCmdOk(".system.tcp.close 49510");

    result = runCmdOk(".system.tcp.show");
    EXPECT_TRUE(result.find("49510  OUT    1/1    ---") == std::string::npos) ;
    EXPECT_TRUE(result.find("49511  OUT    1/1    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    1/3    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    2/3    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    3/3    ---") != std::string::npos) ;

    result = runCmdOk(".system.tcp.close 49511");

    result = runCmdOk(".system.tcp.show");
    EXPECT_TRUE(result.find("49510  OUT    1/1    ---") == std::string::npos) ;
    EXPECT_TRUE(result.find("49511  OUT    1/1    ---") == std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    1/3    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    2/3    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    3/3    ---") != std::string::npos) ;

    result = runCmdOk(".system.tcp.close 49512");

    result = runCmdOk(".system.tcp.show");
    EXPECT_TRUE(result.find("49510  OUT    1/1    ---") == std::string::npos) ;
    EXPECT_TRUE(result.find("49511  OUT    1/1    ---") == std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    1/3    ---") == std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    2/3    ---") == std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    3/3    ---") == std::string::npos) ;


}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(TcpModelTests, Connect)
{
	ILoggable::setLogConsole(true) ;
	ILoggable::setLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE) ;

    std::string result;

    result = runCmdOk(".system.tcp.open 49510");
    result = runCmdOk(".system.tcp.open 49511");
    result = runCmdOk(".system.tcp.open 49512 OUT 3");

    result = runCmdOk(".system.tcp.show");
    EXPECT_TRUE(result.find("49510  OUT    1/1    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49511  OUT    1/1    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    1/3    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    2/3    ---") != std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    3/3    ---") != std::string::npos) ;

    std::shared_ptr<TestSocketClient> client_a( startClient(49510,"Connection A") ) ;
    result = runCmdOk(".system.tcp.show");

    std::shared_ptr<TestSocketClient> client_b( startClient(49511,"Connection B") ) ;
    result = runCmdOk(".system.tcp.show");

    std::shared_ptr<TestSocketClient> client_c1( startClient(49512,"Connection C1") ) ;
    result = runCmdOk(".system.tcp.show");

    std::shared_ptr<TestSocketClient> client_c2( startClient(49512,"Connection C2") ) ;
    result = runCmdOk(".system.tcp.show");

    std::shared_ptr<TestSocketClient> client_c3( startClient(49512,"Connection C3") ) ;
    result = runCmdOk(".system.tcp.show");

    EXPECT_TRUE(result.find("49510  OUT    1/1    0.0.0.0") != std::string::npos) ;
    EXPECT_TRUE(result.find("49511  OUT    1/1    0.0.0.0") != std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    1/3    0.0.0.0") != std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    2/3    0.0.0.0") != std::string::npos) ;
    EXPECT_TRUE(result.find("49512  OUT    3/3    0.0.0.0") != std::string::npos) ;


//    std::shared_ptr<TestSocketClient> client_c4( startClientError(49512,"Connection C4") ) ;
//    std::shared_ptr<TestSocketClient> client_a2( startClientError(49510,"Connection A2") ) ;

    result = runCmdOk(".system.tcp.close 49510");
    result = runCmdOk(".system.tcp.close 49511");
    result = runCmdOk(".system.tcp.close 49512");

//    result = runCmdOk(".system.tcp.show");
//    EXPECT_TRUE(result.find("49510  OUT    1/1    ---") == std::string::npos) ;
//    EXPECT_TRUE(result.find("49511  OUT    1/1    ---") == std::string::npos) ;
//    EXPECT_TRUE(result.find("49512  OUT    1/3    ---") == std::string::npos) ;
//    EXPECT_TRUE(result.find("49512  OUT    2/3    ---") == std::string::npos) ;
//    EXPECT_TRUE(result.find("49512  OUT    3/3    ---") == std::string::npos) ;


}


//===================================================================================================================

TestSocketClient::TestSocketClient(int port, const std::string& name ) :
        SocketClient("localhost", port, 0),
        mDoSend(),
        mReplyRecvd(false),
        mReplyOk(false),
        mConnected(false),
        mThereWasAnException( false ),
        mName( name )
{
}

TestSocketClient::~TestSocketClient()
{
}

bool TestSocketClient::doSend()
{
    mDoSend = true;
    return true;
}

bool TestSocketClient::replyRevd()
{
    return mReplyRecvd;
}

bool TestSocketClient::checkReply()
{
    return mReplyOk;
}

bool TestSocketClient::doClose()
{
    mConnected = false;
    return mConnected;
}

int TestSocketClient::handler()
{

    mConnected = true;
    mThereWasAnException = false;

    while (mConnected)
    {
        while (!mDoSend)
        {
            msSleep(100);
        }
        if( mConnected )
        {
            mDoSend = false;
            mReplyOk = false;
            mReplyRecvd = false;

            std::string reply;

            try
            {
                *this << mName;
                *this >> reply;
                mReplyRecvd = true;
            } catch (SocketException& e)
            {
                std::cout << mName << " exception caught:" << e.description() << std::endl;
                mThereWasAnException = true;
                mConnected = false;
            }

            std::cout << mName << " received this response from the server: " << reply
                    << std::endl;

            if (reply == mName)
            {
                mReplyOk = true;
            }
        }
    }
    mDoSend = false;
    mReplyOk = false;
    mReplyRecvd = false;
    if( mThereWasAnException )
        return ERROR;
    return 0;
}
