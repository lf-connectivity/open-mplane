/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PamCalDataTestCase.cpp
 * \brief     The Test file for PamCalDataTestCase
 *
 *
 * \details   The Test file for PamCalDataTestCase
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>
#include <memory>

#include "ICalDownloadManagement.h"

#include "CalDataTestTypes.h"
#include "PamCalData.h"
#include "PamCalDownload.h"


using namespace Mplane;
using namespace std;

/***************************/

namespace Mplane
{

static const std::string testCalFilePath = TEST_CALDATA_FILEPATH;

//-------------------------------------------------------------------------------------------------------
// Fixture
class TestPamCalData : public PamCalData
{
public:
    TestPamCalData() :
        PamCalData(std::shared_ptr<ICalDownload>( new PamCalDownload() ) )
    {
        // tell cal download manager to change the root install directory.
        std::string failReason;
        mCalDownload->testInjectInstallDir(testCalFilePath, failReason);
        mCalDownload->setInstallFileName("pamcal.xml",failReason);
    }

    virtual ~TestPamCalData() {}

};

//-------------------------------------------------------------------------------------------------------
// Fixture
class PamCalTestCase : public ::testing::Test
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

        std::shared_ptr<PamCalData> pamCalData (new TestPamCalData() );

        ASSERT_EQ( pamCalData->load(), ReturnType::RT_OK );

        ASSERT_TRUE( pamCalData->isLoaded() );

        ASSERT_NE( pamCalData->mPamCal, nullptr );

        ASSERT_EQ( pamCalData->mPamCal->mVersion , "1");
        ASSERT_EQ( pamCalData->mPamCal->mCountry , "UK");
        ASSERT_EQ( pamCalData->mPamCal->mFacility , "Swindon");
        ASSERT_EQ( pamCalData->mPamCal->mOperator , "Simon");

        std::shared_ptr<PaGainStep> pgsp = pamCalData->mPamCal->mPaGainStepData[1];

        ASSERT_NE( pgsp, nullptr );

        ASSERT_EQ( pgsp->getPath(), 1 );
        ASSERT_EQ( pgsp->getDate(), "06/04/16 00:00:00");
        ASSERT_NEAR( pgsp->getStepCoefficient(), 0.005, 0.000001 );
        ASSERT_NEAR( pgsp->getCoefficient(), 0.011, 0.000001 );

        std::shared_ptr<PgsFrequencyTable> freqTable;
        std::shared_ptr<PgsFrequencyTable> uprFreqTable;

        Frequency freq( 2325000.0, Frequency::KHz );
        ASSERT_FALSE( pgsp->findFrequency(freq, freqTable, uprFreqTable ) );
        freq.set( 1982500.0, Frequency::KHz);
        ASSERT_TRUE( pgsp->findFrequency( freq , freqTable, uprFreqTable ));
        freq.set( 1987500.0, Frequency::KHz);
        ASSERT_TRUE( pgsp->findFrequency( freq , freqTable, uprFreqTable ));
        freq.set( 1992500.0, Frequency::KHz);
        ASSERT_TRUE( pgsp->findFrequency( freq , freqTable, uprFreqTable ));

        ASSERT_EQ( freqTable->getFrequency() , freq );


        std::shared_ptr<IPaGainStep> pgs = pamCalData->getPaGainStep(1);

        Frequency frequency( 1987500.0, Frequency::KHz);
        Temperature temperature( 35.5 ); // equals the radio cal temp
        Power power( 38.0 ); // equals the radio cal output power
        float radioCalTemperature;
        float pamCalTemperature;
        unsigned int vvaPwm;
        Power lowGainOutputPower;
        Power highGainOutputPower;
        ASSERT_TRUE( pgs->getData( frequency, power, radioCalTemperature, pamCalTemperature, vvaPwm, lowGainOutputPower, highGainOutputPower));

        ASSERT_EQ( vvaPwm, 12385u );
        ASSERT_FLOAT_EQ( radioCalTemperature, 33.5f );
        ASSERT_FLOAT_EQ( pamCalTemperature, 43.5f );
        ASSERT_FLOAT_EQ( lowGainOutputPower.get(), 23.2f );
        ASSERT_FLOAT_EQ( highGainOutputPower.get(), 38.0f );

        ASSERT_TRUE( pgs->getData( frequency, power, radioCalTemperature, pamCalTemperature, vvaPwm, lowGainOutputPower, highGainOutputPower));

