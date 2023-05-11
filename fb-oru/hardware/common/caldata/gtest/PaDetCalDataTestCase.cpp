/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PaDetCalDataTestCase.cpp
 * \brief     The Test file for PaDetCalDataTestCase
 *
 *
 * \details   The Test file for PaDetCalDataTestCase
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>
#include <memory>

#include "CalDataTestTypes.h"
#include "PaDetCal.h"
#include "PaDetCalDownload.h"

using namespace Mplane;
using namespace std;

/***************************/

namespace Mplane
{

static const std::string testCalFilePath = TEST_CALDATA_FILEPATH;

//-------------------------------------------------------------------------------------------------------
// Fixture
class TestPaDetCalData : public PaDetCalData
{
public:
    TestPaDetCalData() :
        PaDetCalData(std::shared_ptr<ICalDownload>( new PaDetCalDownload()))
    {
        // override the location of the xml file
        // the test cal-file. Note - doesn't contain true PA cal data but
        // data to test the parsing operation, spline interpolation of power
        // values and linear interpolation between frequency points.
        mCalFilePath = testCalFilePath + "padetcal.xml";
    }

    virtual ~TestPaDetCalData() {}

};

//-------------------------------------------------------------------------------------------------------
// Fixture
class PaDetCalTestCase : public ::testing::Test
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
        std::shared_ptr<PaDetCalData> paCal (new TestPaDetCalData() );

        ASSERT_EQ( paCal->load(), ReturnType::RT_OK );

        ASSERT_TRUE( paCal->isLoaded() );

        ASSERT_NE( paCal->mPaDetCal, nullptr );

        ASSERT_EQ( paCal->mPaDetCal->mVersion , "1");
        ASSERT_EQ( paCal->mPaDetCal->mCountry , "UK");
        ASSERT_EQ( paCal->mPaDetCal->mFacility , "Harlow");
        ASSERT_EQ( paCal->mPaDetCal->mOperator , "HJS");

        std::shared_ptr<PaDet> PaData = paCal->mPaDetCal->mPaDetData[1];

        ASSERT_NE( PaData, nullptr );

        ASSERT_EQ( PaData->getPath(), 1 );
        ASSERT_EQ( PaData->getDate(), "08/12/2016 11:10:39");


        std::shared_ptr<PaDetFrequency> freqTable1, freqTable2;

        /* Check whether a lower and upper frequency table is returned when the
         * reqested frequency is not one of the frequencies at which the cal was
         * performed (the required value is then linearly interpolated) */
        Frequency freq;
        freq.set( 900000.0, Frequency::KHz);
        ASSERT_TRUE( PaData->findFrequencyTables(freq, freqTable1, freqTable2 ) );

        /* The lower frequency table (#1) should be 700MHz */
        Frequency frequency( 700000.0, Frequency::KHz);
        ASSERT_EQ( freqTable1->getFrequency() , frequency );

        /* the upper frequency table (#2) should be 1700MHz */
        frequency.set( 1200000.0, Frequency::KHz);
        ASSERT_EQ( freqTable2->getFrequency() , frequency );


        std::shared_ptr<PaDet> paDet = paCal->getPaDet(1);

        float pwrIn;
        float dbm;
        int pwrDet;

        /* This corresponds with a calibration point so should
         * return the precise table value */
        frequency.set( 700000.0, Frequency::KHz);
        pwrDet = 1326;
        paDet->getdBm( frequency, pwrDet, dbm );
        ASSERT_FLOAT_EQ( dbm, 48.0 );

        paDet->getPwrIn( frequency, dbm, pwrIn );
        ASSERT_FLOAT_EQ( pwrIn, -17.9 );

        /* 700MHz, PwrDet= 3000. Expect 5.0 dBm */
        pwrDet=2669;
        paDet->getdBm( frequency, pwrDet, dbm );
        ASSERT_FLOAT_EQ( dbm, 15.03 );

        paDet->getPwrIn( frequency, dbm, pwrIn );
        ASSERT_FLOAT_EQ( pwrIn, -55.02 );


       /* Now check an interpolation between power levels and between
        * frequency tables. Obtain the measurement at 1200MHz and at
        * an ADC reading of 1250. */

        /* STEP 1. Obtain dBm value at frequency table below
         * the requested frequency */

        pwrDet= 1250;
        frequency.set(700000.0, Frequency::KHz);
        paDet->getdBm( frequency, pwrDet, dbm );
        ASSERT_NEAR( dbm, 50.699, 0.01 );

        paDet->getPwrIn( frequency, dbm, pwrIn );
        ASSERT_NEAR( pwrIn, -14.519, 0.01 );

        /* STEP2 - frequency table above the requested frequency */
        frequency.set( 1700000.0, Frequency::KHz);
        paDet->getdBm( frequency, pwrDet, dbm );
        ASSERT_NEAR( dbm, 51.605, 0.01 );

