/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxQuadCalDataTestCase.cpp
 * \brief     The Test file for TxQuadCalDataTestCase
 *
 *
 * \details   The Test file for TxQuadCalDataTestCase
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>
#include <memory>

#include "CalDataTestTypes.h"
#include "TxQuadCal.h"

using namespace Mplane;
using namespace std;

/***************************/

namespace Mplane
{

static const std::string testCalFilePath = TEST_CALDATA_FILEPATH;

//-------------------------------------------------------------------------------------------------------
// Fixture
class TestTxQuadCalData : public TxQuadOffsetCalData
{
public:
    TestTxQuadCalData() :
        TxQuadOffsetCalData(std::shared_ptr<ICalDownload>( new TxQuadOffsetCalDownload() ))
	{
		// override the location of the xml file
		mCalFilePath = testCalFilePath + "TxQuadratureOffset.xml";
	}

	virtual ~TestTxQuadCalData() {}

};

//-------------------------------------------------------------------------------------------------------
// Fixture
class TxQuadOffsetCalTestCase : public ::testing::Test
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
        std::shared_ptr<TxQuadOffsetCalData> txCal (new TestTxQuadCalData() );

        ASSERT_EQ( txCal->load(), ReturnType::RT_OK );

        ASSERT_TRUE( txCal->isLoaded() );

        ASSERT_NE( txCal->mTxQuadOffsetCal, nullptr );

        ASSERT_EQ( txCal->mTxQuadOffsetCal->mVersion , "1");
        ASSERT_EQ( txCal->mTxQuadOffsetCal->mCountry , "UK");
        ASSERT_EQ( txCal->mTxQuadOffsetCal->mFacility , "Swindon");
        ASSERT_EQ( txCal->mTxQuadOffsetCal->mOperator , "Jason");

        std::shared_ptr<TxQuadOffset> dcOffsetData = txCal->mTxQuadOffsetCal->mTxQuadOffsetData[1];

        ASSERT_NE( dcOffsetData, nullptr );

        ASSERT_EQ( dcOffsetData->getPath(), 1 );
        ASSERT_EQ( dcOffsetData->getDate(), "10/02/2015 14:12:23");
//        ASSERT_NEAR( dcOffsetData->getCoefficient(), 0.05, 0.000001 );

        std::shared_ptr<TxQuadOffsetFrequency> freqTable;

        Frequency freq;

        freq.set( 700000.0, Frequency::KHz);
        ASSERT_TRUE( dcOffsetData->findFrequency(freq, freqTable ) );

        ASSERT_EQ( freqTable->getFrequency() , freq );


        std::shared_ptr<TxQuadOffset> txol = txCal->getTxQuadOffset(1);

        Frequency frequency( 1200000.0, Frequency::KHz);

        float temperature;
        int phaseq;
        int phasei;
        int magi;
        int magq;

        txol->getData(frequency, temperature, phasei, phaseq, magi, magq );

        ASSERT_NEAR( temperature, 40.1 , 0.001);
        ASSERT_EQ( phasei, 38 );
        ASSERT_EQ( phaseq, 0 );
        ASSERT_EQ( magi, 9 );
        ASSERT_EQ( magq, 0 );

        frequency.set(650000.0, Frequency::KHz );

        txol->getData(frequency, temperature, phasei, phaseq, magi, magq );

        ASSERT_EQ( phasei, -15 );
        ASSERT_EQ( phaseq, 0 );
        ASSERT_EQ( magi, 9 );
        ASSERT_EQ( magq, 0 );


        frequency.set(2750000.0, Frequency::KHz );

        txol->getData(frequency, temperature, phasei, phaseq, magi, magq );

        ASSERT_EQ( phasei, -21 );
        ASSERT_EQ( phaseq, 0 );
        ASSERT_EQ( magi, 1 );
        ASSERT_EQ( magq, 0 );

        frequency.set(2670000.0, Frequency::KHz );

        txol->getData(frequency, temperature, phasei, phaseq, magi, magq );

        ASSERT_EQ( phasei, -21 );
        ASSERT_EQ( phaseq, 0 );
        ASSERT_EQ( magi, 1 );
        ASSERT_EQ( magq, 0 );


        frequency.set(760000.0, Frequency::KHz );

        txol->getData(frequency, temperature, phasei, phaseq, magi, magq );

        ASSERT_EQ( phasei, 55 );
        ASSERT_EQ( phaseq, 0 );
        ASSERT_EQ( magi, 9 );
        ASSERT_EQ( magq, 0 );



        //        Temperature temperature( 22.0 );
    }

};

}
//-------------------------------------------------------------------------------------------------------




/*
 * Unit test fixtures
 */
TEST_F(TxQuadOffsetCalTestCase, unittest)
{
    unittest();
}
