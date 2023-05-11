/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TaskTestCase.cpp
 * \brief     Implementation of the CppUnit test harness for Task
 *
 *
 * \details   This file contains the implementation of the CppUnit test cases
 *            for the common task Task class.
 *
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>
#include <limits.h>

#include "SocketsTestCase.h"

using namespace Mplane;

using namespace std;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION(SocketsTestCase);

/*
 * Unit tests
 */
void SocketsTestCase::unittests()
{
//	try
//	{

    cout << endl << "*** SocketsTestCase Tests ***" << endl;

    /*
     * Create a new socket server on port 6001 and allow up to 3 connections, priority 0=middle for diddle
     */
    server = new SocketServer(9500, 3, 0);
    /*
     * Create the connection handler threads that are started for each new connection
     */
    conn_a = std::shared_ptr<TestSocketHandler>(new TestSocketHandler("Server A"));
    conn_b = std::shared_ptr<TestSocketHandler>(new TestSocketHandler("Server B"));
    conn_c = std::shared_ptr<TestSocketHandler>(new TestSocketHandler("Server C"));
    conn_d = std::shared_ptr<TestSocketHandler>(new TestSocketHandler("Server D"));

    client_a = new TestSocketClient(9500,"Connection A");
    client_b = new TestSocketClient(9500,"Connection B");
    client_c = new TestSocketClient(9500,"Connection C");
    client_d = new TestSocketClient(9500,"Connection D");
    client_bad = new TestSocketClient(9501,"Connection BAD");

    CPPUNIT_ASSERT(server->isRunning() == false);
    CPPUNIT_ASSERT(server->isValid() == false);
    CPPUNIT_ASSERT(conn_a->isRunning() == false);
    CPPUNIT_ASSERT(conn_a->isValid() == false);
    CPPUNIT_ASSERT(conn_b->isRunning() == false);
    CPPUNIT_ASSERT(conn_b->isValid() == false);
    CPPUNIT_ASSERT(conn_c->isRunning() == false);
    CPPUNIT_ASSERT(conn_c->isValid() == false);
    CPPUNIT_ASSERT(conn_d->isRunning() == false);
    CPPUNIT_ASSERT(conn_d->isValid() == false);
    CPPUNIT_ASSERT(client_a->isRunning() == false);
    CPPUNIT_ASSERT(client_a->isValid() == false);
    CPPUNIT_ASSERT(client_b->isRunning() == false);
    CPPUNIT_ASSERT(client_b->isValid() == false);
    CPPUNIT_ASSERT(client_c->isRunning() == false);
    CPPUNIT_ASSERT(client_c->isValid() == false);
    CPPUNIT_ASSERT(client_d->isRunning() == false);
    CPPUNIT_ASSERT(client_d->isValid() == false);
    CPPUNIT_ASSERT(client_bad->isRunning() == false);
    CPPUNIT_ASSERT(client_bad->isValid() == false);

    try
    {
        client_bad->start();
    } catch (SocketException& e)
    {
        std::cout << "client_bad - Exception caught:" << e.description() << std::endl;

        std::string substring = e.description().substr(0,22);
        CPPUNIT_ASSERT(substring == "Could not bind to port");
    }

    CPPUNIT_ASSERT(server->mHandlerCount == 0);
    bool result = server->addSocketHandlers( std::dynamic_pointer_cast<SocketHandler>(conn_a) );
    CPPUNIT_ASSERT(result == true);
    CPPUNIT_ASSERT(server->mHandlerCount == 1);
    result = server->addSocketHandlers(conn_b);
    CPPUNIT_ASSERT(result == true);
    CPPUNIT_ASSERT(server->mHandlerCount == 2);
    result = server->addSocketHandlers(conn_c);
    CPPUNIT_ASSERT(result == true);
    CPPUNIT_ASSERT(server->mHandlerCount == 3);
    result = server->addSocketHandlers(conn_d);
    CPPUNIT_ASSERT(result == false);
    CPPUNIT_ASSERT(server->mHandlerCount == 3);

    // make sure first client with correct port can't connect
    try
    {
        client_a->start();
    } catch (SocketException& e)
    {
        std::cout << "client_a->start() - Exception caught:" << e.description() << std::endl;

        std::string substring = e.description().substr(0,22);
        CPPUNIT_ASSERT(substring == "Could not bind to port");
    }

    CPPUNIT_ASSERT(client_a->isRunning() == false);

    try
    {
    	server->start();
    } catch (SocketException& e)
    {
        std::cout << "server->start() - Exception caught:" << e.description() << std::endl;
        CPPUNIT_ASSERT(false);    // should not throw an exception
    }
    usleep(200 * 1000);
    CPPUNIT_ASSERT(server->isRunning() == true);
    CPPUNIT_ASSERT(server->isValid() == true);

    // connect the first client
    try
    {
        client_a->start();
    } catch (SocketException& e)
    {
        std::cout << "client_a->start() - Exception caught:" << e.description() << std::endl;
        CPPUNIT_ASSERT(false);    // should not throw an exception
    }
    usleep(200 * 1000); // a small delay to allow the thread to start
    CPPUNIT_ASSERT(client_a->isRunning() == true);
    CPPUNIT_ASSERT(client_a->isValid() == true);

    CPPUNIT_ASSERT(conn_a->isRunning() == true);
    CPPUNIT_ASSERT(conn_a->isValid() == true);

    client_a->doSend();
    usleep(200 * 1000); // a small delay to allow the thread to start
    CPPUNIT_ASSERT( client_a->checkReply() == true );

    // connect the second client
    try
    {
        client_b->start();
    } catch (SocketException& e)
    {
        std::cout << "client_b->start() - Exception caught:" << e.description() << std::endl;
        CPPUNIT_ASSERT(false);    // should not throw an exception
    }
    usleep(200 * 1000); // a small delay to allow the thread to start
    CPPUNIT_ASSERT(client_b->isRunning() == true);
    CPPUNIT_ASSERT(client_b->isValid() == true);

    CPPUNIT_ASSERT(conn_b->isRunning() == true);
    CPPUNIT_ASSERT(conn_b->isValid() == true);

    client_b->doSend();
    usleep(200 * 1000); // a small delay to allow the thread to start
    CPPUNIT_ASSERT( client_b->checkReply() == true );

    // connect the second client
    try
    {
        client_c->start();
    } catch (SocketException& e)
    {
        std::cout << "client_c->start() - Exception caught:" << e.description() << std::endl;
        CPPUNIT_ASSERT(false);    // should not throw an exception
    }
    usleep(200 * 1000); // a small delay to allow the thread to start
    CPPUNIT_ASSERT(client_c->isRunning() == true);
    CPPUNIT_ASSERT(client_c->isValid() == true);

    CPPUNIT_ASSERT(conn_c->isRunning() == true);
    CPPUNIT_ASSERT(conn_c->isValid() == true);

    client_c->doSend();
    usleep(200 * 1000); // a small delay to allow the thread to start
    CPPUNIT_ASSERT( client_c->checkReply() == true );

    client_a->doSend();
    client_b->doSend();
    client_c->doSend();
    usleep(200 * 1000); // a small delay to allow the thread to start
    CPPUNIT_ASSERT( client_a->checkReply() == true );
    CPPUNIT_ASSERT( client_b->checkReply() == true );
    CPPUNIT_ASSERT( client_c->checkReply() == true );

    // connect the second client
    try
    {
        client_d->start();
    } catch (SocketException& e)
    {
        std::cout << "client_d->start() - Exception caught:" << e.description() << std::endl;
        CPPUNIT_ASSERT(true);    // should not throw an exception
    }

    // should fail because we reached our connection limit
    client_d->doSend();
    usleep(200 * 1000); // a small delay to allow the thread to start
    CPPUNIT_ASSERT( client_d->checkReply() == false );
    CPPUNIT_ASSERT( client_d->isRunning() == false);
    CPPUNIT_ASSERT( client_d->isValid() == false);


    client_b->doClose();
    client_b->doSend();
    usleep(200 * 1000); // a small delay to allow the thread to start
    CPPUNIT_ASSERT( client_b->isRunning() == false);
    CPPUNIT_ASSERT( client_b->isValid() == false);

    // check connectio handler b is stopped and available
    CPPUNIT_ASSERT(conn_b->isRunning() == false);
    CPPUNIT_ASSERT(conn_b->isValid() == false);


    // connect the second client
    try
    {
        client_d->start();
    } catch (SocketException& e)
    {
        std::cout << "client_d->start() - Exception caught:" << e.description() << std::endl;
        CPPUNIT_ASSERT(false);    // should not throw an exception
    }
    usleep(200 * 1000); // a small delay to allow the thread to start
    CPPUNIT_ASSERT(client_d->isRunning() == true);
    CPPUNIT_ASSERT(client_d->isValid() == true);

    CPPUNIT_ASSERT(conn_b->isRunning() == true);
    CPPUNIT_ASSERT(conn_b->isValid() == true);

    client_d->doSend();
    usleep(200 * 1000); // a small delay to allow the thread to start
    CPPUNIT_ASSERT( client_d->checkReply() == true );


    client_a->doSend();
    client_c->doSend();
    client_d->doSend();
    usleep(200 * 1000); // a small delay to allow the thread to start
    CPPUNIT_ASSERT( client_a->checkReply() == true );
    CPPUNIT_ASSERT( client_c->checkReply() == true );
    CPPUNIT_ASSERT( client_d->checkReply() == true );

    client_a->doClose();
    client_a->doSend();
    client_c->doClose();
    client_c->doSend();
    client_d->doClose();
    client_d->doSend();
    usleep(200 * 1000); // a small delay to allow the thread to start

    CPPUNIT_ASSERT(conn_a->isRunning() == false);
    CPPUNIT_ASSERT(conn_a->isValid() == false);
    CPPUNIT_ASSERT(conn_b->isRunning() == false);
    CPPUNIT_ASSERT(conn_b->isValid() == false);
    CPPUNIT_ASSERT(conn_c->isRunning() == false);
    CPPUNIT_ASSERT(conn_c->isValid() == false);
    CPPUNIT_ASSERT(conn_d->isRunning() == false);
    CPPUNIT_ASSERT(conn_d->isValid() == false);
    CPPUNIT_ASSERT(client_a->isRunning() == false);
    CPPUNIT_ASSERT(client_a->isValid() == false);
    CPPUNIT_ASSERT(client_b->isRunning() == false);
    CPPUNIT_ASSERT(client_b->isValid() == false);
    CPPUNIT_ASSERT(client_c->isRunning() == false);
    CPPUNIT_ASSERT(client_c->isValid() == false);
    CPPUNIT_ASSERT(client_d->isRunning() == false);
    CPPUNIT_ASSERT(client_d->isValid() == false);

    // delete eveerything

    delete client_a;
    delete client_b;
    delete client_c;
    delete client_d;
    delete client_bad;

    CPPUNIT_ASSERT(server->isRunning() == true );
    CPPUNIT_ASSERT(server->isValid() == true );


//    server = new SocketServer(9500, 3, 0);

    server->shutdown();
    usleep(200 * 1000); // a small delay to allow the thread to start
    CPPUNIT_ASSERT(server->isRunning() == false );
    CPPUNIT_ASSERT(server->isValid() == false );


    delete server;

//    } catch (exception& e)
//    {
//        std::cout << "Exception caught:" << e.what() << std::endl;
//        CPPUNIT_ASSERT( false );
//    }


}

