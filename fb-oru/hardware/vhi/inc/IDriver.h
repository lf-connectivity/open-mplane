/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDriver.h
 * \brief     Virtual interface to a driver
 *
 *
 * \details   Virtual interface to a driver
 *
 */


#ifndef VHI_IDRIVER_H_
#define VHI_IDRIVER_H_

#include <vector>
#include <string>

#include "GlobalTypeDefs.h"

namespace Mplane {

/*!
 * \class  IDriver
 * \brief
 * \details
 *
 */
class IDriver {
public:
	IDriver() {}
	virtual ~IDriver() {}

    /**
     * This method is implemented by the final driver implementation
     * to indicate its type.
     *
     * @return Name of the driver instance.
     */
    virtual std::string getName() const =0 ;

} ;

}

#endif /* VHI_IDRIVER_H_ */
