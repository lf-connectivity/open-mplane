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

#include "Spline.h"

using namespace std;
using namespace Mplane;


//------------------------------------------------------------------------------------------------------------------------
// Test fixture
class SplineTests : public ::testing::Test
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

    virtual ~SplineTests(){}

};



//========================================================================================================================
// TESTS
//========================================================================================================================


//------------------------------------------------------------------------------------------------------------------------
TEST_F(SplineTests, floats)
{
    Spline* spline = new Spline();

    spline->addpoint( 1.0f, 1.0f);
    spline->addpoint( 3.0f, 1.5f);
    spline->addpoint( 5.0f, 2.0f);
    spline->addpoint( 7.0f, 2.5f);
    spline->addpoint( 9.0f, 3.0f);

    EXPECT_FLOAT_EQ( spline->getY( 2.0f), 1.25f );
    EXPECT_FLOAT_EQ( spline->getY( 3.5f), 1.625f );
    EXPECT_FLOAT_EQ( spline->getY( 7.265f), 2.56625009f );
    EXPECT_FLOAT_EQ( spline->getY( 10.0f), 3.25f );
    EXPECT_FLOAT_EQ( spline->getY( 0.75f), 0.9375f );
    EXPECT_FLOAT_EQ( spline->getY( -1.0f), 0.5f );

    delete spline;

}
//------------------------------------------------------------------------------------------------------------------------
TEST_F(SplineTests, pwm)
{

    // PWM calibration data, feed parts of this into the spline and check the accuracy of
    // the spline function when filling in the gaps
    //    0   33.3
    //    39  33.3
    //    78  33.3
    //    117 33.29
    //    156 33.3
    //    195 33.31
    //    234 33.3
    //    273 33.3
    //    312 33.32
    //    351 33.29
    //    390 33.27
    //    429 33.29
    //    468 33.29
    //    507 33.29
    //    546 33.27
    //    585 33.26
    //    624 33.24
    //    663 33.23
    //    702 33.16
    //    741 33.12
    //    780 33.03
    //    819 32.85
    //    858 32.6
    //    897 32.19
    //    936 31.5
    //    975 30.18
    //    1014    28.03
    //    1053    25.3
    //    1092    22.44
    //    1131    19.86
    //    1170    17.68
    //    1209    15.9
    //    1248    14.45
    //    1287    13.26
    //    1326    12.28
    //    1365    11.46
    //    1404    10.77
    //    1443    10.17
    //    1482    9.66
    //    1521    9.21
    //    1560    8.81
    //    1599    8.45
    //    1638    8.12
    //    1677    7.83
    //    1716    7.55
    //    1755    7.29
    //    1794    7.05
    //    1833    6.83
    //    1872    6.61
    //    1911    6.4
    //    1950    6.21
    //    1989    6.02
    //    2028    5.83
    //    2067    5.65
    //    2106    5.47
    //    2145    5.3
    //    2184    5.13
    //    2223    4.97
    //    2262    4.8
    //    2301    4.65
    //    2340    4.49
    //    2379    4.33
    //    2418    4.17
    //    2457    4.03
    //    2496    3.88
    //    2535    3.73
    //    2574    3.59
    //    2613    3.44
    //    2652    3.3
    //    2691    3.16
    //    2730    3.02
    //    2769    2.88
    //    2808    2.75
    //    2847    2.62
    //    2886    2.48
    //    2925    2.36
    //    2964    2.23
    //    3003    2.11
    //    3042    1.99
    //    3081    1.87
    //    3120    1.76
    //    3159    1.64
    //    3198    1.54
    //    3237    1.43
    //    3276    1.33
    //    3315    1.24
    //    3354    1.14
    //    3393    1.05
    //    3432    0.96
    //    3471    0.88
    //    3510    0.8
    //    3549    0.73
    //    3588    0.66
    //    3627    0.59
    //    3666    0.52
    //    3705    0.46
    //    3744    0.4
    //    3783    0.34
    //    3822    0.29
    //    3861    0.25
    //    3900    0.2
    //    3939    0.15
    //    3978    0.11
    //    4017    0.07
    //    4056    0.04
    //    4096    0

    Spline spline;

    spline.addpoint( 0.02f, 3900.0f  );
    spline.addpoint( 0.8f, 3510.0f   );
    spline.addpoint( 1.76f, 3120.0f  );
    spline.addpoint( 3.02f, 2730.0f  );
    spline.addpoint( 3.73f, 2535.0f  );
    spline.addpoint( 4.49f, 2340.0f  );
    spline.addpoint( 6.21f, 1950.0f  );
    spline.addpoint( 7.29f, 1755.0f  );
    spline.addpoint( 8.81f, 1560.0f  );
    spline.addpoint( 10.77f, 1404.0f  );
    spline.addpoint( 13.26f, 1287.0f  );
    spline.addpoint( 17.68f, 1170.0f );
    spline.addpoint( 22.4f, 1092.0f );
    spline.addpoint( 28.03f, 1010.0f );
    spline.addpoint( 30.18f, 975.0f  );

    ASSERT_NEAR( spline.getY( 30.0f), 978.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 28.0f), 1010.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 26.0f), 1041.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 24.0f), 1069.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 22.44f), 1092.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 20.0f), 1129.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 17.68f), 1170.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 15.9f), 1209.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 14.45f), 1248.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 13.26f), 1287.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 12.28f), 1326.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 10.17f), 1443.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 8.81f), 1560.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 7.55f), 1715.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 6.83f), 1832.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 6.21f), 1950.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 5.47f), 2108.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 4.97f), 2223.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 4.49f), 2340.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 3.88f), 2495.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 3.44f), 2613.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 3.02f), 2730.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 2.36f), 2923.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 1.76f), 3120.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 1.24f), 3318.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 0.8f), 3510.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 0.52f), 3645.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 0.2f), 3807.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 0.11), 3853.0f, 1.0 );
    ASSERT_NEAR( spline.getY( 0.0), 3910.0f, 1.0);

}

