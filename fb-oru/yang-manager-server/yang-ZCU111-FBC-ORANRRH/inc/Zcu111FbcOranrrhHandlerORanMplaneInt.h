/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanMplaneInt.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANMPLANEINT_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANMPLANEINT_H_

#include <string>
#include <memory>
#include <set>
#include <mutex>

#include "YangMgrServer.h"
#include "YangParamUtils.h"
#include "YangHandlerSysrepo.h"
#include "SysrepoGetitemsCallback.h"
#include "IDhcpOptions.h"

namespace Mplane
{

/*!
 * \class  Zcu111FbcOranrrhHandlerORanMplaneInt
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerORanMplaneInt : public YangHandlerSysrepo
{
public:
	Zcu111FbcOranrrhHandlerORanMplaneInt(std::shared_ptr<IYangModuleMgr> moduleMgr);
	virtual ~Zcu111FbcOranrrhHandlerORanMplaneInt();

	/*
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() override;

protected:
	/**
	 * Module change hook - called by module_change() method with filtered events
	 */
	virtual void valueChange(const std::string& xpath, std::shared_ptr<YangParam> oldValue, std::shared_ptr<YangParam> newValue) override ;

	/*!
	 \brief Module change hook - called by module_change() method to have this class validate the proposed values changes
	 \param params A YangParams pointer containing all of the changed values
	 \return SR_ERR_OK if the values are validated; SR_ERR_VALIDATION_FAILED on validation failure. Can return any other sysrepo error
	 status as necessary.
	 */
	virtual int validate(std::shared_ptr<YangParams> params, std::shared_ptr<YangParams> deletedParams) override ;

private:
	void getDhcpOptions(const std::string& interface) ;
	std::string handleGetCallback(const std::string& leafName, const std::string& ifvlan) ;

private:
	std::shared_ptr<SysrepoGetitemsCallback> mCallback;
	std::shared_ptr<ILeafContainer> mMplaneInterfacesContainer ;

	//class InterfaceInfo ;
	std::mutex mMutex ;
	//std::map<std::string, std::shared_ptr<InterfaceInfo>> mInterfaceInfo ;
	std::shared_ptr<IDhcpOptions> mDhcpOptions;
	std::vector<std::string> mInterfaces;
};

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANMPLANEINT_H_ */
