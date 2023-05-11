/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TimeoutTimer.h
 * \brief     Class that maintains a timeout timer
 *
 *
 * \details   A timer is initialised to a specified amount of time and, when
 * started, counts down from this time to 0. Once the timer reaches 0 it has
 * timed out.
 *
 *             This class can be created with a timer value and will
 * immediately start timing down. Or it can be created with no time and the
 * timer value set. The class can be reused to re-time the existing timer value
 * or set to time new values.
 *
 */

#ifndef INC_TIMEOUTTIMER_H_
#define INC_TIMEOUTTIMER_H_

#include <chrono>
#include <functional>

namespace Mplane {

/*!
 * \class  TimeoutTimer
 * \brief
 * \details
 *
 */
class TimeoutTimer {
 public:
  TimeoutTimer();
  TimeoutTimer(const std::chrono::milliseconds& timerTime);
  virtual ~TimeoutTimer();

  /**
   * Set a function to be called when the timer times out
   */
  using TimerCallback = std::function<void()>;
  virtual void setTimedCallback(TimerCallback func);

  /**
   * Start the timer using any existing timer setting
   */
  virtual void startTimer();

  /**
   * Set the timer time and start the timer
   */
  virtual void startTimer(const std::chrono::milliseconds& timerTime);

  /**
   * Stop the timer. Will not time out and will not call callback
   */
  virtual void stopTimer();

  /**
   * Has this timer timed out?
   */
  virtual bool isTimedOut();

 private:
  std::chrono::milliseconds mDuration;
  TimerCallback mCallback;
  bool mTimedOut;
  std::chrono::steady_clock::time_point mEndTime;
  bool mRunning;
};

} // namespace Mplane

#endif /* INC_TIMEOUTTIMER_H_ */
