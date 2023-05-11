/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxCalDataTestCase.cpp
 * \brief     The Test file for RxCalDataTestCase
 *
 *
 * \details   The Test file for RxCalDataTestCase
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include <memory>

#include "RxCalData.h"
#include "RxCalDownload.h"

using namespace Mplane;
using namespace std;

/***************************/


namespace Mplane
{

//-------------------------------------------------------------------------------------------------------
// Fixture


class TestRxCalData : public RxCalData
{
public:
    TestRxCalData() :
        RxCalData(std::shared_ptr<ICalDownload>( new RxCalDownload() ) )
    {
        // override the location of the xml file
        mCalFilePath = "../../../../common/caldata/gtest/config/ftu_rx_cal.xml" ;
    }

    virtual ~TestRxCalData() {}

};


class TestEuropaRxCalData : public RxCalData
{
public:
    TestEuropaRxCalData() :
        RxCalData(std::shared_ptr<ICalDownload>( new RxCalDownload() ) )
    {
        // override the location of the xml file
        mCalFilePath = "../../../../common/caldata/gtest/config/rxcal.xml" ;
    }

    virtual ~TestEuropaRxCalData() {}

};

class TestNimrodRxCalData : public RxCalData
{
public:
	TestNimrodRxCalData() :
        RxCalData(std::shared_ptr<ICalDownload>( new RxCalDownload() ) )
    {
        // override the location of the xml file
        mCalFilePath = "../../../../common/caldata/gtest/config/nimrod_rx_cal.xml" ;
    }

    virtual ~TestNimrodRxCalData() {}

};



class RxCalTestCase : public ::testing::Test
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

        std::shared_ptr<RxCalData> rxCal (new TestRxCalData() );

        EXPECT_EQ( rxCal->load(), ReturnType::RT_OK );

        EXPECT_TRUE( rxCal->isLoaded() );

        EXPECT_NE( rxCal->mRxCal, nullptr );

        EXPECT_EQ( rxCal->mRxCal->mVersion , "1");
        EXPECT_EQ( rxCal->mRxCal->mCountry , "UK");
        EXPECT_EQ( rxCal->mRxCal->mFacility , "Swindon");
        EXPECT_EQ( rxCal->mRxCal->mOperator , "Jason");

        std::shared_ptr<RxOpenLoop> olp = rxCal->mRxCal->mRxOpenLoopData[1];

        EXPECT_NE( olp, nullptr );

        EXPECT_EQ( olp->getPath(), 1 );
        EXPECT_EQ( olp->getDate(), "10/01/2008 15:12:33");
        EXPECT_NEAR( olp->getCoefficient(), 0.05, 0.00001 );

        Frequency frequency(2350000.0f, Frequency::KHz);
        Power ifAtten;
        EXPECT_TRUE( olp->getIfAtten( frequency, ifAtten ));

        EXPECT_NEAR( ifAtten.get(), 5.5f, 0.0001);
        frequency.set(2450000.0f, Frequency::KHz);
//        EXPECT_FALSE( olp->getIfAtten( frequency, ifAtten ));
        EXPECT_TRUE( olp->getIfAtten( frequency, ifAtten )); // now picks the closest frequency band in the cal
        frequency.set(2250000.0f, Frequency::KHz);
//        EXPECT_FALSE( olp->getIfAtten( frequency, ifAtten ));
        EXPECT_TRUE( olp->getIfAtten( frequency, ifAtten )); // now picks the closest frequency band in the cal


        frequency.set(2325000.0f, Frequency::KHz);
        Power rfAtten;
        Power amplitude = -9.19f;
        EXPECT_TRUE( olp->getRfAtten( frequency, amplitude, rfAtten  ));
        EXPECT_NEAR( rfAtten.get(), 6.0, 0.00001 );

        frequency.set(2327000.0f, Frequency::KHz);
        amplitude = -9.19f;
        EXPECT_TRUE( olp->getRfAtten( frequency, amplitude, rfAtten  ));
        EXPECT_NEAR( rfAtten.get(), 6.0, 0.00001 );


        frequency.set(2331000.0f, Frequency::KHz);
        amplitude = -6.0f;
        EXPECT_TRUE( olp->getRfAtten( frequency, amplitude, rfAtten  ));
        EXPECT_NEAR( rfAtten.get(), 9.0, 0.00001 );


        frequency.set(2335000.0f, Frequency::KHz);
        amplitude = -6.0f;
        EXPECT_TRUE( olp->getRfAtten( frequency, amplitude, rfAtten  ));
        EXPECT_NEAR( rfAtten.get(), 9.0, 0.00001 );


