/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ILogHistory.h
 * \brief     Virtual API for a rolling history of logs
 *
 *
 * \details   Virtual API for a rolling history of logs
 *
 */

#ifndef VCOMMONI_INC_ILOGHISTORY_H_
#define VCOMMONI_INC_ILOGHISTORY_H_

#include <memory>
#include <string>
#include <vector>

#include "ILoggable.h"

namespace Mplane {

/*!
 * \class  ILogHistory
 * \brief
 * \details
 *
 */
class ILogHistory {
 public:
  /**
   * Singleton
   */
  static std::shared_ptr<ILogHistory> singleton();

  ILogHistory() {}
  virtual ~ILogHistory() {}

  /**
   * Get the buffered history logs
   */
  virtual std::vector<std::string> getHistory() const = 0;

  /**
   * Change the history logging level
   */
  virtual void setLogLevel(ILoggable::LogLevel level) = 0;

  /**
   * Change the history depth
   */
  virtual void setHistoryDepth(unsigned depth) = 0;

  /**
   * Clear history (Mainly for debug)
   */
  virtual void clear() = 0;

  /**
   * Display contents for debug
   */
  virtual void show() = 0;
};

} // namespace Mplane

#endif /* VCOMMONI_INC_ILOGHISTORY_H_ */
