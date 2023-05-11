/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PowerTestCase.cpp
 * \brief     Implementation of the CppUnit test harness for Power
 *
 *
 * \details   This file contains the implementation of the CppUnit test cases
 *            for the common datatype Power class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <math.h>

#include "Power.h"

using namespace Mplane;

using namespace std;

/*
 * Unit tests
 */
TEST(PowerTestCase, creation)
{
    cout << endl << "*** PowerTestCase Tests ***" <<  endl;
    cout << __func__ << " - START" <<  endl;

    Power* power_p = new Power();

    EXPECT_TRUE(power_p != 0);
    EXPECT_TRUE(power_p->get() == 0);

    // Test the power conversion functions
    // Watts to dBm
    power_p->setWatts( 0.0001f );
    EXPECT_EQ(power_p->get(), -10.0f);
    power_p->setWatts( 0.001f );
    EXPECT_EQ(power_p->get(), 0.0f);
    power_p->setWatts( 1.0f );
    EXPECT_EQ(power_p->get(), 30.0f);
    power_p->setWatts( 10.0f );
    EXPECT_EQ(power_p->get(), 40.0f);
    // dBm to Watts
    power_p->set( -10.0f );
    EXPECT_EQ(power_p->getWatts(), 0.0001f);
    power_p->set( 0.0f );
    EXPECT_EQ(power_p->getWatts(), 0.001f);
    power_p->set( 30.0f );
    EXPECT_EQ(power_p->getWatts(), 1.0f);
    power_p->set( 40.0f );
    EXPECT_EQ(power_p->getWatts(), 10.0f);

    std::string sPower="20.0";
    power_p->set( sPower );
    EXPECT_EQ(power_p->get(), 20.0f);

    delete power_p;

    Power pdbm1(21.0, Power::dBm);
    Power pdbm2(22.0, Power::TdBm);   // = 2.2dBm
    Power pdbm3(25.0, Power::HdBm);   // = 0.25dBm
    Power pdbm4(1234.0, Power::KdBm); // = 1.234dBm
    EXPECT_TRUE(pdbm1.get() == (float)21.0);
    EXPECT_TRUE(pdbm2.get() == (float)2.2);
    EXPECT_TRUE(pdbm3.get() == (float)0.25);
    EXPECT_TRUE(pdbm4.get() == (float)1.234);

    Power p1(34.5); // in dBm
    float power_in_dBm = p1.get();
//    float power_in_watts = p1.getWatts();
    EXPECT_TRUE(power_in_dBm == 34.5);
    cout << "34.5 dbM is " << p1.getWatts() <<  endl;
//    EXPECT_TRUE(power_in_watts == p1.convertdBmToWatts(power_in_dBm));

    power_p = new Power(12.34);

    EXPECT_TRUE(power_p != 0);
    EXPECT_TRUE(power_p->get() == (float)12.34);
    EXPECT_TRUE(power_p->get(Power::dBm) == (float)12.34);
    EXPECT_TRUE(power_p->get(Power::TdBm) == (float)123.4);
    EXPECT_TRUE(power_p->get(Power::HdBm) == (float)1234.0);
    EXPECT_TRUE(power_p->get(Power::KdBm) == (float)12340.0);

    delete power_p;

    Power pconst(12.34); // = 12.34dBm
    int power_HdBm = pconst.getInt(Power::HdBm); // = 1234
    EXPECT_TRUE(power_HdBm == 1234);
    EXPECT_TRUE(pconst.getInt(Power::dBm) == 12);
    EXPECT_TRUE(pconst.getInt(Power::TdBm) == 123);
    EXPECT_TRUE(pconst.getInt(Power::KdBm) == 12340);

    Power pconst2(23.67); // = 23.67dBm
    EXPECT_TRUE(pconst2.getInt(Power::dBm) == 24);
    EXPECT_TRUE(pconst2.getInt(Power::TdBm) == 237);
    EXPECT_TRUE(pconst2.getInt(Power::HdBm) == 2367);
    EXPECT_TRUE(pconst2.getInt(Power::KdBm) == 23670);

    Power pconst3(-43.67); // = -43.67dBm
    EXPECT_TRUE(pconst3.getInt(Power::dBm) == -44);
    EXPECT_TRUE(pconst3.getInt(Power::TdBm) == -437);
    EXPECT_TRUE(pconst3.getInt(Power::HdBm) == -4367);
    EXPECT_TRUE(pconst3.getInt(Power::KdBm) == -43670);

    cout << __func__ << " - END" <<  endl;
}

