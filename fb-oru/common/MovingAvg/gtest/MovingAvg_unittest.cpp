/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MemMap_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include <typeinfo>
#include <string>
#include <iostream>
#include <vector>

#include <numeric>
#include <functional>
#include <algorithm>

#include "MovingAvg.hpp"

using namespace std;
using namespace Mplane;


//------------------------------------------------------------------------------------------------------------------------
// Test fixture
class MovingAvgTests : public ::testing::Test
{
public:

    /*! @brief Setup the test
     */
    virtual void SetUp()
    {
        const ::testing::TestInfo* const test_info =
          ::testing::UnitTest::GetInstance()->current_test_info();

        cout << endl << "*** " << test_info->test_case_name() << " Tests ***" <<  endl;
        cout << test_info->name() << " - START" <<  endl;

    }

    /*! @brief Tear down the test
     */
    virtual void TearDown()
    {

    }

    virtual ~MovingAvgTests(){}

};



//========================================================================================================================
// TESTS
//========================================================================================================================


//------------------------------------------------------------------------------------------------------------------------
TEST_F(MovingAvgTests, floats)
{

    /* Default window size 10. The first data.add will
     * cause the window to be populated with
     * the value 3.5. Each subsequent add will remove
     * the oldest sample and append the latest - then
     * generate the average. Add 11 values to ensure
     * testing the case where all the original "fill"
     * samples have been replaced */

    MovingAvg<float> data;

    data.add( 3.5f );

    EXPECT_FLOAT_EQ( data.get(), 3.5f);

    data.add( 4.0f );

    EXPECT_FLOAT_EQ( data.get(), 3.55f );

    data.add( 4.5f );

    EXPECT_FLOAT_EQ( data.get(), 3.65f );

    data.add( -5.0f );

    EXPECT_FLOAT_EQ( data.get(), 2.8f );

    data.add( 5.5f );

    EXPECT_FLOAT_EQ( data.get(), 3.0f );

    data.add( 6.0f );

    EXPECT_FLOAT_EQ( data.get(), 3.25f );

    data.add( -6.5f );

    EXPECT_FLOAT_EQ( data.get(), 2.25f );

    data.add( 7.0f );

    EXPECT_FLOAT_EQ( data.get(), 2.6f );

    data.add( 7.5f );

    EXPECT_FLOAT_EQ( data.get(), 3.0f );

    data.add( -8.0f );

    EXPECT_FLOAT_EQ( data.get(), 1.85f );

    data.add( 8.5f );

    EXPECT_FLOAT_EQ( data.get(), 2.35f );

    EXPECT_FLOAT_EQ( data.variation(), 16.5f );

    data.setSize(20);

    /* The window is now 20 bins. The 10 additional bins are
     * populated with the oldest value (i.e. 4). So, the new average is
     * (23.5 + 4*10 )/20 = 3.175 */
    EXPECT_FLOAT_EQ( data.get(), 3.175f );


    /* Resize to 10. This will retain the latest 10 samples - so will
     * provide the same average figure as that obtained prior to the resize to
     * 20 samples. */

    data.setSize(10);

    EXPECT_FLOAT_EQ( data.get(), 2.35f);

    /* Add more data points */
    data.add( 3.5f );

    EXPECT_FLOAT_EQ( data.get(), 2.3f);

    data.add( 4.0f );

    EXPECT_FLOAT_EQ( data.get(), 2.25f );

    data.add( 4.5f );

    EXPECT_FLOAT_EQ( data.get(), 3.2f );

    data.add( -50.0f );

    EXPECT_FLOAT_EQ( data.get(), -2.35f );

    EXPECT_FLOAT_EQ( data.variation(), 58.5f );

    /* Resize to 2 points. Average should then
     * be that of the last two samples (-50 + 4.5)/2 =-22.75 */
    data.setSize(2);

    EXPECT_DOUBLE_EQ( data.get(), -22.75f);


    /* Test using double data type */
    MovingAvg<double> ddata;

    ddata.setSize(20);

    ddata.add( 3.5 );

    /* All bins now set to 3.5 after initial fill operation */
    EXPECT_DOUBLE_EQ( ddata.get(), 3.5);

    ddata.add( 4.0 );

    EXPECT_DOUBLE_EQ( ddata.get(), 3.525 );

    ddata.add( 5.0f );

    EXPECT_DOUBLE_EQ( ddata.get(), 3.6 );





}

//------------------------------------------------------------------------------------------------------------------------
TEST_F(MovingAvgTests, ints)
{

    MovingAvg<int> data;

    data.setSize(5);

    data.add( 3 );

    EXPECT_EQ( data.get(), 3 );

    data.add( 4 );

    EXPECT_EQ( data.get(), 3 );

    data.add( 7 );

    EXPECT_EQ( data.get(), 4 );

    EXPECT_EQ( data.variation(), 4 );

    data.setSize(10);

    EXPECT_EQ( data.get(), 3 );

    data.add(8);

    EXPECT_EQ( data.variation(), 5 );

    data.add(2);

    EXPECT_EQ( data.variation(), 6 );


}
