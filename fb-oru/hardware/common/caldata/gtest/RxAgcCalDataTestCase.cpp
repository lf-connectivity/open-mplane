/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxAgcCalDataTestCase.cpp
 * \brief     The Test file for RxAgcCalDataTestCase
 *
 *
 * \details   The Test file for RxAgcCalDataTestCase
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include <memory>

#include "CalDataTestTypes.h"
#include "RxCalDownload.h"
#include "RxAgcCalData.h"

using namespace Mplane;
using namespace std;

/***************************/


namespace Mplane
{

static const std::string testCalFilePath = TEST_CALDATA_FILEPATH;

//-------------------------------------------------------------------------------------------------------
// Fixture


class TestRxAgcCalData : public RxAgcCalData
{
public:
    TestRxAgcCalData() :
        RxAgcCalData(std::shared_ptr<ICalDownload>( new RxCalDownload() ) )
    {
        // override the location of the xml file
        mCalFilePath = testCalFilePath + "rxagccal.xml";
    }

    virtual ~TestRxAgcCalData() {}

};




class RxAgcCalTestCase : public ::testing::Test
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
        std::shared_ptr<RxAgcCalData> rxAgcCal (new TestRxAgcCalData() );

        EXPECT_EQ( rxAgcCal->load(), ReturnType::RT_OK );

        EXPECT_TRUE( rxAgcCal->isLoaded() );

        std::shared_ptr<IRxOpenLoop> olp = rxAgcCal->getRxOpenLoop(1);

        EXPECT_NE( olp, nullptr );

        EXPECT_EQ( olp->getPath(), 1 );
        EXPECT_EQ( olp->getDate(), "03/02/15 12:28:23.410");
        EXPECT_NEAR( olp->getCoefficient(), 0.05, 0.00001 );

        std::vector<Power> cgSteps(rxAgcCal->getCgSteps(1)) ;

        unsigned idx(0) ;
        for (auto cg : cgSteps)
        {
        	std::cerr << idx++ << ":" << cg << std::endl ;
        }


//        Frequency frequency(2350000.0f, Frequency::KHz);
//        Power ifAtten;
//        EXPECT_TRUE( olp->getIfAtten( frequency, ifAtten ));
//
//        EXPECT_NEAR( ifAtten.get(), 5.5f, 0.0001);
//        frequency.set(2450000.0f, Frequency::KHz);
//        EXPECT_FALSE( olp->getIfAtten( frequency, ifAtten ));
//        frequency.set(2250000.0f, Frequency::KHz);
//        EXPECT_FALSE( olp->getIfAtten( frequency, ifAtten ));
//
//
//        frequency.set(2325000.0f, Frequency::KHz);
//        Power rfAtten;
//        Power amplitude = -9.19f;
//        EXPECT_TRUE( olp->getRfAtten( frequency, amplitude, rfAtten  ));
//        EXPECT_NEAR( rfAtten.get(), 6.0, 0.00001 );
//
//        frequency.set(2327000.0f, Frequency::KHz);
//        amplitude = -9.19f;
//        EXPECT_TRUE( olp->getRfAtten( frequency, amplitude, rfAtten  ));
//        EXPECT_NEAR( rfAtten.get(), 6.0, 0.00001 );
//
//
//        frequency.set(2331000.0f, Frequency::KHz);
//        amplitude = -6.0f;
//        EXPECT_TRUE( olp->getRfAtten( frequency, amplitude, rfAtten  ));
//        EXPECT_NEAR( rfAtten.get(), 9.0, 0.00001 );
//
//
//        frequency.set(2335000.0f, Frequency::KHz);
//        amplitude = -6.0f;
//        EXPECT_TRUE( olp->getRfAtten( frequency, amplitude, rfAtten  ));
//        EXPECT_NEAR( rfAtten.get(), 9.0, 0.00001 );
//
//
//        frequency.set(2335000.0f, Frequency::KHz);
//        Power rfDsa( 22.0f );
//        Power offset;
//        float temperature = 23.5;
//        EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), 7.29f, 0.0001);
//
//        frequency.set(2335000.0f, Frequency::KHz);
//        rfDsa= 3.0f;
//         temperature = 20.0f;
//        EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), -12.4650f, 0.0001);
//
//        frequency.set(2338000.0f, Frequency::KHz);
//        rfDsa= 3.0f;
//         temperature = 20.0f;
//        EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), -12.4650f, 0.0001);
//
//
//        frequency.set(2361000.0f, Frequency::KHz);
//        rfDsa= 15.0f;
//         temperature = 25.0f;
//        EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), 0.59f, 0.0001);
//
//        frequency.set(2365000.0f, Frequency::KHz);
//        rfDsa= 15.0f;
//         temperature = 25.0f;
//        EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), 0.59f, 0.0001);
//
//        frequency.set(2365000.0f, Frequency::KHz);
//        rfDsa= 15.0f;
//         temperature = 28.0f;
//        EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), 0.7400f, 0.0001);
//
//        olp = rxAgcCal->getRxOpenLoop(2);
//
//        frequency.set(2325000.0f, Frequency::KHz);
//        rfDsa= 1.2f;
//         temperature = 23.5f;
//        EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), -14.19f, 0.0001);
//
//        frequency.set(2325000.0f, Frequency::KHz);
//        rfDsa= 1.5f;
//         temperature = 23.5f;
//        EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), -13.19f, 0.0001);

        // reload the cala data and make sure there are no memory leaks.

        EXPECT_EQ( rxAgcCal->load(), ReturnType::RT_OK );

        EXPECT_TRUE( rxAgcCal->isLoaded() );


    }

};

}

/*
 * Unit test fixtures
 */
TEST_F(RxAgcCalTestCase, unittest)
{
    unittest();
}