TEST(PowerTestCase, assignment)
{
    cout << __func__ << " - START" <<  endl;

    Power* power_p = new Power();

    EXPECT_TRUE(power_p != 0);

    EXPECT_TRUE(power_p->getInt() == 0);

    *power_p = (Power)1.236;

    EXPECT_TRUE(power_p->get() == (float)1.236);
    EXPECT_TRUE(power_p->getInt() == 1);
    EXPECT_TRUE(power_p->getInt(Power::HdBm) == 124);

    *power_p = (float)-56.9;

    EXPECT_TRUE(power_p->get() == (float)-56.9);
    EXPECT_TRUE(power_p->getInt() == -57);

    *power_p = (int)-34;

    EXPECT_TRUE(power_p->get() == (float)-34.0);
    EXPECT_TRUE(power_p->getInt() == -34);

    *power_p = Power(89.0);

    EXPECT_TRUE(power_p->getInt() == 89);

    delete power_p;

    cout << __func__ << " - END" <<  endl;
}

TEST(PowerTestCase, addition)
{
    cout << __func__ << " - START" <<  endl;

    Power* power_p = new Power();

    EXPECT_TRUE(power_p != 0);

    EXPECT_TRUE(power_p->getInt() == 0);


    *power_p = *power_p + 10;

    EXPECT_TRUE(power_p->get() == (float)10.0);
    EXPECT_TRUE(power_p->getInt() == 10);

    *power_p = *power_p + (float)30.1;
    EXPECT_TRUE(power_p->get() == (float)40.1);
    EXPECT_TRUE(power_p->getInt() == 40);

    Power* p2_p = new Power(60.0);

    *power_p = *power_p + *p2_p;

    EXPECT_TRUE(power_p->get() == (float)100.1);
    EXPECT_TRUE(power_p->getInt() == 100);

    *power_p = *power_p + (int) -2.0;

    EXPECT_TRUE(power_p->get() == (float)98.1);
    EXPECT_TRUE(power_p->getInt() == 98);

    *power_p += (float)40.1;
    EXPECT_TRUE(power_p->get() == (float)138.2);
    EXPECT_TRUE(power_p->getInt() == 138);

    *power_p += (int)3;
    EXPECT_TRUE(power_p->get() == (float)141.2);
    EXPECT_TRUE(power_p->getInt() == 141);

    *power_p += *p2_p;
    EXPECT_TRUE(power_p->get() == (float)201.2);
    EXPECT_TRUE(power_p->getInt() == 201);

    delete power_p;
    delete p2_p;

    Power p1 = 1.5;
    Power p2 = 2.2;
    Power p3 = p1 + p2;
    EXPECT_TRUE(p3.get() == (float)3.7);
    EXPECT_TRUE(p3.getInt() == 4);

    cout << __func__ << " - END" <<  endl;
}

