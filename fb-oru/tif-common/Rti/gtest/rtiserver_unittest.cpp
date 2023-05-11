/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      gentool_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */
#include "gtest/gtest.h"

#include <regex.h>

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include "SocketClient.h"
#include "stringfunc.hpp"
#include "Ati.h"

using namespace Mplane ;

// I've commented these tests out because they are very time dependent and flaky
#ifdef NOTUSED
//===================================================================================================================
class TestSocketClient: public SocketClient
{
public:
    TestSocketClient() :
    	SocketClient("localhost", 49500, 0),
    	mClosed(false),
    	mConnected(false),
    	mThereWasAnException(false),
    	mMsg(""),
    	mReply("")
	{
    	std::cerr << "CLIENT: Create" << std::endl ;
	}
    ~TestSocketClient() {

    	std::cerr << "CLIENT: Destroy" << std::endl ;
    }

    void sendMsg(const std::string& msg)
    {
    	mReply.clear() ;
    	mMsg = msg ;
    }

    std::string getReply()
    {
    	return mReply ;
    }

    void doClose()
    {
    	std::cerr << "CLIENT: Close" << std::endl ;
        mConnected = false;
        mMsg = "\n";
    }

    void waitClosed()
    {
    	while (!mClosed)
    	{
            usleep(200 * 1000);
    	}
    }


protected:

    virtual int handler()
    {
		mConnected = true;
		mThereWasAnException = false;

		while (mConnected)
		{
			while (mMsg.empty())
			{
				msSleep(100);
			}
			if( mConnected )
			{
				mReply.clear() ;
				try
				{
std::cerr << "CLIENT: ---> " << mMsg <<std::endl ;
					*this << mMsg;
					usleep(20 * 1000) ;
					*this >> mReply;
std::cerr << "CLIENT: <--- " << mReply <<std::endl ;

				} catch (SocketException& e)
				{
					std::cout << "exception caught:" << e.description() << std::endl;
					mThereWasAnException = true;
					mConnected = false;
				}

				mMsg.clear() ;
				std::cout << " received this response from the server: " << mReply << std::endl;
			}
		}
		mClosed = true ;
		if( mThereWasAnException )
			return ERROR;
		return 0;
    }

    bool mClosed ;
    bool mConnected ;
    bool mThereWasAnException ;
    std::string mMsg ;
    std::string mReply ;
};

//===================================================================================================================
class RtiServerTests : public ::testing::Test
{
public:

    /*! @brief Setup the test
     */
    virtual void SetUp()
    {
    	const ::testing::TestInfo* const test_info =
    	  ::testing::UnitTest::GetInstance()->current_test_info();

    	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    	std::cout << test_info->name() << " - START" <<  std::endl;

    	// create server
    	mRti = new Rti() ;
        try
        {
        	mRti->server_rti->start();
        } catch (SocketException& e)
        {
            FAIL() << "server->start() - Exception caught:" << e.description() << std::endl;
        }
        usleep(200 * 1000);

        // create client
        mClient = new TestSocketClient() ;
        try
        {
        	mClient->start();
        } catch (SocketException& e)
        {
            std::cout << "mClient->start() - Exception caught:" << e.description() << std::endl;

            std::string substring = e.description().substr(0,22);
            FAIL() << substring;
        }


    }

    /*! @brief Tear down the test
     */
    virtual void TearDown()
    {
    	mClient->doClose() ;
    	mClient->waitClosed() ;
        delete mClient ;

        mRti->server_rti->shutdown();
        usleep(500 * 1000);
    	delete mRti ;
    }

protected:
    /**
     * Run the command with the expectation that there will be no error
     * @param cmd command string
     * @return reply string
     */
    std::string runCmdOk(const std::string& cmd)
    {
    	mClient->sendMsg(cmd + "\n") ;
        usleep(200 * 1000);
    	std::string result = mClient->getReply() ;
    	std::cout << "CMD: " << cmd << std::endl << "REPLY: '" << result << "'" << std::endl ;
    	EXPECT_TRUE( result.find("Error") == std::string::npos ) << "Unexpected command error" ;
    	EXPECT_TRUE( result.find("error") == std::string::npos ) << "Unexpected command error" ;
    	EXPECT_TRUE( result.find("STATUS=OK") == std::string::npos ) << "Unexpected command error" ;

    	return result ;
    }

