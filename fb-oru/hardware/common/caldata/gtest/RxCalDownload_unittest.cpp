/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxCalDownload_unittest.cpp
 * \brief     Google Test of RxCalDownload
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the RxCalDownload class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "Path.h"
#include "cm_fixture.h"
#include "RxCalDownload.h"

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
 * In this case ftu_rx_cal.xml must be available on the swin-11 build saver.
 *
 */
class RxCalDownloadTest : public CmTestFixture
{
};


//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST_F(RxCalDownloadTest, MethodsSimple)
{
    std::shared_ptr<TestCalDownload<RxCalDownload>> cd(new TestCalDownload<RxCalDownload>()) ;
    MethodsSimple(std::dynamic_pointer_cast<ITestCalDownload>(cd)) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(RxCalDownloadTest, InstallChecks)
{
    std::shared_ptr<TestCalDownload<RxCalDownload>> cd(new TestCalDownload<RxCalDownload>()) ;
    InstallChecks(std::dynamic_pointer_cast<ITestCalDownload>(cd)) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(RxCalDownloadTest, Download)
{
    std::shared_ptr<TestCalDownload<RxCalDownload>> cd(new TestCalDownload<RxCalDownload>()) ;
    Download(cd, "ftu_rx_cal.xml") ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(RxCalDownloadTest, DownloadUseInstall)
{
    std::shared_ptr<TestCalDownload<RxCalDownload>> cd(new TestCalDownload<RxCalDownload>()) ;
    DownloadUseInstall(cd, "ftu_rx_cal.xml") ;
}
