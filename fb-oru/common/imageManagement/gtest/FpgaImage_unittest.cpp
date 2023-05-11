/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaImage_unittest.cpp
 * \brief     Google Test of FpgaImage
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the FpgaImage class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "IAppSettingsFactory.h"
#include "AppSettings.h"

#include "Path.h"
#include "im_fixture.h"
#include "FpgaImage.h"

using namespace Mplane;

using namespace std;

//===========================================================================================================
// CLASSES

//-------------------------------------------------------------------------------------------------------------
class FpgaImageTest : public ImTestFixture
{
	using super = ImTestFixture ;

    virtual void SetUp()
    {
    	this->super::SetUp() ;

    	// tell test fixture that we're testing app
    	mImageType = "app" ;
    }

};


//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaImageTest, MethodsSimple)
{
    std::shared_ptr<FpgaImage> ib(new FpgaImage(mImageTask)) ;
    MethodsSimple(ib) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaImageTest, InstallChecks)
{
    std::shared_ptr<FpgaImage> ib(new FpgaImage(mImageTask)) ;
    InstallChecks(ib) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaImageTest, Download)
{
    std::shared_ptr<FpgaImage> ib(new FpgaImage(mImageTask)) ;
    Download(ib, "CDRSC2G6_Top-CPRI-4954.tgz", "TEST") ;
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaImageTest, FormatName)
{
    std::shared_ptr<FpgaImage> ib(new FpgaImage(mImageTask)) ;

    // format name
    std::string buildNumber("1234") ;
    std::string version("aversion") ;
    std::string name(ib->formatName(version, buildNumber)) ;

    // create expected name
	std::shared_ptr<IAppSettings> appSettings( IAppSettingsFactory::getInterface() ) ;
	std::string expectName("") ;

	EXPECT_EQ(expectName, name) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaImageTest, Methods)
{
	// Use the test version of the class to individually call the methods
    std::shared_ptr<TestImage<FpgaImage>> ib(new TestImage<FpgaImage>(mImageTask)) ;
    Methods(std::dynamic_pointer_cast<ITestImage>(ib), "CDRSC2G6_Top-CPRI-4954.tgz", "TEST", "") ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaImageTest, Clean)
{
    std::shared_ptr<FpgaImage> ib(new FpgaImage(mImageTask)) ;
    std::string failReason("") ;

    std::string fname( "CDRSC2G6_Top-CPRI-4954.tgz" ) ;
    std::string installedFile = getDownloadDir() + "/" + fname ;
    std::string current = getDownloadDir() + "/TEST" ;

    // Create initial file
    std::string cmd = std::string("touch ") + installedFile ;
    EXPECT_EQ(0, system(cmd.c_str())) ;
    EXPECT_TRUE(Path::createLink(current, installedFile)) ;

    // should now have 'current' link, but no 'previous' link
    std::string link ;
	EXPECT_TRUE(Path::exists(current)) ;
	EXPECT_TRUE(Path::isLink(current)) ;
	EXPECT_TRUE(Path::readLink(current, link)) ;
    EXPECT_EQ(installedFile, link) ;
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
    std::string tgz1( "CDRSC2G6_Top-CPRI-4955.tgz" ) ;
    std::string tgz2( "CDRSC2G6_Top-CPRI-4956.tgz" ) ;
    std::string tgz3( "CDRSC2G6_Top-CPRI-4957.tgz" ) ;
    std::string tgz4( "CDRSC2G6_Top-CPRI-4958.tgz" ) ;
    std::string tgz5( "CDRSC2G6_Top-CPRI-4959.tgz" ) ;
    std::string tgz6( "CDRSC2G6_Top-CPRI-4960.tgz" ) ;
    std::string tgz7( "CDRSC2G6_Top-CPRI-4961.tgz" ) ;

	Path::fileCopy(installedFile, getDownloadDir() + "/" + tgz1);
	Path::fileCopy(installedFile, getDownloadDir() + "/" + tgz2);
	Path::fileCopy(installedFile, getDownloadDir() + "/" + tgz3);
	Path::fileCopy(installedFile, getDownloadDir() + "/" + tgz4);
	Path::fileCopy(installedFile, getDownloadDir() + "/" + tgz5);
	Path::fileCopy(installedFile, getDownloadDir() + "/" + tgz6);
	Path::fileCopy(installedFile, getDownloadDir() + "/" + tgz7);
	Path::fileCopy(installedFile + ".md5", getDownloadDir() + "/" + tgz7 + ".md5");

	// run clean - remove everything
    EXPECT_TRUE( ib->setInstallDir(getDownloadDir(), failReason) );
    EXPECT_TRUE( ib->clean(failReason) );
    if (!failReason.empty())
    	std::cerr << "Fail: " << failReason << std::endl ;

std::cerr << "installedFile=" << installedFile << " getDownloadDir()=" << getDownloadDir() << std::endl ;
    EXPECT_FALSE(Path::exists(current)) ;
    EXPECT_FALSE(Path::exists(installedFile)) ;
	EXPECT_FALSE(Path::exists(getDownloadDir() + "/" + tgz1)) ;
	EXPECT_FALSE(Path::exists(getDownloadDir() + "/" + tgz2)) ;
	EXPECT_FALSE(Path::exists(getDownloadDir() + "/" + tgz3)) ;
	EXPECT_FALSE(Path::exists(getDownloadDir() + "/" + tgz4)) ;
	EXPECT_FALSE(Path::exists(getDownloadDir() + "/" + tgz5)) ;
	EXPECT_FALSE(Path::exists(getDownloadDir() + "/" + tgz6)) ;
	EXPECT_FALSE(Path::exists(getDownloadDir() + "/" + tgz7)) ;
	EXPECT_FALSE(Path::exists(getDownloadDir() + "/" + tgz7 + ".md5")) ;
}
