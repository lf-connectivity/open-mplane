#ifndef _COMMON_SERVICE_H_
#define _COMMON_SERVICE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Service.h
 * \brief     Defines the base class functionality and interface that must be
 * supported by all services.
 *
 *
 * \details   Defines the base class functionality and interface that must be
 * supported by all services.
 *
 */

#include "Conditional.h"
#include "Loggable.h"
#include "Mutex.h"
#include "Task.h"
#include <vector>

namespace Mplane {

using namespace Mplane;

/**
 * This is the base class that must be implemented by all radio services. It
 * provides a common mechanism through which the service can be controlled and
 * execute.
 *
 * It inherits from the base class Task, that provides a POSIX thread context
 * in which the service will execute.
 *
 * The Service provides a basic state machine with methods used to control
 * the service state. The initial service state is ServiceCreated, this
 * indicates that the Service object has been created and is waiting to be
 * started. The service design must be such that other threads can access the
 * service data once it is created. This must include the ability for service
 * observers to register for event notification.
 *
 * @note All data access must be thread safe and protected through one of the
 * available protection classes, Mutex, RecursiveMutex or Conditional.
 *
 * The Radio Control process, will start the service, this will result in
 * the registerObservers() method being called, the base implementation does
 * nothing and must be overloaded by the extending class. After this the
 * Task base class execute() method will be called, that in turns calls
 * the service run() method. The run() method sets up a repeating
 * service timer, with the TimerService. This will result in the service being
 * periodically awakened at which time the service() method may be called. On
 * return from the service() method, the run() method will restart the repeating
 * timer and wait to be notified.
 *
 * Some services are expected to be able to reset to a known initial state,
 * these services must overload the reset() method and return their data and
 * state to its start condition.
 * @note This MUST NOT include the modification of any registered data
 * observers.
 *
 * The suspend method allows the radio control process to temporarily stop
 * the service() method being called. No further processing will be performed
 * until the resume() method is called.
 *
 * The priority of the service can be set to any value between the
 * SERVICE_MINIMUM_PRIORITY and the SERVICE_MAXIMUM_PRIORITY, a number of
 * predefined priority constants have been provided.
 *
 */

class Service : public Task {
 public:
  friend class ServiceTestCase;

  typedef enum State {
    ServiceCreated,
    ServiceStarted,
    ServiceReset,
    ServiceSuspended,
    ServiceResumed,
    ServiceRunning,
    ServiceFault,
    ServiceShutdown
  } State;

  typedef enum CtlState {
    Noop,
    Start,
    Reset,
    Suspend,
    Resume,
    Shutdown
  } CtlState;

  typedef int ServicePriority_t;

  static const ServicePriority_t SERVICE_MINIMUM_PRIORITY = 20;
  static const ServicePriority_t SERVICE_MIGHT_GET_DONE_PRIORITY = 25;
  static const ServicePriority_t SERVICE_LOW_PRIORITY = 30;
  static const ServicePriority_t SERVICE_MEDIUM_PRIORITY = 50;
  static const ServicePriority_t SERVICE_MEDIUM__HIGH_PRIORITY = 60;
  static const ServicePriority_t SERVICE_HIGH_PRIORITY = 70;
  static const ServicePriority_t SERVICE_MUST_GET_DONE_PRIORITY = 80;
  static const ServicePriority_t SERVICE_MAXIMUM_PRIORITY = 80;

  /**
   * Method called by the controlling radio process to start the service
   *
   * @note Calling the start method in any other state than ServiceCreated
   * has no effect.
   *
   * @return the control state used or Noop if control request ignored
   */
  CtlState start();

  /**
   * Method called by the controlling radio process to reset the service
   * data and state to its default. This method calls the protected
   * doReset() method.
   *
   * @note The default doReset method is implemented as an empty method and
   * must be overridden by the inheriting service implementation.
   *
   * @note Calling the reset method in any other state than ServiceRunning
   * has no effect.
   *
   * @warning On entry to this functional the threads mutex is locked
   * and will unlock on exit, therefore overridden implementations of
   * the doReset worker method <b>?do not need to lock the mutex.</B>
   *
   * @return the control state used or Noop if control request ignored
   */
  CtlState reset();

