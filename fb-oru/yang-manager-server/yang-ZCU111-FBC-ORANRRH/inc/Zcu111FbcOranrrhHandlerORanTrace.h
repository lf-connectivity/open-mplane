/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanTrace.cpp
 * \brief     O-RAN radio trace module handler
 *
 *
 * \details   O-RAN radio trace module handler
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANTRACE_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANTRACE_H_

#include <memory>

#include "IORanLogFileMgr.h"
#include "IYangModuleMgr.h"

#include "Zcu111FbcOranrrhHandlerORanLog.h"

namespace Mplane
{

/*!
 * \class  Zcu111FbcOranrrhHandlerORanTrace
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerORanTrace : public Zcu111FbcOranrrhHandlerORanLog

{
public:
	Zcu111FbcOranrrhHandlerORanTrace(std::shared_ptr<IYangModuleMgr> moduleMgr);
	virtual ~Zcu111FbcOranrrhHandlerORanTrace();

protected:

	std::shared_ptr<IORanLogFileMgr> fileManager();

private:

};

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANTRACE_H_ */
