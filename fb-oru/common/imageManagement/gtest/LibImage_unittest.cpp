/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LibImage_unittest.cpp
 * \brief     Google Test of LibImage
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the LibImage class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "IAppSettingsFactory.h"
#include "AppSettings.h"

#include "Path.h"
#include "LibImage.h"

#include "im_fixture.h"

using namespace Mplane;

using namespace std;

//===========================================================================================================
// CLASSES

//-------------------------------------------------------------------------------------------------------------
class LibImageTest : public ImTestFixture
{
	using super = ImTestFixture ;

    virtual void SetUp()
    {
    	this->super::SetUp() ;

    	// tell test fixture that we're testing lib
    	mImageType = "lib" ;
    }

};


//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST_F(LibImageTest, MethodsSimple)
{
    std::shared_ptr<LibImage> ib(new LibImage(mImageTask)) ;
    MethodsSimple(ib) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(LibImageTest, InstallChecks)
{
    std::shared_ptr<LibImage> ib(new LibImage(mImageTask)) ;
    InstallChecks(ib) ;
}

#if 0
//-------------------------------------------------------------------------------------------------------------
TEST_F(LibImageTest, Download)
{
    std::shared_ptr<LibImage> ib(new LibImage(mImageTask)) ;
    Download(ib, "ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz") ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(LibImageTest, DownloadBad)
{
    std::shared_ptr<LibImage> ib(new LibImage(mImageTask)) ;
    DownloadBad(ib, "ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz") ;
}
#endif


//-------------------------------------------------------------------------------------------------------------
TEST_F(LibImageTest, FormatName)
{
    std::shared_ptr<LibImage> ib(new LibImage(mImageTask)) ;

    // format name
    std::string buildNumber("1234") ;
    std::string version("aversion") ;
    std::string name(ib->formatName(version, buildNumber)) ;

    // create expected name
	std::shared_ptr<IAppSettings> appSettings( IAppSettingsFactory::getInterface() ) ;
	std::string expectName =
		appSettings->getBoardString() + "-" +
		appSettings->getCustomerString() + "-" +
		appSettings->getAppString() + "-" +
		version + "-" +
		buildNumber ;
	expectName.append("-LIB.tgz") ;

	EXPECT_EQ(expectName, name) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST_F(LibImageTest, Methods)
{
	// Use the test version of the class to individually call the methods
    std::shared_ptr<TestImage<LibImage>> ib(new TestImage<LibImage>(mImageTask)) ;
    Methods(std::dynamic_pointer_cast<ITestImage>(ib), "ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz") ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(LibImageTest, Clean)
{
    std::shared_ptr<LibImage> ib(new LibImage(mImageTask)) ;
    Clean(ib) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(LibImageTest, DownloadMd5list)
{
    std::shared_ptr<LibImage> ib(new LibImage(mImageTask)) ;

    std::string failReason("") ;
    EXPECT_TRUE( ib->initialise(failReason) );
    EXPECT_EQ( std::string(""), failReason );

    // expected to work
    std::string fname("ETNA-AXIS-FTU-TDD-CPRI-0.0-33-LIB.tgz") ;
    EXPECT_TRUE( ib->setImageName(fname, failReason) );
    EXPECT_TRUE( ib->setInstallDir(getDownloadDir(), failReason) );
    EXPECT_TRUE( ib->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) );
    EXPECT_TRUE( ib->getAndInstall(failReason) );

    if (!failReason.empty())
    	std::cerr << "Fail: " << failReason << std::endl ;
    failReason.clear() ;

    std::string current = getDownloadDir() + "/current" ;
    std::string previous = getDownloadDir() + "/previous" ;
    std::string link ;

    // check file existence
    std::string baseTgz = getDownloadDir() + "/" + fname ;
    std::string tgz = getDownloadDir() + "/" + fname ;
    EXPECT_TRUE(Path::exists(tgz)) ;
    EXPECT_TRUE(Path::isFile(tgz)) ;
    std::string md5 = tgz + ".md5" ;
    EXPECT_TRUE(Path::exists(md5)) ;
    EXPECT_TRUE(Path::isFile(md5)) ;
    std::string md5list = tgz + ".md5list" ;
    EXPECT_TRUE(Path::exists(md5list)) ;
    EXPECT_TRUE(Path::isFile(md5list)) ;

    EXPECT_TRUE(Path::exists(current)) ;
    EXPECT_TRUE(Path::isLink(current)) ;
    EXPECT_TRUE(Path::readLink(current, link)) ;
    EXPECT_EQ(tgz, link) ;
    EXPECT_FALSE(Path::exists(previous)) ;



    //== Request for 34 should just use 33 since md5list is same ==
    fname = "ETNA-AXIS-FTU-TDD-CPRI-0.0-34-LIB.tgz" ;
    EXPECT_TRUE( ib->setImageName(fname, failReason) );
    EXPECT_TRUE( ib->getAndInstall(failReason) );

    if (!failReason.empty())
    	std::cerr << "Fail: " << failReason << std::endl ;
    failReason.clear() ;

    // check file existence - tarball should just be a link to 33
    tgz = getDownloadDir() + "/" + fname ;
    EXPECT_TRUE(Path::exists(tgz)) ;
    EXPECT_FALSE(Path::isFile(tgz)) ;
    EXPECT_TRUE(Path::isLink(tgz)) ;
    md5 = tgz + ".md5" ;
    EXPECT_TRUE(Path::isLink(md5)) ;
    EXPECT_FALSE(Path::isFile(md5)) ;
    md5list = tgz + ".md5list" ;
    EXPECT_TRUE(Path::isLink(md5list)) ;
    EXPECT_FALSE(Path::isFile(md5list)) ;

    EXPECT_TRUE(Path::exists(current)) ;
    EXPECT_TRUE(Path::isLink(current)) ;
    EXPECT_TRUE(Path::readLink(current, link)) ;
    EXPECT_EQ(tgz, link) ;
    EXPECT_TRUE(Path::exists(previous)) ;
    EXPECT_TRUE(Path::isLink(previous)) ;
    EXPECT_TRUE(Path::readLink(previous, link)) ;
    EXPECT_EQ(baseTgz, link) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST_F(LibImageTest, CleanMd5list)
{
    std::shared_ptr<LibImage> ib(new LibImage(mImageTask)) ;

    std::string failReason("") ;

    std::string current = getDownloadDir() + "/current" ;
    std::string previous = getDownloadDir() + "/previous" ;

    EXPECT_TRUE( ib->setInstallDir(getDownloadDir(), failReason) );
    EXPECT_TRUE( ib->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) );

	// create some dummy files
    std::string A(getDownloadDir() + "/A.tgz") ;
    std::string B(getDownloadDir() + "/B.tgz") ;
    std::string C(getDownloadDir() + "/C.tgz") ;
    std::string D(getDownloadDir() + "/D.tgz") ;
    std::string dummy(getDownloadDir() + "/dummy") ;

    std::string cmd = std::string("touch ") + A ;
    system(cmd.c_str()) ;
    Path::fileCopy(A, B) ;
    Path::fileCopy(A, C) ;
    Path::fileCopy(A, D) ;
    Path::fileCopy(A, dummy) ;

    // Create some "trees" of links
    Path::createLink(getDownloadDir() + "/a1.tgz", A) ;
    Path::createLink(getDownloadDir() + "/a2.tgz", A) ;
    Path::createLink(getDownloadDir() + "/a3.tgz", A) ;
    Path::createLink(getDownloadDir() + "/a4.tgz", A) ;
    Path::createLink(getDownloadDir() + "/a5.tgz", A) ;

    Path::createLink(getDownloadDir() + "/b1.tgz", B) ;
    Path::createLink(getDownloadDir() + "/b2.tgz", B) ;
    Path::createLink(getDownloadDir() + "/b3.tgz", B) ;
    Path::createLink(getDownloadDir() + "/b4.tgz", B) ;
    Path::createLink(getDownloadDir() + "/b5.tgz", B) ;

    Path::createLink(getDownloadDir() + "/c1.tgz", C) ;
    Path::createLink(getDownloadDir() + "/c2.tgz", C) ;
    Path::createLink(getDownloadDir() + "/c3.tgz", C) ;
    Path::createLink(getDownloadDir() + "/c4.tgz", C) ;
    Path::createLink(getDownloadDir() + "/c5.tgz", C) ;

    // Create top links to the trees
    Path::createLink(getDownloadDir() + "/current", getDownloadDir() + "/a4.tgz") ;
    Path::createLink(getDownloadDir() + "/previous", getDownloadDir() + "/b2.tgz") ;
    Path::createLink(getDownloadDir() + "/keep", D) ;


    // Test for all files

    /*
    lrwxrwxrwx 1 sprice wtl_axis 31 Nov 23 15:46 a1.tgz -> /tmp/sprice-image/install/A.tgz
    lrwxrwxrwx 1 sprice wtl_axis 31 Nov 23 15:46 a2.tgz -> /tmp/sprice-image/install/A.tgz
    lrwxrwxrwx 1 sprice wtl_axis 31 Nov 23 15:46 a3.tgz -> /tmp/sprice-image/install/A.tgz
    lrwxrwxrwx 1 sprice wtl_axis 31 Nov 23 15:46 a4.tgz -> /tmp/sprice-image/install/A.tgz
    lrwxrwxrwx 1 sprice wtl_axis 31 Nov 23 15:46 a5.tgz -> /tmp/sprice-image/install/A.tgz
    -rw-r--r-- 1 sprice wtl_axis  0 Nov 23 15:46 A.tgz
    lrwxrwxrwx 1 sprice wtl_axis 31 Nov 23 15:46 b1.tgz -> /tmp/sprice-image/install/B.tgz
    lrwxrwxrwx 1 sprice wtl_axis 31 Nov 23 15:46 b2.tgz -> /tmp/sprice-image/install/B.tgz
    lrwxrwxrwx 1 sprice wtl_axis 31 Nov 23 15:46 b3.tgz -> /tmp/sprice-image/install/B.tgz
    lrwxrwxrwx 1 sprice wtl_axis 31 Nov 23 15:46 b4.tgz -> /tmp/sprice-image/install/B.tgz
    lrwxrwxrwx 1 sprice wtl_axis 31 Nov 23 15:46 b5.tgz -> /tmp/sprice-image/install/B.tgz
    -rw-r--r-- 1 sprice wtl_axis  0 Nov 23 15:46 B.tgz
    lrwxrwxrwx 1 sprice wtl_axis 31 Nov 23 15:46 c1.tgz -> /tmp/sprice-image/install/C.tgz
    lrwxrwxrwx 1 sprice wtl_axis 31 Nov 23 15:46 c2.tgz -> /tmp/sprice-image/install/C.tgz
    lrwxrwxrwx 1 sprice wtl_axis 31 Nov 23 15:46 c3.tgz -> /tmp/sprice-image/install/C.tgz
    lrwxrwxrwx 1 sprice wtl_axis 31 Nov 23 15:46 c4.tgz -> /tmp/sprice-image/install/C.tgz
    lrwxrwxrwx 1 sprice wtl_axis 31 Nov 23 15:46 c5.tgz -> /tmp/sprice-image/install/C.tgz
    -rw-r--r-- 1 sprice wtl_axis  0 Nov 23 15:46 C.tgz
    lrwxrwxrwx 1 sprice wtl_axis 32 Nov 23 15:46 current -> /tmp/sprice-image/install/a4.tgz
    -rw-r--r-- 1 sprice wtl_axis  0 Nov 23 15:46 D.tgz
    -rw-r--r-- 1 sprice wtl_axis  0 Nov 23 15:46 dummy
    lrwxrwxrwx 1 sprice wtl_axis 31 Nov 23 15:46 keep -> /tmp/sprice-image/install/D.tgz
    lrwxrwxrwx 1 sprice wtl_axis 32 Nov 23 15:46 previous -> /tmp/sprice-image/install/b2.tgz
    */

    EXPECT_TRUE(Path::isFile(A)) ;
    EXPECT_TRUE(Path::isFile(B)) ;
    EXPECT_TRUE(Path::isFile(C)) ;
    EXPECT_TRUE(Path::isFile(D)) ;
    EXPECT_TRUE(Path::isFile(dummy)) ;

    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/a1.tgz")) ;
    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/a2.tgz")) ;
    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/a3.tgz")) ;
    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/a4.tgz")) ;
    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/a5.tgz")) ;

    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/b1.tgz")) ;
    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/b2.tgz")) ;
    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/b3.tgz")) ;
    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/b4.tgz")) ;
    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/b5.tgz")) ;

    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/c1.tgz")) ;
    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/c2.tgz")) ;
    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/c3.tgz")) ;
    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/c4.tgz")) ;
    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/c5.tgz")) ;

    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/current")) ;
    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/previous")) ;
    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/keep")) ;




	// run clean
    EXPECT_TRUE( ib->clean(failReason) );


    // Test for all files
    // After cleaning, expect the files to now look like:
    /*
    lrwxrwxrwx 1 sprice wtl_axis 31 Nov 23 15:46 a4.tgz -> /tmp/sprice-image/install/A.tgz
    -rw-r--r-- 1 sprice wtl_axis  0 Nov 23 15:46 A.tgz
    lrwxrwxrwx 1 sprice wtl_axis 31 Nov 23 15:46 b2.tgz -> /tmp/sprice-image/install/B.tgz
    -rw-r--r-- 1 sprice wtl_axis  0 Nov 23 15:46 B.tgz
    lrwxrwxrwx 1 sprice wtl_axis 32 Nov 23 15:46 current -> /tmp/sprice-image/install/a4.tgz
    -rw-r--r-- 1 sprice wtl_axis  0 Nov 23 15:46 D.tgz
    lrwxrwxrwx 1 sprice wtl_axis 31 Nov 23 15:46 keep -> /tmp/sprice-image/install/D.tgz
    lrwxrwxrwx 1 sprice wtl_axis 32 Nov 23 15:46 previous -> /tmp/sprice-image/install/b2.tgz
    */

    EXPECT_TRUE(Path::isFile(A)) ;
    EXPECT_TRUE(Path::isFile(B)) ;
    EXPECT_FALSE(Path::isFile(C)) ;
    EXPECT_TRUE(Path::isFile(D)) ;
    EXPECT_FALSE(Path::isFile(dummy)) ;

    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/a1.tgz")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/a2.tgz")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/a3.tgz")) ;
    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/a4.tgz")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/a5.tgz")) ;

    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/b1.tgz")) ;
    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/b2.tgz")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/b3.tgz")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/b4.tgz")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/b5.tgz")) ;

    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/c1.tgz")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/c2.tgz")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/c3.tgz")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/c4.tgz")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/c5.tgz")) ;

    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/current")) ;
    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/previous")) ;
    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/keep")) ;

    // Remove some links
    Path::remove(getDownloadDir() + "/keep") ;
    Path::remove(getDownloadDir() + "/previous") ;

	// run clean
    EXPECT_TRUE( ib->clean(failReason) );

    /*
    lrwxrwxrwx 1 sprice wtl_axis 31 Nov 23 16:06 a4.tgz -> /tmp/sprice-image/install/A.tgz
    -rw-r--r-- 1 sprice wtl_axis  0 Nov 23 16:06 A.tgz
    lrwxrwxrwx 1 sprice wtl_axis 32 Nov 23 16:06 current -> /tmp/sprice-image/install/a4.tgz
    */

    EXPECT_TRUE(Path::isFile(A)) ;
    EXPECT_FALSE(Path::isFile(B)) ;
    EXPECT_FALSE(Path::isFile(C)) ;
    EXPECT_FALSE(Path::isFile(D)) ;
    EXPECT_FALSE(Path::isFile(dummy)) ;

    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/a1.tgz")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/a2.tgz")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/a3.tgz")) ;
    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/a4.tgz")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/a5.tgz")) ;

    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/b1.tgz")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/b2.tgz")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/b3.tgz")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/b4.tgz")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/b5.tgz")) ;

    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/c1.tgz")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/c2.tgz")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/c3.tgz")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/c4.tgz")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/c5.tgz")) ;

    EXPECT_TRUE(Path::isLink(getDownloadDir() + "/current")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/previous")) ;
    EXPECT_FALSE(Path::isLink(getDownloadDir() + "/keep")) ;
}
