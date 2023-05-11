/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonDevicesTestCase.cpp
 * \brief     Define the unit tests for the CommonDevices class
 *
 *
 * \details   Define the unit tests for the CommonDevices class
 *
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "Device.h"
#include "CommonDevices.h"
#include "CommonDevicesTestCase.h"

using namespace Mplane;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( CommonDevicesTestCase );

using namespace std;


/****** End of Area for unit test specifics  ******/

/*
 * Unit tests
 */
void CommonDevicesTestCase::unittest()
{
    cout << endl << "*** CommonDeviceTestCase Tests ***" <<  endl;

    std::shared_ptr<CommonDevices> devices( new CommonDevices() );

    try
    {
        devices->initialise();
    } catch( std::invalid_argument &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "initialise() must be implemented by a radio specific base class." ) == 0 );
    }

    try
    {
        devices->shutdown();
    } catch( std::invalid_argument &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "shutdown() must be implemented by a radio specific base class." ) == 0 );
    }

    try
    {
        devices->getRxAdc( 0 );
    } catch( std::invalid_argument &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "getRxAdc() must be implemented by a radio specific base class, if supported." ) == 0 );
    }

    try
    {
        devices->getDpdAdc(0);
    } catch( std::invalid_argument &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "getDpdAdc() must be implemented by a radio specific base class, if supported." ) == 0 );
    }

    try
    {
        devices->getTxDac(0);
    } catch( std::invalid_argument &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "getTxDac() must be implemented by a radio specific base class, if supported." ) == 0 );
    }

    try
    {
        devices->getLed(0);
    } catch( std::invalid_argument &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "getLed() must be implemented by a radio specific base class, if supported." ) == 0 );
    }

    try
    {
        devices->getRxIFAttenuator(0);
    } catch( std::invalid_argument &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "getRxIFAttenuator() must be implemented by a radio specific base class, if supported." ) == 0 );
    }

    try
    {
        devices->getRxRFAttenuator(0);
    } catch( std::invalid_argument &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "getRxRFAttenuator() must be implemented by a radio specific base class, if supported." ) == 0 );
    }

    try
    {
        devices->getTxIFAttenuator(0);
    } catch( std::invalid_argument &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "getTxIFAttenuator() must be implemented by a radio specific base class, if supported." ) == 0 );
    }

    try
    {
        devices->getTxRFAttenuator(0);
    } catch( std::invalid_argument &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "getTxRFAttenuator() must be implemented by a radio specific base class, if supported." ) == 0 );
    }

    try
    {
        devices->getTxSynth(0);
    } catch( std::invalid_argument &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "getTxSynth() must be implemented by a radio specific base class, if supported." ) == 0 );
    }

    try
    {
        devices->getRxSynth(0);
    } catch( std::invalid_argument &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "getRxSynth() must be implemented by a radio specific base class, if supported." ) == 0 );
    }

    try
    {
        devices->getDpdSynth(0);
    } catch( std::invalid_argument &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "getDpdSynth() must be implemented by a radio specific base class, if supported." ) == 0 );
    }

    try
    {
        devices->getSystemSynth(0);
    } catch( std::invalid_argument &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "getSystemSynth() must be implemented by a radio specific base class, if supported." ) == 0 );
    }

    try
    {
        devices->getSystemFpga(0);
    } catch( std::invalid_argument &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "getSystemFpga() must be implemented by a radio specific base class, if supported." ) == 0 );
    }

    try
    {
        devices->getCam(0);
    } catch( std::invalid_argument &e )
    {
        CPPUNIT_ASSERT( strcmp( e.what(), "getCam() must be implemented by a radio specific base class, if supported." ) == 0 );
    }

}