        // look up a different high gain power exact match
        power = 35.0f;
        ASSERT_TRUE( pgs->getData( frequency, power, radioCalTemperature, pamCalTemperature, vvaPwm, lowGainOutputPower, highGainOutputPower));
        ASSERT_EQ( vvaPwm, 8643u );
        ASSERT_FLOAT_EQ( radioCalTemperature, 35.5f );
        ASSERT_FLOAT_EQ( pamCalTemperature, 45.5f );
        ASSERT_FLOAT_EQ( lowGainOutputPower.get(), 20.2f );
        ASSERT_FLOAT_EQ( highGainOutputPower.get(), 35.0f );

        // look up a different low gain power exact match
        power = 19.2f;
        ASSERT_TRUE( pgs->getData( frequency, power, radioCalTemperature, pamCalTemperature, vvaPwm, lowGainOutputPower, highGainOutputPower));
        ASSERT_EQ( vvaPwm, 7900u );
        ASSERT_FLOAT_EQ( radioCalTemperature, 35.5f );
        ASSERT_FLOAT_EQ( pamCalTemperature, 45.5f );
        ASSERT_FLOAT_EQ( lowGainOutputPower.get(), 19.2f );
        ASSERT_FLOAT_EQ( highGainOutputPower.get(), 34.0f );

        // look up a different low gain power inexact match, requires interpolation
        power = 20.1f;
        ASSERT_TRUE( pgs->getData( frequency, power, radioCalTemperature, pamCalTemperature, vvaPwm, lowGainOutputPower, highGainOutputPower));
        ASSERT_EQ( vvaPwm, 8568u );
        ASSERT_FLOAT_EQ( radioCalTemperature, 35.5f );
        ASSERT_FLOAT_EQ( pamCalTemperature, 45.5f );
        ASSERT_FLOAT_EQ( lowGainOutputPower.get(), 20.1f );
        ASSERT_FLOAT_EQ( highGainOutputPower.get(), 34.9f );

        // look up a different high gain power inexact match, requires interpolation
        power = 34.1f;
        ASSERT_TRUE( pgs->getData( frequency, power, radioCalTemperature, pamCalTemperature, vvaPwm, lowGainOutputPower, highGainOutputPower));
        ASSERT_EQ( vvaPwm, 7974u );
        ASSERT_FLOAT_EQ( radioCalTemperature, 35.5f );
        ASSERT_FLOAT_EQ( pamCalTemperature, 45.5f );
        ASSERT_FLOAT_EQ( lowGainOutputPower.get(), 19.3f );
        ASSERT_FLOAT_EQ( highGainOutputPower.get(), 34.1f );


        // now test the low freq
        frequency.set( 1982500.0, Frequency::KHz);
        temperature = 35.0f;
        power = 38.1f;

        ASSERT_TRUE( pgs->getData( frequency, power, radioCalTemperature, pamCalTemperature, vvaPwm, lowGainOutputPower, highGainOutputPower));

        ASSERT_EQ( vvaPwm, 12384u );
        ASSERT_FLOAT_EQ( radioCalTemperature, 33.5f );
        ASSERT_FLOAT_EQ( pamCalTemperature, 43.5f );
        ASSERT_FLOAT_EQ( lowGainOutputPower.get(), 23.1f );
        ASSERT_FLOAT_EQ( highGainOutputPower.get(), 38.1f );


        // now test the high freq
        frequency.set( 1992500.0, Frequency::KHz);
        temperature = 35.0f;
        power = 38.2f;

        ASSERT_TRUE( pgs->getData( frequency, power, radioCalTemperature, pamCalTemperature, vvaPwm, lowGainOutputPower, highGainOutputPower));

        ASSERT_EQ( vvaPwm, 12387u );
        ASSERT_FLOAT_EQ( radioCalTemperature, 33.5f );
        ASSERT_FLOAT_EQ( pamCalTemperature, 43.5f );
        ASSERT_FLOAT_EQ( lowGainOutputPower.get(), 23.2f );
        ASSERT_FLOAT_EQ( highGainOutputPower.get(), 38.2f );


        // now test a freq between two freqs
        frequency.set( 1991500.0, Frequency::KHz);
        temperature = 35.0f;
        power = 37.9f;
        ASSERT_TRUE( pgs->getData( frequency, power, radioCalTemperature, pamCalTemperature, vvaPwm, lowGainOutputPower, highGainOutputPower));

