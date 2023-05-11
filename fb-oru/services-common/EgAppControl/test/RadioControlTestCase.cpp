/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonServicesTestCase.cpp
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

#include "CommonServices.h"

#include "IServicesCtl.h"

#include "TxService.h"

#include "IAppControl.h"

#include "EgAppControl.h"

#include "CommonRadio.h"

#include "RadioControlTestCase.h"

using namespace Mplane;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( RadioControlTestCase );

using namespace std;




/*
 * Unit test
 */
void RadioControlTestCase::unittest()
{
    cout << "RadioControl unit test" << endl;

    std::shared_ptr<IAppControl> rc( IAppControlFactory::getInterface() );

    std::shared_ptr<TestRadioControl> rcp = std::dynamic_pointer_cast<TestRadioControl>(rc);

    rc->start();

    usleep( 1200 * 1000 );

    CPPUNIT_ASSERT( rcp->runWasCalled == true );

}
