#ifndef _VRH_ISPIDEVICE_H_
#define _VRH_ISPIDEVICE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISpiDevice.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "GlobalTypeDefs.h"

namespace Mplane
{

class ISpiDevice
{
public:
    /**
     * Method returns the SPI bus ID associated with the SPI device
     * @return SPI device bus
     */
    virtual const UINT32 getSpiId() = 0;
    /**
     * Method return the SPI device ID on the specific bus, used with the device number to determine
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
    virtual ~ISpiDevice(){};
};

}

#endif /* _ISPIDEVICE_H_ */
