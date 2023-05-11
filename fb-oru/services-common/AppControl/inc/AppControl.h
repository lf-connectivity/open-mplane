/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AppControl.h
 * \brief     Base IAppControl
 *
 *
 * \details   Provides generic AppControl which an application can derive from and extend
 *
 */


#ifndef APPCONTROL_H_
#define APPCONTROL_H_

#include "IRadio.h"
#include "IAppControl.h"
#include "Conditional.h"
#include "Loggable.h"

namespace Mplane
{
class IServicesMonitor;
class IServicesCtl;

/**
 *
 */
class AppControl:  public IAppControl, public Loggable
{
public:
	explicit AppControl(const std::string& name) ;
	virtual ~AppControl() ;

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
    virtual void start() override ;

    /**
     * This method can be called to temporarily suspend the applications
     * service. They are not destroyed and can be resumed at any time.
     */
    virtual void suspend() override ;

    /**
     * This method can be used to resume the applications suspended services,
     * calling this method when the services are not suspended will have no effect.
     */
    virtual void resume() override ;

    /**
     * Method used to provide a means to terminate the application
     */
    void shutdown() ;

    /**
     * Display the application state
     */
    virtual void show() ;

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
    virtual void run() override;

    /**
     * Returns this instance's name
     */
    virtual std::string getName() const ;

protected:
    std::shared_ptr<IRadio> mRadio;

    std::shared_ptr<IServicesMonitor> mServicesMonitor;

    std::shared_ptr<IServicesCtl> mRadioServices;

    std::shared_ptr<IServicesCtl> mApplicationServices;


private:
    std::string mAppName ;

    // Variable indicated that the application should shutdown, normally never changes
    bool mShutdown;

    // A conditional used in the threads run loop, to provide loop timing and
    // event notification.
    Conditional mConditional;
} ;

}

#endif /* APPCONTROL_H_ */
