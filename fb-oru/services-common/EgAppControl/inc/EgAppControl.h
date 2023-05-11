#ifndef _MPLANE_SVC_APPCONTROL_H_
#define _MPLANE_SVC_APPCONTROL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioControl.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "IRadio.h"
#include "IAppControl.h"

namespace Mplane
{

class IServicesMonitor;
class IServicesCtl;

/**
 * This is an example (Eg) application control interface implementation. It has been
 * created to instantiate the common services implementations and test the base functionality
 * of an IAppControl interface implementation independent of any custer product implementation.
 */
class EgAppControl:  public IAppControl
{
public:

    /**
     * This method is the entry point to the entire radio application.
     * It is called from the radio control processes main() function.
     * It will start the ServicesMonitor task, initialise the radio
     * hardware and then use the IServicesCtl interface for the common
     * and application services to start all the radio services.
     *
     * After a successful start up process, it will call the radio process
     * run method.
     *
     */
    virtual void start();

    /**
      * This method can be called to temporarily suspend the applications
      * service. They are not destroyed and can be resumed at any time.
      */
     virtual void suspend();

     /**
      * This method can be used to resume the applications suspended services,
      * calling this method when the services are not suspended will have no effect.
      */
     virtual void resume();

protected:

    /**
     * This method is the entry point for a specific radio radio application
     * implementation. It is called from the radio control base class start
     * method after all processes have been started.
     *
     * The run method should implement the normal radio control operation.
     *
     * @note As this is the method is where the main radio control process ends
     * up, the application must always remain in this method until the radio
     * is rebooted.
     *
     */
    virtual void run() = 0;


    friend class IAppControlFactory;
    /**
     * The RadioControl constructor is protected so it can only be created
     * as a singleton through the IRadioControlFactory static getInstance
     * method.
     */
    EgAppControl();

    /**
     * Protected virtual destructor should never get called.
     */
    virtual ~EgAppControl();

    std::shared_ptr<IRadio> radio;

    std::shared_ptr<IServicesMonitor> servicesMonitor;

    std::shared_ptr<IServicesCtl> services;



private:
};

}

#endif /* _MPLANE_SVC_APPCONTROL_H_ */
