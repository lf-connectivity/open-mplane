/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Sc18is602bBus.h
 * \brief     An I2cToSpi bus using the SC18IS602B device
 *
 *
 * \details   An I2cToSpi bus using the SC18IS602B device
 *
 */


#ifndef COMMON_I2CTOSPI_INC_SC18IS602BBUS_H_
#define COMMON_I2CTOSPI_INC_SC18IS602BBUS_H_

#include "I2cToSpiBus.h"

namespace Mplane {

/*!
 * \class  Sc18is602bBus
 * \brief
 * \details
 *
 */
class Sc18is602bBus : public I2cToSpiBus {
public:
	Sc18is602bBus(std::shared_ptr<II2cBus> i2c, std::shared_ptr<IBusReadonlySettings> busSettings, unsigned spiSelect) ;
	virtual ~Sc18is602bBus() ;

} ;

}

#endif /* COMMON_I2CTOSPI_INC_SC18IS602BBUS_H_ */
