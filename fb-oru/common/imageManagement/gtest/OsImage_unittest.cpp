/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OsImage_unittest.cpp
 * \brief     Google Test of OsImage
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the OsImage class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "IAppSettingsFactory.h"
#include "AppSettings.h"
#include "IBootEnv.h"

#include "Path.h"
#include "im_fixture.h"

#include "OsImage.h"

using namespace Mplane;

using namespace std;

//===========================================================================================================
// CLASSES

//-------------------------------------------------------------------------------------------------------------
class OsImageTest : public ImTestFixture
{
	using super = ImTestFixture ;

    virtual void SetUp()
    {
    	this->super::SetUp() ;

    	// tell test fixture that we're testing os
    	mImageType = "os" ;
    }

};



//===========================================================================================================
// TESTS


//-------------------------------------------------------------------------------------------------------------
TEST_F(OsImageTest, MethodsSimple)
{
    std::shared_ptr<OsImage> ib(new OsImage(mImageTask)) ;
    MethodsSimple(ib) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(OsImageTest, InstallChecks)
{
    std::shared_ptr<OsImage> ib(new OsImage(mImageTask)) ;
    InstallChecks(ib) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(OsImageTest, FormatName)
{
    std::shared_ptr<OsImage> ib(new OsImage(mImageTask)) ;

    // format name
    std::string buildNumber("1234") ;
    std::string version("aversion") ;
    std::string name(ib->formatName(version, buildNumber)) ;

    // create expected name
	std::shared_ptr<IAppSettings> appSettings( IAppSettingsFactory::getInterface() ) ;
	std::string expectName = "os." + buildNumber + "-ROS_" +
				appSettings->getAppString() + ".tgz" ;

	EXPECT_EQ(expectName, name) ;
}


#if 0
//-------------------------------------------------------------------------------------------------------------
TEST_F(OsImageTest, DownloadBad)
{
    std::shared_ptr<OsImage> ib(new OsImage(mImageTask)) ;
    DownloadBad(ib, "os.30-ROS_FTU.tgz") ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(OsImageTest, Download)
{
    std::shared_ptr<OsImage> ib(new OsImage(mImageTask)) ;

    std::string failReason("") ;
    EXPECT_TRUE( ib->initialise(failReason) );
    EXPECT_EQ( std::string(""), failReason );

    // this should fail due to no image name
    EXPECT_FALSE( ib->getAndInstall(failReason) );
    EXPECT_EQ( std::string("Image name not set"), failReason );
    failReason.clear();

    std::string fname("os.30-ROS_FTU.tgz") ;

    ib->show() ;

    // expected to fail
    EXPECT_TRUE( ib->setImageName(fname, failReason) );
    EXPECT_TRUE( ib->setInstallDir(getDownloadDir(), failReason) );
    EXPECT_TRUE( ib->setRemoteUrl("http://swin-11/~guest/test_files/xx-images", failReason) );
    EXPECT_FALSE( ib->getAndInstall(failReason) );
    EXPECT_EQ(std::string("Failed to download os.30-ROS_FTU.tgz"), failReason) ;


    // expected to work
    failReason.clear() ;
	EXPECT_TRUE( ib->setUbootInstall(true, failReason) ) ;
    EXPECT_TRUE( ib->setImageName(fname, failReason) );
    EXPECT_TRUE( ib->setInstallDir(getDownloadDir(), failReason) );
    EXPECT_TRUE( ib->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) );

    EXPECT_TRUE( ib->getAndInstall(failReason) );

    if (!failReason.empty())
    	std::cerr << "Fail: " << failReason << std::endl ;
    failReason.clear() ;

    // check file existence
    std::string tgz = getDownloadDir() + "/" + fname ;
    EXPECT_FALSE(Path::exists(tgz)) ;
    std::string md5 = getDownloadDir() + "/" + fname + ".md5" ;
    EXPECT_TRUE(Path::exists(md5)) ;

    for (auto linkName : {"pImage2", "dtb2", "u-boot"})
    {
		std::string current = getDownloadDir() + "/" + linkName ;
		EXPECT_TRUE(Path::exists(current)) ;
		EXPECT_TRUE(Path::isLink(current)) ;
		std::string link ;
		EXPECT_TRUE(Path::readLink(current, link)) ;
		EXPECT_EQ(md5, link) ;
    }
    for (auto linkName : {"pImage1", "dtb1"})
    {
		std::string current = getDownloadDir() + "/" + linkName ;
		EXPECT_FALSE(Path::exists(current)) ;
    }

    // Check NOR has been "flashed"
    EXPECT_FALSE(Path::exists(getNorDir() + "/boot1/pImage.30-ROS_FTU")) ;
    EXPECT_FALSE(Path::exists(getNorDir() + "/dtb1/axis-dtb.30-ROS_FTU")) ;
    EXPECT_TRUE(Path::exists(getNorDir() + "/boot2/pImage.30-ROS_FTU")) ;
    EXPECT_TRUE(Path::exists(getNorDir() + "/dtb2/axis-dtb.30-ROS_FTU")) ;
    EXPECT_TRUE(Path::exists(getNorDir() + "/u-boot/uboot.30-ROS_FTU")) ;

    ib->show() ;

    // Run again - should be NO-OP as already downloaded
    Path::removeDirContents(getNorDir(), true) ;

    EXPECT_TRUE( ib->getAndInstall(failReason) );

    if (!failReason.empty())
    	std::cerr << "Fail: " << failReason << std::endl ;
    failReason.clear() ;


    // Check NOR has NOT been "flashed"
    EXPECT_FALSE(Path::exists(getNorDir() + "/boot1/pImage.30-ROS_FTU")) ;
    EXPECT_FALSE(Path::exists(getNorDir() + "/dtb1/axis-dtb.30-ROS_FTU")) ;
    EXPECT_FALSE(Path::exists(getNorDir() + "/boot2/pImage.30-ROS_FTU")) ;
    EXPECT_FALSE(Path::exists(getNorDir() + "/dtb2/axis-dtb.30-ROS_FTU")) ;
    EXPECT_FALSE(Path::exists(getNorDir() + "/u-boot/uboot.30-ROS_FTU")) ;

    ib->show() ;
}
#endif

//-------------------------------------------------------------------------------------------------------------
TEST_F(OsImageTest, Methods)
{
	// Clear down the BootEnv first - sets active OS to BANK1
	std::shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance()) ;
	bootEnv->reset() ;

	// Use the test version of the class to individually call the methods
    std::shared_ptr<TestImage<OsImage>> ib(new TestImage<OsImage>(mImageTask)) ;

    std::string failReason("") ;
    EXPECT_TRUE(ib->initialise(failReason)) ;

    std::string fname("os.30-ROS_FTU.tgz") ;

    std::string installedFile = getDownloadDir() + "/" + fname ;
    std::string md5File = installedFile + ".md5" ;

    failReason.clear() ;
	EXPECT_TRUE( ib->setUbootInstall(false, failReason) ) ;
    EXPECT_TRUE( ib->setImageName(fname, failReason) );
    EXPECT_TRUE( ib->setInstallDir(getDownloadDir(), failReason) );
    EXPECT_TRUE( ib->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) );

    EXPECT_FALSE( ib->alreadyDownloaded() ) ;
    EXPECT_FALSE( ib->alreadyInstalled() ) ;

    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;


    // download only - should NOT be affected by file space
    ib->mFreeSpace = false ;
    EXPECT_TRUE( ib->download(failReason) );

    // download only - should work
    failReason.clear() ;
    ib->mFreeSpace = true ;
    EXPECT_TRUE( ib->download(failReason) );

    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;


    // Run check
    EXPECT_TRUE( ib->check(failReason) );

    EXPECT_FALSE( ib->alreadyDownloaded() ) ;
    EXPECT_FALSE( ib->alreadyInstalled() ) ;

    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;


    // Install - installs into BANK2 *and* BANK1
    std::cerr << "INSTALL 1" << std::endl ;
    EXPECT_TRUE( ib->install(failReason) );

    EXPECT_TRUE( ib->alreadyDownloaded() ) ;
    EXPECT_TRUE( ib->alreadyInstalled() ) ;

    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;


    // should now have links
    std::string md5 = getDownloadDir() + "/" + fname + ".md5" ;
    std::string link ;
    for (auto linkName : {"pImage1", "dtb1"})
    {
		std::string current = getDownloadDir() + "/" + linkName ;
		EXPECT_TRUE(Path::exists(current)) ;
		EXPECT_TRUE(Path::isLink(current)) ;
		std::string link ;
		EXPECT_TRUE(Path::readLink(current, link)) ;
		EXPECT_EQ(md5, link) ;
    }
    for (auto linkName : {"pImage2", "dtb2"})
    {
    	// default now is to also install to the other bank
		std::string current = getDownloadDir() + "/" + linkName ;
		EXPECT_TRUE(Path::exists(current)) ;
    }
    for (auto linkName : {"u-boot"})
    {
    	// default now is to also install to the other bank
		std::string current = getDownloadDir() + "/" + linkName ;
		EXPECT_FALSE(Path::exists(current)) ;
    }


    // Check NOR has been "flashed"
    EXPECT_TRUE(Path::exists(getNorDir() + "/boot1/pImage.30-ROS_FTU")) ;
    EXPECT_TRUE(Path::exists(getNorDir() + "/dtb1/axis-dtb.30-ROS_FTU")) ;
    EXPECT_TRUE(Path::exists(getNorDir() + "/boot2/pImage.30-ROS_FTU")) ;
    EXPECT_TRUE(Path::exists(getNorDir() + "/dtb2/axis-dtb.30-ROS_FTU")) ;
    EXPECT_FALSE(Path::exists(getNorDir() + "/u-boot/uboot.30-ROS_FTU")) ;


    Path::removeDirContents(getNorDir(), true) ;

    // Change to installing u-boot
	EXPECT_TRUE( ib->setUbootInstall(true, failReason) ) ;
    EXPECT_FALSE( ib->alreadyDownloaded() ) ;
    EXPECT_FALSE( ib->alreadyInstalled() ) ;


    // Download again
    EXPECT_TRUE( ib->download(failReason) );

    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;

    EXPECT_FALSE( ib->alreadyDownloaded() ) ;
    EXPECT_FALSE( ib->alreadyInstalled() ) ;

	// install again - installs into BANK2
    std::cerr << "INSTALL 2" << std::endl ;
    EXPECT_TRUE( ib->install(failReason) );
    for (auto linkName : {"pImage1", "dtb1", "u-boot"})
    {
		std::string current = getDownloadDir() + "/" + linkName ;
		EXPECT_TRUE(Path::exists(current)) ;
		EXPECT_TRUE(Path::isLink(current)) ;
		std::string link ;
		EXPECT_TRUE(Path::readLink(current, link)) ;
		EXPECT_EQ(md5, link) ;
    }
    for (auto linkName : {"pImage2", "dtb2"})
    {
		std::string current = getDownloadDir() + "/" + linkName ;
		EXPECT_TRUE(Path::exists(current)) ;
    }

    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;

    EXPECT_TRUE( ib->alreadyDownloaded() ) ;
    EXPECT_TRUE( ib->alreadyInstalled() ) ;

    EXPECT_FALSE(Path::exists(getNorDir() + "/boot1/pImage.30-ROS_FTU")) ;
    EXPECT_FALSE(Path::exists(getNorDir() + "/dtb1/axis-dtb.30-ROS_FTU")) ;
    EXPECT_TRUE(Path::exists(getNorDir() + "/boot2/pImage.30-ROS_FTU")) ;
    EXPECT_TRUE(Path::exists(getNorDir() + "/dtb2/axis-dtb.30-ROS_FTU")) ;
    EXPECT_TRUE(Path::exists(getNorDir() + "/u-boot/uboot.30-ROS_FTU")) ;

    ib->show() ;

	std::cerr << "NOR: " << getNorDir() << std::endl ;

}

