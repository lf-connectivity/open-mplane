/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      cm_fixture.cpp
 * \brief     Cal Download Management test fixture
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <stdlib.h>

#include <string>
#include <iostream>
#include <algorithm>

#include "Path.h"
#include "cm_fixture.h"
#include "RxCalDownload.h"
#include "TxCalDownload.h"

using namespace Mplane;


//===================================================================================================================
// DATA
//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
std::string CmTestFixture::mTempDir("") ;
std::string CmTestFixture::mDownloadDir("") ;
std::string CmTestFixture::mNandDir("") ;
std::shared_ptr<RxCalDownload> CmTestFixture::rxcdl( new RxCalDownload() );
std::shared_ptr<TxCalDownload> CmTestFixture::txcdl( new TxCalDownload() );


//===================================================================================================================
// STATIC METHODS
//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
std::string CmTestFixture::getTempDir(void)
{
	if (mTempDir.empty())
	{
	    // Create a user-specific temp directory in which to run tests
	    std::string user(::getenv("USER")) ;
	    if (user.empty())
	    	user = "test" ;
	    mTempDir = std::string("/tmp/") + user + "-cal" ;
	}

	return mTempDir ;
}


//-------------------------------------------------------------------------------------------------------------------
std::string CmTestFixture::getDownloadDir(void)
{
	if (mDownloadDir.empty())
	{
	    // Create a user-specific temp directory in which to run tests
	    std::string tempDir( getTempDir() ) ;
	    mDownloadDir = tempDir + "/install" ;
	}

	return mDownloadDir ;
}

//-------------------------------------------------------------------------------------------------------------------
std::string CmTestFixture::getNandDir(void)
{
	if (mNandDir.empty())
	{
	    // Create a user-specific temp directory in which to run tests
	    std::string tempDir( getTempDir() ) ;
	    mNandDir = tempDir + "/nandflash" ;
	}

	return mNandDir ;
}


//===================================================================================================================
// TEST FIXTURE METHODS
//===================================================================================================================



//-------------------------------------------------------------------------------------------------------------------
void CmTestFixture::SetUp()
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    std::cout << test_info->name() << " - START" <<  std::endl;

    // Create a user-specific temp directory in which to run tests
    Path::removeDirContents(getTempDir(), true) ;
    Path::removeDirContents(getDownloadDir(), true) ;
    Path::removeDirContents(getNandDir(), true) ;

    Path::mkpath(getTempDir()) ;
    Path::mkpath(getDownloadDir()) ;
    Path::mkpath(getNandDir()) ;

    std::cerr << "TEMP: " << getTempDir() << std::endl ;
    std::cerr << "INSTALL: " << getDownloadDir() << std::endl ;
    std::cerr << "NAND: " << getNandDir() << std::endl ;

}


//-------------------------------------------------------------------------------------------------------------------
void CmTestFixture::TearDown()
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << test_info->name() << " - END" <<  std::endl;
}




//===================================================================================================================
// TEST METHODS
//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
void CmTestFixture::MethodsSimple(std::shared_ptr<ITestCalDownload> cd)
{
	cd->setNandDir(getNandDir()) ;

    std::string failReason ;
    cd->initialise(failReason) ;

    cd->show() ;
    cd->setRemoteUrl("http://served", failReason);
    cd->setInstallDir(getDownloadDir(), failReason);

    cd->getAndInstall("test.xml", failReason) ;
}


//-------------------------------------------------------------------------------------------------------------
void CmTestFixture::InstallChecks(std::shared_ptr<ITestCalDownload> cd)
{
	cd->setNandDir(getNandDir()) ;

    std::string failReason("") ;
    EXPECT_TRUE( cd->initialise(failReason) );
    EXPECT_EQ( std::string(""), failReason );

    // install file will be set by default
    // install dir will be set by default

    // this should fail due to no server url
    EXPECT_TRUE( cd->setInstallFileName("test.xml", failReason) );
    EXPECT_FALSE( cd->getAndInstall("test.xml", failReason) );
    EXPECT_EQ( std::string("Server URL not set"), failReason );
    failReason.clear();

    EXPECT_TRUE( cd->setRemoteUrl("http://./served", failReason) );
}

