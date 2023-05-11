#ifndef _VRH_II2C_H_
#define _VRH_II2C_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      II2c.h
 * \brief     A file to define generic interface to an I2C bus
 *
 *
 * \details   A file to define generic interface to an I2C bus
 *
 */

// Includes go here, before the namespace
#include "GlobalTypeDefs.h"
#include <memory>
#include <vector>
#include <stdexcept>

namespace Mplane
{

/*! \brief  Generic I2C interface
 *
 *  A virtual interface base class defining an interface to a I2C bus.
 *  The interface contains configuration and control aspects.
 */
class II2c
{
public:

//    class Lock;
    /**
     * A Resource Allocation Is Initialisation (RAII) implementation of the II2c
     * that automatically locks the I2C bus (by calling the lock() method) and
     * then unlocks the I2C bus (by calling the unlock() method) when the Lock
     * goes out of scope.
     */
    class Lock
    {
    public:

        /**
         * Lock constructor
         *
         * \param i2c
        *  \param portInfo the I2C port configuration information
         */
        Lock(std::shared_ptr<II2c> i2c, UINT8* portInfo);
        ~Lock();

    private:
        std::shared_ptr<II2c> mI2c;
        UINT8* mPortInfo;
    };

    /*! \brief  The initialise method
     *
     *  Method called during system startup.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise() = 0;

    /*! \brief  Lock the I2C bus for atomic access
     *
     *  Ensures that the I2C accesses are non-interruptible due to
     *  pre-emption. This locks the bus until unlocked by the reciprocal
     *  call to unlock().
     *  Locking the bus means the bus is available to the one doing the locking
     *  until the bus is unlocked. Thereby ensuring atomic access to the bus.
     *
     *  \param portInfo the I2C port configuration information
     */
    virtual void lock(UINT8* portInfo) = 0;

    /*! \brief  Unlock the I2C bus, any atomic access has completed
     *
     *  Completes an I2C access sequence, during which the bus was locked from
     *  multiple access attempts.
     */
    virtual void unlock() = 0;

