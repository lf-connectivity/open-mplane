/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TokeniserTestCase.cpp
 * \brief     Implementation of the CppUnit test harness for string Tokeniser
 *
 *
 * \details   This file contains the implementation of the CppUnit test cases
 *            for the common string tokeniser class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <sstream>

#include "Tokeniser.h"


using namespace std;

/*
 * Unit tests
 */
TEST(TokeniserTestCase, unittest)
{
    cout << endl << "*** TokeniserTestCase Tests ***" <<  endl;
    cout << __func__ << " - START" <<  endl;

    std::string test = "One Two\tThree\rFour\nThe::End";

    Tokeniser t(test);

    std::string token;

    EXPECT_TRUE( t.nextToken() == true );

    token = t.getToken();

    EXPECT_TRUE( token == "One");

    char delimiter = t.getDelimiter();

    EXPECT_TRUE( delimiter == 0);


    EXPECT_TRUE( t.nextToken() == true );

    token = t.getToken();

    EXPECT_TRUE( token == "Two");

    delimiter = t.getDelimiter();

    EXPECT_TRUE( delimiter == ' ');

    EXPECT_TRUE( t.nextToken() == true );

    token = t.getToken();

    EXPECT_TRUE( token == "Three");

    delimiter = t.getDelimiter();

    EXPECT_TRUE( delimiter == '\t');

    EXPECT_TRUE( t.nextToken() == true );

    token = t.getToken();

    EXPECT_TRUE( token == "Four");

    delimiter = t.getDelimiter();

    EXPECT_TRUE( delimiter == '\r');


    EXPECT_TRUE( t.nextToken() == true );

    token = t.getToken();

    EXPECT_TRUE( token == "The::End");

    delimiter = t.getDelimiter();

    EXPECT_TRUE( delimiter == '\n');

    EXPECT_TRUE( t.nextToken() == false );


    Tokeniser t2( token );

    t.reset();

    EXPECT_TRUE( t.nextToken() == true );

    token = t.getToken();

    EXPECT_TRUE( token == "One");

    delimiter = t.getDelimiter();


    EXPECT_TRUE( t2.nextToken(":") == true );

    token = t2.getToken();

    EXPECT_TRUE( token == "The");

    delimiter = t2.getDelimiter();

    EXPECT_TRUE( delimiter == 0);

    EXPECT_TRUE( t2.nextToken(":") == true );

    token = t2.getToken();

    EXPECT_TRUE( token == "End");

    delimiter = t2.getDelimiter();

    EXPECT_TRUE( delimiter == ':');

    EXPECT_TRUE( t2.nextToken(":") == false );


    Tokeniser t3(test, ":");

    EXPECT_TRUE( t3.nextToken() == true );

    token = t3.getToken();

    EXPECT_TRUE( token == "One Two\tThree\rFour\nThe");

    delimiter = t3.getDelimiter();

    EXPECT_TRUE( delimiter == 0);

    EXPECT_TRUE( t3.nextToken() == true );

    token = t3.getToken();

    EXPECT_TRUE( token == "End");

    delimiter = t3.getDelimiter();

    EXPECT_TRUE( delimiter == ':');

    EXPECT_TRUE( t3.nextToken() == false );


    cout << __func__ << " - END" <<  endl;
}

