/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxVVACalDataTestCase.cpp
 * \brief     The Test file for TxVVACalDataTestCase
 *
 *
 * \details   The Test file for TxVVACalDataTestCase
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>
#include <memory>

#include "CalDataTestTypes.h"
#include "TxVVACal.h"
#include "TxVVACalDownload.h"

using namespace Mplane;
using namespace std;

/***************************/

namespace Mplane
{

static const std::string testCalFilePath = TEST_CALDATA_FILEPATH;

//-------------------------------------------------------------------------------------------------------
// Fixture
class TestTxVVACalData : public TxVVACalData
{
public:
    TestTxVVACalData() :
        TxVVACalData(std::shared_ptr<ICalDownload>( new TxVVACalDownload()))
    {
        // tell cal download manager to change the root install directory.
        std::string failReason;
        mCalDownload->testInjectInstallDir(testCalFilePath, failReason);
        mCalDownload->setInstallFileName("TxVVA.xml",failReason);
        // override the location of the xml file
//        mCalFilePath = testCalFilePath + "TxVVA.xml";
    }

    virtual ~TestTxVVACalData() {}

};

//-------------------------------------------------------------------------------------------------------
// Fixture
class TxVVACalTestCase : public ::testing::Test
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
        std::shared_ptr<TxVVACalData> txCal (new TestTxVVACalData() );

        ASSERT_EQ( txCal->load(), ReturnType::RT_OK );

        ASSERT_TRUE( txCal->isLoaded() );

        ASSERT_NE( txCal->mTxVVACal, nullptr );

        ASSERT_EQ( txCal->mTxVVACal->mVersion , "1");
        ASSERT_EQ( txCal->mTxVVACal->mCountry , "UK");
        ASSERT_EQ( txCal->mTxVVACal->mFacility , "Swindon");
        ASSERT_EQ( txCal->mTxVVACal->mOperator , "Jason");

        std::shared_ptr<TxVVA> VVAData = txCal->mTxVVACal->mTxVVAData[1];

        ASSERT_NE( VVAData, nullptr );

        ASSERT_EQ( VVAData->getPath(), 1 );
        ASSERT_EQ( VVAData->getDate(), "16/12/2014 15:25:27");
//        ASSERT_NEAR( dcOffsetData->getCoefficient(), 0.05, 0.000001 );

        std::shared_ptr<TxVVAFrequency> freqTable;

        Frequency freq;

        freq.set( 2340000.0, Frequency::KHz);
        ASSERT_TRUE( VVAData->findFrequency(freq, freqTable ) );

        Frequency frequency( 2300000.0, Frequency::KHz);

        ASSERT_EQ( freqTable->getFrequency() , frequency );


        std::shared_ptr<TxVVA> txVVA = txCal->getTxVVA(1);


        Power attn;
        int pwm;

//        0, 16383
        attn.set(0.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 16383 );

//        1, 13697
        attn.set(1.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 13697 );

//        2, 12164
        attn.set(2.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 12164 );

//        3, 10917
        attn.set(3.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 10917 );

//        4, 9796
        attn.set(4.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 9796 );

//        5, 8763
        attn.set(5.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 8763 );

//        6, 7850
        attn.set(6.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 7850 );

//        7, 7103
        attn.set(7.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 7103 );

//        8, 6535
        attn.set(8.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 6535 );

//        9, 6107
        attn.set(9.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 6107 );

//        10, 5785
        attn.set(10.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 5785 );

//        11, 5537
        attn.set(11.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 5537 );

//        12, 5341
        attn.set(12.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 5341 );

//        13, 5179
        attn.set(13.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 5179 );

//        14, 5043
        attn.set(14.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 5043 );

//        15, 4927
        attn.set(15.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 4927 );

//        16, 4826
        attn.set(16.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 4826 );

//        17, 4737
        attn.set(17.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 4737 );


//        18, 4657
        attn.set(18.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 4657 );

//        19, 4585
        attn.set(19.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 4585 );

//        20, 4517
        attn.set(20.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 4517 );

//        21, 4454
        attn.set(21.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 4454 );

//        22, 4395
        attn.set(22.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 4395 );

//        23, 4337
        attn.set(23.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 4337 );

//        24, 4282
        attn.set(24.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 4282 );

//        25, 4228
        attn.set(25.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 4228 );

//        26, 4174
        attn.set(26.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 4174 );

//        27, 4121
        attn.set(27.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 4121 );

//        28, 4066
        attn.set(28.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 4066 );

//        29, 4010
        attn.set(29.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 4010 );

//        30, 3951
        attn.set(30.0);
        txVVA->getPWM( frequency, attn.get(), pwm );
        ASSERT_EQ( pwm, 3951 );

//        31, 3889
//        for( float d=0.0f; d < 32.0f; d++ )
//        {
//            attn.set( d );
//            txVVA->getPWM( frequency, attn.get(), pwm );
//            std::cout << attn.get() << ", " << pwm << std::endl;
//        }



    }

};

}
//-------------------------------------------------------------------------------------------------------


/*
 * Unit test fixtures
 */
TEST_F(TxVVACalTestCase, unittest)
{
    unittest();
}
