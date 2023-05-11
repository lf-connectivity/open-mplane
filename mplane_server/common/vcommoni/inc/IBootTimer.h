/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IBootTimer.h
 * \brief     Interface to boot timing object
 *
 *
 * \details
 *
 */

#ifndef IBOOTTIMER_H_
#define IBOOTTIMER_H_

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>

namespace Mplane {

/*!
 * \class IBootTimer
 */
class IBootTimer {
 public:
  /**
   * Singleton
   */
  static std::shared_ptr<IBootTimer> getInstance();

  IBootTimer() {}
  virtual ~IBootTimer() {}

  /**
   * This marks the time at which the tif interface has started.
   */
  virtual void tifStarted() = 0;

  /**
   * This marks the time at which the application has completely started. Stops
   * all running timers.
   */
  virtual void appStarted() = 0;

  /**
   * Marks the time at which the named item has started / completed
   * @param name
   */
  virtual void nameComplete(const std::string& name) = 0;

  /**
   * Show all information
   * @param os
   */
  virtual void show(std::ostream& os) = 0;

  /**
   * Get the time (from boot) at which the application started in seconds
   * @return start time
   */
  virtual float getStartTime() const = 0;

  /**
   * Get the time (from boot) at which the tif interface is ready
   * @return the start time in seconds
   */
  virtual float getTifTime() const = 0;

  /**
   * Get the elapsed time (from the start of the application) at which the tif
   * interface is ready
   * @return the elapsed time in seconds
   */
  virtual float getTifElapsed() const = 0;

  /**
   * Get the time (from boot) at which the application is running
   * @return the start time in seconds
   */
  virtual float getAppTime() const = 0;

  /**
   * Get the elapsed time (from the start of the application) at which the
   * application is ready
   * @return the elapsed time in seconds
   */
  virtual float getAppElapsed() const = 0;

  /**
   * Get the time from boot to now
   * @return the elapsed time in seconds
   */
  virtual float getRunTime() const = 0;

  /**
   * Get the time at which the named item is ready
   * @return the start time in seconds
   */
  virtual float getNameTime(const std::string& name) const = 0;

  /**
   * Get the elapsed time from the start of the application at which the named
   * item is ready
   * @return the elapsed time in seconds
   */
  virtual float getNameElapsed(const std::string& name) const = 0;

  /**
   * Callback for when app startup is complete.
   */
  using AppCompleteCallback = std::function<void()>;

  /**
   * Callback for when tif startup is complete.
   */
  using TifCompleteCallback = std::function<void()>;

  /**
   * Callback for when generic named activity is complete.
   */
  using NamedCompleteCallback = std::function<void(const std::string& name)>;

  /**
   * Add a callback for app complete
   */
  virtual bool registerAppCompleteCallback(AppCompleteCallback cb) = 0;

  /**
   * Add a callback for tif complete
   */
  virtual bool registerTifCompleteCallback(TifCompleteCallback cb) = 0;

  /**
   * Add a callback for app complete
   */
  virtual bool registerNamedCompleteCallback(
      const std::string& name, NamedCompleteCallback cb) = 0;
};

} // namespace Mplane

#endif /* IBOOTTIMER_H_ */
