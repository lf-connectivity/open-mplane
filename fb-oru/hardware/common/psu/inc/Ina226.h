/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Ina226.h
 * \brief     TI INA226 power monitor
 *
 *
 * \details   TI INA226 power monitor on i2c bus
 *
 */


#ifndef COMMON_PSU_INC_INA226_H_
#define COMMON_PSU_INC_INA226_H_

#include "IPsuMonitorDriver.h"
#include "bus/II2cBus.h"
#include "RegDriver.h"
#include "RegModel.h"

namespace Mplane {

/*!
 * \class  Ina226
 * \brief
 * \details
 *
 */
class Ina226 : public virtual IPsuMonitorDriver, public RegDriver {
public:
	Ina226(std::shared_ptr<II2cBus> i2c, const std::string& name,
			float maxCurrent, float shuntResistor) ;
	virtual ~Ina226() ;

	/**
	 * Initialise the driver
	 */
	virtual ReturnType::State initialise(void) override;

    /*! \brief  Debug output
     *
     */
    virtual void show(void) override;

    /**
     * Get the name of the driver
     *
     */
    std::string name() const override ;

    /**
     * Get the power reading (if possible, may return 0)
     */
    virtual float power() override ;

    /**
     * Get the voltage reading (if possible, may return 0)
     */
    virtual float voltage() override ;

    /**
     * Get the current reading (if possible, may return 0)
     */
    virtual float current() override ;

    /**
     * Does this monitor support power measurement
     */
    virtual bool isPowerSupported() const override ;

    /**
     * Does this monitor support voltage measurement
     */
    virtual bool isVoltageSupported() const override ;

    /**
     * Does this monitor support current measurement
     */
    virtual bool isCurrentSupported() const override ;

private:
	void calcCalibration() ;

private:
	std::shared_ptr<II2cBus> mI2c ;
	float mMaxCurrent ;
	float mShuntResistor ;

	float mCurrentLSB ;
	unsigned mCalibration ;
} ;

}

#endif /* COMMON_PSU_INC_INA226_H_ */
