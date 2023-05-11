/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TemperatureTestCase.cpp
 * \brief     Implementation of the CppUnit test harness for Temperature
 *
 *
 * \details   This file contains the implementation of the CppUnit test cases
 *            for the common datatype Temperature class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <math.h>

#include "Temperature.h"

using namespace Mplane;

using namespace std;

/*
 * Unit tests
 */
TEST(TemperatureTestCase, creation)
{
    cout << endl << "*** TemperatureTestCase Tests ***" <<  endl;
    cout << __func__ << " - START" <<  endl;

    Temperature pdbm1(21.0f );
    Temperature pdbm2(22.0f );
    Temperature pdbm3(25.0f );
    Temperature pdbm4(1234.0f );
    EXPECT_TRUE(pdbm1 == 21.0f);
    EXPECT_TRUE(pdbm2 == 22.0f);
    EXPECT_TRUE(pdbm3 == 25.0f);
    EXPECT_TRUE(pdbm4 == 1234.0f);

    Temperature p1(34.5f);
    EXPECT_TRUE( p1 == 34.5f);

    std::string temperature = "25.5";
    p1.set( temperature );
    EXPECT_TRUE( p1 == 25.5f);

    Temperature rtemp( 0.03663, -50.0 );
    rtemp = 2048;
    EXPECT_EQ( 25, rtemp.getInt() );

    cout << __func__ << " - END" <<  endl;
}

TEST(TemperatureTestCase, assigment)
{
    cout << __func__ << " - START" <<  endl;

    Temperature temperature;
    EXPECT_TRUE(temperature == 0.0f);

    temperature = 12.0f;
    EXPECT_TRUE(temperature == 12.0f);

    Temperature rtemp( 0.03663, -50.0 );

    rtemp = 2048;
    EXPECT_TRUE( rtemp.getInt() == 25 );

    rtemp = 4095;
    EXPECT_TRUE( rtemp.getInt() == 100 );

    rtemp = 0;
    EXPECT_TRUE( rtemp.getInt() == -50 );

    cout << __func__ << " - END" <<  endl;
}


TEST(TemperatureTestCase, comparison)
{
    cout << __func__ << " - START" <<  endl;

    // test the == functions
    const Temperature f1 = 10;
    Temperature f2 = 10;

    EXPECT_TRUE(f1 == 10);
    EXPECT_TRUE(f1 == (float)10.0);
    EXPECT_TRUE(f1 == f2);
    EXPECT_TRUE(f2 == 10);
    EXPECT_TRUE(f2 == (float)10.0);
    EXPECT_TRUE(!(f2 == 20));
    EXPECT_TRUE(!(f2 == (float)20.0));

    // test the != functions
    f2 = 30;
    EXPECT_TRUE(!(f1 == f2));
    EXPECT_TRUE(!(f1 == 40));
    EXPECT_TRUE(!(f1 == 30));
    EXPECT_TRUE(!(f1 == (float)30.0));

//    EXPECT_TRUE(f1.getInt() == 10);

    f2 = 20;
    Temperature f3 = 10;
    Temperature f4 = 20;
    Temperature f5 = 30;
    Temperature f6 = 20;

    EXPECT_TRUE(f4 == f2);
    f2 = 30;
    EXPECT_TRUE(!(f4 == f2));
    EXPECT_TRUE(f3 != 20);
    EXPECT_TRUE(f3 != (float)20.0);
    EXPECT_TRUE(f3 != f4);
    f4 = 10;
    EXPECT_TRUE(!(f3 != f4));
    EXPECT_TRUE(!(f3 != 10));
    EXPECT_TRUE(!(f3 != (float)10.0));

//    EXPECT_TRUE(f3.getInt() == 10);

    // test the != const functions
    Temperature f7 = 9;
    EXPECT_TRUE((f1 != 9));
    EXPECT_TRUE(!(f1 != 10));
    EXPECT_TRUE((f1 != (float)9.0));
    EXPECT_TRUE(!(f1 != (float)10.0));
    EXPECT_TRUE((f1 != f7));
    EXPECT_TRUE(!(f1 != f3));

    // test the > functions
    EXPECT_TRUE(f5 > 20);
    EXPECT_TRUE(f5 > (float)20.0);
    EXPECT_TRUE(f5 > f6);
    f6 = 50;
    EXPECT_TRUE(!(f5 > f6));
    EXPECT_TRUE(!(f5 > 60));
    EXPECT_TRUE(!(f5 > (float)60.0));

    // test the > const functions
    EXPECT_TRUE((f1 > 9));
    EXPECT_TRUE(!(f1 > 10));
    EXPECT_TRUE((f1 > (float)9.0));
    EXPECT_TRUE(!(f1 > (float)10.0));
    EXPECT_TRUE((f1 > f7));
    EXPECT_TRUE(!(f1 > f6));

    // test the < functions
    EXPECT_TRUE(f5 < 50);
    EXPECT_TRUE(f5 < (float)50.0);
    EXPECT_TRUE(f5 < f6);
    f6 = 20;
    EXPECT_TRUE(!(f5 < f6));
    EXPECT_TRUE(!(f5 < 10));
    EXPECT_TRUE(!(f5 < (float)10.0));

    // test the < const functions
    EXPECT_TRUE((f1 < 11));
    EXPECT_TRUE(!(f1 < 10));
    EXPECT_TRUE((f1 < (float)11.0));
    EXPECT_TRUE(!(f1 < (float)10.0));
    EXPECT_TRUE((f1 < f6));
    EXPECT_TRUE(!(f1 < f7));

    cout << __func__ << " - END" <<  endl;
}


