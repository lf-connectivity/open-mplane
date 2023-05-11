/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanSoftwareManagement.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANSoftwareManagement_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANSoftwareManagement_H_

#include "YangHandlerSysrepo.h"
#include "CallbackORanSoftwareMgr.h"

namespace Mplane {

/*!
 * \class  Zcu111FbcOranrrhUplaneHandler
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerORanSoftwareManagement : public YangHandlerSysrepo {
public:
	Zcu111FbcOranrrhHandlerORanSoftwareManagement(std::shared_ptr<IYangModuleMgr> moduleMgr) ;
	virtual ~Zcu111FbcOranrrhHandlerORanSoftwareManagement() ;

	/**
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() override ;

private:
	bool rpcDownload(std::shared_ptr<sysrepo::Session> session, const std::string& rpcXpath,
			std::shared_ptr<YangParams> callList, std::shared_ptr<YangParams> retList) ;
	bool rpcInstall(std::shared_ptr<sysrepo::Session> session, const std::string& rpcXpath,
			std::shared_ptr<YangParams> callList, std::shared_ptr<YangParams> retList) ;
	bool rpcActivate(std::shared_ptr<sysrepo::Session> session, const std::string& rpcXpath,
			std::shared_ptr<YangParams> callList, std::shared_ptr<YangParams> retList) ;

	void statusOk(const std::string& rpc, std::shared_ptr<YangParams> retList) ;
	void statusFail(const std::string& rpc, std::shared_ptr<YangParams> retList, const std::string& reason, const std::string& status = "FAILED") ;

private:
	std::shared_ptr<CallbackORanSoftwareMgr> mCallback;
	std::string mSoftwareDir ;

} ;

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANSoftwareManagement_H_ */