    /**
     * Run the command with the expectation that there *will* be an error
     * @param cmd command string
     * @return reply string
     */
    std::string runCmdError(const std::string& cmd)
    {
    	mClient->sendMsg(cmd + "\n") ;
        usleep(200 * 1000);
    	std::string result = mClient->getReply() ;
    	std::cout << "CMD: " << cmd << std::endl << "REPLY: " << result << std::endl ;
    	EXPECT_TRUE( result.find("Error") != std::string::npos ) << "Expected command error but found none" ;
    	EXPECT_TRUE( result.find("STATUS=ERROR") == std::string::npos ) << "Expected command error but found none" ;

    	return result ;
    }

protected:
    Rti *mRti;
    TestSocketClient* mClient ;
};

//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
TEST_F(RtiServerTests, DISABLED_Navigation)
{
	std::string result ;

	// chdir to scripts from here
	result = runCmdOk("cd /tif:scripts") ;
	EXPECT_TRUE( result.find("Current directory: /tif:scripts") != std::string::npos ) ;

	// chdir to /
	result = runCmdOk("cd") ;
	EXPECT_TRUE( result.find("Current directory: /") != std::string::npos ) ;

	// error handling
	result = runCmdError("cd xxx") ;
}

#if 0
//-------------------------------------------------------------------------------------------------------------------
TEST_F(RtiServerTests, Listing)
{
	std::string result ;

	// Should have the special test device
	result = runCmdOk("ls") ;
	EXPECT_TRUE( result.find("tif:settings/") != std::string::npos ) ;
	EXPECT_TRUE( result.find("tif:scripts/") != std::string::npos ) ;

	result = runCmdOk("ls tif:settings") ;

	result = runCmdOk("ls tif:scripts") ;

	result = runCmdOk("cd /tif:scripts") ;

	result = runCmdError("ls xxx") ;
	EXPECT_TRUE( result.find("Error: Cannot run ls on xxx") != std::string::npos ) ;


}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(RtiServerTests, Help)
{
	std::string result ;

	result = runCmdOk("help") ;
	EXPECT_TRUE( result.find("Commands:") != std::string::npos ) ;

	result = runCmdOk("help tif:settings") ;

	result = runCmdOk("help tif:scripts") ;

	result = runCmdOk("cd /tif:scripts") ;


	result = runCmdError("help xxx") ;
	EXPECT_TRUE( result.find("Error: Cannot run help on xxx") != std::string::npos ) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(RtiServerTests, Settings)
{
	std::string result ;

	result = runCmdOk("ls tif:settings") ;
	EXPECT_TRUE( result.find("showInfo") != std::string::npos ) ;
	EXPECT_TRUE( result.find("showColumn") != std::string::npos ) ;
	EXPECT_TRUE( result.find("scriptsDir") != std::string::npos ) ;

	result = runCmdOk("tif:settings.showInfo true") ;
	result = runCmdOk("tif:settings.showColumn true") ;
	result = runCmdOk("tif:settings.scriptsDir ~/git/builTools") ;

	result = runCmdOk("ls tif:settings") ;
	EXPECT_TRUE( result.find("showInfo=true") != std::string::npos ) ;
	EXPECT_TRUE( result.find("showColumn=true") != std::string::npos ) ;
	EXPECT_TRUE( result.find("scriptsDir=\"~/git/builTools\"") != std::string::npos ) ;
}

#endif

//-------------------------------------------------------------------------------------------------------------------
TEST_F(RtiServerTests, DISABLED_ScriptsDir)
{
	std::string result ;

	result = runCmdOk("ls /") ;

	// running in build-local, point to test scripts under gtest
	result = runCmdOk("/tif:settings.scriptsDir ../common/Rti/gtest/scripts") ;
	result = runCmdOk("ls /tif:scripts") ;

	// refresh contents
	result = runCmdOk("cd /tif:scripts") ;
	result = runCmdOk("ls") ;
	result = runCmdOk("ls carrier") ;
	result = runCmdOk("/tif:scripts/simpleTest") ;
	result = runCmdOk("/tif:scripts/anotherTest") ;

}


//===================================================================================================================

#endif