        paDet->getPwrIn( frequency, dbm, pwrIn );
        ASSERT_NEAR( pwrIn, -10.712, 0.01 );


        /* STEP3 - dBm figure at 1200MHz. Should be mid-way between
         * the results obtained in step 1 and 2 i.e. 42.5dBm */
        frequency.set( 1200000.0, Frequency::KHz);
        paDet->getdBm( frequency, pwrDet, dbm );
        ASSERT_NEAR(dbm, 48.418, 0.01);

        paDet->getPwrIn( frequency, dbm, pwrIn );
        ASSERT_NEAR( pwrIn, -16.459, 0.01 );


        /***********  Repeat for path 2 **************
         *
         * Use a non-linear relationship described by
         * the following eqn:

         y = 0.000005x^2 - 0.035x + 80 (700MHz)

         ADC     dBm
         1000    50.0
         1500    38.75
         2000    30.0
         2500    23.75
         3000    20.0

         interpolation test value:
         1800    33.2

         For 1700MHz and 2700MHz add 5 and 10dBm, i.e.
         y = 0.000005x^2 - 0.035x + 85  (1700MHz)
         y = 0.000005x^2 - 0.035x + 90  (2700MHz) */



        PaData = paCal->mPaDetCal->mPaDetData[2];

        ASSERT_NE( PaData, nullptr );

        ASSERT_EQ( PaData->getPath(), 2 );
        ASSERT_EQ( PaData->getDate(), "08/12/2016 11:10:39");


        /* Check whether a lower and upper frequency table is returned when the
         * reqested frequency is not one of the frequencies at which the cal was
         * performed (the required value is then linearly interpolated) */

        freq.set( 900000.0, Frequency::KHz);
        ASSERT_TRUE( PaData->findFrequencyTables(freq, freqTable1, freqTable2 ) );

        /* The lower frequency table (#1) should be 700MHz */
        frequency.set( 700000.0, Frequency::KHz);
        ASSERT_EQ( freqTable1->getFrequency() , frequency );

        /* the upper frequency table (#2) should be 1700MHz */
        frequency.set( 1700000.0, Frequency::KHz);
        ASSERT_EQ( freqTable2->getFrequency() , frequency );


        paDet = paCal->getPaDet(2);

        //----------------------------------------------------------------------
        // dBm checks

        /* 700MHz, PerDet=1000
         * This corresponds with a calibration point so should
         * return the table value i.e. 50.0 dBm */
        frequency.set( 700000.0, Frequency::KHz);
        pwrDet = 1401;
        paDet->getdBm( frequency, pwrDet, dbm );
        ASSERT_NEAR( dbm, 47.0, 0.01 );

        paDet->getPwrIn( frequency, dbm, pwrIn );
        ASSERT_NEAR( pwrIn, -13.99, 0.01 );

        /* 700MHz, PwrDet= 2500. Expect 23.75 dBm */
        pwrDet=2999;
        paDet->getdBm( frequency, pwrDet, dbm );
        ASSERT_NEAR( dbm, 12.02, 0.01 );

        paDet->getPwrIn( frequency, dbm, pwrIn );
        ASSERT_NEAR( pwrIn, -52.48, 0.01 );

       /* Now check a value that needed interpolation
        * 1200.0 MHz. First read the power data from the
        * frequency table immediately below, then above
        * the 1200.0MHz (for pwrDet=1800) */
        pwrDet= 1800;
        frequency.set(700000.0, Frequency::KHz);
        paDet->getdBm( frequency, pwrDet, dbm );
        ASSERT_NEAR( dbm, 37.004, 0.02 );

        paDet->getPwrIn( frequency, dbm, pwrIn );
        ASSERT_NEAR( pwrIn, -23.366, 0.01 );

        /* Now determine the dBm value for pwrDet=1800
         * at 1700MHz */
        frequency.set( 1700000.0, Frequency::KHz);
        paDet->getdBm( frequency, pwrDet, dbm );
        ASSERT_NEAR( dbm, 37.004, 0.02 );

        paDet->getPwrIn( frequency, dbm, pwrIn );
        ASSERT_NEAR( pwrIn, -22.065, 0.01 );


        /* Now for the dBm figure at 1200MHz (i.e. mid-way
         * between the between the dBm values at 700MHz
         * and 1700MHz (as determined above)  */
        frequency.set( 1200000.0, Frequency::KHz);
        paDet->getdBm( frequency, pwrDet, dbm );
        ASSERT_NEAR(dbm, 37.004, 0.02);

        paDet->getPwrIn( frequency, dbm, pwrIn );
        ASSERT_NEAR( pwrIn, -22.716, 0.01 );
    }

};

}
//-------------------------------------------------------------------------------------------------------




/*
 * Unit test fixtures
 */
TEST_F(PaDetCalTestCase, unittest)
{
    unittest();
}