  /**
   * Method called by the controlling radio process to temporarily suspend
   * the service and prevent the service() method from being called. The service
   * state will be set to ServiceSuspended.
   *
   * @note calling suspend while in any other state than ServiceRunning
   * has no effect.
   *
   * @return the control state used or Noop if control request ignored
   */
  CtlState suspend();

  /**
   * Method called by the controlling radio process to resume a currently
   * suspended service.
   *
   * @note Calling the resume method in any other state than ServiceSuspended
   * has no effect.
   *
   * @return the control state used or Noop if control request ignored
   */
  CtlState resume();

  /**
   * Method called by the controlling radio process to shutdown the service
   * after which the thread associated with service will be destroyed
   *
   * @note Calling the shutdown method in any other state than ServiceRunning
   * has no effect.
   *
   * @return the control state used or Noop if control request ignored
   */
  virtual CtlState shutdown();

  /**
   * Method used to return the current service state.
   * @return One of the service state enumerated value
   */
  State getState();

  /**
   * Method defined by the Loggable interface must be implemented by all
   * object to force the display of the objects current status.
   */
  virtual void show();

  /**
   * Helper method used to return the name associated with a service state
   * @param service state
   * @return pointer to a state name
   */
  static const char* getStateName(State);

  /**
   * Helper method used to return the name associated with a service control
   * type
   * @param service control state
   * @return pointer to a state name
   */
  static const char* getControlName(CtlState);

 protected:
  /**
   * @note: Standard copy constructors defined but not implemented as a Service
   * cannot be copied.
   */
  explicit Service(const Service&);
  Service& operator=(const Service&);

  /**
   * The Service constructor is protected as it must only be called by
   * the actual service task that extends it.
   *
   * The default constructor will create a medium prority task , with a small
   * stack that calls its service() method once a second.
   *
   * @param priority a prority between SERVICE_MINIMUM_PRIORITY and
   * SERVICE_MAXIMUM_PRIORITY
   * @param stacksize One of the available Task defined stack sizes of
   * SMALL_STACK, MEDIUM_STACK or LARGE_STACK
   * @param msecTimerPeriod a millisecond update time from 10 to 86,400,000
   */
  Service(
      ServicePriority_t priority = SERVICE_MEDIUM_PRIORITY,
      StackSize stacksize = SMALL_STACK,
      unsigned int msecTimerPeriod = 1000,
      const char* name = "Unnamed Service",
      const char* suName = "SV");

  virtual ~Service();

  /**
   * Default run method that maintains the service state and calls the service()
   * method when the update time expires.
   * @return
   */
  int run();

  /**
   * Method that MUST be implemented by the inheriting service. The work done
   * by the service, is implemented by this method.
   *
   * @note The service method will continue to be called for as long as is
   * returns zero, non-zero indicates and execution error in the service
   * that will result in it being shutdown and the error made available to the
   * Task exit value.
   *
   * @return 0 when running normally, any other value is a error condition
   */
  virtual int service() = 0;

  /**
   * Method called by the service start() method, to register this service with
   * any particular Observer/Notify interface implementation.
   *
   * @note This method must be implemented by the inheriting service in order
   * for it to register as an observer of other objects.
   *
   * @return true if registration successful.
   */
  virtual bool registerObservers();

  /**
   * Method called as a result of the radio control process calling reset
   * in the service. By default the base class implementation does nothing.
   */
  virtual void doReset();

  /**
   * This method can be used in the implementation of the public
   * Mplane::Observer methods that provide data to a service in order for the
   * service thread to be Signalled and as a result the service can act upon the
   * data change immediately or at least when it is scheduled to run.
   */
  void eventNotify();

  /**
   * This conditional is used in the main run loop by calling the
   * conditionals wait with timeout method the service() method will either
   * be called as a result of the timer expiring or being notified by
   * a call to the conditional signal method.
   */
  Conditional mNotify;

  /**
   * The service update rate
   */
  unsigned int mMsecTimerPeriod;

  /**
   * The current service state
   */
  State mState;

  /**
   * Used to control the service state machine
   */
  CtlState mControl;
};

} // namespace Mplane

#endif /* _COMMON_SERVICE_H_ */
