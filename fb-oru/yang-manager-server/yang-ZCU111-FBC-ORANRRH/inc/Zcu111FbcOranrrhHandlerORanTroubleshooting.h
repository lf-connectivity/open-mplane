/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanTroubleshooting.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANTROUBLESHOOTING_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANTROUBLESHOOTING_H_

#include <memory>

#include "IORanLogFileMgr.h"
#include "IYangModuleMgr.h"

#include "Zcu111FbcOranrrhHandlerORanLog.h"

namespace Mplane
{

/*!
 * \class  Zcu111FbcOranrrhHandlerORanTroubleshooting
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerORanTroubleshooting : public Zcu111FbcOranrrhHandlerORanLog
{
public:
	Zcu111FbcOranrrhHandlerORanTroubleshooting(std::shared_ptr<IYangModuleMgr> moduleMgr);
	virtual ~Zcu111FbcOranrrhHandlerORanTroubleshooting();

protected:

	std::shared_ptr<IORanLogFileMgr> fileManager();

private:

};

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANTROUBLESHOOTING_H_ */
