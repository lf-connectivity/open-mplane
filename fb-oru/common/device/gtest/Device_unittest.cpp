/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDelayAttrInterface_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "Device.h"

using namespace std;

namespace Mplane
{

class TestDevice: public Device
{
public:
    TestDevice():
        Device(Device::CAM,1,"TestDevice"),
        mDoInitCalled( false )
    {
    }
    ~TestDevice()
    {
    }

    /*! \brief  Display the device data, ie registers
     *
     *  Display the state of the device registers on the console or log file
     */
    virtual void show(void)
    {
        cout << "Device name: " << getName() << " index: " << getIndex() << endl;
    }

    virtual ReturnType::State doInit()
    {
        mDoInitCalled = true;
        return ReturnType::RT_OK;
    }


    bool mDoInitCalled;

};

}

/****** End of Area for unit test specifics  ******/

using namespace Mplane;


/*
 * Unit tests
 */
TEST( CommonDevice,unittest)
{
    cout << endl << "*** DeviceTestCase Tests ***" <<  endl;

    TestDevice* testDevice = new TestDevice();

    ASSERT_EQ( testDevice->getType(), Device::CAM);
    ASSERT_EQ( testDevice->getIndex(), 1 );
    ASSERT_EQ( strcmp( testDevice->getName().c_str(), "TestDevice"), 0  );

    ASSERT_FALSE( testDevice->mDoInitCalled  );
    ASSERT_EQ( testDevice->initialise(), ReturnType::RT_OK );
    ASSERT_TRUE( testDevice->mDoInitCalled );

    testDevice->show();

    delete( testDevice );

}

//===================================================================================================================
