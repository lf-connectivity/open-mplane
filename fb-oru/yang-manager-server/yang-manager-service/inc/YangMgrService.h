/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangMgrService.h
 * \brief     YANG Manager service
 *
 *
 * \details   YANG Manager service - Loads YANG modules manager to access data stored in sysrepo.
 *
 */

#ifndef _YANG_MGR_SERVICE_H_
#define _YANG_MGR_SERVICE_H_

#include <memory>

#include "Service.h"

#include "YangMgrServer.h"

namespace Mplane
{

class YangMgrService: public Service
{
public:

	static std::shared_ptr<YangMgrService> singleton();

	YangMgrService();

	/**
	 *
	 */
	virtual ~YangMgrService();

	/**
	 * Get the pointer to the YANG manager server
	 */
	std::shared_ptr<YangMgrServer> getYangMgrServer() const ;

protected:
	/**
	 * Method defined by the Loggable interface must be implemented by all
	 * object to force the display of the objects current status.
	 */
	virtual void show();

	/**
	 * Method that MUST be implemented by the inheriting service. The work done
	 * by the service, is implemented by this method.
	 * @return
	 */
	virtual int service();


	/**
	 * Method called as a result of the radio control process calling reset
	 * in the service. By default the base class implementation does nothing.
	 */
	virtual void doReset();

private:
	std::shared_ptr<YangMgrServer> mYangMgr;

};


} /* namespace Mplane */

#endif /* _YANG_MGR_SERVICE_H_ */