    /*! \brief  Read the I2C bus
     *
     *  Do the read from the bus.
     *
     *  This does NOT lock the bus prior to performing the bus access.
     *  It relies on the bus being locked prior to this being invoked.
     *
     *  \param deviceAddress        The I2C address of the device that we wish to read from
     *  \param numberOfBytesToRead  The number of bytes that we wish to read
     *  \param bufferPtrToWriteTo   The buffer that we wish the data to be written to
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State read( UINT8  deviceAddress,
                                    UINT8  numberOfBytesToRead,
                                    UINT8* bufferPtrToWriteTo ) = 0;

    /*! \brief  Read the I2C bus
     *
     *  Do the read from the bus.
     *
     *  This does NOT lock the bus prior to performing the bus access.
     *  It relies on the bus being locked prior to this being invoked.
     *
     *  \param deviceAddress        The I2C address of the device that we wish to read from
     *  \param registerAddrToRead   The register address that we wish to read from
     *  \param numberOfBytesToRead  The number of bytes that we wish to read
     *  \param bufferPtrToWriteTo   The buffer that we wish the data to be written to
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State read( UINT8  deviceAddress,
                                    UINT8  registerAddrToRead,
                                    UINT8  numberOfBytesToRead,
                                    UINT8* bufferPtrToWriteTo ) = 0;

    /*! \brief  Write to the I2C bus
     *
     *  Do the write to the bus.
     *
     *  This does NOT lock the bus prior to performing the bus access.
     *  It relies on the bus being locked prior to this being invoked.
     *
     *  \param dataLen is the number of words to write.
     *  \param dataPtr is the buffer containing the data to write.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write(UINT16 dataLen, UINT8* dataPtr) = 0;

    /*!
     *
     * \brief  Write to the I2C bus
     *
     *  Do the write to the bus.
     *
     *  This does NOT lock the bus prior to performing the bus access.
     *  It relies on the bus being locked prior to this being invoked.
     *
     *  \param deviceAddress is the I2C address of the device that we wish to write to
     *  \param dataLen is the number of words to write.
     *  \param dataPtr is the buffer containing the data to write.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write(UINT8  deviceAddress, UINT16 dataLen, UINT8* dataPtr) = 0;

    /*! \brief  Read the I2C bus, a complete atomic sequence
     *
     *  Do the read from the bus.
     *  It will perform the complete access in a single atomic sequence.
     *  The sequence must include:\n
     *  - lock the bus\n
     *  - access the device (read)\n
     *  - unlock the bus.
     *
     *  \param portInfo the I2C port configuration information
     *  \param deviceAddress        The I2C address of the device that we wish to read from
     *  \param numberOfBytesToRead  The number of bytes that we wish to read
     *  \param bufferPtrToWriteTo   The buffer that we wish the data to be written to
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State read( UINT8* portInfo,
                                    UINT8  deviceAddress,
                                    UINT8  numberOfBytesToRead,
                                    UINT8* bufferPtrToWriteTo ) = 0;

    /*! \brief  Read the I2C bus, a complete atomic sequence
     *
     *  Do the read from the bus.
     *  It will perform the complete access in a single atomic sequence.
     *  The sequence must include:\n
     *  - lock the bus\n
     *  - access the device (read)\n
     *  - unlock the bus.
     *
     *  \param portInfo             Te I2C port configuration information
     *  \param deviceAddress        The I2C address of the device that we wish to read from
     *  \param registerAddrToRead   The register address that we wish to read from
     *  \param numberOfBytesToRead  The number of bytes that we wish to read
     *  \param bufferPtrToWriteTo   The buffer that we wish the data to be written to
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State read( UINT8* portInfo,
                                    UINT8  deviceAddress,
                                    UINT8  registerAddrToRead,
                                    UINT8  numberOfBytesToRead,
                                    UINT8* bufferPtrToWriteTo ) = 0;

    /*! \brief  Write to the I2C bus, a complete atomic sequence
     *
     *  Do the write to the bus.
     *  It will perform the complete access in a single atomic sequence.
     *  The sequence must include:\n
     *  - lock the bus\n
     *  - access the device (write)\n
     *  - unlock the bus.
     *
     *  \param portInfo             The I2C port configuration information
     *  \param deviceAddress        The I2C address of the device that we wish to read from
     *  \param registerAddrToRead   The register address that we wish to read from
     *  \param numberOfBytesToRead  The number of bytes that we wish to read
     *  \param bufferPtrToWriteTo   The buffer that we wish the data to be written to
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write(UINT8* portInfo, UINT16 dataLen, UINT8* dataPtr) = 0;

    /*! \brief Get the I2C index
     *
     * Get the zero based index that can be used to reference the I2C from
     * a list of I2Cs.
     *
     * \return zero-based index of the I2C
     */
    virtual int getIndex() = 0;

    /*! \brief Get the I2C bus number
     *
     * A one-based number that usually refers to the associated I2C number.
     *
     * \return one-based DAC number
     */
    virtual int getNumber() = 0;

    /*! \brief Get the I2C bus name string
     *
     * A string name associated with the I2C bus used in logging and debugging.
     *
     * \return I2C name string
     */
    virtual const char* getName() = 0;

    /*! \brief Destructor
     *
     */
    virtual ~II2c() { };


protected:

    /*! \brief Constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     *  Needed due to the class Lock inclusion, for RAII.
     */
    II2c();


};


/*! \brief  Generic I2C factory interface
 *
 * The II2cFactory is a polymorphic I2C bus interface factory that allows a
 * specific radio implementation to set the number of I2C buses supported by
 * that particular hardware implementation, create the actual I2C bus implementation,
 * again specific to the radio implementation and return the I2C requested.
 *
 * The interface contains a static getMaxNumI2cs() method, which when implemented
 * will get the maximum I2C buses available on the radio hardware.
 *
 * The implementation will change for each board variant, and the factory
 * knows implicitly the make-up of the I2C buses for each particular board.
 *
 * The interface contains a static getI2c() method, which when implemented
 * will create all I2Cs available on the particular hardware implementation on
 * it's first invocation, and then return get the I2C actually requested.
 */
class II2cFactory
{
public:
    static int getMaxNumI2cs();
    static std::shared_ptr<II2c> getI2c( int i2cIndex ) /* throw (std::invalid_argument) */;
};

} /* namespace Mplane */

#endif /* _VRH_II2C_H_ */
