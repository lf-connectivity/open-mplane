/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ITraceMgr.h
 * \brief     API for manager of trace files
 *
 *
 * \details   Singleton for collecting the trace files in an application and for
 * generating those files
 *
 */

#ifndef VCOMMONI_INC_ITRACEMGR_H_
#define VCOMMONI_INC_ITRACEMGR_H_

#include <memory>
#include <string>
#include <vector>

#include "IORanLogFileMgr.h"

namespace Mplane {

/*!
 * \class  ITraceMgr
 * \brief
 * \details
 *
 */
class ITraceMgr : public virtual IORanLogFileMgr {
 public:
  /**
   * Singleton
   */
  static std::shared_ptr<IORanLogFileMgr> singleton();

  ITraceMgr() {}
  virtual ~ITraceMgr() {}
};

} // namespace Mplane

#endif /* VCOMMONI_INC_ITRACEMGR_H_ */
