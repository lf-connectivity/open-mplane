/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerMgr.h
 * \brief     A singleton class that serves as the YangHandlerMgr
 *			  used for ZCU111-FBC-ORANRRH applications.
 *
 *
 * \details
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERMGR_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERMGR_H_

#include "YangHandlerMgr.h"

namespace Mplane {

/*!
 * \class  Zcu111FbcOranrrhHandlerMgr
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerMgr : public YangHandlerMgr {
public:
	Zcu111FbcOranrrhHandlerMgr(std::shared_ptr<IYangModuleMgr> moduleMgr) ;
	virtual ~Zcu111FbcOranrrhHandlerMgr() ;

} ;

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERMGR_H_ */
