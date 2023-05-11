/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonPortTestCase.cpp
 * \brief     Define the unit tests for the CommonPort class
 *
 *
 * \details   Define the unit tests for the CommonPort class
 *
 */



#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>

#include <memory>
#include "IPort.h"
#include "CommonPort.h"
#include "CommonPortTestCase.h"

using namespace Mplane;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( CommonPortTestCase );

using namespace std;

/*
 * Unit tests
 */
void CommonPortTestCase::unittest()
{
    cout << "CommonPort unit test" << endl;

    CommonPort* commonPort = new CommonPort( 0, "ThePort") ;

    CPPUNIT_ASSERT(commonPort != 0);

    CPPUNIT_ASSERT(commonPort->getIndex() == 0);

    CPPUNIT_ASSERT(commonPort->getName() == "ThePort" );

    delete( commonPort );

    IPort *iPort = dynamic_cast<IPort*> (new CommonPort( 2, "VirtualPort"));

    CPPUNIT_ASSERT(iPort != 0);

    CPPUNIT_ASSERT(iPort->getIndex() == 2);

    CPPUNIT_ASSERT(iPort->getName() == "VirtualPort" );

    delete iPort ;


}
