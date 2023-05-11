/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SwrCalDownload_unittest.cpp
 * \brief     Google Test of SwrCalDownload
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the SwrCalDownload class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "Path.h"
#include "cm_fixture.h"
#include "SwrCalDownload.h"

using namespace Mplane;

using namespace std;

//===========================================================================================================
// CLASSES

/**
 * Unit test class used to check the base cal data down load functionality.
 *
 * @note This test is dependent upon the appropriate calibration data file being stored
 * on the main build server (swin-11) under a guest account. ie /home/guest/public_html/test_files/cal.
 *
 * In this case swrcal must be available on the swin-11 build saver.
 *
 */
class SwrCalDownloadTest : public CmTestFixture
{
};


//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST_F(SwrCalDownloadTest, MethodsSimple)
{
    std::shared_ptr<TestCalDownload<SwrCalDownload>> cd(new TestCalDownload<SwrCalDownload>()) ;
    MethodsSimple(std::dynamic_pointer_cast<ITestCalDownload>(cd)) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(SwrCalDownloadTest, InstallChecks)
{
    std::shared_ptr<TestCalDownload<SwrCalDownload>> cd(new TestCalDownload<SwrCalDownload>()) ;
    InstallChecks(std::dynamic_pointer_cast<ITestCalDownload>(cd)) ;
}


//-------------------------------------------------------------------------------------------------------------
//TEST_F(SwrCalDownloadTest, Download)
//{
//    std::shared_ptr<TestCalDownload<SwrCalDownload>> cd(new TestCalDownload<SwrCalDownload>()) ;
//    Download(cd, "swrcal.xml") ;
//}

//-------------------------------------------------------------------------------------------------------------
//TEST_F(SwrCalDownloadTest, DownloadUseInstall)
//{
//    std::shared_ptr<TestCalDownload<SwrCalDownload>> cd(new TestCalDownload<SwrCalDownload>()) ;
//    DownloadUseInstall(cd, "swrcal.xml") ;
//}
