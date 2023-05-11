/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AppServices_unittests.cpp
 * \brief     main method to start the application services
 *
 *
 */

#include "gtest/gtest.h"


#include <string.h>
#include <iostream>

#include "IRadio.h"
#include "IAppOptions.h"

#include "Task.h"
#include "AppServices.h"


using namespace Mplane;


using namespace std;


TEST(AppServicesTests, Basic)
{
    std::shared_ptr<AppServices> services( std::make_shared<AppServices>("test") );

    services->start();
    Task::msSleep( 1200 );

    services->show() ;

    services->suspend() ;
    Task::msSleep( 1200 );

    services->resume() ;
    Task::msSleep( 1200 );

    services->shutdown() ;
    Task::msSleep( 1200 );

}
