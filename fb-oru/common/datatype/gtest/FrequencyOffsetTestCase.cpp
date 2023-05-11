/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FrequencyOffsetTestCase.cpp
 * \brief     Implementation of the CppUnit test harness for Frequency
 *
 *
 * \details   This file contains the implementation of the CppUnit test cases
 *            for the common datatype FrequencyOffset class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>

#include "Frequency.h"
#include "FrequencyOffset.h"

using namespace Mplane;


using namespace std;

/*
 * Unit tests
 */
TEST(FrequencyOffsetTestCase, creation)
{
    FrequencyOffset * freq_p = new FrequencyOffset();

    EXPECT_TRUE(freq_p != 0);

    EXPECT_TRUE(freq_p->getUint() == 0);

    delete freq_p;

    freq_p = new FrequencyOffset(1234567890U);

    EXPECT_TRUE(freq_p != 0);

    EXPECT_TRUE(freq_p->getUint() == 1234567890U);

    delete freq_p;

    FrequencyOffset f1(100U);
    EXPECT_TRUE(f1.getUint() == 100U);

    cout << __func__ << " - END" <<  endl;
}

TEST(FrequencyOffsetTestCase, assigment)
{
    cout << __func__ << " - START" <<  endl;
    FrequencyOffset * freq_p = new FrequencyOffset();

    EXPECT_TRUE(freq_p != 0);

    EXPECT_TRUE(freq_p->getUint() == 0);

    *freq_p = 999U;

    EXPECT_TRUE(freq_p->getUint() == 999);

    *freq_p = 1111U;

    EXPECT_TRUE(freq_p->getUint() == 1111);

    *freq_p = FrequencyOffset(2100.0);

    EXPECT_TRUE(freq_p->getUint() == 2100);

    delete freq_p;

    cout << __func__ << " - END" <<  endl;
}

TEST(FrequencyOffsetTestCase, addition)
{
    cout << __func__ << " - START" <<  endl;
    FrequencyOffset * freq_p = new FrequencyOffset();
    FrequencyOffset * freq_q = new FrequencyOffset(1000.0);

    EXPECT_TRUE(freq_p != 0);
    EXPECT_TRUE(freq_p->getUint() == 0);
    EXPECT_TRUE(freq_q != 0);
    EXPECT_TRUE(freq_q->getUint() == 1000);

    *freq_q = *freq_p ;

    *freq_p = *freq_p + 100u;

    EXPECT_TRUE(freq_p->getUint() == 100);

    *freq_p = *freq_p + 300;

    EXPECT_TRUE(freq_p->getUint() == 400);

    FrequencyOffset * f2_p = new FrequencyOffset(600U);

    *freq_p = *freq_p + *f2_p;

    EXPECT_TRUE(freq_p->getUint() == 1000);

    *freq_p = *freq_p + (unsigned int) 2000.0;

    EXPECT_TRUE(freq_p->getUint() == 3000);

    *freq_p += 4000;
    EXPECT_TRUE(freq_p->getUint() == 7000);

    *freq_p += *f2_p;
    EXPECT_TRUE(freq_p->getUint() == 7600);

    delete freq_p;
    delete freq_q;

    delete f2_p;

    FrequencyOffset f1 = 100U;
    FrequencyOffset f2 = 200U;
    FrequencyOffset f3 = f1 + f2;
    EXPECT_TRUE(f3.getUint() == 300U);

    cout << __func__ << " - END" <<  endl;
}

TEST(FrequencyOffsetTestCase, multiply)
{
    cout << __func__ << " - START" <<  endl;
    FrequencyOffset * freq_p = new FrequencyOffset( 10U );

    EXPECT_TRUE(freq_p != 0);

    *freq_p = *freq_p * 100;

    EXPECT_TRUE(freq_p->getUint() == 1000);


    FrequencyOffset * f2_p = new FrequencyOffset(600U);

    *freq_p = *freq_p * *f2_p;

    EXPECT_TRUE(freq_p->getUint() == 600000);

    *freq_p = 22;

    *freq_p *= 1111;
    EXPECT_TRUE(freq_p->getUint() == 24442);

    *freq_p *= *f2_p;
    EXPECT_TRUE(freq_p->getUint() == 14665200);

    delete freq_p;

    delete f2_p;

    FrequencyOffset f1 = 100U;
    FrequencyOffset f2 = 200U;
    FrequencyOffset f3 = f1 * f2;
    EXPECT_TRUE(f3.getUint() == 20000U);

    cout << __func__ << " - END" <<  endl;
}

