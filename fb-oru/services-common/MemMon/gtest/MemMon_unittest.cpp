/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdService_unittests.cpp
 * \brief     DPD services unit tests
 *
 *
 *
 */

#include "gtest/gtest.h"


#include <string>
#include <iostream>
#include <memory>

#include "Service.h"
#include "IMemMon.h"
#include "MemMon.h"

using namespace Mplane;

//============================================================================================================================================
namespace {
	static std::vector<std::string> savedMsgs ;
	static long int expectedUsage(0) ;
	static bool expectOverThreshold(false) ;

	void handleMsg(const std::string& msg)
	{
		std::cerr << msg << std::endl ;
		savedMsgs.push_back(msg) ;

		if (expectOverThreshold)
		{
			if (msg.find("Memory usage exceeded threshold"))
			{
				expectOverThreshold = false ;
			}
		}

		std::string usageStr(msg) ;
		long usage(0) ;

		std::size_t pos(msg.find("usageKb=")) ;
		std::size_t endpos(msg.find(" ", pos)) ;
		if (pos != std::string::npos)
		{
			usageStr = msg.substr(pos+8, endpos) ;
			usage = std::strtol(usageStr.c_str(), NULL, 10) ;

			if (expectedUsage == 0)
				return ;

			EXPECT_TRUE( (usage >= expectedUsage-10) && (usage <= expectedUsage+10) );
		}
	}
}


//--------------------------------------------------------------------------------------------------------------------------------------------
TEST(MemMonTests, Basic)
{
	std::shared_ptr<MemMon> memMon( std::make_shared<MemMon>() );
	std::shared_ptr<IMemMon> imemMon( std::dynamic_pointer_cast<IMemMon>(memMon) );
	std::shared_ptr<Service> service( std::dynamic_pointer_cast<Service>(imemMon) );
	expectedUsage = 0 ;
	savedMsgs.clear() ;

	ASSERT_TRUE(memMon.get() != 0) ;
	ASSERT_TRUE(imemMon.get() != 0) ;
	ASSERT_TRUE(service.get() != 0) ;

	EXPECT_EQ( Service::Start, service->start() ) ;
    sleep(1) ;

	EXPECT_TRUE( service->isRunning() ) ;

	EXPECT_EQ( Service::Shutdown, service->shutdown() );
    Task::msSleep( 200 );   // small sleep give it time to process but not as much as wait
//	EXPECT_FALSE( service->isRunning() ) ;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
// Kill this test because it's too difficult to ensure the test environment is stable enough for the test to pass (if anything else is being
// run/built on the server then memory usage will be changing during the test
#if 0
TEST(MemMonTests, OnChange)
{
	std::shared_ptr<MemMon> memMon( std::make_shared<MemMon>() );
	std::shared_ptr<IMemMon> imemMon( std::dynamic_pointer_cast<IMemMon>(memMon) );
	std::shared_ptr<Service> service( std::dynamic_pointer_cast<Service>(imemMon) );
	expectedUsage = 0 ;
	savedMsgs.clear() ;
	expectOverThreshold = false ;

	ASSERT_TRUE(memMon.get() != 0) ;
	ASSERT_TRUE(imemMon.get() != 0) ;
	ASSERT_TRUE(service.get() != 0) ;

	// Change settings
	imemMon->setUpdateRate(1) ;
	imemMon->setLogRate(IMemMon::ONCHANGE) ;
	imemMon->setLogging(true) ;
	imemMon->setLogFunction(handleMsg) ;
	EXPECT_EQ(0L, imemMon->getLastMemUsage()) ;

	long int current(imemMon->getCurrentMemUsage()) ;
	std::cerr << "Current mem = " << current << "kB" <<std::endl ;

	EXPECT_EQ( Service::Start, service->start() ) ;
	expectOverThreshold = true ;
	sleep(3) ;

	current = imemMon->getCurrentMemUsage() ;
	std::cerr << "Current (started) mem = " << current << "kB" <<std::endl ;
	expectedUsage = current ;

	imemMon->setThreshold(current+5) ;

    sleep(5) ;

    // allocate 10K
    expectedUsage = 0 ; // disable checks
    std::cerr << "Malloc 10k" << std::endl ;
    void* ptr = ::malloc(10 * 1024) ;
    sleep(3) ;

    // should have seen over threshold alarm
    EXPECT_FALSE(expectOverThreshold) ;

    std::cerr << "Free 10k" << std::endl ;
    if (ptr)
    	free(ptr) ;

    std::cerr << "Num messages=" << savedMsgs.size() << std::endl ;
    EXPECT_TRUE( (savedMsgs.size() >= 1) && (savedMsgs.size() <= 5) );

    for (auto saved : savedMsgs)
    {
    	std::cerr << "SAVED: " << saved << std::endl ;
    }

    EXPECT_EQ( Service::Shutdown, service->shutdown() );
    Task::msSleep( 200 );   // small sleep give it time to process but not as much as wait
	EXPECT_FALSE( service->isRunning() ) ;
}
#endif

//--------------------------------------------------------------------------------------------------------------------------------------------
TEST(MemMonTests, Periodic)
{
	std::shared_ptr<MemMon> memMon( std::make_shared<MemMon>() );
	std::shared_ptr<IMemMon> imemMon( std::dynamic_pointer_cast<IMemMon>(memMon) );
	std::shared_ptr<Service> service( std::dynamic_pointer_cast<Service>(imemMon) );
	expectedUsage = 0 ;
	savedMsgs.clear() ;
	expectOverThreshold = false ;

	ASSERT_TRUE(memMon.get() != 0) ;
	ASSERT_TRUE(imemMon.get() != 0) ;
	ASSERT_TRUE(service.get() != 0) ;

	// Change settings
	imemMon->setUpdateRate(1) ;
	imemMon->setLogRate(IMemMon::PERIODIC) ;
	imemMon->setLogging(true) ;
	imemMon->setLogFunction(handleMsg) ;
	EXPECT_EQ(0L, imemMon->getLastMemUsage()) ;

	long int current(imemMon->getCurrentMemUsage()) ;
	std::cerr << "Current mem = " << current << "kB" <<std::endl ;

	EXPECT_EQ( Service::Start, service->start() ) ;
	expectOverThreshold = true ;
	sleep(3) ;

	current = imemMon->getCurrentMemUsage() ;
	std::cerr << "Current (started) mem = " << current << "kB" <<std::endl ;
	expectedUsage = current ;

	imemMon->setThreshold(current+5) ;

    sleep(5) ;

    // allocate 10K
    expectedUsage = 0 ; // disable checks
    std::cerr << "Malloc 10k" << std::endl ;
    void* ptr = ::malloc(10 * 1024) ;
    sleep(3) ;

    // should have seen over threshold alarm
    EXPECT_FALSE(expectOverThreshold) ;

    std::cerr << "Free 10k" << std::endl ;
    if (ptr)
    	free(ptr) ;

    std::cerr << "Num messages=" << savedMsgs.size() << std::endl ;
    EXPECT_TRUE( (savedMsgs.size() >= 10) && (savedMsgs.size() <= 12) );

    for (auto saved : savedMsgs)
    {
    	std::cerr << "SAVED: " << saved << std::endl ;
    }

    EXPECT_EQ( Service::Shutdown, service->shutdown() );
    Task::msSleep( 200 );   // small sleep give it time to process but not as much as wait
	EXPECT_FALSE( service->isRunning() ) ;
}
