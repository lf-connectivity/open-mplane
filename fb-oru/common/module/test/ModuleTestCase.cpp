/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ModuleTestCase.cpp
 * \brief     Define the unit tests for the Module class
 *
 *
 * \details   Define the unit tests for the Module class
 *
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>

#include "Module.h"
#include "ModuleTestCase.h"

using namespace Mplane;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( ModuleTestCase );

using namespace std;


/****** End of Area for unit test specifics  ******/

/*
 * Unit tests
 */
void ModuleTestCase::unittest()
{
    cout << endl << "*** ModuleTestCase Tests ***" <<  endl;

    TestFilterModule* testModule = new TestFilterModule();

    CPPUNIT_ASSERT( testModule->getType() == Module::FILTER);
    CPPUNIT_ASSERT( testModule->getNumber() == 2 );
    CPPUNIT_ASSERT( testModule->getIndex() == 1 );
    CPPUNIT_ASSERT( strcmp( testModule->getName(), "TestFilterModule") == 0  );

    CPPUNIT_ASSERT( testModule->mDoInitCalled == false );
    CPPUNIT_ASSERT( testModule->initialise() == ReturnType::RT_OK );
    CPPUNIT_ASSERT( testModule->mDoInitCalled == true );

    testModule->show();

    delete( testModule );

}

Mplane::TestFilterModule::TestFilterModule():
        Module(Module::FILTER,1,2,"TestFilterModule"),
        mDoInitCalled( false )
{
}

Mplane::TestFilterModule::~TestFilterModule()
{
}

void Mplane::TestFilterModule::show(void)
{
    cout << "Module name: " << getName() << " index: " << getIndex() << " number: " << getNumber() << endl;
}

ReturnType::State Mplane::TestFilterModule::doInit()
{
    mDoInitCalled = true;
    return ReturnType::RT_OK;
}
