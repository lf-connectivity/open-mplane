#ifndef _ACE_AXIS_II2CBUSDEVICE_H_
#define _ACE_AXIS_II2CBUSDEVICE_H_

#include "IPeripheralBus.h"

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      II2cBusDevice.h
 * \brief     I2c bus device interface
 *
 *
 * \details   Interface for a bus device to be used by the CommonI2c device to access the peripheral bus
 *
 */

namespace Mplane
{

// forward
struct I2cPortAccessConfig ;

class II2cBusDevice : public IBusDevice
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
	 * @return 	BusType device should match
	 */
    virtual const BusType getType(void) const = 0 ;

	/** @brief constructor
	 *
	 * Protected to force use of the singleton pattern
	 *
	 */
    II2cBusDevice(){};

    /*! @brief  Destructor
     *
     */
    virtual ~II2cBusDevice() {} ;

    // CommonI2c specific access methods

    /**
     * Method used to check the done flag on the device hardware. Should be overridden by derived class
     * to access the real hardware.
     *
     * \return true if done, false otherwise
     */
    virtual bool checkI2cAccessDone(void) = 0;

    /**
     * Method used to check that device hardware is ready to accept data. Should be overridden by derived class
     * to access the real hardware.
     *
     * \return true if done, false otherwise
     */
    virtual bool checkI2cAccessReady(void) = 0;

    /**
     * \brief Pure virtual method used to read data on the device hardware.
     *        Should be overridden by derived class to access the real hardware.
     *
     * \param numberOfBytesToRead The number of bytes that is to be read from the I2C device
     * \param prtToTheData A pointer to where the data can be placed.
     * \return bool Was the read successful
     */
    virtual bool readData(UINT8 numberOfBytesToRead, UINT8* prtToTheData) = 0;

    /**
     * \brief Pure virtual method used to setup the data reg on the device hardware.
     *        Should be overridden by derived class to access the real hardware.
     * \param value The value to write to the IC2 device
     * \return bool Was the write successful
     */
    virtual bool writeData(UINT8 value) = 0;

    /*! \brief Pure virtual method to reset the interrupt status register to
     *         an initialised state.
     *  \param none
     *  \return none
     */
    virtual void resetInterruptStatusReg( void ) = 0;

    /*! \brief Pure virtual method to reset the control and status register to
     *         an initialised state.
     *  \param none
     *  \return none
     */
    virtual void resetCtrlAndStatusReg( void ) = 0;

    /*! \brief Pure virtual method to start the I2C data transfer.
     *         Should be overridden by derived class to access the real hardware.
     *  \param none
     *  \return none
     */
    virtual void startDataTransfer( void ) = 0;

    /*! \brief Pure virtual method to stop the I2C data transfer.
     *         Should be overridden by derived class to access the real hardware.
     *  \param none
     *  \return none
     */
    virtual void stopDataTransfer( void ) = 0;

    /*! \brief Pure virtual method to reset the Reset and Interrupt register.
     *         Should be overridden by derived class to access the real hardware.
     *  \param none
     *  \return none
     */
    virtual void resetResetAndInterruptReg(void) = 0;

    /*!
     *  \brief Used to initialise I2C
     *  \param none
     *  \return none
     */
    virtual void initialiseI2c(void) = 0;

    /*!
     *
     *  \brief Pure virtual method used to set the rx FIFO depth.
     *         Should be overridden by derived class to access the real hardware.
     *
     *  \param value to set rxFifoDepth.
     *  \return none
     */
    virtual ReturnType::State setRxFifoDepth( UINT8 rxFifoDepth ) = 0;

};


typedef std::shared_ptr<II2cBusDevice> II2cBusDevicePtr ;

}

#endif /* _ACE_AXIS_II2CBUSDEVICE_H_ */
