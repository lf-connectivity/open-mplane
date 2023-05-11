/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranRrhUpdateService.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#ifndef _MPLANE_ORANRRHUPDATESERVICE_H_
#define _MPLANE_ORANRRHUPDATESERVICE_H_

#include "Service.h"
#include "IRadio.h"

#include "RrhFaults.h"
#include "IFaultsList.h"

#include "IServicesMonitor.h"
#include "IServicesMonitorFactory.h"

#include "Observer.hpp"

namespace Mplane
{

using namespace Mplane;

class OranRrhUpdateService: public Service
{
public:
	static std::shared_ptr<OranRrhUpdateService> singleton();

	OranRrhUpdateService();
	virtual ~OranRrhUpdateService();

protected:
	/**
	 * Method that MUST be implemented by the inheriting service. The work done
	 * my the service, is implemented by this method.
	 */
	virtual void show();

	/**
	 * Method that MUST be implemented by the inheriting service. The work done
	 * my the service, is implemented by this method.
	 * @return
	 */
	virtual int service();


	/**
	 * Method called as a result of the radio control process calling reset
	 * in the service. By default the base class implementation does nothing.
	 */
	virtual void doReset();

	/**
	 * Used by the observer/Subject pattern to name objects that observe subjects.
	 * @return
	 */
	virtual const char* name() const;

private:

	std::shared_ptr<IRadio> mRadio;
	std::shared_ptr<RrhFaults> mFaults;
	std::shared_ptr<IFaultsList> mFaultList;
	std::shared_ptr<IServicesMonitor> mServicesMon;

};


} /* namespace Mplane */

#endif /* _MPLANE_ORANRRHUPDATESERVICE_H_ */
