/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IPsuMonitorService.h
 * \brief     Virtual interface to PSU monitor service
 *
 *
 * \details   Facilitates the IRQ notification for the PSU monitor
 *
 */

#ifndef IPSU_MONITOR_SERVICE_H_
#define IPSU_MONITOR_SERVICE_H_

#include <memory>

namespace Mplane {

class IPsuMonitorService {
public:
	IPsuMonitorService() {}
	virtual ~IPsuMonitorService() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IPsuMonitorService> getInstance() ;
} ;

}

#endif /* IPSU_MONITOR_SERVICE_H_ */
