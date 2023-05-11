/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SRxCalDataTestCase.cpp
 * \brief     The Test file for SRxCalDataTestCase
 *
 *
 * \details   The Test file for SRxCalDataTestCase
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include <memory>

#include "CalDataTestTypes.h"
#include "SRxCalData.h"
#include "SRxCalDownload.h"

using namespace Mplane;
using namespace std;

/***************************/


namespace Mplane
{

static const std::string testCalFilePath = TEST_CALDATA_FILEPATH;

//-------------------------------------------------------------------------------------------------------
// Fixture


class TestSRxCalData : public SRxCalData
{
public:
    TestSRxCalData() :
        SRxCalData(std::shared_ptr<ICalDownload>( new SRxCalDownload() ) )
    {
        // override the location of the xml file
        // Don't do it here because it will get overwritten, do it in the initialise.
        //        string failstr;
        //        this->mCalDownload->testInjectInstallDir("../../../../common/caldata/gtest/config",failstr);
        // don't use mCalFilePath because it gets changed in the load method.
        //        mCalFilePath = "../../../../common/caldata/gtest/config/srxcal.xml" ;
    }

    virtual ~TestSRxCalData() {}

    void initialise()
    {
        // set up a path to the test srxcal using the underlying SRxCalDown class support.
        string failstr;
        mCalDownload->initialise(failstr);
        mCalDownload->testInjectInstallDir(testCalFilePath,failstr);
    }
};




class SRxCalTestCase : public ::testing::Test
{
public:

    /*! @brief Setup the test
     */
    virtual void SetUp()
    {
        const ::testing::TestInfo* const test_info =
          ::testing::UnitTest::GetInstance()->current_test_info();

        std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
        std::cout << test_info->name() << " - START" <<  std::endl;

    }

    /*! @brief Tear down the test
     */
    virtual void TearDown()
    {
    }

    void unittest()
    {
        std::shared_ptr<TestSRxCalData> srxCal ( new TestSRxCalData() );

        srxCal->initialise();

//        std::shared_ptr<SRxCalData> srxCal (new TestSRxCalData() );



        ASSERT_EQ( srxCal->load(), ReturnType::RT_OK );

        ASSERT_TRUE( srxCal->isLoaded() );

        ASSERT_NE( srxCal->mSRxCal, nullptr );

//        ASSERT_EQ( rxCal->mRxCal->mVersion , "1");
//        ASSERT_EQ( rxCal->mRxCal->mCountry , "UK");
//        ASSERT_EQ( rxCal->mRxCal->mFacility , "Swindon");
//        ASSERT_EQ( rxCal->mRxCal->mOperator , "Jason");
//
//        std::shared_ptr<RxOpenLoop> olp = rxCal->mRxCal->mRxOpenLoopData[1];
//
//        ASSERT_NE( olp, nullptr );
//
//        ASSERT_EQ( olp->getPath(), 1 );
//        ASSERT_EQ( olp->getDate(), "10/01/2008 15:12:33");
//        ASSERT_NEAR( olp->getCoefficient(), 0.05, 0.00001 );
//
//        Frequency frequency(2350000.0f, Frequency::KHz);
//        Power ifAtten;
//        ASSERT_TRUE( olp->getIfAtten( frequency, ifAtten ));
//
//        ASSERT_NEAR( ifAtten.get(), 5.5f, 0.0001);
//        frequency.set(2450000.0f, Frequency::KHz);
//        ASSERT_FALSE( olp->getIfAtten( frequency, ifAtten ));
//        frequency.set(2250000.0f, Frequency::KHz);
//        ASSERT_FALSE( olp->getIfAtten( frequency, ifAtten ));
//
//
//        frequency.set(2325000.0f, Frequency::KHz);
//        Power rfAtten;
//        Power amplitude = -9.19f;
//        ASSERT_TRUE( olp->getRfAtten( frequency, amplitude, rfAtten  ));
//        ASSERT_NEAR( rfAtten.get(), 6.0, 0.00001 );
//
//        frequency.set(2327000.0f, Frequency::KHz);
//        amplitude = -9.19f;
//        ASSERT_TRUE( olp->getRfAtten( frequency, amplitude, rfAtten  ));
//        ASSERT_NEAR( rfAtten.get(), 6.0, 0.00001 );
//
//
//        frequency.set(2331000.0f, Frequency::KHz);
//        amplitude = -6.0f;
//        ASSERT_TRUE( olp->getRfAtten( frequency, amplitude, rfAtten  ));
//        ASSERT_NEAR( rfAtten.get(), 9.0, 0.00001 );
//
//
//        frequency.set(2335000.0f, Frequency::KHz);
//        amplitude = -6.0f;
//        ASSERT_TRUE( olp->getRfAtten( frequency, amplitude, rfAtten  ));
//        ASSERT_NEAR( rfAtten.get(), 9.0, 0.00001 );
//
//
//        frequency.set(2335000.0f, Frequency::KHz);
//        Power rfDsa( 22.0f );
//        Power offset;
//        float temperature = 23.5;
//        ASSERT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), 7.29f, 0.0001);
//
//        frequency.set(2335000.0f, Frequency::KHz);
//        rfDsa= 3.0f;
//         temperature = 20.0f;
//        ASSERT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), -12.4650f, 0.0001);
//
//        frequency.set(2338000.0f, Frequency::KHz);
//        rfDsa= 3.0f;
//         temperature = 20.0f;
//        ASSERT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), -12.4650f, 0.0001);
//
//
//        frequency.set(2361000.0f, Frequency::KHz);
//        rfDsa= 15.0f;
//         temperature = 25.0f;
//        ASSERT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), 0.59f, 0.0001);
//
//        frequency.set(2365000.0f, Frequency::KHz);
//        rfDsa= 15.0f;
//         temperature = 25.0f;
//        ASSERT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), 0.59f, 0.0001);
//
//        frequency.set(2365000.0f, Frequency::KHz);
//        rfDsa= 15.0f;
//         temperature = 28.0f;
//        ASSERT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), 0.7400f, 0.0001);
//
//        olp = rxCal->mRxCal->mRxOpenLoopData[2];
//
//        frequency.set(2325000.0f, Frequency::KHz);
//        rfDsa= 1.2f;
//         temperature = 23.5f;
//        ASSERT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), -14.19f, 0.0001);
//
//        frequency.set(2325000.0f, Frequency::KHz);
//        rfDsa= 1.5f;
//         temperature = 23.5f;
//        ASSERT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), -13.19f, 0.0001);
//
//        // reload the cala data and make sure there are no memory leaks.
//
//        ASSERT_EQ( rxCal->load(), ReturnType::RT_OK );
//
//        ASSERT_TRUE( rxCal->isLoaded() );
//
//        ASSERT_NE( rxCal->mRxCal, nullptr );
//
//        ASSERT_EQ( rxCal->mRxCal->mVersion , "1");
//        ASSERT_EQ( rxCal->mRxCal->mCountry , "UK");
//        ASSERT_EQ( rxCal->mRxCal->mFacility , "Swindon");
//        ASSERT_EQ( rxCal->mRxCal->mOperator , "Jason");


    }

};

}

/*
 * Unit test fixtures
 */
TEST_F(SRxCalTestCase, unittest)
{
    unittest();
}
