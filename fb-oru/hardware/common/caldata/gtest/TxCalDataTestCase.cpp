/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxCalDataTestCase.cpp
 * \brief     The Test file for TxCalDataTestCase
 *
 *
 * \details   The Test file for TxCalDataTestCase
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>
#include <memory>

#include "ICalDownloadManagement.h"
#include "CalData.h"

#include "CalDataTestTypes.h"
#include "TxCalData.h"
#include "TxCalDownload.h"

using namespace Mplane;
using namespace std;

/***************************/

namespace Mplane
{

static const std::string testCalFilePath = TEST_CALDATA_FILEPATH;

//-------------------------------------------------------------------------------------------------------
// Fixture
class MyTxCalData : public TxCalData
{
public:
    MyTxCalData() :
        TxCalData(std::dynamic_pointer_cast<ICalDownload>(std::make_shared<TxCalDownload>()) )
    {
        // tell cal download manager to change the root install directory.
        std::string failReason ;
        mCalDownload->testInjectInstallDir(testCalFilePath, failReason) ;
        mCalDownload->setInstallFileName("txcal.xml",failReason);
    }

    virtual ~MyTxCalData() {}

};

//-------------------------------------------------------------------------------------------------------
// Fixture
class TxCalTestCase : public ::testing::Test
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

