/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanLog.h
 * \brief     O-RAN log handler base class
 *
 *
 * \details   O-RAN log handler base class
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERLOG_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERLOG_H_

#include <string>
#include <memory>
#include <atomic>

#include "YangParam.h"

#include "TaskEvent.h"
#include "YangHandlerSysrepoUnlogged.h"
#include "IORanLogFileMgr.h"

namespace Mplane
{

/*!
 * \class  Zcu111FbcOranrrhHandlerORanLog
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerORanLog : public YangHandlerSysrepoUnlogged, public TaskEvent	// TaskEvent is ILoggable
{
public:
	Zcu111FbcOranrrhHandlerORanLog(std::shared_ptr<IYangModuleMgr> moduleMgr,
	                               const std::string & moduleName,
	                               const std::string & taskName,
	                               const std::string & rpcStart,
	                               const std::string & rpcStop,
	                               const std::string & notification);
	virtual ~Zcu111FbcOranrrhHandlerORanLog();

	/**
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() override;

protected:
	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	virtual bool runEvent() override;

	/**
	 * Called to display info. A loggable derived class will override this with a call to eventInfo()
	 */
	virtual void logInfo(const std::string& info) override;

	/**
	 * Called to display info. A loggable derived class will override this with a call to Loggable::groupName()
	 */
	virtual std::string groupName() const override;

	/**
	 * Returns the file manager
	 */
	virtual std::shared_ptr<IORanLogFileMgr> fileManager() = 0;

private:
	bool rpcStart(std::shared_ptr<sysrepo::Session> session,
                  const std::string & rpcXpath,
	              std::shared_ptr<YangParams> callList,
	              std::shared_ptr<YangParams> retList);
	bool rpcStop(std::shared_ptr<sysrepo::Session> session,
	             const std::string & rpcXpath,
	             std::shared_ptr<YangParams> callList,
	             std::shared_ptr<YangParams> retList);

	void statusOk(const std::string & rpc,
	              std::shared_ptr<YangParams> retList);
	void statusFail(const std::string & rpc,
	                std::shared_ptr<YangParams> retList,
	                const std::string & reason);
	void notify(const std::vector<std::string> & paths);

	const std::string mPathRpcStart;
	const std::string mPathRpcStop;
	const std::string mPathNotify;

	std::atomic<bool> mEnabled;

};

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERLOG_H_ */