TEST(PowerTestCase, multiply)
{
    cout << __func__ << " - START" <<  endl;

    Power* power_p = new Power(10.1);

    EXPECT_TRUE(power_p != 0);

    *power_p = *power_p * (float)10.0;

    EXPECT_TRUE(power_p->get() == (float)101.0);
    EXPECT_TRUE(power_p->getInt() == 101);

    *power_p = *power_p * 2;

    EXPECT_TRUE(power_p->get() == (float)202.0);
    EXPECT_TRUE(power_p->getInt() == 202);

    Power* p2_p = new Power(5.5);

    *power_p = 10;
    *power_p = *power_p * *p2_p;

    EXPECT_TRUE(power_p->get() == (float)55.0);
    EXPECT_TRUE(power_p->getInt() == 55);

    *power_p = 20;

    *power_p *= 10;
    EXPECT_TRUE(power_p->get() == (float)200.0);
    EXPECT_TRUE(power_p->getInt() == 200);

    *power_p *= (float)10.0;
    EXPECT_TRUE(power_p->get() == (float)2000.0);
    EXPECT_TRUE(power_p->getInt() == 2000);

    *power_p *= *p2_p;
    EXPECT_TRUE(power_p->get() == (float)11000.0);
    EXPECT_TRUE(power_p->getInt() == 11000);

    delete power_p;
    delete p2_p;

    Power p1 = 2.2;
    Power p2 = 5.0;
    Power p3 = p1 * p2;
    float result = p3.get();
    EXPECT_TRUE(result == (float)11.0);
    EXPECT_TRUE(p3.getInt() == 11);

    cout << __func__ << " - END" <<  endl;
}

TEST(PowerTestCase, divide)
{
    cout << __func__ << " - START" <<  endl;

    Power* power_p = new Power(120);

    EXPECT_TRUE(power_p != 0);

    *power_p = *power_p / (float)1.5;

    EXPECT_TRUE(power_p->getInt() == 80);

    *power_p = *power_p / (int)2;

    EXPECT_TRUE(power_p->getInt() == 40);

    Power* p2_p = new Power(20);

    *power_p = *power_p / *p2_p;

    EXPECT_TRUE(power_p->getInt() == 2);

    *power_p = 3333;

    *power_p /= (int)11;
    EXPECT_TRUE(power_p->getInt() == 303);

    *power_p = 300;
    *power_p /= (float)1.5;
    EXPECT_TRUE(power_p->getInt() == 200);

    *power_p /= *p2_p;
    EXPECT_TRUE(power_p->getInt() == 10);

    delete power_p;
    delete p2_p;

    Power p1 = 200;
    Power p2 = 100;
    Power p3 = p1 / p2;
    EXPECT_TRUE(p3.getInt() == 2 );

    cout << __func__ << " - END" <<  endl;
}

TEST(PowerTestCase, subtraction)
{
    cout << __func__ << " - START" <<  endl;

    Power* power_p = new Power(30);

    EXPECT_TRUE(power_p != 0);

    EXPECT_TRUE(power_p->getInt() == 30);


    *power_p = *power_p - 10;

    EXPECT_TRUE(power_p->get() == (float)20.0);
    EXPECT_TRUE(power_p->getInt() == 20);

    *power_p = *power_p - (float)9.9;
    EXPECT_TRUE(power_p->get() == (float)10.1);
    EXPECT_TRUE(power_p->getInt() == 10);

    *power_p = *power_p - (float)1.2;
    EXPECT_TRUE(power_p->getInt() == 9);

    *power_p = 20;
    Power* p2_p = new Power(60.0);

    *power_p = *power_p - *p2_p;

    EXPECT_TRUE(power_p->get() == (float)-40.0);
    EXPECT_TRUE(power_p->getInt() == -40);

    *power_p = *power_p - (int) -2.0;

    EXPECT_TRUE(power_p->get() == (float)-38.0);
    EXPECT_TRUE(power_p->getInt() == -38);

    *power_p -= (float)-138.0;
    EXPECT_TRUE(power_p->get() == (float)100.0);
    EXPECT_TRUE(power_p->getInt() == 100);

    *power_p -= (int)3;
    EXPECT_TRUE(power_p->get() == (float)97.0);
    EXPECT_TRUE(power_p->getInt() == 97);

    *power_p -= *p2_p;
    EXPECT_TRUE(power_p->get() == (float)37.0);
    EXPECT_TRUE(power_p->getInt() == 37);

    delete power_p;
    delete p2_p;

    Power f1 = 30;
    Power f2 = 20;
    Power f3 = f1 - f2;
    EXPECT_TRUE(f3.getInt() == 10);

    cout << __func__ << " - END" <<  endl;
}

