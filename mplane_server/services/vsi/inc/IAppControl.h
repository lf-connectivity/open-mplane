#ifndef _IAPPCONTROL_H_
#define _IAPPCONTROL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IAppControl.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <memory>

namespace Mplane {

/*!
 * The IAppControl interface is provided to allow for the creation of
 * a singleton class that will provide the entry point for all application
 * processes. The following example shows how the interface is used.
 *
@code

    main()
    {

        IAppControl& appControl = IAppControl.getInterface();


        appControl.start();

        appControl.run();
    }

@endcode
 *
 */
class IAppControl {
 public:
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
  virtual void start() = 0;

  /**
   * This method can be called to temporarily suspend the applications
   * service. They are not destroyed and can be resumed at any time.
   */
  virtual void suspend() = 0;

  /**
   * This method can be used to resume the applications suspended services,
   * calling this method when the services are not suspended will have no
   * effect.
   */
  virtual void resume() = 0;

  /**
   * Method used to provide a means to terminate the application
   */
  virtual void shutdown() = 0;

  virtual ~IAppControl(){};

  /**
   * This method is the entry point for a specific application
   * implementation. It is called from the application control start
   * method after all other service threads have been started.
   *
   * The run method should implement to provide normal application control
   * operation.
   *
   * @note As this is the method is where the main  process ends
   * up, the application must always remain in this method until the system
   * is rebooted.
   *
   */
  virtual void run() = 0;
};

/**
 * The IappControlFactory class defines a factory interface used to create an
 * instance of an Mplane::IAppControl implementation. The actual
 * implementation is defined by the application build at final link.
 */
class IAppControlFactory {
 public:
  /**
   * Method defines a static method used to get the single instance of
   * the radio control program.
   * @return a reference to the radio control class
   */
  static std::shared_ptr<IAppControl> getInterface();
};

} /* namespace Mplane */
#endif /* _IAPPCONTROL_H_ */
