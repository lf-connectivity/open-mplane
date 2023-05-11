/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxDCOffsetCalDataTestCase.cpp
 * \brief     The Test file for TxDCOffsetCalDataTestCase
 *
 *
 * \details   The Test file for TxDCOffsetCalDataTestCase
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>
#include <memory>

#include "CalDataTestTypes.h"
#include "TxDCOffsetCal.h"

using namespace Mplane;
using namespace std;

/***************************/

namespace Mplane
{

static const std::string testCalFilePath = TEST_CALDATA_FILEPATH;

//-------------------------------------------------------------------------------------------------------
// Fixture
class TestTxDCOffsetCalData : public TxDCOffsetCalData
{
public:
    TestTxDCOffsetCalData() :
        TxDCOffsetCalData(std::shared_ptr<ICalDownload>( new TxDCOffsetCalDownload()))
    {
        // override the location of the xml file
        mCalFilePath = testCalFilePath + "TxDcOffset.xml";
    }

    virtual ~TestTxDCOffsetCalData() {}

};

//-------------------------------------------------------------------------------------------------------
// Fixture
class TxDCOffsetCalTestCase : public ::testing::Test
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
        std::shared_ptr<TxDCOffsetCalData> txCal (new TestTxDCOffsetCalData() );

        ASSERT_EQ( txCal->load(), ReturnType::RT_OK );

        ASSERT_TRUE( txCal->isLoaded() );

        ASSERT_NE( txCal->mTxDCOffsetCal, nullptr );

        ASSERT_EQ( txCal->mTxDCOffsetCal->mVersion , "1");
        ASSERT_EQ( txCal->mTxDCOffsetCal->mCountry , "UK");
        ASSERT_EQ( txCal->mTxDCOffsetCal->mFacility , "Cricklade");
        ASSERT_EQ( txCal->mTxDCOffsetCal->mOperator , "Gareth");

        std::shared_ptr<TxDCOffset> dcOffsetData = txCal->mTxDCOffsetCal->mTxDCOffsetData[1];

        ASSERT_NE( dcOffsetData, nullptr );

        ASSERT_EQ( dcOffsetData->getPath(), 1 );
        ASSERT_EQ( dcOffsetData->getDate(), "29/01/2015 11:06:44");
//        ASSERT_NEAR( dcOffsetData->getCoefficient(), 0.05, 0.000001 );

        std::shared_ptr<TxDCOffsetFrequency> freqTable;

        Frequency freq;

        freq.set( 2320000.0, Frequency::KHz);
        ASSERT_TRUE( dcOffsetData->findFrequency(freq, freqTable ) );

        ASSERT_EQ( freqTable->getFrequency() , freq );


        std::shared_ptr<TxDCOffset> txol = txCal->getTxDCOffset(1);

        Frequency frequency( 2330000.0, Frequency::KHz);

        float temperature;
        int dcq;
        int dci;

        txol->getIQOffsets(frequency, temperature, dci, dcq );

        ASSERT_FLOAT_EQ( temperature, 39.2 );
        ASSERT_EQ( dcq, 51 );
        ASSERT_EQ( dci, 53 );


        frequency.set( 2295000, Frequency::KHz );

        txol->getIQOffsets(frequency, temperature, dci, dcq );
        ASSERT_EQ( dcq, 100 );
        ASSERT_EQ( dci, 21 );


        frequency.set( 2450000, Frequency::KHz );

        txol->getIQOffsets(frequency, temperature, dci, dcq );
        ASSERT_EQ( dcq,-24 );
        ASSERT_EQ( dci, 71 );

        frequency.set( 2357000, Frequency::KHz );

        txol->getIQOffsets(frequency, temperature, dci, dcq );
        ASSERT_EQ( dcq, 5 );
        ASSERT_EQ( dci, 73 );


    }

};

}
//-------------------------------------------------------------------------------------------------------


/*
 * Unit test fixtures
 */
TEST_F(TxDCOffsetCalTestCase, unittest)
{
    unittest();
}