//-------------------------------------------------------------------------------------------------------------
void CmTestFixture::Download(std::shared_ptr<ITestCalDownload> cd, const std::string& fname)
{
	cd->setNandDir(getNandDir()) ;

    std::string failReason("") ;
    EXPECT_TRUE( cd->initialise(failReason) );
    EXPECT_EQ( std::string(""), failReason );

    // this should fail due to no url
    EXPECT_FALSE( cd->getAndInstall("test.xml", failReason) );
    EXPECT_EQ( std::string("Server URL not set"), failReason );
    failReason.clear();

    // expected to fail
    EXPECT_TRUE( cd->setInstallFileName(fname, failReason) );
    EXPECT_TRUE( cd->setInstallDir(getDownloadDir(), failReason) );
    EXPECT_TRUE( cd->setRemoteUrl("http://swin-11/~guest/test_files/cal", failReason) );
    EXPECT_FALSE( cd->getAndInstall(std::string("XXX-") + fname, failReason) );

    std::string expected("Failed to download http://swin-11/~guest/test_files/cal/XXX-" + fname) ;
    EXPECT_TRUE(failReason.find(expected) != std::string::npos) ;
    Path::remove(std::string("/tmp/XXX-") + fname) ;

    if (!failReason.empty())
    	std::cerr << "EXPECTED: " << failReason << std::endl ;
    failReason.clear() ;

    // expected to work
    EXPECT_TRUE( cd->setInstallFileName(fname, failReason) );
    EXPECT_TRUE( cd->setInstallDir(getDownloadDir(), failReason) );
    EXPECT_TRUE( cd->setRemoteUrl("http://swin-11/~guest/test_files/cal", failReason) );
    EXPECT_TRUE( cd->getAndInstall(fname, failReason) );

    if (!failReason.empty())
    	std::cerr << "Fail: " << failReason << std::endl ;
    failReason.clear() ;

    // check file existence
    std::string xml = getDownloadDir() + "/" + fname ;
    EXPECT_TRUE(Path::exists(xml)) ;


}

//-------------------------------------------------------------------------------------------------------------
void CmTestFixture::DownloadUseInstall(std::shared_ptr<ITestCalDownload> cd, const std::string& fname)
{
	cd->setNandDir(getNandDir()) ;

    std::string failReason("") ;
    EXPECT_TRUE( cd->initialise(failReason) );
    EXPECT_EQ( std::string(""), failReason );

    EXPECT_TRUE( cd->setInstallDir(getDownloadDir(), failReason) );
    EXPECT_TRUE( cd->setRemoteUrl("http://swin-11/~guest/test_files/cal", failReason) );
    EXPECT_TRUE( cd->getAndInstall(fname, failReason) );

    if (!failReason.empty())
    	std::cerr << "Fail: " << failReason << std::endl ;
    failReason.clear() ;

    // check file existence
    std::string xml = getDownloadDir() + "/" + cd->getInstallFileName() ;
    EXPECT_TRUE(Path::exists(xml)) ;

    // Does installed xml file path match expected
    EXPECT_EQ(xml, cd->getInstallFilePath()) ;


}


//-------------------------------------------------------------------------------------------------------------
void Mplane::CmTestFixture::clearStatus(void) {
	mStatus.clear() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::CmTestFixture::getStatus(void) {
	return mStatus ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::CmTestFixture::writeStatus(const std::string& status) {

	std::cerr << "status update: " << status ;
	mStatus.append(status) ;
}

std::shared_ptr<RxCalDownload> Mplane::CmTestFixture::getRxcdl()
{
    return rxcdl;
}

std::shared_ptr<TxCalDownload> Mplane::CmTestFixture::getTxcdl()
{
    return txcdl;
}
