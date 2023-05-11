#ifndef _AA_COMMON_SOCKETSTESTCASE_H_
#define _AA_COMMON_SOCKETSTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SocketsTestCase.h
 * \brief     The CppUnit test harness for server and client sockets
 *
 *
 * \details   The CppUnit test harness for server and client sockets
 *
 */

#include <cppunit/extensions/HelperMacros.h>

#include "SocketServer.h"
#include "SocketHandler.h"
#include "SocketClient.h"

namespace Mplane
{


class TestSocketHandler: public SocketHandler
{
public:
    TestSocketHandler(std::string name);
    ~TestSocketHandler();
protected:

    virtual int handler();
    bool mConnected;
    bool mThereWasAnException;
    std::string mName;

};

class TestSocketClient: public SocketClient
{
public:
    TestSocketClient( int port, const char* name);
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
    const char *mName;
};


/*! @brief Unit test harness for the collection of socket classes class.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the common socket server and client base classes.
 */
class SocketsTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( SocketsTestCase );
    CPPUNIT_TEST( unittests );
    CPPUNIT_TEST_SUITE_END();

public:

    /*! @brief Setup the test harness
     */
    void setUp() {};

    /*! @brief Tear down the test harness
     */
    void tearDown() {};

    /**
     * @test Test the socket server and client through test implementations
     * of the base class.
     */
    void unittests();

private:

    SocketServer* server;
    std::shared_ptr<TestSocketHandler> conn_a;
    std::shared_ptr<TestSocketHandler> conn_b;
    std::shared_ptr<TestSocketHandler> conn_c;
    std::shared_ptr<TestSocketHandler> conn_d;
    TestSocketClient*   client_a;
    TestSocketClient*   client_b;
    TestSocketClient*   client_c;
    TestSocketClient*   client_d;
    TestSocketClient*   client_bad;

};


} /* namespace Mplane */

#endif /* _AA_COMMON_SOCKETSTESTCASE_H_ */
