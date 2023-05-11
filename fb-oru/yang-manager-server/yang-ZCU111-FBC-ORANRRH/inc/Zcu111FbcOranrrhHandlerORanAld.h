/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanAld.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANALD_H_
#define ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANALD_H_

#include "YangHandlerSysrepo.h"
#include "SysrepoGetitemsCallback.h"
#include "IAldPort.h"
#include <atomic>

namespace Mplane {

/*!
 * \class  Zcu111FbcOranrrhHandlerORanAld
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerORanAld : public YangHandlerSysrepo {
public:
	Zcu111FbcOranrrhHandlerORanAld(std::shared_ptr<IYangModuleMgr> moduleMgr) ;
	virtual ~Zcu111FbcOranrrhHandlerORanAld() ;

	/**
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() override ;

	static const unsigned int AldRespTimeout;
	static const unsigned int HdlcRespTimeout;

private:

	bool rpcAldCommunication(std::shared_ptr<sysrepo::Session> session, const std::string& rpcXpath,
			std::shared_ptr<YangParams> callList, std::shared_ptr<YangParams> retList) ;

	std::atomic<unsigned char> mHdlcErrorFlag;
	std::vector<unsigned char> mAldResp;
	std::atomic<bool> mRespRecd;

} ;

}

#endif /* ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANALD_H_ */
