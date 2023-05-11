/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ILogEvent.h
 * \brief     Event logging methods
 *
 *
 * \details   Interface to the methods used for event logging
 *
 */

#ifndef ILOGEVENT_H_
#define ILOGEVENT_H_

#include <string>

namespace Mplane {

class ILogEvent {
 public:
  ILogEvent() {}
  virtual ~ILogEvent() {}

  /**
   * log a data event (e.g. an ARD command)
   */
  virtual void eventData(const std::string& eventStr) const = 0;

  /**
   * log informational event
   */
  virtual void eventInfo(const std::string& eventStr) const = 0;

  /**
   * log a warning
   */
  virtual void eventWarning(const std::string& eventStr) const = 0;

  /**
   * log a non-fatal error
   */
  virtual void eventError(const std::string& eventStr) const = 0;

  /**
   * log a fatal error (and terminate)
   */
  virtual void eventFatal(const std::string& eventStr) const = 0;
};

} // namespace Mplane

#endif /* ILOGEVENT_H_ */
