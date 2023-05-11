#ifndef _ACE_AXIS_IADC9613BUSDEVICE_H_
#define _ACE_AXIS_IADC9613BUSDEVICE_H_

#include "GlobalTypeDefs.h"
#include "IPeripheralBus.h"

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IAdcAD9613BusDevice.h
 * \brief     Adc bus device interface
 *
 *
 * \details   Interface for a bus device to be used by the AdcAD9613 device to access the peripheral bus
 *
 */

namespace Mplane
{


class IAdcAD9613BusDevice : public IBusDevice
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
	 */
    IAdcAD9613BusDevice(){};

    /*! @brief  Destructor
     *
     */
    virtual ~IAdcAD9613BusDevice() {} ;

    // AdcAD9613 specific access methods

    /**
     * Method used to clear the deskew bit on the device hardware. Should be overridden by derived class
     * to access the real hardware.
     *
     * \return RT_OK if successful, RT_other otherwise
     */
    virtual ReturnType::State clearDeskew(void)= 0 ;

    /**
     * Method used to clear the deskew alarm on the device hardware. Should be overridden by derived class
     * to access the real hardware.
     *
     * \return RT_OK if successful, RT_other otherwise
     */
    virtual ReturnType::State clearDeskewAlarm(void) = 0 ;

    /**
     * Checks for a deskew alarm.
     *
     * \return RT_OK if no alarm, RT_ERROR otherwise
     */
    virtual ReturnType::State checkDeskewAlarm(void) = 0 ;

    /**
     * Method used to enable the deskew bit on the device hardware. Should be overridden by derived class
     * to access the real hardware.
     *
     * \return RT_OK if successful, RT_other otherwise
     */
    virtual ReturnType::State enableDeskew(void) = 0 ;

};

typedef std::shared_ptr<IAdcAD9613BusDevice> IAdcAD9613BusDevicePtr ;


}

#endif /* _ACE_AXIS_IADC9613BUSDEVICE_H_ */
