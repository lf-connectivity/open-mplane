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


#include "gtest/gtest.h"


#include <string.h>
#include <iostream>


#include "IServicesCtl.h"

#include "IAppControl.h"

#include "RrhAppControlTestCase.h"
#include "OranRrhAppControl.h"

using namespace Mplane;


using namespace std;


TEST(RrhAppControlTestCases, unittest)
{

    std::shared_ptr<IAppControl> rc( IAppControlFactory::getInterface() );

    std::shared_ptr<RrhAppControlTest> rcp = std::dynamic_pointer_cast<RrhAppControlTest>(rc);

    rc->start();

    rc->run();

    usleep( 1200 * 1000 );

    ASSERT_TRUE( rcp->runWasCalled == true );
}
