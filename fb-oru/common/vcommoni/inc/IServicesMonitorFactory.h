#ifndef _ISERVICESMONITORFACTORY_H_
#define _ISERVICESMONITORFACTORY_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IServicesMonitorFactory.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <memory>

namespace Mplane
{

class IServicesMonitor;

class IServicesMonitorFactory
{

public:
    /*!
     *
     * @return
     */
    static std::shared_ptr<IServicesMonitor> getInterface();

};

}

#endif /* _ISERVICESMONITORFACTORY_H_ */
