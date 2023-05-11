#ifndef _MPLANE_CMFIXTURE_H_
#define _MPLANE_CMFIXTURE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      cm_fixture.h
 * \brief     Cal Download Management test fixture
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <vector>
#include <string>
#include <memory>

#include "gtest/gtest.h"

#include "TestCalDownload.hpp"

#include "ICalDownload.h"
#include "CalDownload.h"
#include "RxCalDownload.h"
#include "TxCalDownload.h"

namespace Mplane
{

/*! @brief Test fixture for Image Management
 *
 *  This class uses the Google test facilities to perform unit testing
 */
class CmTestFixture : public ::testing::Test
{
public:

    /*! @brief Setup the test
     */
    virtual void SetUp();

    /*! @brief Tear down the test
     */
    virtual void TearDown();

    // Image class test methods
    virtual void MethodsSimple(std::shared_ptr<ITestCalDownload> ib) ;
    virtual void InstallChecks(std::shared_ptr<ITestCalDownload> ib);
    virtual void Download(std::shared_ptr<ITestCalDownload> ib, const std::string& fname);
    virtual void DownloadUseInstall(std::shared_ptr<ITestCalDownload> ib, const std::string& fname);

    void clearStatus(void) ;
    std::string getStatus(void) ;
    void writeStatus(const std::string& status) ;

    static std::shared_ptr<RxCalDownload> getRxcdl();
    static std::shared_ptr<TxCalDownload> getTxcdl();


    static std::string getTempDir(void) ;
    static std::string getDownloadDir(void) ;
    static std::string getNandDir(void) ;

private:
    // directories
    static std::string mTempDir ;
    static std::string mDownloadDir ;
    static std::string mNandDir ;

    std::string mStatus ;

    static std::shared_ptr<RxCalDownload> rxcdl;
    static std::shared_ptr<TxCalDownload> txcdl;

};



} /* namespace Mplane */

#endif
