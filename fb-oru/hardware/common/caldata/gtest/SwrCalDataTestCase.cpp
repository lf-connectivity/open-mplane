/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SwrCalDataTestCase.cpp
 * \brief     The Test file for SwrCalDataTestCase
 *
 *
 * \details   The Test file for SwrCalDataTestCase
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include <memory>

#include "CalDataTestTypes.h"
#include "SwrCalData.h"
#include "SwrCalDownload.h"

using namespace Mplane;
using namespace std;

/***************************/


namespace Mplane
{

static const std::string testCalFilePath = TEST_CALDATA_FILEPATH;

//-------------------------------------------------------------------------------------------------------
// Fixture


class TestSwrCalData : public SwrCalData
{
public:
    TestSwrCalData() :
        SwrCalData(std::shared_ptr<ICalDownload>( new SwrCalDownload() ) )
    {
        // override the location of the xml file
        // Don't do it here because it will get overwritten, do it in the initialise.
        //        string failstr;
        //        this->mCalDownload->testInjectInstallDir("../../../../common/caldata/gtest/config",failstr);
        // don't use mCalFilePath because it gets changed in the load method.
        //        mCalFilePath = "../../../../common/caldata/gtest/config/swrcal.xml" ;
    }

    virtual ~TestSwrCalData() {}

    void initialise()
    {
        // set up a path to the test swrcal using the underlying SwrCalDown class support.
        string failstr;
        mCalDownload->initialise(failstr);
        mCalDownload->testInjectInstallDir(testCalFilePath,failstr);
    }
};




class SwrCalTestCase : public ::testing::Test
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
        std::shared_ptr<TestSwrCalData> swrCal ( new TestSwrCalData() );

        swrCal->initialise();

//        std::shared_ptr<SRxCalData> srxCal (new TestSRxCalData() );



        ASSERT_EQ( swrCal->load(), ReturnType::RT_OK );

        ASSERT_TRUE( swrCal->isLoaded() );

        ASSERT_NE( swrCal->mSwrCal, nullptr );


        Frequency frequency(740000.0f, Frequency::KHz);
        Power rfAtten = 3.0;
        float temperature = 38.1;

        shared_ptr<ISwrOpenLoop> iswr = swrCal->mSwrCal->getSwrOpenLoop(1);

        Power power = iswr->dBfsTodBm( frequency, rfAtten, temperature );

        ASSERT_FLOAT_EQ( power.get(), 56.98f );


    }

};

}

/*
 * Unit test fixtures
 */
TEST_F(SwrCalTestCase, unittest)
{
    unittest();
}
