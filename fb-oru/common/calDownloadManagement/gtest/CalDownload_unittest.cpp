/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CalDownload_unittest.cpp
 * \brief     Google Test of CalDownload
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the CalDownload class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "Path.h"
#include "cm_fixture.h"
#include "CalDownload.h"

using namespace Mplane;

using namespace std;

//===========================================================================================================
// CLASSES

//-------------------------------------------------------------------------------------------------------------
class CalDownloadTest : public CmTestFixture
{
};


//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST_F(CalDownloadTest, MethodsSimple)
{
    std::shared_ptr<TestCalDownload<CalDownload>> cd(new TestCalDownload<CalDownload>("CalDownload")) ;
    MethodsSimple(std::dynamic_pointer_cast<ITestCalDownload>(cd)) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(CalDownloadTest, InstallChecks)
{
    std::shared_ptr<TestCalDownload<CalDownload>> cd(new TestCalDownload<CalDownload>("CalDownload")) ;

    std::string failReason ;
    EXPECT_TRUE(cd->initialise(failReason)) ;

    cd->setInstallDir("/tmp", failReason) ;
    cd->setInstallFileName("tmp.xml", failReason) ;
    InstallChecks(std::dynamic_pointer_cast<ITestCalDownload>(cd)) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(CalDownloadTest, Download)
{
    std::shared_ptr<TestCalDownload<CalDownload>> cd(new TestCalDownload<CalDownload>("CalDownload")) ;

    std::string failReason ;
    EXPECT_TRUE(cd->initialise(failReason)) ;

    cd->setInstallFileName("tmp.xml", failReason) ;
    Download(std::dynamic_pointer_cast<ITestCalDownload>(cd), "ftu_tx_cal.xml") ;
}
