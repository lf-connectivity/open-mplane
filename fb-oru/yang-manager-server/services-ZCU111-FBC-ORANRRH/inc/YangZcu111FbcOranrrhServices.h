#ifndef _YangZcu111FbcOranrrhServices_H_
#define _YangZcu111FbcOranrrhServices_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangZcu111FbcOranrrhServices.h
 * \brief     Class extends the IServicesCtl interface to provide control of host application services.
 *
 *
 * \details   Class extends the IServicesCtl interface to provide control of host application services.
 *
 */
#include <memory>
#include "YangOranrrhServices.h"
#include "OranFaults.h"
#include "OranAlarms.h"

namespace Mplane
{

class YangZcu111FbcOranrrhServices: public YangOranrrhServices
{
public:

	YangZcu111FbcOranrrhServices();

	virtual ~YangZcu111FbcOranrrhServices();

	std::shared_ptr<OranFaults> mOranFaults;
	std::shared_ptr<OranAlarms> mOranAlarms;
};

}

#endif /* _YangZcu111FbcOranrrhServices_H_ */
