/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ImageBase_unittest.cpp
 * \brief     Google Test of ImageBase
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the ImageBase class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "Path.h"
#include "im_fixture.h"
#include "ImageBase.h"

using namespace Mplane;

using namespace std;

//===========================================================================================================
// CLASSES

//-------------------------------------------------------------------------------------------------------------
class ImageBaseTest : public ImTestFixture
{
	using super = ImTestFixture ;

    virtual void SetUp()
    {
    	this->super::SetUp() ;

    	// tell test fixture that we're testing base
    	mImageType = "base" ;
    }

};


//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST_F(ImageBaseTest, MethodsSimple)
{
    std::shared_ptr<ImageBase> ib(new ImageBase(mImageTask, "ImageBase")) ;
    MethodsSimple(ib) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(ImageBaseTest, InstallChecks)
{
    std::shared_ptr<ImageBase> ib(new ImageBase(mImageTask, "ImageBase")) ;

    std::string failReason("") ;
    EXPECT_TRUE( ib->initialise(failReason) );
    EXPECT_EQ( std::string(""), failReason );

    // this should fail due to no image name
    EXPECT_FALSE( ib->getAndInstall(failReason) );
    EXPECT_EQ( std::string("Image name not set"), failReason );
    failReason.clear();

    // check install dir
    EXPECT_TRUE( ib->setImageName("test.tgz", failReason) );
    EXPECT_FALSE( ib->getAndInstall(failReason) );
    EXPECT_EQ( std::string("Install directory not set"), failReason );
    failReason.clear();

    // this should fail due to no server url
    EXPECT_TRUE( ib->setInstallDir("/tmp", failReason) );
    EXPECT_FALSE( ib->getAndInstall(failReason) );
    EXPECT_EQ( std::string("Server URL not set"), failReason );
    failReason.clear();

    EXPECT_TRUE( ib->setRemoteUrl("http://./served", failReason) );
}

#if 0
//-------------------------------------------------------------------------------------------------------------
TEST_F(ImageBaseTest, Download)
{
    std::shared_ptr<ImageBase> ib(new ImageBase(mImageTask, "ImageBase")) ;
    Download(ib, "ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz") ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(ImageBaseTest, DownloadBad)
{
    std::shared_ptr<ImageBase> ib(new ImageBase(mImageTask, "ImageBase")) ;
    DownloadBad(ib, "ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz") ;
}
#endif

//-------------------------------------------------------------------------------------------------------------
TEST_F(ImageBaseTest, Methods)
{
	// Use the test version of the class to individually call the methods
    std::shared_ptr<TestImage<ImageBase>> ib(new TestImage<ImageBase>(mImageTask, "ImageBase")) ;
    Methods(std::dynamic_pointer_cast<ITestImage>(ib), "ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz") ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(ImageBaseTest, Clean)
{
    std::shared_ptr<ImageBase> ib(new ImageBase(mImageTask, "ImageBase")) ;
    Clean(ib) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(ImageBaseTest, getVersionBuild)
{
    std::shared_ptr<TestImage<ImageBase>> ib(new TestImage<ImageBase>(mImageTask, "ImageBase")) ;

    std::string baseName ;
    float version ;
    unsigned buildNumber ;
    EXPECT_TRUE( ib->getVersionBuild("ETNA-AXIS-FTU-TDD-CPRI-0.0-32-LIB.tgz", baseName, version, buildNumber) ) ;
    EXPECT_EQ(0.0f, version) ;
    EXPECT_EQ(32u, buildNumber) ;
    EXPECT_EQ(std::string("ETNA-AXIS-FTU-TDD-CPRI"), baseName) ;

    EXPECT_TRUE( ib->getVersionBuild("ETNAAXISFTUTDDCPRI-10.3-1-LIB.tgz", baseName, version, buildNumber) ) ;
    EXPECT_EQ(10.3f, version) ;
    EXPECT_EQ(1u, buildNumber) ;
    EXPECT_EQ(std::string("ETNAAXISFTUTDDCPRI"), baseName) ;

    EXPECT_FALSE( ib->getVersionBuild("ETNA-AXIS-FTU-TDD-CPRI-0.0-32.tgz", baseName, version, buildNumber) ) ;

}