TEST(PowerTestCase, comparison)
{
    cout << __func__ << " - START" <<  endl;

    // test the == functions
    const Power f1 = 10;
    Power f2 = 10;

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

    EXPECT_TRUE(f1.getInt() == 10);

    f2 = 20;
    Power f3 = 10;
    Power f4 = 20;
    Power f5 = 30;
    Power f6 = 20;

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

    EXPECT_TRUE(f3.getInt() == 10);

    // test the != const functions
    Power f7 = 9;
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

TEST(PowerTestCase, accessors)
{
    cout << __func__ << " - START" <<  endl;

    Power* power_p = new Power(21000.0, Power::KdBm);

    EXPECT_TRUE(power_p != 0);

    EXPECT_TRUE(power_p->getInt() == 21);
    EXPECT_TRUE(power_p->getInt(Power::KdBm) == 21000);

    power_p->set(12, Power::dBm);
    EXPECT_TRUE(power_p->getInt() == 12);
    power_p->set(70, Power::TdBm );
    EXPECT_TRUE(power_p->getInt() == 7);
    power_p->set( 800, Power::HdBm);
    EXPECT_TRUE(power_p->getInt() == 8);
    EXPECT_TRUE(power_p->getInt(Power::KdBm) == 8000 );
    EXPECT_TRUE(power_p->getInt(Power::HdBm) == 800 );
    EXPECT_TRUE(power_p->getInt(Power::TdBm) == 80 );
    EXPECT_TRUE(power_p->getInt(Power::dBm)  == 8 );

    power_p->set(85.5, Power::TdBm);
    EXPECT_TRUE(power_p->get() == (float)8.55);
    EXPECT_TRUE(power_p->getInt() == 9);
    EXPECT_TRUE(power_p->getInt(Power::KdBm) == 8550 );

    // test the Watts access
    power_p->setWatts(1.0);
    EXPECT_TRUE(power_p->getWatts() == (float)1.0);
    EXPECT_TRUE(power_p->get() == (float)30.0);
    EXPECT_TRUE(power_p->getInt() == 30);

    power_p->setWatts(10.0);
    EXPECT_TRUE(power_p->getWatts() == (float)10.0);
    EXPECT_TRUE(power_p->get() == (float)40.0);
    EXPECT_TRUE(power_p->getInt() == 40);
    EXPECT_TRUE(power_p->get(Power::W) == (float)10.0);
    EXPECT_TRUE(power_p->get(Power::mW) == (float)10000.0);

    power_p->set(100, Power::W);
    EXPECT_TRUE(power_p->getWatts() == (float)100.0);
    EXPECT_TRUE(power_p->get() == (float)50.0);
    EXPECT_TRUE(power_p->getInt() == 50);
    EXPECT_TRUE(power_p->get(Power::W) == (float)100.0);
    EXPECT_TRUE(power_p->get(Power::mW) == (float)100000.0);

    delete power_p;

    cout << __func__ << " - END" <<  endl;
}

TEST(PowerTestCase, unitToStr)
{
    cout << __func__ << " - START" <<  endl;

    EXPECT_TRUE(strcmp(Power::unit2Str(Power::dBm),"dBm") == 0);
    EXPECT_TRUE(strcmp(Power::unit2Str(Power::TdBm),"TdBm") == 0);
    EXPECT_TRUE(strcmp(Power::unit2Str(Power::HdBm),"HdBm") == 0);
    EXPECT_TRUE(strcmp(Power::unit2Str(Power::KdBm),"KdBm") == 0);
    EXPECT_TRUE(strcmp(Power::unit2Str((Power::Unit)55),"unknown") == 0);

    cout << __func__ << " - END" <<  endl;
}
