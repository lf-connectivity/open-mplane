/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      I2cBus.h
 * \brief     Base-level i2c bus
 *
 *
 * \details   Base-level i2c bus
 *
 */


#ifndef COMMON_BUS_INC_I2CBUS_H_
#define COMMON_BUS_INC_I2CBUS_H_

#include "bus/II2cBus.h"
#include "Bus.h"

namespace Mplane {

/*!
 * \class  I2cBus
 * \brief
 * \details
 *
 */
class I2cBus : public virtual II2cBus, public Bus {
public:
	I2cBus(const std::string& busName, const std::string& busDetails, unsigned i2cAddress, std::shared_ptr<IBusLock> busLock,
			std::shared_ptr<IBusReadonlySettings> busSettings) ;
	virtual ~I2cBus() ;


protected:
	/**
	 * Get the device address
	 */
	unsigned i2cAddress() const ;

private:
	unsigned mI2cAddress ;
} ;

}

#endif /* COMMON_BUS_INC_I2CBUS_H_ */
