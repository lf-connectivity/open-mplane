/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanFileManagement.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANFILEMANAGEMENT_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANFILEMANAGEMENT_H_

#include "YangHandlerSysrepo.h"

namespace Mplane {

/*!
 * \class  Zcu111FbcOranrrhUplaneHandler
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerORanFileManagement : public YangHandlerSysrepo {
public:
	Zcu111FbcOranrrhHandlerORanFileManagement(std::shared_ptr<IYangModuleMgr> moduleMgr) ;
	virtual ~Zcu111FbcOranrrhHandlerORanFileManagement() ;

	static const std::string mDirPrefix;
	static const std::string mOranLogFolder;
	static const std::string mOranPMFolder;
	static const std::string mOranTransceiverFolder;

	/**
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() override ;

private:
	bool rpcFileUpload(std::shared_ptr<sysrepo::Session> session, const std::string& rpcXpath,
			std::shared_ptr<YangParams> callList, std::shared_ptr<YangParams> retList) ;
	bool rpcFileDownload(std::shared_ptr<sysrepo::Session> session, const std::string& rpcXpath,
			std::shared_ptr<YangParams> callList, std::shared_ptr<YangParams> retList) ;
	bool rpcFileList(std::shared_ptr<sysrepo::Session> session, const std::string& rpcXpath,
			std::shared_ptr<YangParams> callList, std::shared_ptr<YangParams> retList) ;

	bool handleFileTransfer(bool upload, std::shared_ptr<YangParams> callList, std::shared_ptr<YangParams> retList) ;
	void statusOk(const std::string& rpc, std::shared_ptr<YangParams> retList) ;
	void statusFail(const std::string& rpc, std::shared_ptr<YangParams> retList, const std::string& reason) ;
} ;

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANFILEMANAGEMENT_H_ */
