/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierFailTestCase.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>


#include "CommonCarrierFail.h"
#include "CommonCarrierFailTestCase.h"


using namespace std;
using namespace Mplane;

//------------------------------------------------------------------------------------------------------------------------
/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( CommonCarrierFailTestCase );


//------------------------------------------------------------------------------------------------------------------------
/*
 * Unit tests
 */
void CommonCarrierFailTestCase::unittest()
{
    cout << "CommonCarrierFailTestCase unit test" << endl;

    CommonCarrierFail fail ;

    CPPUNIT_ASSERT_EQUAL(std::string(""), fail.failReason()) ;

    fail.setFailReason("a test message") ;
    CPPUNIT_ASSERT_EQUAL(std::string("a test message"), fail.failReason()) ;
    CPPUNIT_ASSERT_EQUAL(std::string(""), fail.failReason()) ;

    fail.setFailReason("a test message") ;
    fail.clearFailReason() ;
    CPPUNIT_ASSERT_EQUAL(std::string(""), fail.failReason()) ;
}
