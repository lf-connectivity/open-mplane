#ifndef _YangServices_H_
#define _YangServices_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangServices.h
 * \brief     Class extends the IServicesCtl interface to provide control of host application services.
 *
 *
 * \details   Class extends the IServicesCtl interface to provide control of host application services.
 *
 */
#include <memory>

#include "AppServices.h"

namespace Mplane
{

class YangServices: public AppServices
{
public:
 YangServices();

 virtual ~YangServices();

 /**
  * Method used to shutdown all services after which the service may be
  * deleted or restarted using the start() method.
  */
 virtual void shutdown() override;
};

}

#endif /* _YangServices_H_ */
