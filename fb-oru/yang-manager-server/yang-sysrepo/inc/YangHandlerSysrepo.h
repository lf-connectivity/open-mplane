/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangHandlerSysrepo.h
 * \brief     YangHandler with sysrepo connections
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef YANG_SYSREPO_INC_YANGHANDLERSYSREPO_H_
#define YANG_SYSREPO_INC_YANGHANDLERSYSREPO_H_

#include "Loggable.h"
#include "YangHandlerSysrepoUnlogged.h"


namespace Mplane {


/*!
 * \class  YangHandlerSysrepo
 * \brief
 * \details
 *
 */
class YangHandlerSysrepo : public YangHandlerSysrepoUnlogged, public Loggable
{
public:
	YangHandlerSysrepo(const std::string & moduleName, std::shared_ptr<IYangModuleMgr> moduleMgr, const std::string & logInstanceName) ;
	virtual ~YangHandlerSysrepo() ;

	/**
	 * Called to display info. A loggable derived class will override this with a call to eventInfo()
	 */
	virtual void logInfo(const std::string& info) override ;

protected:
	/**
	 * Called to display info. A loggable derived class will override this with a call to Loggable::groupName()
	 */
	virtual std::string groupName() const override ;

} ;

}

#endif /* YANG_SYSREPO_INC_YANGHANDLERSYSREPO_H_ */
