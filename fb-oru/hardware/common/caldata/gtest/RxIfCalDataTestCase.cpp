/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxIfCalDataTestCase.cpp
 * \brief     The Test file for RxIfCalDataTestCase
 *
 *
 * \details   The Test file for RxIfCalDataTestCase
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include <memory>

#include "CalDataTestTypes.h"
#include "RxIfCalData.h"
#include "RxIfCalDownload.h"

using namespace Mplane;
using namespace std;

/***************************/


namespace Mplane
{

static const std::string testCalFilePath = TEST_CALDATA_FILEPATH;

//-------------------------------------------------------------------------------------------------------
// Fixture


class TestRxIfCalData : public RxIfCalData
{
public:
    TestRxIfCalData() :
        RxIfCalData(std::shared_ptr<ICalDownload>( new RxIfCalDownload() ) )
    {
        // override the location of the xml file
        mCalFilePath = testCalFilePath + "rxifcal.xml";
    }

    virtual ~TestRxIfCalData() {}

    // Test access
    std::shared_ptr<RxIfCal> getRxIfCal() const
    {
        return mRxIfCal;
    }

};


class RxIfCalTestCase : public ::testing::Test
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

        std::shared_ptr<TestRxIfCalData> rxIfCalData (new TestRxIfCalData() );

        EXPECT_EQ( rxIfCalData->load(), ReturnType::RT_OK );

        EXPECT_TRUE( rxIfCalData->isLoaded() );

        std::shared_ptr<RxIfCal> rxIfCal(rxIfCalData->getRxIfCal()) ;
        EXPECT_TRUE( (bool)rxIfCal );

        EXPECT_EQ( rxIfCal->getVersion(), "1");
        EXPECT_EQ( rxIfCal->getCountry(), "UK");
        EXPECT_EQ( rxIfCal->getFacility(), "Swindon");
        EXPECT_EQ( rxIfCal->getOperator(), "M_Mouse");

        std::shared_ptr<IRxIfResponse> rip = rxIfCal->getRxIfResponse(1);

        EXPECT_NE( rip, nullptr );

        EXPECT_EQ( rip->getPath(), 1 );
        EXPECT_EQ( rip->getDate(), "02/09/2015 18:57:34");
        EXPECT_NEAR( rip->getCoefficient(), 0.0, 0.00001 );


        Power gain ;
        FrequencyOffset freqOffset ;

        freqOffset.set(-25000.0, Frequency::KHz) ;
        EXPECT_TRUE( rip->getGain(freqOffset, gain) ) ;
        EXPECT_NEAR( gain.get(), -0.6, 0.00001 ) << "At -25000";

        freqOffset.set(-27000.0, Frequency::KHz) ;
        EXPECT_TRUE( rip->getGain(freqOffset, gain) ) ;
        EXPECT_NEAR( gain.get(), -0.6, 0.00001 ) << "At -27000";

        freqOffset.set(-29000.0, Frequency::KHz) ;
        EXPECT_TRUE( rip->getGain(freqOffset, gain) ) ;
        EXPECT_NEAR( gain.get(), -0.9, 0.00001 ) << "At -29000";

        freqOffset.set(-30000.0, Frequency::KHz) ;
        EXPECT_TRUE( rip->getGain(freqOffset, gain) ) ;
        EXPECT_NEAR( gain.get(), -0.9, 0.00001 ) << "At -30000";

        // outside range
        freqOffset.set(-31000.0, Frequency::KHz) ;
        EXPECT_FALSE( rip->getGain(freqOffset, gain) ) << "At -31000" ;


        freqOffset.set(25000.0, Frequency::KHz) ;
        EXPECT_TRUE( rip->getGain(freqOffset, gain) ) ;
        EXPECT_NEAR( gain.get(), -0.8, 0.00001 ) << "At 25000";

        freqOffset.set(27000.0, Frequency::KHz) ;
        EXPECT_TRUE( rip->getGain(freqOffset, gain) ) ;
        EXPECT_NEAR( gain.get(), -0.8, 0.00001 ) << "At 27000";

        freqOffset.set(29000.0, Frequency::KHz) ;
        EXPECT_TRUE( rip->getGain(freqOffset, gain) ) ;
        EXPECT_NEAR( gain.get(), -1.1, 0.00001 ) << "At 29000";

        freqOffset.set(30000.0, Frequency::KHz) ;
        EXPECT_TRUE( rip->getGain(freqOffset, gain) ) ;
        EXPECT_NEAR( gain.get(), -1.1, 0.00001 ) << "At 30000";

        // outside range
        freqOffset.set(31000.0, Frequency::KHz) ;
        EXPECT_FALSE( rip->getGain(freqOffset, gain) ) << "At 31000" ;




        // reload the cala data and make sure there are no memory leaks.
        EXPECT_EQ( rxIfCalData->load(), ReturnType::RT_OK );

        EXPECT_TRUE( rxIfCalData->isLoaded() );

        rxIfCal = rxIfCalData->getRxIfCal() ;
        EXPECT_NE( rxIfCal, nullptr );

        EXPECT_EQ( rxIfCal->getVersion(), "1");
        EXPECT_EQ( rxIfCal->getCountry(), "UK");
        EXPECT_EQ( rxIfCal->getFacility(), "Swindon");
        EXPECT_EQ( rxIfCal->getOperator(), "M_Mouse");

    }

};

}

/*
 * Unit test fixtures
 */
TEST_F(RxIfCalTestCase, unittest)
{
    unittest();
}
