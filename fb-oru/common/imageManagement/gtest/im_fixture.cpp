/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      im_fixture.cpp
 * \brief     Image Management test fixture
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include <string>
#include <iostream>
#include <algorithm>

#include "IBootEnv.h"
#include "Path.h"
#include "im_fixture.h"

using namespace Mplane;


//===================================================================================================================
// DATA
//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
std::string ImTestFixture::mTempDir("") ;
std::string ImTestFixture::mDownloadDir("") ;
std::string ImTestFixture::mNorDir("") ;
std::string ImTestFixture::mNandDir("") ;

//===================================================================================================================
// WorkingDir METHODS
//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
std::string WorkingDir::wd(".") ;

void WorkingDir::getWd()
{
	char buff[PATH_MAX] ;
	WorkingDir::wd = std::string(getcwd(buff, sizeof(buff))) ;

	std::cerr << "WorkingDir::getWd() " << WorkingDir::wd << std::endl ;
}

void WorkingDir::chdirWd()
{
	std::cerr << "WorkingDir::chdirWd() " << WorkingDir::wd << std::endl ;
	chdir(WorkingDir::wd.c_str()) ;
}

//===================================================================================================================
// STATIC METHODS
//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
std::string ImTestFixture::getTempDir(void)
{
	if (mTempDir.empty())
	{
	    // Create a user-specific temp directory in which to run tests
	    std::string user(::getenv("USER")) ;
	    if (user.empty())
	    	user = "test" ;
	    mTempDir = std::string("/tmp/") + user + "-image" ;
	}

	return mTempDir ;
}


//-------------------------------------------------------------------------------------------------------------------
std::string ImTestFixture::getDownloadDir(void)
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
std::string ImTestFixture::getNorDir(void)
{
	if (mNorDir.empty())
	{
	    // Create a user-specific temp directory in which to run tests
	    std::string tempDir( getTempDir() ) ;
	    mNorDir = tempDir + "/NOR" ;
	}

	return mNorDir ;
}


//-------------------------------------------------------------------------------------------------------------------
std::string ImTestFixture::getNandDir(void)
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
void ImTestFixture::SetUp()
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    std::cout << test_info->name() << " - START" <<  std::endl;

    mImageType = "?" ;

	// Clear down the BootEnv first - sets active OS to BANK1
	std::shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance()) ;
	bootEnv->reset() ;

	Mplane::ILoggable::setLogDebugLevel(Mplane::ILoggable::LOG_DEBUG_VERBOSE) ;

	// Create a user-specific temp directory in which to run tests
    Path::removeDirContents(getTempDir(), true) ;
    Path::removeDirContents(getDownloadDir(), true) ;
    Path::removeDirContents(getNorDir(), true) ;
    Path::removeDirContents(getNandDir(), true) ;

    Path::mkpath(getTempDir()) ;
    Path::mkpath(getDownloadDir()) ;
    Path::mkpath(getNorDir()) ;
    Path::mkpath(getNandDir()) ;
}


//-------------------------------------------------------------------------------------------------------------------
void ImTestFixture::TearDown()
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << test_info->name() << " - END" <<  std::endl;

	// Clear out any temp files
    system("rm -f /tmp/ETNA* 2>/dev/null") ;
    system("rm -f /tmp/test.tgz* 2>/dev/null") ;
    system("rm -f /tmp/gmon* 2>/dev/null") ;
    system("rm -rf /tmp/os-temp 2>/dev/null") ;
    system("rm -rf /tmp/manifest* 2>/dev/null") ;
}





//===================================================================================================================
// TEST METHODS
//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
void ImTestFixture::MethodsSimple(std::shared_ptr<IImage> ib)
{
    std::string failReason ;
    ib->initialise(failReason) ;

    ib->show() ;
    ib->setImageName("test.tgz", failReason);
    ib->setRemoteUrl("http://served", failReason);
    ib->setInstallDir(getDownloadDir(), failReason);
    ib->clean(failReason);

    std::string name = ib->formatName("0.0", "123") ;

    ib->getAndInstall(failReason) ;
}