        // there are two interpolations, between frequencies and powers
        // freq ratio is 0.8
        // power ratio is 0.3
        ASSERT_EQ( vvaPwm, 12017u );                     // 12243+(11961-12243)*0.3
        ASSERT_FLOAT_EQ( radioCalTemperature, 33.76f );       // 33.8+(33.6-33.8)*.8
        ASSERT_FLOAT_EQ( pamCalTemperature, 43.76f );         // 43.8+(43.6-43.8)*0.8
        ASSERT_NEAR( lowGainOutputPower.get(), 22.94f, 0.00001 );  // 23.1+(22.9-23.1)*0.8
        ASSERT_FLOAT_EQ( highGainOutputPower.get(), 37.9f );

        // there are two interpolations, between frequencies and powers, one power is exact
        power = 37.2f;
        ASSERT_TRUE( pgs->getData( frequency, power, radioCalTemperature, pamCalTemperature, vvaPwm, lowGainOutputPower, highGainOutputPower));

        // freq ratio is 0.8
        // power ratio is 0.8
        ASSERT_EQ( vvaPwm, 11023u );                     // 11249+(10967-11249)*0.3
        ASSERT_FLOAT_EQ( radioCalTemperature, 34.46f );       // 34.3+(34.5-34.3)*.8
        ASSERT_FLOAT_EQ( pamCalTemperature, 44.46f );         // 44.3+(44.5-44.3)*0.8
        ASSERT_NEAR( lowGainOutputPower.get(), 22.24f, 0.00001 );  // 22.4+(22.2-22.4)*0.8
        ASSERT_FLOAT_EQ( highGainOutputPower.get(), 37.2f );

        // What happens if we fall off of the bottom of the table?
        frequency.set( 1993500.0, Frequency::KHz);
        temperature = 39.5f;
        power = 23.0f;
        ASSERT_TRUE( pgs->getData( frequency, power, radioCalTemperature, pamCalTemperature, vvaPwm, lowGainOutputPower, highGainOutputPower));

        ASSERT_EQ( vvaPwm, 4318u );
        ASSERT_FLOAT_EQ( radioCalTemperature, 39.5f );
        ASSERT_FLOAT_EQ( pamCalTemperature, 32.7f );
        ASSERT_FLOAT_EQ( lowGainOutputPower.get(), -07.00f );
        ASSERT_FLOAT_EQ( highGainOutputPower.get(), 23.02f );

        // What happens if we off the top of the table?
        power = 38.0f;
        ASSERT_TRUE( pgs->getData( frequency, power, radioCalTemperature, pamCalTemperature, vvaPwm, lowGainOutputPower, highGainOutputPower));

        ASSERT_EQ( vvaPwm, 6059u );
        ASSERT_FLOAT_EQ( radioCalTemperature, 39.5f );
        ASSERT_FLOAT_EQ( pamCalTemperature, 32.5f );
        ASSERT_FLOAT_EQ( lowGainOutputPower.get(),  08.20f );
        ASSERT_FLOAT_EQ( highGainOutputPower.get(), 37.99f );

        // What happens if we are well and truly in no mans land?
        power = 15.52f;
        ASSERT_TRUE( pgs->getData( frequency, power, radioCalTemperature, pamCalTemperature, vvaPwm, lowGainOutputPower, highGainOutputPower));

        ASSERT_EQ( vvaPwm, 4318u );
        ASSERT_FLOAT_EQ( radioCalTemperature, 39.5f );
        ASSERT_FLOAT_EQ( pamCalTemperature, 32.7f );
        ASSERT_FLOAT_EQ( lowGainOutputPower.get(), -07.00f );
        ASSERT_FLOAT_EQ( highGainOutputPower.get(), 23.02f );

        // test a secondary load and make sure no memory leaks

        ASSERT_EQ( pamCalData->load(), ReturnType::RT_OK );

        ASSERT_TRUE( pamCalData->isLoaded() );

        ASSERT_NE( pamCalData->mPamCal, nullptr );

        ASSERT_EQ( pamCalData->mPamCal->mVersion , "1");
        ASSERT_EQ( pamCalData->mPamCal->mCountry , "UK");
        ASSERT_EQ( pamCalData->mPamCal->mFacility , "Swindon");
        ASSERT_EQ( pamCalData->mPamCal->mOperator , "Simon");

    }

};

}
//-------------------------------------------------------------------------------------------------------




/*
 * Unit test fixtures
 */
TEST_F(PamCalTestCase, unittest)
{
    unittest();
}
