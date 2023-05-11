/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NXPLM75B.h
 * \brief     Digital temperature sensor driver
 *
 *
 * \details   Temperature sensor driver for NXP LM75B chip
 *
 */

#ifndef _SENSORS_NXPLM75B__H_
#define _SENSORS_NXPLM75B__H_

#include "bus/II2cBus.h"
#include "ITemperatureSensorDriver.h"
#include "RegDriver.h"
#include "RegModel.h"
#include "Mutex.h"

namespace Mplane
{

/*! \brief  NXP LM75B Temperature Sensor driver
 *
 */
class NXPLM75B: public virtual ITemperatureSensorDriver, public RegDriver
{
public:

    /*! \brief Destructor
     *
     */
    NXPLM75B(std::shared_ptr<II2cBus> spi, const std::string& name);

    /*! \brief Destructor
     *
     */
    virtual ~NXPLM75B() { };

	/**
	 * Initialise the driver
	 */
	virtual ReturnType::State initialise( void ) override;

    /*! \brief Pure virtual method to get the temperature
     *
     * \return The Temperature
     */
    virtual const Temperature getTemperature( void ) override;

    /*! \brief  Dump the temperature sensor debug information
     *
     *  Dump the information of the temperature sensor to the console or log file
     */
    virtual void show(std::ostream& os) override;
    virtual void show(void) override;

protected:

    static const unsigned ADDR_WIDTH;
    static const unsigned DATA_WIDTH;
    static const unsigned ADDR_LSB; //The address is not part of the register data, hence setting it to max value
    static const uint8_t TEMPERATURE_REG_ADDR;
    static const uint16_t TEMPERATURE_DATA_MASK;
    static const uint16_t TEMPERATURE_SHIFT;
    static const uint16_t TEMPERATURE_SIGN_BIT_MASK;
    static const unsigned MAX_FAIL ;

private:
	std::shared_ptr<II2cBus> mI2c ;		//!> Pointer to the bus class
	Mutex mMutex ;             			//!> Mutex to protect getTemperature method
	bool mEnable ;						//!> Allow the driver to be disabled if it can't access the hardware
	unsigned mFailCount ;
};

} /* namespace Mplane */

#endif /* _SENSORS_NXPLM75B__H_ */