Mplane::TestSocketHandler::TestSocketHandler(std::string name):
       mConnected(false), mThereWasAnException( false ),
       mName(name)
{
}

Mplane::TestSocketHandler::~TestSocketHandler()
{
}

int Mplane::TestSocketHandler::handler()
{
    mConnected = true;
    mThereWasAnException = false;

    while (mConnected)
    {
        try
        {
            std::string data;
            *this >> data;      // simply echo back what we received
            if( data.length() > 0 )
            {
                *this << data;
            }

        } catch (SocketException& e)
        {
            std::cout << " TestServerHandler " << mName << "Exception caught:" << e.description() << std::endl;
            mThereWasAnException = true;
            mConnected = false;
        }
    }
    if( mThereWasAnException )
        return ERROR;
    return 0;
}

Mplane::TestSocketClient::TestSocketClient(int port, const char* name ) :
        SocketClient("localhost", port, 0),
        mDoSend(),
        mReplyRecvd(false),
        mReplyOk(false),
        mConnected(false),
        mThereWasAnException( false ),
        mName( name )
{
}

Mplane::TestSocketClient::~TestSocketClient()
{
}

bool Mplane::TestSocketClient::doSend()
{
    mDoSend = true;
    return true;
}

bool Mplane::TestSocketClient::replyRevd()
{
    return mReplyRecvd;
}

bool Mplane::TestSocketClient::checkReply()
{
    return mReplyOk;
}

bool Mplane::TestSocketClient::doClose()
{
    mConnected = false;
    return mConnected;
}

int Mplane::TestSocketClient::handler()
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
                std::cout << mName << " exception caught: " << e.description() << std::endl;
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
