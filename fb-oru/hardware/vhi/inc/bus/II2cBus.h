/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      II2cBus.h
 * \brief     Generic I2c bus (implementing the IBus virtual interface)
 *
 *
 * \details   Generic I2c bus (implementing the IBus virtual interface)
 *
 */


#ifndef VHI_INC_BUS_II2CBUS_H_
#define VHI_INC_BUS_II2CBUS_H_

#include "IBus.h"

namespace Mplane {

/*!
 * \class  II2cBus
 * \brief
 * \details
 *
 */
class II2cBus : public virtual IBus {
public:
	II2cBus() {}
	virtual ~II2cBus() {}



} ;

}

#endif /* VHI_INC_BUS_II2CBUS_H_ */
