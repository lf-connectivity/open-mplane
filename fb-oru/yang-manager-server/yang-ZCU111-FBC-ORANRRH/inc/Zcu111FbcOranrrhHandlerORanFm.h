/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanFm.h
 * \brief     Implements o-ran-fm.yang by using OranFm.cpp
 *
 *
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANFM_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANFM_H_

#include <memory>
#include "OranFm.h"
#include "YangHandlerSysrepo.h"
#include "SysrepoGetitemsCallback.h"

namespace Mplane
{

/*!
 * \class  Zcu111FbcOranrrhHandlerORanFm
 * \brief
 * \details
 *
 */

class Zcu111FbcOranrrhHandlerORanFm : public YangHandlerSysrepo
{
public:
	Zcu111FbcOranrrhHandlerORanFm(std::shared_ptr<IYangModuleMgr> moduleMgr);
	~Zcu111FbcOranrrhHandlerORanFm();

	/*
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	bool initialise() override;

private:
	std::shared_ptr<SysrepoGetitemsCallback> mCallback;
	OranFm mAlarmFault;

};

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANFM_H_ */
