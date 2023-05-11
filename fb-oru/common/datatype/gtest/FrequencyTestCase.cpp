/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FrequencyTestCase.cpp
 * \brief     Implementation of the CppUnit test harness for Frequency
 *
 *
 * \details   This file contains the implementation of the CppUnit test cases
 *            for the common datatype Frequency class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>

#include "Frequency.h"

using namespace Mplane;

using namespace std;

/*
 * Unit tests
 */
TEST(FrequencyTestCase, creation)
{
    cout << endl << "*** FrequencyTestCase Tests ***" <<  endl;
    cout << __func__ << " - START" <<  endl;

    Frequency * freq_p = new Frequency();

    EXPECT_TRUE(freq_p != 0);

    EXPECT_TRUE(freq_p->getUint() == 0);

    delete freq_p;

    freq_p = new Frequency(1234567890ULL);

    EXPECT_TRUE(freq_p != 0);

    EXPECT_TRUE(freq_p->getUint() == 1234567890U);

    delete freq_p;

    Frequency f1(100ULL);
    EXPECT_TRUE(f1.getUint() == 100U);

    f1.set(10000.0, Frequency::KHz );
    EXPECT_EQ( f1.get( Frequency::Hz), 10000000ull );

    std::string sfreq = "5999";
    f1.set( sfreq, Frequency::KHz );
    EXPECT_EQ( f1.get( Frequency::Hz), 5999000ull );


    cout << __func__ << " - END" <<  endl;
}

TEST(FrequencyTestCase, assignment)
{
    cout << __func__ << " - START" <<  endl;
    Frequency * freq_p = new Frequency();

    EXPECT_TRUE(freq_p != 0);

    EXPECT_TRUE(freq_p->getUint() == 0u);

    *freq_p = 999ULL;

    EXPECT_TRUE(freq_p->getUint() == 999u);

    *freq_p = 1111ULL;

    EXPECT_TRUE(freq_p->getUint() == 1111u);

    *freq_p = Frequency(2100.0);

    EXPECT_TRUE(freq_p->getUint() == 2100u);

    delete freq_p;

    cout << __func__ << " - END" <<  endl;
}

TEST(FrequencyTestCase, addition)
{
    cout << __func__ << " - START" <<  endl;
    Frequency * freq_p = new Frequency();

    EXPECT_TRUE(freq_p != 0);

    EXPECT_TRUE(freq_p->getUint() == 0u);


    *freq_p = *freq_p + 100;

    EXPECT_TRUE(freq_p->getUint() == 100u);

    *freq_p = *freq_p + 300;

    EXPECT_TRUE(freq_p->getUint() == 400u);

    Frequency * f2_p = new Frequency(600ULL);

    *freq_p = *freq_p + *f2_p;

    EXPECT_TRUE(freq_p->getUint() == 1000u);

    *freq_p = *freq_p + (unsigned int) 2000.0;

    EXPECT_TRUE(freq_p->getUint() == 3000u);

    *freq_p += 4000;
    EXPECT_TRUE(freq_p->getUint() == 7000u);

    *freq_p += *f2_p;
    EXPECT_TRUE(freq_p->getUint() == 7600u);

    delete freq_p;

    delete f2_p;

    Frequency f1 = 100ULL;
    Frequency f2 = 200ULL;
    Frequency f3 = f1 + f2;
    EXPECT_TRUE(f3.getUint() == 300U);

    cout << __func__ << " - END" <<  endl;
}

TEST(FrequencyTestCase, multiply)
{
    cout << __func__ << " - START" <<  endl;
    Frequency * freq_p = new Frequency( 10ULL );

    EXPECT_TRUE(freq_p != 0);

    *freq_p = *freq_p * 100;

    EXPECT_TRUE(freq_p->getUint() == 1000u);


    Frequency * f2_p = new Frequency(600ULL);

    *freq_p = *freq_p * *f2_p;

    EXPECT_TRUE(freq_p->getUint() == 600000u);

    *freq_p = 22.0;

    *freq_p *= 1111;
    EXPECT_TRUE(freq_p->getUint() == 24442u);

    *freq_p *= *f2_p;
    EXPECT_TRUE(freq_p->getUint() == 14665200u);

    delete freq_p;

    delete f2_p;

    Frequency f1 = 100ULL;
    Frequency f2 = 200ULL;
    Frequency f3 = f1 * f2;
    EXPECT_TRUE(f3.getUint() == 20000U);

    cout << __func__ << " - END" <<  endl;
}

