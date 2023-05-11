/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PkgImage_unittest.cpp
 * \brief     Google Test of PkgImage
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the PkgImage class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "IAppSettingsFactory.h"
#include "AppSettings.h"

#include "Path.h"
#include "IImageManagement.h"
#include "PkgImage.h"

#include "im_fixture.h"

using namespace Mplane;

using namespace std;

//===========================================================================================================
// CLASSES

//-------------------------------------------------------------------------------------------------------------
class PkgImageTest : public ImTestFixture
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
TEST_F(PkgImageTest, MethodsSimple)
{
    std::shared_ptr<PkgImage> ib(new PkgImage(mImageTask)) ;
    MethodsSimple(ib) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(PkgImageTest, InstallChecks)
{
    std::shared_ptr<PkgImage> ib(new PkgImage(mImageTask)) ;
    InstallChecks(ib) ;
}

#if 0
//-------------------------------------------------------------------------------------------------------------
TEST_F(PkgImageTest, Download)
{
    std::shared_ptr<PkgImage> ib(new PkgImage(mImageTask)) ;

    std::string failReason ;
	std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;
	imageMgr->setUbootInstall(true, failReason) ;

    Download(ib, "FTU-0.0-35.pkg") ;

    // This package contains:
	//    os	os.30-ROS_FTU.tgz			399ca28c621dba14b45e506ec7d2acad
	//    app	ETNA-AXIS-FTU-TDD-CPRI-0.0-35-APP.tgz	b73c958b4ce40a45acbba21c2757e6a2
	//    lib	ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz	b7ad5de353dc534dd9546d7e32b69c24


    // check app file existence
    std::string appName("ETNA-AXIS-FTU-TDD-CPRI-0.0-35-APP.tgz") ;
    std::string tgz = getNandDir() + "/app-images/" + appName ;
std::cerr << "APP: tgz=" << tgz << std::endl ;
    EXPECT_TRUE(Path::exists(tgz)) ;
    std::string md5 = tgz + ".md5" ;
    EXPECT_TRUE(Path::exists(md5)) ;
    std::string current = getNandDir() + "/app-images/current" ;
    EXPECT_TRUE(Path::exists(current)) ;
    EXPECT_TRUE(Path::isLink(current)) ;
    std::string link ;
    EXPECT_TRUE(Path::readLink(current, link)) ;
    EXPECT_EQ(tgz, link) ;

    // check lib file existence
    std::string libName("ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz") ;
    tgz = getNandDir() + "/lib-images/" + libName ;
    EXPECT_TRUE(Path::exists(tgz)) ;
    md5 = tgz + ".md5" ;
    EXPECT_TRUE(Path::exists(md5)) ;
    current = getNandDir() + "/lib-images/current" ;
    EXPECT_TRUE(Path::exists(current)) ;
    EXPECT_TRUE(Path::isLink(current)) ;
    EXPECT_TRUE(Path::readLink(current, link)) ;
    EXPECT_EQ(tgz, link) ;

    // check os file existence
    std::string osName("os.30-ROS_FTU.tgz") ;
    tgz = getNandDir() + "/os-images/" + osName ;
    EXPECT_FALSE(Path::exists(tgz)) ;
    md5 = tgz + ".md5" ;
    EXPECT_TRUE(Path::exists(md5)) ;
    current = getNandDir() + "/os-images/pImage1" ;
    EXPECT_TRUE(Path::exists(current)) ;
    EXPECT_TRUE(Path::isLink(current)) ;
    EXPECT_TRUE(Path::readLink(current, link)) ;
    EXPECT_EQ(md5, link) ;
    current = getNandDir() + "/os-images/dtb1" ;
    EXPECT_TRUE(Path::exists(current)) ;
    EXPECT_TRUE(Path::isLink(current)) ;
    EXPECT_TRUE(Path::readLink(current, link)) ;
    EXPECT_EQ(md5, link) ;
    current = getNandDir() + "/os-images/u-boot" ;
    EXPECT_TRUE(Path::exists(current)) ;
    EXPECT_TRUE(Path::isLink(current)) ;
    EXPECT_TRUE(Path::readLink(current, link)) ;
    EXPECT_EQ(md5, link) ;

}


////-------------------------------------------------------------------------------------------------------------
//TEST_F(PkgImageTest, DownloadBad)
//{
//    std::shared_ptr<PkgImage> ib(new PkgImage(mImageTask)) ;
//    DownloadBad(ib, "FTU-0.0-35.pkg") ;
//}
#endif

//-------------------------------------------------------------------------------------------------------------
TEST_F(PkgImageTest, FormatName)
{
    std::shared_ptr<PkgImage> ib(new PkgImage(mImageTask)) ;

    // format name
    std::string buildNumber("1234") ;
    std::string version("aversion") ;
    std::string name(ib->formatName(version, buildNumber)) ;

    // create expected name
	std::shared_ptr<IAppSettings> appSettings( IAppSettingsFactory::getInterface() ) ;
	std::string expectName =
			appSettings->getBoardString() + "-" +
			appSettings->getAppString() + "-" +
			version + "-" +
			buildNumber +
			".pkg" ;

	EXPECT_EQ(expectName, name) ;

}



//-------------------------------------------------------------------------------------------------------------
TEST_F(PkgImageTest, Clean)
{
    std::shared_ptr<PkgImage> ib(new PkgImage(mImageTask)) ;
    Clean(ib) ;
}