//-------------------------------------------------------------------------------------------------------------
void ImTestFixture::InstallChecks(std::shared_ptr<IImage> ib)
{
    std::string failReason("") ;
    EXPECT_TRUE( ib->initialise(failReason) );
    EXPECT_EQ( std::string(""), failReason );

    // this should fail due to no image name
    EXPECT_FALSE( ib->getAndInstall(failReason) );
    EXPECT_EQ( std::string("Image name not set"), failReason );
    failReason.clear();

    // install dir will be set by default

    // this should fail due to no server url
    EXPECT_TRUE( ib->setImageName("test.tgz", failReason) );
    EXPECT_FALSE( ib->getAndInstall(failReason) );
    EXPECT_EQ( std::string("Server URL not set"), failReason );
    failReason.clear();

    EXPECT_TRUE( ib->setRemoteUrl("http://./served", failReason) );
}

//-------------------------------------------------------------------------------------------------------------
void ImTestFixture::Download(std::shared_ptr<IImage> ib, const std::string& fname, const std::string& currentLink)
{
    std::string failReason("") ;
    EXPECT_TRUE( ib->initialise(failReason) );
    EXPECT_EQ( std::string(""), failReason );

    // this should fail due to no image name
    EXPECT_FALSE( ib->getAndInstall(failReason) );
    EXPECT_EQ( std::string("Image name not set"), failReason );
    failReason.clear();

    // expected to fail
    EXPECT_TRUE( ib->setImageName(std::string("XXX-") + fname, failReason) );
    EXPECT_TRUE( ib->setInstallDir(getDownloadDir(), failReason) );
    EXPECT_TRUE( ib->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) );
    EXPECT_FALSE( ib->getAndInstall(failReason) );
    EXPECT_EQ(std::string("Failed to download XXX-") + fname, failReason) ;
    Path::remove(std::string("/tmp/XXX-") + fname) ;

    if (!failReason.empty())
    	std::cerr << "EXPECTED: " << failReason << std::endl ;
    failReason.clear() ;

    // expected to work
    EXPECT_TRUE( ib->setImageName(fname, failReason) );
    EXPECT_TRUE( ib->setInstallDir(getDownloadDir(), failReason) );
    EXPECT_TRUE( ib->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) );
    EXPECT_TRUE( ib->getAndInstall(failReason) );

    if (!failReason.empty())
    	std::cerr << "Fail: " << failReason << std::endl ;
    failReason.clear() ;

    // check file existence
    std::string tgz = getDownloadDir() + "/" + fname ;
    EXPECT_TRUE(Path::exists(tgz)) ;
    std::string md5 = getDownloadDir() + "/" + fname + ".md5" ;
    EXPECT_TRUE(Path::exists(md5)) ;

    // Check for link existence and pointing at correct file
    std::string linkPath = getDownloadDir() + "/" + currentLink;
    EXPECT_TRUE(Path::exists(linkPath)) ;
    EXPECT_TRUE(Path::isLink(linkPath)) ;

    std::string link ;
    EXPECT_TRUE(Path::readLink(linkPath, link));
    EXPECT_EQ(link, tgz) ;

}


//-------------------------------------------------------------------------------------------------------------
void ImTestFixture::DownloadBad(std::shared_ptr<IImage> ib, const std::string& fname)
{
    std::string failReason("") ;
    EXPECT_TRUE( ib->initialise(failReason) );
    EXPECT_EQ( std::string(""), failReason );

    // this should fail due to no image name
    EXPECT_FALSE( ib->getAndInstall(failReason) );
    EXPECT_EQ( std::string("Image name not set"), failReason );
    failReason.clear();

    // download files with bad MD5
    EXPECT_TRUE( ib->setImageName(fname, failReason) );
    EXPECT_TRUE( ib->setInstallDir(getDownloadDir(), failReason) );
    EXPECT_TRUE( ib->setRemoteUrl("http://swin-11/~guest/test_files/bad-images", failReason) );
    EXPECT_FALSE( ib->getAndInstall(failReason) );
    EXPECT_EQ(fname + " failed MD5 check", failReason) ;
    if (!failReason.empty())
    	std::cerr << "EXPECTED: " << failReason << std::endl ;
    failReason.clear() ;

    // check file existence - should have deleted bad files
    std::string tgz = getDownloadDir() + "/" + fname ;
    EXPECT_FALSE(Path::exists(tgz)) ;
    std::string md5 = getDownloadDir() + "/" + fname + ".md5" ;
    EXPECT_FALSE(Path::exists(md5)) ;

}