//-------------------------------------------------------------------------------------------------------------
TEST_F(OsImageTest, Clean)
{
    std::shared_ptr<OsImage> ib(new OsImage(mImageTask)) ;

    std::string failReason("") ;

    std::string fname("os.30-ROS_FTU.tgz") ;

    std::string installedFile = getDownloadDir() + "/" + fname ;
    std::string current = getDownloadDir() + "/current" ;
    std::string previous = getDownloadDir() + "/previous" ;

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

    // Set up with some dummy values
    EXPECT_TRUE( ib->setInstallDir(getDownloadDir(), failReason) );
    std::string cmd = std::string("touch ") + getDownloadDir() + "/bank1.md5" ;
    system(cmd.c_str()) ;
    Path::fileCopy(getDownloadDir() + "/bank1.md5", getDownloadDir() + "/bank2.md5") ;
    Path::fileCopy(getDownloadDir() + "/bank1.md5", getDownloadDir() + "/dtb1.md5") ;
    Path::fileCopy(getDownloadDir() + "/bank1.md5", getDownloadDir() + "/dtb2.md5") ;
    Path::fileCopy(getDownloadDir() + "/bank1.md5", getDownloadDir() + "/uboot.md5") ;
    Path::fileCopy(getDownloadDir() + "/bank1.md5", getDownloadDir() + "/delete1.md5") ;
    Path::fileCopy(getDownloadDir() + "/bank1.md5", getDownloadDir() + "/delete2.md5") ;
    Path::fileCopy(getDownloadDir() + "/bank1.md5", getDownloadDir() + "/delete3.md5") ;


    Path::createLink(getDownloadDir() + "/pImage1", getDownloadDir() + "/bank1.md5") ;
    Path::createLink(getDownloadDir() + "/pImage2", getDownloadDir() + "/bank2.md5") ;
    Path::createLink(getDownloadDir() + "/dtb1", getDownloadDir() + "/dtb1.md5") ;
    Path::createLink(getDownloadDir() + "/dtb2", getDownloadDir() + "/dtb2.md5") ;
    Path::createLink(getDownloadDir() + "/u-boot", getDownloadDir() + "/uboot.md5") ;
    Path::createLink(getDownloadDir() + "/xxx", getDownloadDir() + "/ubootxxx.md5") ;

std::cerr << "getDownloadDir()=" << getDownloadDir() << std::endl ;

    EXPECT_TRUE(Path::exists(getDownloadDir() + "/bank1.md5")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/bank2.md5")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/dtb1.md5")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/dtb2.md5")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/uboot.md5")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/delete1.md5")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/delete2.md5")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/delete3.md5")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/pImage1")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/pImage2")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/dtb1")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/dtb2")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/u-boot")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/xxx")) ;

    failReason.clear() ;
    EXPECT_TRUE( ib->clean(failReason) );
    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;

    EXPECT_TRUE(Path::exists(getDownloadDir() + "/bank1.md5")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/bank2.md5")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/dtb1.md5")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/dtb2.md5")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/uboot.md5")) ;
    EXPECT_FALSE(Path::exists(getDownloadDir() + "/delete1.md5")) ;
    EXPECT_FALSE(Path::exists(getDownloadDir() + "/delete2.md5")) ;
    EXPECT_FALSE(Path::exists(getDownloadDir() + "/delete3.md5")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/pImage1")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/pImage2")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/dtb1")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/dtb2")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/u-boot")) ;
    EXPECT_FALSE(Path::exists(getDownloadDir() + "/xxx")) ;


    // Break a link
    Path::remove(getDownloadDir() + "/bank1.md5") ;

    EXPECT_TRUE( ib->clean(failReason) );
    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;

    EXPECT_FALSE(Path::exists(getDownloadDir() + "/bank1.md5")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/bank2.md5")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/dtb1.md5")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/dtb2.md5")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/uboot.md5")) ;
    EXPECT_FALSE(Path::exists(getDownloadDir() + "/delete1.md5")) ;
    EXPECT_FALSE(Path::exists(getDownloadDir() + "/delete2.md5")) ;
    EXPECT_FALSE(Path::exists(getDownloadDir() + "/delete3.md5")) ;
    EXPECT_FALSE(Path::exists(getDownloadDir() + "/pImage1")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/pImage2")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/dtb1")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/dtb2")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/u-boot")) ;
    EXPECT_FALSE(Path::exists(getDownloadDir() + "/xxx")) ;

    // Remove a link
    Path::remove(getDownloadDir() + "/pImage2") ;

    EXPECT_TRUE( ib->clean(failReason) );
    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;

    EXPECT_FALSE(Path::exists(getDownloadDir() + "/bank1.md5")) ;
    EXPECT_FALSE(Path::exists(getDownloadDir() + "/bank2.md5")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/dtb1.md5")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/dtb2.md5")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/uboot.md5")) ;
    EXPECT_FALSE(Path::exists(getDownloadDir() + "/delete1.md5")) ;
    EXPECT_FALSE(Path::exists(getDownloadDir() + "/delete2.md5")) ;
    EXPECT_FALSE(Path::exists(getDownloadDir() + "/delete3.md5")) ;
    EXPECT_FALSE(Path::exists(getDownloadDir() + "/pImage1")) ;
    EXPECT_FALSE(Path::exists(getDownloadDir() + "/pImage2")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/dtb1")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/dtb2")) ;
    EXPECT_TRUE(Path::exists(getDownloadDir() + "/u-boot")) ;
    EXPECT_FALSE(Path::exists(getDownloadDir() + "/xxx")) ;


}
