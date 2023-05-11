/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      II2cToSpiBus.h
 * \brief     Models a device that converts the I2c bus into an SPI bus
 *
 *
 * \details   The default read/write methods map to an ISpiBus, but collect the data and then transport it via an I2cBus
 * 				so that the data is correctly sent to the physical I2cToSpi bridge device over I2c
 *
 */


#ifndef VHI_INC_BUS_II2CTOSPIBUS_H_
#define VHI_INC_BUS_II2CTOSPIBUS_H_

#include "bus/II2cBus.h"
#include "bus/ISpiBus.h"

namespace Mplane {

/*!
 * \class  II2cToSpiBus
 * \brief
 * \details
 *
 */
class II2cToSpiBus : public virtual II2cBus, public virtual ISpiBus {
public:
	II2cToSpiBus() {}
	virtual ~II2cToSpiBus() {}

} ;

}

#endif /* VHI_INC_BUS_II2CTOSPIBUS_H_ */
