/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonModulesTestCase.cpp
 * \brief     Define the unit tests for the CommonModules class
 *
 *
 * \details   Define the unit tests for the CommonModules class
 *
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "Module.h"
#include "CommonModules.h"
#include "CommonModulesTestCase.h"

using namespace Mplane;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( CommonModulesTestCase );

using namespace std;


/****** End of Area for unit test specifics  ******/

/*
 * Unit tests
 */
void CommonModulesTestCase::unittest()
{
    cout << endl << "*** CommonModuleTestCase Tests ***" <<  endl;

    std::shared_ptr<CommonModules> modules( new CommonModules() );

    try
    {
        modules->initialise();
    } catch( std::invalid_argument &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "initialise() must be implemented by a radio specific base class." ) == 0 );
    }

    try
    {
        modules->shutdown();
    } catch( std::invalid_argument &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "shutdown() must be implemented by a radio specific base class." ) == 0 );
    }

    try
    {
        modules->getFilter( 0 );
    } catch( std::invalid_argument &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "getFilter() must be implemented by a radio specific base class, if supported." ) == 0 );
    }

    try
    {
        modules->getFem( 0 );
    } catch( std::invalid_argument &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "getFem() must be implemented by a radio specific base class, if supported." ) == 0 );
    }

}