TEST(FrequencyOffsetTestCase, divide)
{
    cout << __func__ << " - START" <<  endl;
    FrequencyOffset * freq_p = new FrequencyOffset( 1000U );

    EXPECT_TRUE(freq_p != 0);

    *freq_p = *freq_p / 10;

    EXPECT_TRUE(freq_p->getUint() == 100);


    FrequencyOffset * f2_p = new FrequencyOffset(20U);

    *freq_p = *freq_p / *f2_p;

    EXPECT_TRUE(freq_p->getUint() == 5);

    *freq_p = 3333;

    *freq_p /= 11;
    EXPECT_TRUE(freq_p->getUint() == 303);

    *freq_p /= *f2_p;
    EXPECT_TRUE(freq_p->getUint() == 15);

    delete freq_p;

    delete f2_p;

    FrequencyOffset f1 = 200U;
    FrequencyOffset f2 = 100U;
    FrequencyOffset f3 = f1 / f2;
    EXPECT_TRUE(f3.getUint() == 2U );

    cout << __func__ << " - END" <<  endl;
}


TEST(FrequencyOffsetTestCase, subtraction)
{
    cout << __func__ << " - START" <<  endl;
    FrequencyOffset * freq_p = new FrequencyOffset();

    EXPECT_TRUE(freq_p != 0);

    EXPECT_TRUE(freq_p->getUint() == 0);


    *freq_p = 4000000000U;

    EXPECT_TRUE(freq_p->getUint() == 4000000000U);

    *freq_p = *freq_p - 2000000000U;

    EXPECT_TRUE(freq_p->getUint() == 2000000000U);

    FrequencyOffset * f2_p = new FrequencyOffset(100000000U);

    *freq_p = *freq_p - *f2_p;

    EXPECT_TRUE(freq_p->getUint() == 1900000000U);

    *freq_p -= 4000;
    EXPECT_TRUE(freq_p->getUint() == 1899996000U);

    *freq_p -= *f2_p;
    EXPECT_TRUE(freq_p->getUint() == 1799996000U);



    delete freq_p;

    delete f2_p;

    FrequencyOffset f1 = 300U;
    FrequencyOffset f2 = 200U;
    FrequencyOffset f3 = f1 - f2;
    EXPECT_TRUE(f3.getUint() == 100U);

    f3 = f2 - f1;
    EXPECT_EQ(-100, f3.getInt());

    EXPECT_EQ(-100LL, f3.get());



    cout << __func__ << " - END" <<  endl;
}


TEST(FrequencyOffsetTestCase, comparison)
{
    cout << __func__ << " - START" <<  endl;

const FrequencyBase<long long> fb1 = 200000LL;
FrequencyBase<long long> fb2 = 200000LL;
EXPECT_TRUE(fb1.operator==(fb2));

    const FrequencyOffset f1 = 200000U;
    FrequencyOffset f2 = 200000U;

EXPECT_TRUE(f1.operator==(f2));

    EXPECT_TRUE(f1 == 200000);
    EXPECT_TRUE(f1 == f2);
    EXPECT_TRUE(f2 == 200000U);
    EXPECT_TRUE(!(f2 == 300000U));
    f2 = 300000;
    EXPECT_TRUE(!(f1 == f2));
    EXPECT_TRUE(!(f1 == 400000));

    EXPECT_TRUE(!(f1 == 300000U));

    EXPECT_TRUE(f1.getUint() == 200000);

    f2 = 200000U;
    FrequencyOffset f3 = 100000U;
    FrequencyOffset f4 = 200000U;

    EXPECT_TRUE(f4 == f2);
    f2 = 300000U;
    EXPECT_TRUE(!(f4 == f2));

    EXPECT_TRUE(f3 != 200000);
    EXPECT_TRUE(f3 != f4);
    f4 = 100000;
    EXPECT_TRUE(!(f3 != f4));
    EXPECT_TRUE(!(f3 != 100000));

    EXPECT_TRUE(f3.getUint() == 100000);

    FrequencyOffset f5 = 300000U;
    FrequencyOffset f6 = 200000U;
    FrequencyOffset f7 = 300000U;
    FrequencyOffset f8 = 500000;

    EXPECT_TRUE(f5 > 200000);
    EXPECT_TRUE(f5 >= 200000);
    EXPECT_TRUE(f5 >= 300000);
    EXPECT_TRUE(f5 > f6);
    EXPECT_TRUE(f5 >= f6);
    EXPECT_TRUE(f5 >= f7);

    EXPECT_TRUE(!(f5 > f8));
    EXPECT_TRUE(!(f5 > 600000));

    EXPECT_TRUE(f5 < 500000);
    EXPECT_TRUE(f5 <= 500000);
    EXPECT_TRUE(f5 <= 300000);
    EXPECT_TRUE( !(f5 <= 200000) );
    EXPECT_TRUE(f5 < f8);
    EXPECT_TRUE(f5 <= f8);
    EXPECT_TRUE(f5 <= f7);

    EXPECT_TRUE(!(f5 < f6));
    EXPECT_TRUE(!(f5 < 100000));

    cout << __func__ << " - END" <<  endl;
}


