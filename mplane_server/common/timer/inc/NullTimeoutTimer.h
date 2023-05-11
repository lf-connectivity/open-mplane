/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NullTimeoutTimer.h
 * \brief     A NO-OP timer
 *
 *
 * \details   Looks like a timer but never times out
 *
 */

#ifndef TIMER_INC_NULLTIMEOUTTIMER_H_
#define TIMER_INC_NULLTIMEOUTTIMER_H_

#include "TimeoutTimer.h"

namespace Mplane {

/*!
 * \class  NullTimeoutTimer
 * \brief
 * \details
 *
 */
class NullTimeoutTimer : public TimeoutTimer {
 public:
  NullTimeoutTimer();
  virtual ~NullTimeoutTimer();

  /**
   * Start the timer using any existing timer setting
   */
  virtual void startTimer() override;

  /**
   * Set the timer time and start the timer
   */
  virtual void startTimer(const std::chrono::milliseconds& timerTime) override;

  /**
   * Stop the timer. Will not time out and will not call callback
   */
  virtual void stopTimer() override;

  /**
   * Has this timer timed out?
   */
  virtual bool isTimedOut() override;
};

} // namespace Mplane

#endif /* TIMER_INC_NULLTIMEOUTTIMER_H_ */
