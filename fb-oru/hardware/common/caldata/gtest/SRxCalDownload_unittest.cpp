/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SRxCalDownload_unittest.cpp
 * \brief     Google Test of RxCalDownload
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the SRxCalDownload class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "Path.h"
#include "cm_fixture.h"
#include "SRxCalDownload.h"

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
 * In this case srxcal must be available on the swin-11 build saver.
 *
 */
class SRxCalDownloadTest : public CmTestFixture
{
};


//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST_F(SRxCalDownloadTest, MethodsSimple)
{
    std::shared_ptr<TestCalDownload<SRxCalDownload>> cd(new TestCalDownload<SRxCalDownload>()) ;
    MethodsSimple(std::dynamic_pointer_cast<ITestCalDownload>(cd)) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(SRxCalDownloadTest, InstallChecks)
{
    std::shared_ptr<TestCalDownload<SRxCalDownload>> cd(new TestCalDownload<SRxCalDownload>()) ;
    InstallChecks(std::dynamic_pointer_cast<ITestCalDownload>(cd)) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(SRxCalDownloadTest, Download)
{
    std::shared_ptr<TestCalDownload<SRxCalDownload>> cd(new TestCalDownload<SRxCalDownload>()) ;
    Download(cd, "srxcal.xml") ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(SRxCalDownloadTest, DownloadUseInstall)
{
    std::shared_ptr<TestCalDownload<SRxCalDownload>> cd(new TestCalDownload<SRxCalDownload>()) ;
    DownloadUseInstall(cd, "srxcal.xml") ;
}