//------------------------------------------------------------------------------------------------------------------------
TEST_F(SplineTests, dbm)
{

    Spline spline;

    spline.addpoint( 0.02f, 3900.0f  );
    spline.addpoint( 0.8f, 3510.0f   );
    spline.addpoint( 1.76f, 3120.0f  );
    spline.addpoint( 3.02f, 2730.0f  );
    spline.addpoint( 3.73f, 2535.0f  );
    spline.addpoint( 4.49f, 2340.0f  );
    spline.addpoint( 6.21f, 1950.0f  );
    spline.addpoint( 7.29f, 1755.0f  );
    spline.addpoint( 8.81f, 1560.0f  );
    spline.addpoint( 10.77f, 1404.0f  );
    spline.addpoint( 13.26f, 1287.0f  );
    spline.addpoint( 17.68f, 1170.0f );
    spline.addpoint( 22.4f, 1092.0f );
    spline.addpoint( 28.03f, 1010.0f );
    spline.addpoint( 30.18f, 975.0f  );

#if 0
    std::cout << "spline.getX( 975.0f) " << spline.getX( 975.0f) << std::endl;
    std::cout << "spline.getX( 1010.0f) " << spline.getX( 1010.0f) << std::endl;
    std::cout << "spline.getX( 1092.0f) " << spline.getX( 1092.0f) << std::endl;
    std::cout << "spline.getX( 1170.0f) " << spline.getX( 1170.0f) << std::endl;
    std::cout << "spline.getX( 1287.0f) " << spline.getX( 1287.0f) << std::endl;
    std::cout << "spline.getX( 1404.0f) " << spline.getX( 1404.0f) << std::endl;
    std::cout << "spline.getX( 1560.0f) " << spline.getX( 1560.0f) << std::endl;
    std::cout << "spline.getX( 1755.0f) " << spline.getX( 1755.0f) << std::endl;
    std::cout << "spline.getX( 1950.0f) " << spline.getX( 1950.0f) << std::endl;
    std::cout << "spline.getX( 2340.0f) " << spline.getX( 2340.0f) << std::endl;
#endif

    ASSERT_NEAR( spline.getX( 800.0f), 46.71f, 0.1 );
    ASSERT_NEAR( spline.getX( 975.0f), 30.18f, 0.1 );
    ASSERT_NEAR( spline.getX( 980.0f), 29.87f, 0.1 );
    ASSERT_NEAR( spline.getX( 1010.0f), 28.03f, 0.1 );
    ASSERT_NEAR( spline.getX( 1100.0f), 21.86f, 0.1 );
    ASSERT_NEAR( spline.getX( 1170.0f), 17.68f, 0.1 );
    ASSERT_NEAR( spline.getX( 1755.0f), 7.29f, 0.1 );
    ASSERT_NEAR( spline.getX( 1900.0f), 6.46f, 0.1 );
    ASSERT_NEAR( spline.getX( 2730.0f), 3.02f, 0.1 );
    ASSERT_NEAR( spline.getX( 3100.0f), 1.81f, 0.1 );
    ASSERT_NEAR( spline.getX( 3900.0f), 0.02f, 0.01 );
    ASSERT_NEAR( spline.getX( 4000.0f), -0.172f, 0.01 );
}

