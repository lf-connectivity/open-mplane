/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AppImage_unittest.cpp
 * \brief     Google Test of AppImage
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the AppImage class.
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

#include "AppImage.h"

using namespace Mplane;

using namespace std;

//===========================================================================================================
// CLASSES

//-------------------------------------------------------------------------------------------------------------
class AppImageTest : public ImTestFixture
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
TEST_F(AppImageTest, MethodsSimple)
{
    std::shared_ptr<AppImage> ib(new AppImage(mImageTask)) ;
    MethodsSimple(ib) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(AppImageTest, InstallChecks)
{
    std::shared_ptr<AppImage> ib(new AppImage(mImageTask)) ;
    InstallChecks(ib) ;
}

#if 0
//-------------------------------------------------------------------------------------------------------------
TEST_F(AppImageTest, Download)
{
    std::shared_ptr<AppImage> ib(new AppImage(mImageTask)) ;
    Download(ib, "ETNA-AXIS-FTU-TDD-CPRI-0.0-35-APP.tgz") ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(AppImageTest, DownloadBad)
{
    std::shared_ptr<AppImage> ib(new AppImage(mImageTask)) ;
    DownloadBad(ib, "ETNA-AXIS-FTU-TDD-CPRI-0.0-35-APP.tgz") ;
}
#endif


//-------------------------------------------------------------------------------------------------------------
TEST_F(AppImageTest, FormatName)
{
    std::shared_ptr<AppImage> ib(new AppImage(mImageTask)) ;

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
	expectName.append("-APP.tgz") ;

	EXPECT_EQ(expectName, name) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST_F(AppImageTest, Methods)
{
	Mplane::ILoggable::setLogDebugLevel(Mplane::ILoggable::LOG_DEBUG_VERBOSE) ;

	// Use the test version of the class to individually call the methods
    std::shared_ptr<TestImage<AppImage>> ib(new TestImage<AppImage>(mImageTask)) ;
    Methods(std::dynamic_pointer_cast<ITestImage>(ib), "ETNA-AXIS-FTU-TDD-CPRI-0.0-35-APP.tgz") ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(AppImageTest, Clean)
{
    std::shared_ptr<AppImage> ib(new AppImage(mImageTask)) ;
    Clean(ib) ;
}
