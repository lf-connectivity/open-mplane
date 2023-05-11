/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranYangHandlerMgr.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef INC_ORAN_YANG_HANDLER_MGR_H_
#define INC_ORAN_YANG_HANDLER_MGR_H_

#include "YangHandlerMgr.h"

namespace Mplane {

/*!
 * \class  HandlerMgr
 * \brief
 * \details
 *
 */
class OranYangHandlerMgr : public YangHandlerMgr {
public:
 OranYangHandlerMgr(std::shared_ptr<IYangModuleMgr> moduleMgr);
 virtual ~OranYangHandlerMgr();
} ;

}

#endif /* INC_ORAN_YANG_HANDLER_MGR_H_ */
