#ifndef _ISERVICESMONITOR_H_
#define _ISERVICESMONITOR_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IservicesMonitor.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

namespace Mplane {

/*!
 * The IServiceMonitor interface is the radio applications interface to the
 * monitor task that is responsible for ensuring the application starts up
 * within time and that all services remain active and healthy.
 */
class IServicesMonitor {
 public:
  enum ApplicationState {
    INITIALISING = 0,
    STABLE = 1,
    FAILED = 2,
  };

  /**
   * Method used to start service monitoring task
   */
  virtual void startMonitoring() = 0;

  /**
   * Indicates that the application failed to start, calling this method
   * should for more than 2 successive reboots will result in the current
   * application image being retired and the previous image restored
   * as the primary.
   */
  virtual void applicationFailed() = 0;

  /**
   * Calling this method indicates that the application has reached a stable
   * point where all services have been started and the radio is ready to be
   * connected and configured.
   */
  virtual void applicationStable() = 0;

  /**
   * Return the current application state
   */
  virtual ApplicationState getApplicationState() const = 0;

  virtual ~IServicesMonitor(){};
};

} /* namespace Mplane */
#endif /* _ISERVICESMONITOR_H_ */
