/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BootTimer.h
 * \brief
 *
 *
 * \details
 *
 */

#ifndef BOOTTIMER_H_
#define BOOTTIMER_H_

#include <map>
#include <vector>

#include "IBootTimer.h"

namespace Mplane {

/*!
 * \class BootTimer
 */
class BootTimer : public virtual IBootTimer {
 public:
  BootTimer();
  virtual ~BootTimer();

  /**
   * This marks the time at which the tif interface has started.
   */
  virtual void tifStarted() override;

  /**
   * This marks the time at which the application has completely started. Stops
   * all running timers.
   */
  virtual void appStarted() override;

  /**
   * Marks the time at which the named item has started / completed
   * @param name
   */
  virtual void nameComplete(const std::string& name) override;

  /**
   * Show all information
   * @param os
   */
  virtual void show(std::ostream& os) override;

  /**
   * Get the time at which the application started in seconds
   * @return start time
   */
  virtual float getStartTime() const override;

  /**
   * Get the time at which the tif interface is ready
   * @return the start time in seconds
   */
  virtual float getTifTime() const override;

  /**
   * Get the elapsed time from the start of the application at which the tif
   * interface is ready
   * @return the elapsed time in seconds
   */
  virtual float getTifElapsed() const override;

  /**
   * Get the time at which the application is running
   * @return the start time in seconds
   */
  virtual float getAppTime() const override;

  /**
   * Get the elapsed time from the start of the application at which the
   * application is ready
   * @return the elapsed time in seconds
   */
  virtual float getAppElapsed() const override;

  /**
   * Get the time from boot to now
   * @return the elapsed time in seconds
   */
  virtual float getRunTime() const override;

  /**
   * Get the time at which the named item is ready
   * @return the start time in seconds
   */
  virtual float getNameTime(const std::string& name) const override;

  /**
   * Get the elapsed time from the start of the application at which the named
   * item is ready
   * @return the elapsed time in seconds
   */
  virtual float getNameElapsed(const std::string& name) const override;

  /**
   * Add a callback for app complete
   */
  virtual bool registerAppCompleteCallback(
      IBootTimer::AppCompleteCallback cb) override;

  /**
   * Add a callback for tif complete
   */
  virtual bool registerTifCompleteCallback(
      IBootTimer::TifCompleteCallback cb) override;

  /**
   * Add a callback for app complete
   */
  virtual bool registerNamedCompleteCallback(
      const std::string& name, IBootTimer::NamedCompleteCallback cb) override;

 private:
  bool mComplete;
  float mStartTime;
  std::map<std::string, float> mTimers;
  std::vector<IBootTimer::AppCompleteCallback> mAppCallbacks;
  std::vector<IBootTimer::TifCompleteCallback> mTifCallbacks;
  std::map<std::string, std::vector<IBootTimer::NamedCompleteCallback>>
      mNamedCallbacks;
};

} // namespace Mplane

#endif /* BOOTTIMER_H_ */
