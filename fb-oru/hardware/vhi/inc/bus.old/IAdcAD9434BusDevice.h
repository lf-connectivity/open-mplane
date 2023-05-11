#ifndef _ACE_AXIS_IADC9434BUSDEVICE_H_
#define _ACE_AXIS_IADC9434BUSDEVICE_H_

#include "GlobalTypeDefs.h"
#include "IPeripheralBus.h"

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IAdcAD9434BusDevice.h
 * \brief     Adc bus device interface
 *
 *
 * \details   Interface for a bus device to be used by the AdcAD9434 device to access the peripheral bus
 *
 */

namespace Mplane
{


class IAdcAD9434BusDevice : public IBusDevice
{
public:

    /*! @brief  Check bus device
     *
     *  Checks that this bus device is of the correct type
	 *
	 * @param type		BusType device should match
	 * @return true is correct
	 */
    virtual bool isCorrectType(const BusType type) const = 0 ;

    /*! @brief  Get bus type
     *
     *  Returns the bus type of this device
	 *
	 * @resture 	BusType device should match
	 */
    virtual const BusType getType(void) const = 0 ;

	/** @brief constructor
	 *
	 *
	 */
    IAdcAD9434BusDevice(){};

    /*! @brief  Destructor
     *
     */
    virtual ~IAdcAD9434BusDevice() {} ;

    // AdcAD9434 specific access methods

    /**
     * Method used to reset the device hardware. Should be overridden by derived class
     * to access the real hardware.
     *
     * \return RT_OK if successful, RT_other otherwise
     */
    virtual ReturnType::State reset(void) = 0;

};

typedef std::shared_ptr<IAdcAD9434BusDevice> IAdcAD9434BusDevicePtr ;


}

#endif /* _ACE_AXIS_IADC9434BUSDEVICE_H_ */
