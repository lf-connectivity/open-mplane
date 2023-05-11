/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxIfCalDataTestCase.cpp
 * \brief     The Test file for TxIfCalDataTestCase
 *
 *
 * \details   The Test file for TxIfCalDataTestCase
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include <memory>

#include "CalDataTestTypes.h"
#include "TxIfCalData.h"
#include "TxIfCalDownload.h"

using namespace Mplane;
using namespace std;

/***************************/


namespace Mplane
{

static const std::string testCalFilePath = TEST_CALDATA_FILEPATH;

//-------------------------------------------------------------------------------------------------------
// Fixture


class TestTxIfCalData : public TxIfCalData
{
public:
    TestTxIfCalData() :
        TxIfCalData(std::shared_ptr<ICalDownload>( new TxIfCalDownload() ) )
    {
        // override the location of the xml file
        mCalFilePath = testCalFilePath + "txifcal.xml";
    }

    virtual ~TestTxIfCalData() {}

    // Test access
    std::shared_ptr<TxIfCal> getTxIfCal() const
	{
    	return mTxIfCal ;
	}

};


class TxIfCalTestCase : public ::testing::Test
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

        std::shared_ptr<TestTxIfCalData> txIfCalData (new TestTxIfCalData() );

        EXPECT_EQ( txIfCalData->load(), ReturnType::RT_OK );

        EXPECT_TRUE( txIfCalData->isLoaded() );

        std::shared_ptr<TxIfCal> txIfCal(txIfCalData->getTxIfCal()) ;
        EXPECT_TRUE( (bool)txIfCal );

        EXPECT_EQ( txIfCal->getVersion(), "2");
        EXPECT_EQ( txIfCal->getCountry(), "United Kingdom");
        EXPECT_EQ( txIfCal->getFacility(), "");
        EXPECT_EQ( txIfCal->getOperator(), "pshepherd");

        std::shared_ptr<ITxIfResponse> rip = txIfCal->getTxIfResponse(1);

        EXPECT_NE( rip, nullptr );

        EXPECT_EQ( rip->getPath(), 1 );
        EXPECT_EQ( rip->getDate(), "01/06/18 14:55:54.862");

        Power gain ;
        FrequencyOffset freqOffset ;

        freqOffset.set(-25000.0, Frequency::KHz) ;
        EXPECT_TRUE( rip->getGain(freqOffset, gain) ) ;
        EXPECT_NEAR( gain.get(), -0.029999, 0.00001 ) << "At -25000";

        freqOffset.set(-27000.0, Frequency::KHz) ;
        EXPECT_TRUE( rip->getGain(freqOffset, gain) ) ;
        EXPECT_NEAR( gain.get(), -0.039999, 0.00001 ) << "At -27000";

        freqOffset.set(-29000.0, Frequency::KHz) ;
        EXPECT_TRUE( rip->getGain(freqOffset, gain) ) ;
        EXPECT_NEAR( gain.get(), -0.049999, 0.00001 ) << "At -29000";

        freqOffset.set(-30000.0, Frequency::KHz) ;
        EXPECT_TRUE( rip->getGain(freqOffset, gain) ) ;
        EXPECT_NEAR( gain.get(), -0.059999, 0.00001 ) << "At -30000";

        // outside range
        freqOffset.set(-56000.0, Frequency::KHz) ;
        EXPECT_FALSE( rip->getGain(freqOffset, gain) ) << "At -56000" ;


        freqOffset.set(25000.0, Frequency::KHz) ;
        EXPECT_TRUE( rip->getGain(freqOffset, gain) ) ;
        EXPECT_NEAR( gain.get(), -0.019999, 0.00001 ) << "At 25000";

        freqOffset.set(27000.0, Frequency::KHz) ;
        EXPECT_TRUE( rip->getGain(freqOffset, gain) ) ;
        EXPECT_NEAR( gain.get(), -0.029999, 0.00001 ) << "At 27000";

        freqOffset.set(29000.0, Frequency::KHz) ;
        EXPECT_TRUE( rip->getGain(freqOffset, gain) ) ;
        EXPECT_NEAR( gain.get(), -0.039999, 0.00001 ) << "At 29000";

        freqOffset.set(30000.0, Frequency::KHz) ;
        EXPECT_TRUE( rip->getGain(freqOffset, gain) ) ;
        EXPECT_NEAR( gain.get(), -0.0499999, 0.00001 ) << "At 30000";

        // outside range
        freqOffset.set(56000.0, Frequency::KHz) ;
        EXPECT_FALSE( rip->getGain(freqOffset, gain) ) << "At 56000" ;




        // reload the cala data and make sure there are no memory leaks.
        EXPECT_EQ( txIfCalData->load(), ReturnType::RT_OK );

        EXPECT_TRUE( txIfCalData->isLoaded() );

        txIfCal = txIfCalData->getTxIfCal() ;
        EXPECT_NE( txIfCal, nullptr );

        EXPECT_EQ( txIfCal->getVersion(), "2");
        EXPECT_EQ( txIfCal->getCountry(), "United Kingdom");
        EXPECT_EQ( txIfCal->getFacility(), "");
        EXPECT_EQ( txIfCal->getOperator(), "pshepherd");

    }

};

}

/*
 * Unit test fixtures
 */
TEST_F(TxIfCalTestCase, unittest)
{
    unittest();
}