//-------------------------------------------------------------------------------------------------------------
void ImTestFixture::Methods(std::shared_ptr<ITestImage> ib, const std::string& fname,
		const std::string& currentLink,
		const std::string& previousLink)
{
	// Use the test version of the class to individually call the methods
    std::string failReason("") ;

	EXPECT_TRUE(ib->initialise(failReason)) ;


    std::string installedFile = getDownloadDir() + "/" + fname ;
    std::string current = getDownloadDir() + "/" + currentLink ;
    std::string previous ;
    if (!previousLink.empty())
    	previous = getDownloadDir() + "/" + previousLink ;

    EXPECT_TRUE( ib->setImageName(fname, failReason) );
    EXPECT_TRUE( ib->setInstallDir(getDownloadDir(), failReason) );
    EXPECT_TRUE( ib->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) );

    EXPECT_FALSE( ib->alreadyDownloaded() ) ;
    EXPECT_FALSE( ib->alreadyInstalled() ) ;

    // download only - should fail with no space
    ib->setFreeSpace(false) ;
    EXPECT_FALSE( ib->download(failReason) );

    // download only - should work
    ib->setFreeSpace(true) ;
    EXPECT_TRUE( ib->download(failReason) );

    // Run check
    EXPECT_TRUE( ib->check(failReason) );

    EXPECT_TRUE( ib->alreadyDownloaded() ) ;
    EXPECT_FALSE( ib->alreadyInstalled() ) ;

	EXPECT_FALSE(Path::exists(current)) ;
	EXPECT_FALSE(Path::exists(previous)) ;

    // Install
    EXPECT_TRUE( ib->install(failReason) );

    EXPECT_TRUE( ib->alreadyDownloaded() ) ;
    EXPECT_TRUE( ib->alreadyInstalled() ) ;

    // should now have 'current' link, but no 'previous' link
    std::string link ;
	EXPECT_TRUE(Path::exists(current)) ;
	EXPECT_TRUE(Path::isLink(current)) ;
	EXPECT_TRUE(Path::readLink(current, link)) ;
    EXPECT_EQ(installedFile, link) ;
    if (!previous.empty())
    {
    	EXPECT_FALSE(Path::exists(previous)) ;
    }

    if (!previous.empty())
    {
		// install again which should set up previous
		EXPECT_TRUE( ib->install(failReason) );
		EXPECT_TRUE(Path::exists(current)) ;
		EXPECT_TRUE(Path::isLink(current)) ;
		EXPECT_TRUE(Path::readLink(current, link)) ;
		EXPECT_EQ(installedFile, link) ;
		EXPECT_TRUE(Path::exists(previous)) ;
		EXPECT_TRUE(Path::isLink(previous)) ;
		EXPECT_TRUE(Path::readLink(previous, link)) ;
		EXPECT_EQ(installedFile, link) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void ImTestFixture::Clean(std::shared_ptr<IImage> ib,
		const std::string& currentLink,
		const std::string& previousLink)
{
    std::string failReason("") ;

    std::string fname( ib->formatName("0.0", "35") ) ;
    std::string installedFile = getDownloadDir() + "/" + fname ;
    std::string current = getDownloadDir() + "/" + currentLink ;
    std::string previous ;
    if (!previousLink.empty())
    	previous = getDownloadDir() + "/" + previousLink ;

    // Create initial file
    std::string cmd = std::string("touch ") + installedFile ;
    EXPECT_EQ(0, system(cmd.c_str())) ;
    EXPECT_TRUE(Path::createLink(current, installedFile)) ;
    if (!previous.empty())
    {
    	EXPECT_TRUE(Path::createLink(previous, installedFile)) ;
    }

    // should now have 'current' link, but no 'previous' link
    std::string link ;
	EXPECT_TRUE(Path::exists(current)) ;
	EXPECT_TRUE(Path::isLink(current)) ;
	EXPECT_TRUE(Path::readLink(current, link)) ;
    EXPECT_EQ(installedFile, link) ;

    if (!previous.empty())
    {
		EXPECT_TRUE(Path::exists(previous)) ;
		EXPECT_TRUE(Path::isLink(previous)) ;
		EXPECT_TRUE(Path::readLink(previous, link)) ;
		EXPECT_EQ(installedFile, link) ;
    }

    failReason.clear() ;

    // fail - install dir not set
    EXPECT_FALSE( ib->clean(failReason) );
    EXPECT_EQ(std::string("Install directory not set to valid directory"), failReason) ;
    if (!failReason.empty())
    	std::cerr << "EXPECTED: " << failReason << std::endl ;
    failReason.clear() ;

    // install dir set to invalid dir - should silently pass
    EXPECT_TRUE( ib->setInstallDir("/tmp/xxxxxXXXXXXXXXXXxxxx/wibble", failReason) );
    EXPECT_TRUE( ib->clean(failReason) );
    EXPECT_EQ(std::string(""), failReason) ;
    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;

	// create some dummy files
    std::string tgz1( ib->formatName("3.0", "6") ) ;
    std::string tgz2( ib->formatName("3.1", "1") ) ;
    std::string tgz3( ib->formatName("5.1", "100") ) ;
    std::string tgz4( ib->formatName("0.0", "32") ) ;
    std::string tgz5( ib->formatName("0.0", "30") ) ;
    std::string tgz6( ib->formatName("0.0", "2") ) ;
    std::string tgz7( ib->formatName("0.0", "5") ) ;

	Path::fileCopy(installedFile, getDownloadDir() + "/" + tgz1);
	Path::fileCopy(installedFile, getDownloadDir() + "/" + tgz2);
	Path::fileCopy(installedFile, getDownloadDir() + "/" + tgz3);
	Path::fileCopy(installedFile, getDownloadDir() + "/" + tgz4);
	Path::fileCopy(installedFile, getDownloadDir() + "/" + tgz5);
	Path::fileCopy(installedFile, getDownloadDir() + "/" + tgz6);
	Path::fileCopy(installedFile, getDownloadDir() + "/" + tgz7);
	Path::fileCopy(installedFile + ".md5", getDownloadDir() + "/" + tgz7 + ".md5");

	// run clean - leave current/previous
    EXPECT_TRUE( ib->setInstallDir(getDownloadDir(), failReason) );
    EXPECT_TRUE( ib->clean(failReason) );
    if (!failReason.empty())
    	std::cerr << "Fail: " << failReason << std::endl ;
    failReason.clear() ;

	EXPECT_TRUE(Path::exists(current)) ;
	EXPECT_TRUE(Path::isLink(current)) ;
	EXPECT_TRUE(Path::readLink(current, link)) ;
    EXPECT_EQ(installedFile, link) ;

    if (!previous.empty())
    {
		EXPECT_TRUE(Path::exists(previous)) ;
		EXPECT_TRUE(Path::isLink(previous)) ;
		EXPECT_TRUE(Path::readLink(previous, link)) ;
		EXPECT_EQ(installedFile, link) ;
    }

	EXPECT_TRUE(Path::exists(installedFile)) ;
	EXPECT_FALSE(Path::exists(getDownloadDir() + "/" + tgz1)) ;
	EXPECT_FALSE(Path::exists(getDownloadDir() + "/" + tgz2)) ;
	EXPECT_FALSE(Path::exists(getDownloadDir() + "/" + tgz3)) ;
	EXPECT_FALSE(Path::exists(getDownloadDir() + "/" + tgz4)) ;
	EXPECT_FALSE(Path::exists(getDownloadDir() + "/" + tgz5)) ;
	EXPECT_FALSE(Path::exists(getDownloadDir() + "/" + tgz6)) ;
	EXPECT_FALSE(Path::exists(getDownloadDir() + "/" + tgz7)) ;
	EXPECT_FALSE(Path::exists(getDownloadDir() + "/" + tgz7 + ".md5")) ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::ImTestFixture::clearStatus(void) {
	mStatus.clear() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::ImTestFixture::getStatus(void) {
	return mStatus ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::ImTestFixture::writeStatus(const std::string& status) {

	std::cerr << "status update: " << status ;
	mStatus.append(status) ;
}
