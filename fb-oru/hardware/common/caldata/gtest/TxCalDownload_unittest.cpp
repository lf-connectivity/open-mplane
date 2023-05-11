/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxCalDownload_unittest.cpp
 * \brief     Google Test of TxCalDownload
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the TxCalDownload class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "Path.h"
#include "cm_fixture.h"
#include "TxCalDownload.h"

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
 * In this case ftu_tx_cal.xml must be available on the swin-11 build saver.
 *
 */
class TxCalDownloadTest : public CmTestFixture
{
};


//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST_F(TxCalDownloadTest, MethodsSimple)
{
    std::shared_ptr<TestCalDownload<TxCalDownload>> cd(new TestCalDownload<TxCalDownload>()) ;
    MethodsSimple(std::dynamic_pointer_cast<ITestCalDownload>(cd)) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(TxCalDownloadTest, InstallChecks)
{
    std::shared_ptr<TestCalDownload<TxCalDownload>> cd(new TestCalDownload<TxCalDownload>()) ;
    InstallChecks(std::dynamic_pointer_cast<ITestCalDownload>(cd)) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(TxCalDownloadTest, Download)
{
    std::shared_ptr<TestCalDownload<TxCalDownload>> cd(new TestCalDownload<TxCalDownload>()) ;
    Download(cd, "ftu_tx_cal.xml") ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(TxCalDownloadTest, DownloadUseInstall)
{
    std::shared_ptr<TestCalDownload<TxCalDownload>> cd(new TestCalDownload<TxCalDownload>()) ;
    DownloadUseInstall(cd, "ftu_tx_cal.xml") ;
}