TEST(TemperatureTestCase, addition)
{
    cout << __func__ << " - START" <<  endl;

    Temperature tempA;
    EXPECT_TRUE(tempA == 0.0f);

    tempA = 12.0f;
    EXPECT_TRUE(tempA == 12.0f);

    tempA += 10.0f ;
    EXPECT_TRUE(tempA == 22.0f);

    tempA = tempA + 5.0f ;
    EXPECT_TRUE(tempA == 27.0f);

    Temperature tempB(10.0);
    EXPECT_TRUE(tempB == 10.0f);

    tempA += tempB ;
    EXPECT_TRUE(tempA == 37.0f);

    tempA = tempA + tempB ;
    EXPECT_TRUE(tempA == 47.0f);


    cout << __func__ << " - END" <<  endl;
}

TEST(TemperatureTestCase, subtraction)
{
    cout << __func__ << " - START" <<  endl;

    Temperature tempA(20.0);
    EXPECT_TRUE(tempA == 20.0f);

    tempA -= 2.0f;
    EXPECT_TRUE(tempA == 18.0f);

    tempA = tempA - 5.0f ;
    EXPECT_TRUE(tempA == 13.0f);

    Temperature tempB(10.0);
    EXPECT_TRUE(tempB == 10.0f);

    tempA -= tempB ;
    EXPECT_TRUE(tempA == 3.0f);

    tempA = tempA - tempB ;
    EXPECT_TRUE(tempA == -7.0f);


    cout << __func__ << " - END" <<  endl;
}

TEST(TemperatureTestCase, multiplication)
{
    cout << __func__ << " - START" <<  endl;

    Temperature tempA(20.0);
    EXPECT_TRUE(tempA == 20.0f);

    tempA *= 2.0f ;
    EXPECT_TRUE(tempA == 40.0f);

    tempA = tempA * 0.5f ;
    EXPECT_TRUE(tempA == 20.0f);

    Temperature tempB(3.0);
    EXPECT_TRUE(tempB == 3.0f);

    tempA *= tempB ;
    EXPECT_TRUE(tempA == 60.0f);

    tempA = tempA * tempB ;
    EXPECT_TRUE(tempA == 180.0f);


    cout << __func__ << " - END" <<  endl;
}

TEST(TemperatureTestCase, division)
{
    cout << __func__ << " - START" <<  endl;

    Temperature tempA(20.0);
    EXPECT_TRUE(tempA == 20.0f);

    tempA /= 2.0f ;
    EXPECT_TRUE(tempA == 10.0f);

    tempA = tempA / 0.5f ;
    EXPECT_TRUE(tempA == 20.0f);

    Temperature tempB(2.0);
    EXPECT_TRUE(tempB == 2.0f);

    tempA /= tempB ;
    EXPECT_TRUE(tempA == 10.0f);

    tempA = tempA / tempB ;
    EXPECT_TRUE(tempA == 5.0f);


    cout << __func__ << " - END" <<  endl;
}
