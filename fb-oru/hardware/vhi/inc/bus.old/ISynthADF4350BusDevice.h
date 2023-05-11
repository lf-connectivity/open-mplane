#ifndef _ACE_AXIS_ISYNTHADF4350BUSDEVICE_H_
#define _ACE_AXIS_ISYNTHADF4350BUSDEVICE_H_

#include "GlobalTypeDefs.h"
#include "IPeripheralBus.h"

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISynthADF4350BusDevice.h
 * \brief     DAC bus device
 *
 *
 * \details   Interface for a bus device to be used by the SynthADF4350 device to access the peripheral bus
 *
 */

namespace Mplane
{

class ISynthADF4350BusDevice : public IBusDevice
{
public:

    /*! @brief  Check bus device
     *
     *  Checks that this bus device is of the correct type
	 *
	 * @param type		BusType device should match
	 * @return true is correct
	 */
    virtual bool isCorrectType(const BusType type) const =0 ;

    /*! @brief  Get bus type
     *
     *  Returns the bus type of this device
	 *
	 * @resture 	BusType device should match
	 */
    virtual const BusType getType(void) const =0 ;

	/** @brief constructor
	 *
	 * Protected to force use of the singleton pattern
	 *
	 */
    ISynthADF4350BusDevice(){};

    /*! @brief  Destructor
     *
     */
    virtual ~ISynthADF4350BusDevice() {} ;

    // SynthADF4350 specific access methods

    /**
     * Method used to enable the pll on the device hardware. Should be overridden by derived class
     * to access the real hardware.
     *
     * \return RT_OK if successful, RT_other otherwise
     */
	virtual ReturnType::State enablePll(void) =0 ;

};

typedef std::shared_ptr<ISynthADF4350BusDevice> ISynthADF4350BusDevicePtr ;


}

#endif /* _ACE_AXIS_ISYNTHADF4350BUSDEVICE_H_ */