        txCal = new MyTxCalData();
    }

    /*! @brief Tear down the test
     */
    virtual void TearDown()
    {
        const ::testing::TestInfo* const test_info =
            ::testing::UnitTest::GetInstance()->current_test_info();

        std::cout << test_info->name() << " - TEARDOWN" << std::endl;

        // Do the tear down here
        delete txCal;

        std::cout << test_info->name() << " - TEARDOWN complete" << std::endl;

    }

    MyTxCalData* txCal;

    void unittest()
    {

        EXPECT_EQ( txCal->load(), ReturnType::RT_OK );

        EXPECT_TRUE( txCal->isLoaded() );



        EXPECT_NE( txCal->mTxCal, nullptr );

        EXPECT_EQ( txCal->mTxCal->mVersion , "1");
        EXPECT_EQ( txCal->mTxCal->mCountry , "UK");
        EXPECT_EQ( txCal->mTxCal->mFacility , "Swindon");
        EXPECT_EQ( txCal->mTxCal->mOperator , "Jason");

        std::shared_ptr<TxOpenLoop> olp = txCal->mTxCal->mTxOpenLoopData[1];

        EXPECT_NE( olp, nullptr );

        EXPECT_EQ( olp->getPath(), 1 );
        EXPECT_EQ( olp->getDate(), "10/01/2008 15:12:33");
        EXPECT_NEAR( olp->getCoefficient(), 0.05, 0.000001 );

        std::shared_ptr<FrequencyTable> freqTable;
        std::shared_ptr<FrequencyTable> uprFreqTable;

        Frequency freq( 2370000.0, Frequency::KHz );
        EXPECT_FALSE( olp->findFrequency( freq , freqTable, uprFreqTable ));
        freq.set( 2325000.0, Frequency::KHz);
        EXPECT_TRUE( olp->findFrequency(freq, freqTable, uprFreqTable ) );

        EXPECT_EQ( freqTable->getFrequency() , freq );

        Power power = 16.0f;
        std::shared_ptr<PowerBand> powerBand;
        EXPECT_FALSE( freqTable->isPowerInBand( power, powerBand ));

        power = 14.0f;
        EXPECT_TRUE( freqTable->isPowerInBand( power, powerBand ));

        power = -15.0f;
        EXPECT_TRUE( freqTable->isPowerInBand( power, powerBand ));

        power = -50.0f;
        EXPECT_TRUE( freqTable->isPowerInBand( power, powerBand ));

        power = -2.5f;
        EXPECT_TRUE( freqTable->isPowerInBand( power, powerBand ));


        power = 14.99f;
        EXPECT_TRUE( freqTable->isPowerInBand( power, powerBand ));

        Point calPoint;
        powerBand->findNearestPower( power, calPoint );

        EXPECT_FLOAT_EQ( calPoint.power.get(), 14.98f );
        EXPECT_FLOAT_EQ( calPoint.varDsa.get(), 0.0f );

        power = 14.5f;
        EXPECT_TRUE( freqTable->isPowerInBand( power, powerBand ));

        powerBand->findNearestPower( power, calPoint );

        EXPECT_FLOAT_EQ( calPoint.power.get(), 14.98f );
        EXPECT_FLOAT_EQ( calPoint.varDsa.get(), 0.0f );

        power = 14.0f;
        EXPECT_TRUE( freqTable->isPowerInBand( power, powerBand ));

        powerBand->findNearestPower( power, calPoint );

        EXPECT_FLOAT_EQ( calPoint.power.get(), 13.8f );
        EXPECT_FLOAT_EQ( calPoint.varDsa.get(), 1.0f );

        power.set("12.7");
        EXPECT_TRUE( freqTable->isPowerInBand( power, powerBand ));

        powerBand->findNearestPower( power, calPoint );

        EXPECT_FLOAT_EQ( calPoint.power.get(), 12.7f );
        EXPECT_FLOAT_EQ( calPoint.varDsa.get(), 2.0f );

        power = -1.2f;
        EXPECT_TRUE( freqTable->isPowerInBand( power, powerBand ));

        powerBand->findNearestPower( power, calPoint );

        EXPECT_FLOAT_EQ( calPoint.power.get(), -1.9f ); // cos value is missing for 17 is return s 18s value.
        EXPECT_FLOAT_EQ( calPoint.varDsa.get(), 18.0f );

        power = -1.7f;
        EXPECT_TRUE( freqTable->isPowerInBand( power, powerBand ));

        powerBand->findNearestPower( power, calPoint );

        EXPECT_FLOAT_EQ( calPoint.power.get(), -1.9f );
        EXPECT_FLOAT_EQ( calPoint.varDsa.get(), 18.0f );

        power = -1.98f;
        EXPECT_TRUE( freqTable->isPowerInBand( power, powerBand ));

        powerBand->findNearestPower( power, calPoint );

        EXPECT_FLOAT_EQ( calPoint.power.get(), -1.9f );
        EXPECT_FLOAT_EQ( calPoint.varDsa.get(), 18.0f );

        std::shared_ptr<ITxOpenLoop> txol = txCal->getTxOpenLoop(1);

        Frequency frequency( 2325000.0, Frequency::KHz);
        Temperature temperature( 22.0 );
        Power reqPower(10.0);

        Power rfAttn;
        Power baseBand;
        Power correction;
        float calTemp;
        EXPECT_TRUE( txol->getData( frequency, reqPower, temperature.get(), baseBand, correction, rfAttn, calTemp ));

        EXPECT_FLOAT_EQ( rfAttn.get(), 4.0f );
        EXPECT_NEAR( correction.get(), -0.555 , 0.001 );
        EXPECT_NEAR( baseBand.get(), -3.0 , 0.001 );

        temperature = 26.0f;

        EXPECT_TRUE( txol->getData( frequency, reqPower, temperature.get(), baseBand,  correction, rfAttn, calTemp ));

        EXPECT_FLOAT_EQ( rfAttn.get(), 4.0f );
        EXPECT_NEAR( baseBand.get(), -3.0 , 0.001 );
        EXPECT_NEAR( correction.get(), -0.355 , 0.001 );

        reqPower.set(6.3);

        EXPECT_TRUE( txol->getData( frequency, reqPower, temperature.get(), baseBand,  correction, rfAttn, calTemp ));

        EXPECT_FLOAT_EQ( rfAttn.get(), 8.0f );
        EXPECT_NEAR( correction.get(), -.554 , 0.001 );
        EXPECT_NEAR( baseBand.get(), -3.0 , 0.001 );

        reqPower.set(-5.0);

        EXPECT_TRUE( txol->getData( frequency, reqPower, temperature.get(), baseBand,  correction, rfAttn, calTemp ));

        EXPECT_FLOAT_EQ( rfAttn.get(), 3.0f );
        EXPECT_NEAR( correction.get(), -0.235 , 0.001 );
        EXPECT_NEAR( baseBand.get(), -13.0 , 0.001 );


        Frequency checkFreq( 2335000.0, Frequency::KHz);
        freq.set( 2338000.0, Frequency::KHz);
        EXPECT_TRUE( olp->findFrequency(freq, freqTable, uprFreqTable ) );

        EXPECT_EQ( freqTable->getFrequency() , checkFreq );


        checkFreq.set( 2345000.0, Frequency::KHz);
        freq.set( 2343000.0, Frequency::KHz);
        EXPECT_TRUE( olp->findFrequency(freq, freqTable, uprFreqTable ) );

        EXPECT_EQ( uprFreqTable->getFrequency() , checkFreq );


        reqPower.set(6.3);
        freq.set( 2338000.0, Frequency::KHz);

        EXPECT_TRUE( txol->getData( freq, reqPower, temperature.get(), baseBand,  correction, rfAttn, calTemp ));

        EXPECT_FLOAT_EQ( rfAttn.get(), 9.0f );
//        EXPECT_NEAR( correction.get(), -0.305 , 0.001 );
        EXPECT_NEAR( correction.get(), -0.215 , 0.001 );
        EXPECT_NEAR( baseBand.get(), -3.0 , 0.001 );


        reqPower.set(-5.0);
        freq.set( 2343000.0, Frequency::KHz);

        EXPECT_TRUE( txol->getData( freq, reqPower, temperature.get(), baseBand,  correction, rfAttn, calTemp ));

        EXPECT_FLOAT_EQ( rfAttn.get(), 3.0f );
//        EXPECT_NEAR( correction.get(), 0.045 , 0.001 );
        EXPECT_NEAR( correction.get(), -0.235, 0.001 );
        EXPECT_NEAR( baseBand.get(), -13.0 , 0.001 );


        reqPower.set(12.5);
        freq.set( 2358000.0, Frequency::KHz);

        EXPECT_TRUE( txol->getData( freq, reqPower, temperature.get(), baseBand,  correction, rfAttn, calTemp));

        EXPECT_FLOAT_EQ( rfAttn.get(), 3.0f );
        EXPECT_NEAR( correction.get(), -0.015 , 0.001 );
        EXPECT_NEAR( baseBand.get(), -3.0 , 0.001 );


        // test a secondary load and make sure no memory leaks

        EXPECT_EQ( txCal->load(), ReturnType::RT_OK );

        EXPECT_TRUE( txCal->isLoaded() );

        EXPECT_NE( txCal->mTxCal, nullptr );

        EXPECT_EQ( txCal->mTxCal->mVersion , "1");
        EXPECT_EQ( txCal->mTxCal->mCountry , "UK");
        EXPECT_EQ( txCal->mTxCal->mFacility , "Swindon");
        EXPECT_EQ( txCal->mTxCal->mOperator , "Jason");




        reqPower.set(5.7);
        freq.set( 2355000.0, Frequency::KHz);

        EXPECT_TRUE( txol->getData( freq, reqPower, temperature.get(), baseBand,  correction, rfAttn, calTemp ));

        EXPECT_FLOAT_EQ( rfAttn.get(), 10.0f );
        EXPECT_NEAR( correction.get(), 0.185 , 0.001 );
        EXPECT_NEAR( baseBand.get(), -3.0 , 0.001 );



        /*
         * issue#4359
         * To test for selection of better selection of digital baseband correction
         * factor for non-linear power against frequency response, we need set a frequency
         * between two frequency table entries  and ensure it always select the smaller
         * attenuation value, so that the correction remains a negative value.
         * This prevents digital clipping in favour of slight loss in signal to noise
         * ratio.
         *
         * This test is performed on modified calibration data for the seconds TX path.
         */
        txol = txCal->getTxOpenLoop(2);



        reqPower.set(1.0);
        freq.set( 2358000.0, Frequency::KHz);


        EXPECT_TRUE( txol->getData( freq, reqPower, temperature.get(), baseBand,  correction, rfAttn, calTemp ));


        EXPECT_FLOAT_EQ( rfAttn.get(), 15.0f );
        EXPECT_NEAR( correction.get(), 0.485 , 0.001 );
        EXPECT_NEAR( baseBand.get(), -3.0 , 0.001 );



        reqPower.set(-2.9);
        freq.set( 2363000.0, Frequency::KHz);

        EXPECT_TRUE( txol->getData( freq, reqPower, temperature.get(), baseBand,  correction, rfAttn, calTemp ));

//        EXPECT_FLOAT_EQ( rfAttn.get(), 0.0f );
        EXPECT_FLOAT_EQ( rfAttn.get(), 1.0f );
        EXPECT_NEAR( correction.get(), -0.135, 0.001 );
        EXPECT_NEAR( baseBand.get(), -13.0 , 0.001 );

    }

};

}
//-------------------------------------------------------------------------------------------------------




/*
 * Unit test fixtures
 */
TEST_F(TxCalTestCase, unittest)
{
    unittest();
}