        frequency.set(2335000.0f, Frequency::KHz);
        Power rfDsa( 22.0f );
        Power offset;
        float temperature = 23.5;
        EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), 7.29f, 0.0001);

        frequency.set(2335000.0f, Frequency::KHz);
        rfDsa= 3.0f;
         temperature = 20.0f;
        EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), -12.4650f, 0.0001);

        frequency.set(2338000.0f, Frequency::KHz);
        rfDsa= 3.0f;
         temperature = 20.0f;
        EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), -12.4650f, 0.0001);


        frequency.set(2361000.0f, Frequency::KHz);
        rfDsa= 15.0f;
         temperature = 25.0f;
        EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), 0.59f, 0.0001);

        frequency.set(2365000.0f, Frequency::KHz);
        rfDsa= 15.0f;
         temperature = 25.0f;
        EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), 0.59f, 0.0001);

        frequency.set(2365000.0f, Frequency::KHz);
        rfDsa= 15.0f;
         temperature = 28.0f;
        EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), 0.7400f, 0.0001);

        olp = rxCal->mRxCal->mRxOpenLoopData[2];

        frequency.set(2325000.0f, Frequency::KHz);
        rfDsa= 1.2f;
         temperature = 23.5f;
        EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), -14.19f, 0.0001);

        frequency.set(2325000.0f, Frequency::KHz);
        rfDsa= 1.5f;
         temperature = 23.5f;
        EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), -13.19f, 0.0001);

        // reload the cala data and make sure there are no memory leaks.

        EXPECT_EQ( rxCal->load(), ReturnType::RT_OK );

        EXPECT_TRUE( rxCal->isLoaded() );

        EXPECT_NE( rxCal->mRxCal, nullptr );

        EXPECT_EQ( rxCal->mRxCal->mVersion , "1");
        EXPECT_EQ( rxCal->mRxCal->mCountry , "UK");
        EXPECT_EQ( rxCal->mRxCal->mFacility , "Swindon");
        EXPECT_EQ( rxCal->mRxCal->mOperator , "Jason");


    }

    void Europa_unittest()
    {

        std::shared_ptr<RxCalData> rxCal (new TestEuropaRxCalData() );

        EXPECT_EQ( rxCal->load(), ReturnType::RT_OK );

        EXPECT_TRUE( rxCal->isLoaded() );

        EXPECT_NE( rxCal->mRxCal, nullptr );

        EXPECT_EQ( rxCal->mRxCal->mVersion , "1");
        EXPECT_EQ( rxCal->mRxCal->mCountry , "UK");
        EXPECT_EQ( rxCal->mRxCal->mFacility , "Swindon");
        EXPECT_EQ( rxCal->mRxCal->mOperator , "Jason");

        std::shared_ptr<RxOpenLoop> olp = rxCal->mRxCal->mRxOpenLoopData[1];

        EXPECT_NE( olp, nullptr );

        EXPECT_EQ( olp->getPath(), 1 );
        EXPECT_EQ( olp->getDate(), "03/02/15 12:28:23.410");
        EXPECT_NEAR( olp->getCoefficient(), 0.05, 0.00001 );

        Frequency frequency(700000.0f, Frequency::KHz);
        Power ifAtten;
        EXPECT_TRUE( olp->getIfAtten( frequency, ifAtten ));

        EXPECT_NEAR( ifAtten.get(), 10.0f, 0.0001);
        frequency.set(698000.0f, Frequency::KHz);
//        EXPECT_FALSE( olp->getIfAtten( frequency, ifAtten ));
        EXPECT_TRUE( olp->getIfAtten( frequency, ifAtten )); // now picks the closest frequency band in the cal
        frequency.set(920000.0f, Frequency::KHz);
//        EXPECT_FALSE( olp->getIfAtten( frequency, ifAtten ));
        EXPECT_TRUE( olp->getIfAtten( frequency, ifAtten )); // now picks the closest frequency band in the cal


        frequency.set(704000.0f, Frequency::KHz);
        Power rfAtten;
        Power amplitude = -9.19f;
        EXPECT_TRUE( olp->getRfAtten( frequency, amplitude, rfAtten  ));
        EXPECT_NEAR( rfAtten.get(), 2.0, 0.00001 );


    }

    void Nimrod_unittest()
     {

         std::shared_ptr<RxCalData> rxCal (new TestNimrodRxCalData() );

         EXPECT_EQ( rxCal->load(), ReturnType::RT_OK );

         EXPECT_TRUE( rxCal->isLoaded() );

         EXPECT_NE( rxCal->mRxCal, nullptr );

         EXPECT_EQ( rxCal->mRxCal->mVersion , "1");
         EXPECT_EQ( rxCal->mRxCal->mCountry , "UK");
         EXPECT_EQ( rxCal->mRxCal->mFacility , "Swindon");
         EXPECT_EQ( rxCal->mRxCal->mOperator , "Jason");

         std::shared_ptr<RxOpenLoop> olp = rxCal->mRxCal->mRxOpenLoopData[11];

         EXPECT_NE( olp, nullptr );

         EXPECT_EQ( olp->getPath(), 11 );
         EXPECT_EQ( olp->getDate(), "10/01/2008 15:12:33");
         EXPECT_NEAR( olp->getCoefficient(), 0.05, 0.00001 );

         Frequency frequency(2350000.0f, Frequency::KHz);
         Power ifAtten;
         EXPECT_TRUE( olp->getIfAtten( frequency, ifAtten ));
         EXPECT_NEAR( ifAtten.get(), 8.5f, 0.0001);

         frequency.set(2338000.0f, Frequency::KHz);
         EXPECT_TRUE( olp->getIfAtten( frequency, ifAtten ));
         EXPECT_NEAR( ifAtten.get(), 6.5f, 0.0001);

         frequency.set(2330000.0f, Frequency::KHz);
         EXPECT_TRUE( olp->getIfAtten( frequency, ifAtten ));
         EXPECT_NEAR( ifAtten.get(), 6.5f, 0.0001);

         frequency.set(2450000.0f, Frequency::KHz);
         EXPECT_TRUE( olp->getIfAtten( frequency, ifAtten )); // now picks the closest frequency band in the cal
         EXPECT_NEAR( ifAtten.get(), 9.5f, 0.0001);

         frequency.set(2250000.0f, Frequency::KHz);
         EXPECT_TRUE( olp->getIfAtten( frequency, ifAtten )); // now picks the closest frequency band in the cal
         EXPECT_NEAR( ifAtten.get(), 5.5f, 0.0001);


         frequency.set(2325000.0f, Frequency::KHz);
         Power rfAtten;
         Power amplitude = -9.19f;
         EXPECT_TRUE( olp->getRfAtten( frequency, amplitude, rfAtten  ));
         EXPECT_NEAR( rfAtten.get(), 6.0, 0.00001 );

         frequency.set(2327000.0f, Frequency::KHz);
         amplitude = -9.19f;
         EXPECT_TRUE( olp->getRfAtten( frequency, amplitude, rfAtten  ));
         EXPECT_NEAR( rfAtten.get(), 6.0, 0.00001 );


         frequency.set(2331000.0f, Frequency::KHz);
         amplitude = -6.0f;
         EXPECT_TRUE( olp->getRfAtten( frequency, amplitude, rfAtten  ));
         EXPECT_NEAR( rfAtten.get(), 9.0, 0.00001 );


         frequency.set(2335000.0f, Frequency::KHz);
         amplitude = -6.0f;
         EXPECT_TRUE( olp->getRfAtten( frequency, amplitude, rfAtten  ));
         EXPECT_NEAR( rfAtten.get(), 9.0, 0.00001 );


         frequency.set(2335000.0f, Frequency::KHz);
         Power rfDsa( 22.0f );
         Power offset;
         float temperature = 23.5;
         EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), 7.29f, 0.0001);

         frequency.set(2335000.0f, Frequency::KHz);
         rfDsa= 3.0f;
          temperature = 20.0f;
         EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), -12.4650f, 0.0001);

         frequency.set(2338000.0f, Frequency::KHz);
         rfDsa= 3.0f;
          temperature = 20.0f;
         EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), -12.4650f, 0.0001);


         frequency.set(2361000.0f, Frequency::KHz);
         rfDsa= 15.0f;
          temperature = 25.0f;
         EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), 0.59f, 0.0001);

         frequency.set(2365000.0f, Frequency::KHz);
         rfDsa= 15.0f;
          temperature = 25.0f;
         EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), 0.59f, 0.0001);

         frequency.set(2365000.0f, Frequency::KHz);
         rfDsa= 15.0f;
          temperature = 28.0f;
         EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), 0.7400f, 0.0001);

         olp = rxCal->mRxCal->mRxOpenLoopData[2];

         frequency.set(2325000.0f, Frequency::KHz);
         rfDsa= 1.2f;
          temperature = 23.5f;
         EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), -14.19f, 0.0001);

         frequency.set(2325000.0f, Frequency::KHz);
         rfDsa= 1.5f;
          temperature = 23.5f;
         EXPECT_NEAR( olp->dBfsTodBm( frequency, rfDsa, temperature).get(), -13.19f, 0.0001);

         // reload the cala data and make sure there are no memory leaks.

         EXPECT_EQ( rxCal->load(), ReturnType::RT_OK );

         EXPECT_TRUE( rxCal->isLoaded() );

         EXPECT_NE( rxCal->mRxCal, nullptr );

         EXPECT_EQ( rxCal->mRxCal->mVersion , "1");
         EXPECT_EQ( rxCal->mRxCal->mCountry , "UK");
         EXPECT_EQ( rxCal->mRxCal->mFacility , "Swindon");
         EXPECT_EQ( rxCal->mRxCal->mOperator , "Jason");

         //Test other path IF attenuation values
         std::shared_ptr<RxOpenLoop> olp12 = rxCal->mRxCal->mRxOpenLoopData[12];

         EXPECT_NE( olp12, nullptr );

         EXPECT_EQ( olp12->getPath(), 12 );
         EXPECT_EQ( olp12->getDate(), "10/01/2008 15:12:33");
         EXPECT_NEAR( olp12->getCoefficient(), 0.05, 0.00001 );

         frequency.set(2350000.0f, Frequency::KHz);
         EXPECT_TRUE( olp12->getIfAtten( frequency, ifAtten ));
         EXPECT_NEAR( ifAtten.get(), 18.5f, 0.0001);

         frequency.set(2338000.0f, Frequency::KHz);
         EXPECT_TRUE( olp12->getIfAtten( frequency, ifAtten ));
         EXPECT_NEAR( ifAtten.get(), 16.5f, 0.0001);

         frequency.set(2330000.0f, Frequency::KHz);
         EXPECT_TRUE( olp12->getIfAtten( frequency, ifAtten ));
         EXPECT_NEAR( ifAtten.get(), 16.5f, 0.0001);

         frequency.set(2450000.0f, Frequency::KHz);
         EXPECT_TRUE( olp12->getIfAtten( frequency, ifAtten )); // now picks the closest frequency band in the cal
         EXPECT_NEAR( ifAtten.get(), 19.5f, 0.0001);

         frequency.set(2250000.0f, Frequency::KHz);
         EXPECT_TRUE( olp12->getIfAtten( frequency, ifAtten )); // now picks the closest frequency band in the cal
         EXPECT_NEAR( ifAtten.get(), 15.5f, 0.0001);

         std::shared_ptr<RxOpenLoop> olp2 = rxCal->mRxCal->mRxOpenLoopData[2];

         EXPECT_NE( olp2, nullptr );

         EXPECT_EQ( olp2->getPath(), 2 );
         EXPECT_EQ( olp2->getDate(), "10/01/2008 15:12:33");
         EXPECT_NEAR( olp2->getCoefficient(), 0.05, 0.00001 );

         frequency.set(2350000.0f, Frequency::KHz);
         EXPECT_TRUE( olp2->getIfAtten( frequency, ifAtten ));
         EXPECT_NEAR( ifAtten.get(), 28.5f, 0.0001);

         frequency.set(2338000.0f, Frequency::KHz);
         EXPECT_TRUE( olp2->getIfAtten( frequency, ifAtten ));
         EXPECT_NEAR( ifAtten.get(), 26.5f, 0.0001);

         frequency.set(2330000.0f, Frequency::KHz);
         EXPECT_TRUE( olp2->getIfAtten( frequency, ifAtten ));
         EXPECT_NEAR( ifAtten.get(), 26.5f, 0.0001);

         frequency.set(2450000.0f, Frequency::KHz);
         EXPECT_TRUE( olp2->getIfAtten( frequency, ifAtten )); // now picks the closest frequency band in the cal
         EXPECT_NEAR( ifAtten.get(), 29.5f, 0.0001);

         frequency.set(2250000.0f, Frequency::KHz);
         EXPECT_TRUE( olp2->getIfAtten( frequency, ifAtten )); // now picks the closest frequency band in the cal
         EXPECT_NEAR( ifAtten.get(), 25.5f, 0.0001);


     }

};

}

/*
 * Unit test fixtures
 */
TEST_F(RxCalTestCase, unittest)
{
    unittest();
}

/*
 * Unit test fixtures
 */
TEST_F(RxCalTestCase, Europa_unittest)
{
    Europa_unittest();
}

/*
 * Unit test fixtures
 */
TEST_F(RxCalTestCase, Nimrod_unittest)
{
    Nimrod_unittest();
}