TEST(FrequencyOffsetTestCase, accessors)
{
    cout << __func__ << " - START" <<  endl;
    FrequencyOffset * freq_p = new FrequencyOffset(2100.0, FrequencyOffset::MHz );

    EXPECT_TRUE(freq_p != 0);

    EXPECT_TRUE(freq_p->getUint() == 2100000000);

    EXPECT_TRUE(freq_p->getUint(FrequencyOffset::MHz) == 2100);

    freq_p->set( 1234567890U, FrequencyOffset::Hz );
    EXPECT_TRUE(freq_p->getUint() == 1234567890U );
    freq_p->set( 700U, FrequencyOffset::MHz );
    EXPECT_TRUE(freq_p->getUint() == 700000000U );
    freq_p->set( 800U, FrequencyOffset::KHz );
    EXPECT_TRUE(freq_p->getUint() == 800000U );
    EXPECT_TRUE(freq_p->getUint(FrequencyOffset::KHz ) == 800 );
    EXPECT_TRUE(freq_p->getDbl(FrequencyOffset::MHz ) == 0.8 );

    freq_p->set(853.5, FrequencyOffset::MHz );
    EXPECT_EQ(853500000U, freq_p->getUint() );
    EXPECT_EQ(853500U, freq_p->getUint(FrequencyOffset::KHz ) );

    delete freq_p;

    cout << __func__ << " - END" <<  endl;
}

TEST(FrequencyOffsetTestCase, unitToStr)
{
    cout << __func__ << " - START" <<  endl;
    EXPECT_TRUE(strcmp(FrequencyOffset::unit2Str(FrequencyOffset::Hz),"Hz") == 0);
    EXPECT_TRUE(strcmp(FrequencyOffset::unit2Str(FrequencyOffset::THz),"THz") == 0);
    EXPECT_TRUE(strcmp(FrequencyOffset::unit2Str(FrequencyOffset::HHz),"HHz") == 0);
    EXPECT_TRUE(strcmp(FrequencyOffset::unit2Str(FrequencyOffset::KHz),"KHz") == 0);
    EXPECT_TRUE(strcmp(FrequencyOffset::unit2Str(FrequencyOffset::TKHz),"TKHz") == 0);
    EXPECT_TRUE(strcmp(FrequencyOffset::unit2Str(FrequencyOffset::HKHz),"HKHz") == 0);
    EXPECT_TRUE(strcmp(FrequencyOffset::unit2Str(FrequencyOffset::MHz),"MHz") == 0);
    EXPECT_TRUE(strcmp(FrequencyOffset::unit2Str((FrequencyOffset::Unit)55),"unknown") == 0);

    cout << __func__ << " - END" <<  endl;
}

TEST(FrequencyOffsetTestCase, freqOffset)
{
    cout << __func__ << " - START" <<  endl;

    Frequency f1 = 1000ULL ;
    Frequency f2 = 2000ULL ;

    FrequencyOffset diff = FrequencyOffset(f1) - FrequencyOffset(f2) ;
    EXPECT_EQ(-1000, diff.getInt());
    EXPECT_EQ(-1000.0, diff.getDbl());


    cout << __func__ << " - END" <<  endl;
}
