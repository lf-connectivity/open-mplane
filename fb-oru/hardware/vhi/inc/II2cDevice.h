#ifndef _VRH_II2CDEVICE_H_
#define _VRH_II2CDEVICE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      II2cDevice.h
 * \brief     Device Interface for I2C
 *
 *
 * \details   Device Interface for I2C
 *
 */

#include "GlobalTypeDefs.h"

namespace Mplane
{

class II2cDevice
{
public:
    /**
     * Method returns the I2C bus ID associated with the I2C device
     * @return I2C device bus
     */
    virtual const UINT32 getI2cId() = 0;
    /**
     * Method return the I2C device ID on the specific bus, used with the device number to determine
     * the device select address.
     * @return Device identifier
     */
    virtual const UINT32 getDevId() = 0;
    /**
     * Returns the device number of the given device, used with the device ID to determine the
     * device select address.
     * @return Device number for a given device identifier
     */
    virtual const UINT32 getDevNum() = 0;

    /**
     * Returns the left shift value to be applied to the device number whe creating the device select address.
     * @return
     */
    virtual const UINT32 getDevShift() = 0;

protected:
    virtual ~II2cDevice(){};
};

}

#endif /* _II2CDEVICE_H_ */
