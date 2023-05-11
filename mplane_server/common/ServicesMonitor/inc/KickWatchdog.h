#ifndef _KICKWATCHDOG_H_
#define _KICKWATCHDOG_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      KickWatchdog.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "ServicesMonitor.h"
#include "Task.h"

namespace Mplane {

class KickWatchdog : public Task {
 public:
  /**
   * Constructor
   */
  KickWatchdog();

  /**
   * Destructor, not expected to be deleted
   */
  virtual ~KickWatchdog();

  /**
   * Method used to stop the kick watchdog task and close the watchdog file
   * disable it.
   */
  void shutdown();

 protected:
  /**
   * This is the method that is run by the start() method. As it is pure virtual
   * it must be implemented by the inheriting task.
   * @return the exit status of task process
   */
  virtual int run();

  /**
   * The kick watchdog loop will continue until
   */
  bool mShutdown;

  /**
   * Define the priority of the watchdog kick thread. This thread runs below
   * all other tasks in the application, if it doesn't get to run, the
   * watchdog will timeout and the system will reboot.
   */
  static const int LOW_KICK_WATCHDOG_PRIORITY = 3;

  /**
   * Used to set the watchdog timeout value (in seconds)
   */
  static const int WATCHDOG_TIMEOUT = 60;
};

} // namespace Mplane

#endif /* _KICKWATCHDOG_H_ */
