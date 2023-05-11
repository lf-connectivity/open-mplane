/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CalDownloadManagement_unittest.cpp
 * \brief     Google Test of CalDownloadManagement
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the CalDownloadManagement class.
 *
 */

#include <gtest/gtest.h>

#include <stdlib.h>

#include <string>
#include <iostream>
#include <memory>

#include "Path.h"
#include "cm_fixture.h"
#include "CalDownloadManagement.h"
#include "RxCalDownload.h"
#include "TxCalDownload.h"

using namespace Mplane;

using namespace std;


//===========================================================================================================
// CLASSES

//-------------------------------------------------------------------------------------------------------------
class CalDownloadMgrTest : public CmTestFixture
{
	using super = CmTestFixture ;
};


//-------------------------------------------------------------------------------------------------------------
class TestCalDownloadManagement : public CalDownloadManagement {
public:
	TestCalDownloadManagement() :
		CalDownloadManagement()
	{
	    // Create a user-specific temp directory in which to run tests - needs to match up with test fixture
//		std::string nandDir( CmTestFixture::getNandDir() );

	    // Amend the install directory for each object
//		std::string failReason ;

//		std::shared_ptr<RxCalDownload> rxcdl( new RxCalDownload );
//	    std::shared_ptr<TxCalDownload> txcdl( new TxCalDownload );


//		std::static_pointer_cast<ITestCalDownload>(getCalDownload(ICalDownloadTypes::CAL_FILE_TX))->setInstallDir(nandDir + "/cal", failReason) ;
//		std::static_pointer_cast<ITestCalDownload>(getCalDownload(ICalDownloadTypes::CAL_FILE_RX))->setInstallDir(nandDir + "/cal", failReason) ;

	    addCalDownloadType( CmTestFixture::getRxcdl() );
	    addCalDownloadType( CmTestFixture::getTxcdl() );


	}

	virtual ~TestCalDownloadManagement() {}
};

std::shared_ptr<ICalDownloadManagement> ICalDownloadManagement::getInstance()
{
	static std::shared_ptr<ICalDownloadManagement> instance(new TestCalDownloadManagement()) ;
	static int start = std::dynamic_pointer_cast<TestCalDownloadManagement>(instance)->start() ;

	// avoid compiler warning
	int rc = start ; start = rc ;

	return instance ;
}

//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST_F(CalDownloadMgrTest, MethodsSimple)
{
	std::shared_ptr<CalDownloadManagement> cm(new TestCalDownloadManagement) ;

    std::string failReason ;


    cm->show() ;
    cm->setRemoteUrl("http://server-of-great-repute", failReason) ;
    cm->isDownloading() ;
    cm->isDownloadOk(failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(CalDownloadMgrTest, ArgChecks)
{
	std::shared_ptr<CalDownloadManagement> cm(new TestCalDownloadManagement) ;
	cm->start() ;

    std::string failReason ;

    cm->show() ;

    std::shared_ptr<Conditional> endSignal(new Conditional) ;

    getRxcdl()->initialise(failReason) ;
    getTxcdl()->initialise(failReason) ;

    // fail because server url not set
    EXPECT_FALSE( cm->getAndInstall( getTxcdl()->getName(), "ftu_tx_cal.xml", failReason, endSignal) ) ;

    if (!failReason.empty())
    	std::cerr << "EXPECTED: " << failReason << std::endl ;
    failReason.clear() ;

    // fail because file not found - will start ok
    EXPECT_TRUE( cm->setRemoteUrl("http://swin-11/~guest/test_files/cal", failReason) ) ;
    EXPECT_TRUE( cm->getAndInstall( getTxcdl()->getName(), "xxx_tx_cal.xml", failReason, endSignal) ) ;

    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;

    // wait for complete
    endSignal->wait() ;

    // Expect error
    EXPECT_FALSE(cm->isDownloadOk(failReason)) ;
    if (!failReason.empty())
    	std::cerr << "EXPECTED: " << failReason << std::endl ;
    failReason.clear() ;


std::cerr << "getAndInstall(" << getTxcdl()->getName() << ", ftu_tx_cal.xml)" << std::endl ;

    // should work
    EXPECT_TRUE( cm->getAndInstall( getTxcdl()->getName(), "ftu_tx_cal.xml", failReason, endSignal) ) ;

    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;

    // should be running for a few secs
    EXPECT_TRUE(cm->isDownloading()) ;

    // wait for complete
    endSignal->wait() ;

    // Expect no error
    EXPECT_TRUE(cm->isDownloadOk(failReason)) ;
    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;

    // show installed
    cm->show() ;

    // Should now have installed file
    EXPECT_TRUE(Path::exists(getNandDir() + "/cal/txcal.xml")) ;

    // show installed
    cm->show() ;


    // stop
	std::cerr << "Stopping task..." << std::endl ;
	cm->shutdown() ;
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(CalDownloadMgrTest, Singleton)
{
	// Check multiple instances only start once
	std::shared_ptr<ICalDownloadManagement> cm(ICalDownloadManagement::getInstance()) ;
	std::shared_ptr<ICalDownloadManagement> cm2(ICalDownloadManagement::getInstance()) ;
	std::shared_ptr<ICalDownloadManagement> cm3(ICalDownloadManagement::getInstance()) ;

    std::string failReason ;

    cm->show() ;

    std::shared_ptr<Conditional> endSignal(new Conditional) ;

    getRxcdl()->initialise(failReason) ;
    getTxcdl()->initialise(failReason) ;

    // should work
    EXPECT_TRUE( cm->setRemoteUrl("http://swin-11/~guest/test_files/cal", failReason) ) ;
    EXPECT_TRUE( cm->getAndInstall(getRxcdl()->getName(), "ftu_rx_cal.xml", failReason, endSignal) ) ;

    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;

    // should be running for a few secs
    EXPECT_TRUE(cm->isDownloading()) ;

    // wait for complete
    endSignal->wait() ;

    // Expect no error
    EXPECT_TRUE(cm->isDownloadOk(failReason)) ;
    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;

    // show installed
    cm->show() ;

    // Should now have installed file
    EXPECT_TRUE(Path::exists(getNandDir() + "/cal/rxcal.xml")) ;

}
