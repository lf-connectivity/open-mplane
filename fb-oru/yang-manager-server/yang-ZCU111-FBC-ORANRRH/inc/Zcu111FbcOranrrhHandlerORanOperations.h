/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanOperations.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANOPERATIONS_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANOPERATIONS_H_

#include "YangHandlerSysrepo.h"
#include "SysrepoGetitemsCallback.h"

namespace Mplane
{

/*!
 * \class  Zcu111FbcOranrrhHandlerORanOperations
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerORanOperations : public YangHandlerSysrepo
{
public:
	Zcu111FbcOranrrhHandlerORanOperations(std::shared_ptr<IYangModuleMgr> moduleMgr);

	/*
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() override;

	/**
	 * Module change hook - called by module_change() method with filtered events
	 */
	virtual void valueChange(const std::string& xpath,
	                         std::shared_ptr<YangParam> oldValue,
	                         std::shared_ptr<YangParam> newValue);
protected:

private:
	void callTzSet();
	bool rpcReset(std::shared_ptr<sysrepo::Session> session,
				  const std::string &rpcXpath,
				  std::shared_ptr<YangParams> callList,
				  std::shared_ptr<YangParams> retList);

	std::shared_ptr<SysrepoGetitemsCallback> mCallback;
};

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANOPERATIONS_H_ */