TEST(FrequencyTestCase, divide)
{
    cout << __func__ << " - START" <<  endl;
    Frequency * freq_p = new Frequency( 1000ULL );

    EXPECT_TRUE(freq_p != 0);

    *freq_p = *freq_p / 10;

    EXPECT_TRUE(freq_p->getUint() == 100u);


    Frequency * f2_p = new Frequency(20ULL);

    *freq_p = *freq_p / *f2_p;

    EXPECT_TRUE(freq_p->getUint() == 5);

    *freq_p = 3333.0;

    *freq_p /= 11;
    EXPECT_TRUE(freq_p->getUint() == 303u);

    *freq_p /= *f2_p;
    EXPECT_TRUE(freq_p->getUint() == 15u);

    delete freq_p;

    delete f2_p;

    Frequency f1 = 200ULL;
    Frequency f2 = 100ULL;
    Frequency f3 = f1 / f2;
    EXPECT_TRUE(f3.getUint() == 2U );

    cout << __func__ << " - END" <<  endl;
}


TEST(FrequencyTestCase, subtraction)
{
    cout << __func__ << " - START" <<  endl;
    Frequency * freq_p = new Frequency();

    EXPECT_TRUE(freq_p != 0);

    EXPECT_TRUE(freq_p->getUint() == 0);


    *freq_p = 4000000000ULL;

    EXPECT_TRUE(freq_p->getUint() == 4000000000U);

    *freq_p = *freq_p - 2000000000U;

    EXPECT_TRUE(freq_p->getUint() == 2000000000U);

    Frequency * f2_p = new Frequency(100000000ULL);

    *freq_p = *freq_p - *f2_p;

    EXPECT_TRUE(freq_p->getUint() == 1900000000U);

    *freq_p -= 4000;
    EXPECT_TRUE(freq_p->getUint() == 1899996000U);

    *freq_p -= *f2_p;
    EXPECT_TRUE(freq_p->getUint() == 1799996000U);

    delete freq_p;

    delete f2_p;

    Frequency f1 = 300ULL;
    Frequency f2 = 200ULL;
    Frequency f3 = f1 - f2;
    EXPECT_TRUE(f3.getUint() == 100U);

    cout << __func__ << " - END" <<  endl;
}


TEST(FrequencyTestCase, comparison)
{
    cout << __func__ << " - START" <<  endl;
    const Frequency f1 = 200000ULL;
    Frequency f2 = 200000ULL;

    EXPECT_TRUE(f1 == 200000);
    EXPECT_TRUE(f1 == f2);
    EXPECT_TRUE(f2 == 200000U);
    EXPECT_TRUE(!(f2 == 300000U));
    f2 = 300000.0;
    EXPECT_TRUE(!(f1 == f2));
    EXPECT_TRUE(!(f1 == 400000));

    EXPECT_TRUE(!(f1 == 300000U));

    EXPECT_TRUE(f1.getUint() == 200000u);

    f2 = 200000ULL;
    Frequency f3 = 100000ULL;
    Frequency f4 = 200000ULL;

    EXPECT_TRUE(f4 == f2);
    f2 = 300000ULL;
    EXPECT_TRUE(!(f4 == f2));

    EXPECT_TRUE(f3 != 200000);
    EXPECT_TRUE(f3 != f4);
    f4 = 100000.0;
    EXPECT_TRUE(!(f3 != f4));
    EXPECT_TRUE(!(f3 != 100000));

    EXPECT_TRUE(f3.getUint() == 100000u);

    Frequency f5 = 300000ULL;
    Frequency f6 = 200000ULL;

    EXPECT_TRUE(f5 > 200000);
    EXPECT_TRUE(f5 > f6);
    f6 = 500000ull;
    EXPECT_TRUE(!(f5 > f6));
    EXPECT_TRUE(!(f5 > 600000));

    EXPECT_TRUE(f5 < 500000);
    EXPECT_TRUE(f5 < f6);
    f6 = 200000ull;
    EXPECT_TRUE(!(f5 < f6));
    EXPECT_TRUE(!(f5 < 100000));

    cout << __func__ << " - END" <<  endl;
}


