#ifndef _ACE_AXIS_ISPIBUSDEVICE_H_
#define _ACE_AXIS_ISPIBUSDEVICE_H_

#include "IPeripheralBus.h"

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISpiBusDevice.h
 * \brief     Spi bus device interface
 *
 *
 * \details   Interface for a bus device to be used by the CommonSpi device to access the peripheral bus
 *
 */

namespace Mplane
{

// forward
struct SpiPortAccessConfig ;

class ISpiBusDevice : public IBusDevice
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
	 * Protected to force use of the singleton pattern
	 *
	 */
    ISpiBusDevice(){};

    /*! @brief  Destructor
     *
     */
    virtual ~ISpiBusDevice() {} ;

    // CommonSpi specific access methods

    /**
     * Method used to check the done flag on the device hardware. Should be overridden by derived class
     * to access the real hardware.
     *
     * \return true if done, false otherwise
     */
    virtual bool checkSpiAccessDone(void) = 0;

    /**
     * Method used to read data on the device hardware. Should be overridden by derived class
     * to access the real hardware.
     *
     */
    virtual void readRawData(UINT32* rawData) = 0;

    /**
     * Method used to check the chip select on the device hardware. Should be overridden by derived class
     * to access the real hardware.
     *
     * \return true if ok, false otherwise
     */
    virtual bool checkCS(UINT16 cs) = 0;

    /**
     * Method used to write chip select on the device hardware when none was specified. Should be overridden by derived class
     * to access the real hardware.
     *
     */
    virtual void writeNoCS(void) = 0;

    /**
     * Method used to write chip select on the device hardware. Should be overridden by derived class
     * to access the real hardware.
     *
     */
    virtual void writeCS(UINT16 cs) = 0;

    /**
     * Method used to setup the data reg on the device hardware. Should be overridden by derived class
     * to access the real hardware.
     *
     */
    virtual void setupWriteDataReg(UINT16 lowValue, UINT16 highValue) = 0;

    /**
     * Method used to setup the control reg on the device hardware. Should be overridden by derived class
     * to access the real hardware.
     *
     */
    virtual void setupControlReg(SpiPortAccessConfig* config) = 0;

};


typedef std::shared_ptr<ISpiBusDevice> ISpiBusDevicePtr ;

}

#endif /* _ACE_AXIS_ISPIBUSDEVICE_H_ */