//------------------------------------------------------------------------------------------------------------------------
TEST_F(SplineTests, realPwm)
{



    Spline spline;

    spline.addpoint( 0.01f, 16383.0f  );
    spline.addpoint( 0.5f, 13545.0f   );
    spline.addpoint( 1.02f, 12126.0f  );
    spline.addpoint( 1.59f, 11094.0f  );
    spline.addpoint( 2.14f, 10320.0f  );
    spline.addpoint( 2.70f, 9675.0f  );
    spline.addpoint( 3.21f, 9159.0f  );
    spline.addpoint( 3.77f, 8643.0f  );
    spline.addpoint( 4.41f, 8127.0f  );
    spline.addpoint( 4.95f, 7740.0f  );
    spline.addpoint( 5.56f, 7353.0f  );
    spline.addpoint( 6.24f, 6966.0f );
    spline.addpoint( 6.76f, 6708.0f );
    spline.addpoint( 7.34f, 6450.0f );
    spline.addpoint( 8.02f, 6192.0f  );
    spline.addpoint( 8.82f, 5934.0f );
    spline.addpoint( 9.78f, 5676.0f);
    spline.addpoint( 10.35f, 5547.0f );
    spline.addpoint( 10.99f, 5418.0f);
    spline.addpoint( 11.71f, 5289.0f);
    spline.addpoint( 12.53f, 5160.0f );
    spline.addpoint( 13.48f, 5031.0f );
    spline.addpoint( 14.60f, 4902.0f );
    spline.addpoint( 15.90f, 4473.0f );
    spline.addpoint( 17.45f, 4644.0f );
    spline.addpoint( 19.29f, 4515.0f );
    spline.addpoint( 21.44f, 4386.0f );
    spline.addpoint( 23.93f, 4257.0f );
    spline.addpoint( 26.68f, 4128.0f );
    spline.addpoint( 29.47f, 3999.0f );
    spline.addpoint( 31.96f, 3870.0f );
    spline.addpoint( 33.79f, 3741.0f );
    spline.addpoint( 34.90f, 3612.0f );
    spline.addpoint( 35.47f, 3483.0f );
    spline.addpoint( 35.98f, 2967.0f );
    spline.addpoint( 36.01f, 0.0f );
    spline.addpoint( 50.00f, 0.0f );
    spline.addpoint( 60.00f, 0.0f );

    ASSERT_NEAR( spline.getY( 0.0), 16448.0f, 1.0);

}