TEST(FrequencyTestCase, accessors)
{
    cout << __func__ << " - START" <<  endl;
    Frequency * freq_p = new Frequency(2100.0, Frequency::MHz );

    EXPECT_TRUE(freq_p != 0);

    EXPECT_TRUE(freq_p->getUint() == 2100000000u);

    EXPECT_TRUE(freq_p->getUint(Frequency::MHz) == 2100u);

    freq_p->set( 1234567890U, Frequency::Hz );
    EXPECT_TRUE(freq_p->getUint() == 1234567890U );
    freq_p->set( 700U, Frequency::MHz );
    EXPECT_TRUE(freq_p->getUint() == 700000000U );
    freq_p->set( 800U, Frequency::KHz );
    EXPECT_TRUE(freq_p->getUint() == 800000U );
    EXPECT_TRUE(freq_p->getUint(Frequency::KHz ) == 800u );
    EXPECT_TRUE(freq_p->getDbl(Frequency::MHz ) == 0.8 );

    freq_p->set(853.5, Frequency::MHz );
    EXPECT_TRUE(freq_p->getUint() == 853500000u );
    EXPECT_TRUE(freq_p->getUint(Frequency::KHz ) == 853500u );

    delete freq_p;

    cout << __func__ << " - END" <<  endl;
}

TEST(FrequencyTestCase, unitToStr)
{
    cout << __func__ << " - START" <<  endl;
    EXPECT_TRUE(strcmp(Frequency::unit2Str(Frequency::Hz),"Hz") == 0);
    EXPECT_TRUE(strcmp(Frequency::unit2Str(Frequency::THz),"THz") == 0);
    EXPECT_TRUE(strcmp(Frequency::unit2Str(Frequency::HHz),"HHz") == 0);
    EXPECT_TRUE(strcmp(Frequency::unit2Str(Frequency::KHz),"KHz") == 0);
    EXPECT_TRUE(strcmp(Frequency::unit2Str(Frequency::TKHz),"TKHz") == 0);
    EXPECT_TRUE(strcmp(Frequency::unit2Str(Frequency::HKHz),"HKHz") == 0);
    EXPECT_TRUE(strcmp(Frequency::unit2Str(Frequency::MHz),"MHz") == 0);
    EXPECT_TRUE(strcmp(Frequency::unit2Str((Frequency::Unit)55),"unknown") == 0);

    cout << __func__ << " - END" <<  endl;
}


TEST(FrequencyTestCase, addInt)
{
    cout << __func__ << " - START" <<  endl;
    Frequency freq(700ULL, Frequency::MHz );
    int stepUp(+10000) ;
    int stepDown(-10000) ;

    EXPECT_EQ(700000000ULL, freq.getUint());

    freq += stepUp ;
    EXPECT_EQ(700010000ULL, freq.getUint());
    freq += stepUp ;
    EXPECT_EQ(700020000ULL, freq.getUint());
    freq += stepUp ;
    EXPECT_EQ(700030000ULL, freq.getUint());

    freq += stepDown ;
    EXPECT_EQ(700020000ULL, freq.getUint());
    freq += stepDown ;
    EXPECT_EQ(700010000ULL, freq.getUint());
    freq += stepDown ;
    EXPECT_EQ(700000000ULL, freq.getUint());

    cout << __func__ << " - END" <<  endl;
}
