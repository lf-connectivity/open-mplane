/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Ina226Linux.h
 * \brief     INA226 interface using the Linux kernel driver
 *
 *
 * \details   Accesses the driver information via the /sys file system (usually /sys/class/hwmon/hwmon*)
 *
 */


#ifndef COMMON_PSU_INC_INA226LINUX_H_
#define COMMON_PSU_INC_INA226LINUX_H_

#include "IPsuMonitorDriver.h"

namespace Mplane {

/*!
 * \class  Ina226Linux
 * \brief
 * \details
 *
 */
class Ina226Linux : public virtual IPsuMonitorDriver {
public:
	Ina226Linux(const std::string& sysfsPath) ;
	virtual ~Ina226Linux() ;

	/**
	 * Is this a valid object? If the sysfs path is invalid or points to a non-INA226
	 * device then this object will not be valid
	 */
	bool isValid() const ;

    /*! \brief  Initialise the driver
     *
     */
    virtual ReturnType::State initialise ( void ) override;

    /**
     * Get the name of the driver
     *
     * In this case the name will be of the form:
     *
     * ina226_<identifier>
     */
    std::string name() const override ;


    /*! \brief  Debug output
     *
     */
    virtual void show ( void ) override;

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
    bool readSysfs() ;
    std::string readSysfsFile(const std::string& name) ;
    unsigned readSysfsUnsigned(const std::string& name) ;

private:
	std::string mSysfsPath ;
	std::string mName ;
	bool mValid ;
} ;

}

#endif /* COMMON_PSU_INC_INA226LINUX_H_ */
