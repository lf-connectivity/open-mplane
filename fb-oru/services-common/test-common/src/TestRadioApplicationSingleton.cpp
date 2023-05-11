/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestRadioApplication.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "IAppControl.h"
#include "TestRadioApplication.h"

using namespace Mplane;


class TestRadioControl: public IAppControl
{
public:
    TestRadioControl(): runWasCalled( false )
    {
        services = IServicesFactory::create();
    };
    virtual ~TestRadioControl()
    {

    };


    /**
     * This method is the entry point to starting the entire application.
     * It is called from the application processes main() function.
     * It will start the ServicesMonitor task, initialise the system
     * hardware and then use the IServicesCtl interface to create common
     * and application specific services and start them.
     *
     * After a successful start up process, it will call the radio process
     * run method.
     *
     */
    virtual void start()
    {
        services->start();
    }

    /**
     * This method can be called to temporarily suspend the applications
     * service. They are not destroyed and can be resumed at any time.
     */
    virtual void suspend()
    {
        services->suspend();
    }

    /**
     * This method can be used to resume the applications suspended services,
     * calling this method when the services are not suspended will have no effect.
     */
    virtual void resume()
    {
        services->resume();
    }


    bool runWasCalled;
protected:

    std::shared_ptr<IServicesCtl> services;

    virtual void run()
    {
        runWasCalled = true;
    }

};


std::shared_ptr<IAppControl> IAppControlFactory::getInterface()
{
    static std::shared_ptr<IAppControl> radioControl(new TestRadioControl());
    return radioControl;
}


std::shared_ptr<IServicesCtl> IServicesFactory::create()
{
    static std::shared_ptr<IServicesCtl> application(new TestApplicationServices());
    return application;
}
