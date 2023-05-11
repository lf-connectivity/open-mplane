/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IYangDelayManagementMgr.h
 * \brief     Virtual interface to manager object for YANG Delay Management model
 *
 *
 * \details   Virtual interface to manager object for YANG Delay Management model
 *
 */


#ifndef YANG_HANDLERS_INC_IYANGDELAYMANAGEMENTMGR_H_
#define YANG_HANDLERS_INC_IYANGDELAYMANAGEMENTMGR_H_

#include <memory>
#include <utility>

#include "ILeafContainer.h"

namespace Mplane {

/*!
 * \class  IYangDelayManagementMgr
 * \brief
 * \details
 *
 */
class IYangDelayManagementMgr {
public:
 /**
  * Singleton
  */
 static std::shared_ptr<IYangDelayManagementMgr> singleton();

 IYangDelayManagementMgr() {}
 virtual ~IYangDelayManagementMgr() {}

 /**
  * Initialise the object
  */
 virtual bool initialise() = 0;

 /**
  * Assign the leaf container
  */
 virtual void setLeafContainer(
     std::shared_ptr<ILeafContainer> leafContainer) = 0;

 /**
  * Get the leaf container
  */
 virtual std::shared_ptr<ILeafContainer> leafContainer() = 0;
} ;

}

#endif /* YANG_HANDLERS_INC_IYANGDELAYMANAGEMENTMGR_H_ */
