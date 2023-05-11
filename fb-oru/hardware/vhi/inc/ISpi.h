#ifndef _VRH_ISPI_H_
#define _VRH_ISPI_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISpi.h
 * \brief     A file to define generic interface to an SPI bus
 *
 *
 * \details   A file to define generic interface to an SPI bus
 *
 */

// Includes go here, before the namespace
#include "GlobalTypeDefs.h"
#include <memory>
#include <vector>
#include <stdexcept>

namespace Mplane
{

/*! \brief  Generic SPI interface
 *
 *  A virtual interface base class defining an interface to a SPI bus.
 *  The interface contains configuration and control aspects.
 */
class ISpi
{
public:


//    class Lock;

	// TODO - Need to move this to somewhere like CommonSpi because it's a concrete type, not a virtual interface!

	/**
	 * A Resource Allocation Is Initialisation (RAII) implementation of the ISpi
	 * that automatically locks the SPI bus (by calling the lock() method) and
	 * then unlocks the SPI bus (by calling the unlock() method) when the Lock
	 * goes out of scope.
	 */
	class Lock
	{
	public:

	    /**
	     * Lock constructor
	     *
	     * \param spi
	    *  \param portInfo the SPI port configuration information
	     */
	    Lock(std::shared_ptr<ISpi> spi, UINT8* portInfo);
	    virtual ~Lock();

	protected:
	    /**
	     * Special constructor for derived classes of ISpi so that they can pass a reference to themselves (since they are unable to convert 'this'
	     * into a shared pointer
	     * @param spi
	     * @param portInfo
	     */
	    Lock(ISpi* spi, UINT8* portInfo);

	private:
	    std::shared_ptr<ISpi> mSpiPtr;	// storage to hold shared pointer if constructed with one
	    ISpi* mSpi;	// spi pointer used with either raw pointer constructor or shared pointer constructor
	    UINT8* mPortInfo;

	};

    /*! \brief  The initialise method
     *
     *  Method called during system startup.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise() = 0;

    /*! \brief  Lock the SPI bus for atomic access
     *
     *  Ensures that the SPI accesses are non-interruptible due to
     *  pre-emption. This locks the bus until unlocked by the reciprocal
     *  call to unlock().
     *  Locking the bus means the bus is available to the one doing the locking
     *  until the bus is unlocked. Thereby ensuring atomic access to the bus.
     *
     *  \param portInfo the SPI port configuration information
     */
    virtual void lock(UINT8* portInfo) = 0;

    /*! \brief  Unlock the SPI bus, any atomic access has completed
     *
     *  Completes an SPI access sequence, during which the bus was locked from
     *  multiple access attempts.
     */
    virtual void unlock() = 0;

    /*! \brief  Read the SPI bus
     *
     *  Do the read from the bus.
     *
     *  This does NOT lock the bus prior to performing the bus access.
     *  It relies on the bus being locked prior to this being invoked.
     *
     *  \param dataLen is the number of words to read.
     *  \param dataPtr is the buffer to hold read data. How the data is
     *  placed in the buffer depends on the word size of the selected device.\n
     *  eg.\n
     *  4-8 bits one read per byte.\n
     *  9-16 bits one read every two bytes\n
     *  32 bits one read every four bytes\n
     *  \param numStorageBytes Number of bytes available for storing the read data
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State read(UINT16 dataLen, UINT8* dataPtr, unsigned numStorageBytes) =0;

    /*! \brief  Write to the SPI bus
     *
     *  Do the write to the bus.
     *
     *  This does NOT lock the bus prior to performing the bus access.
     *  It relies on the bus being locked prior to this being invoked.
     *
     *  \param dataLen is the number of words to write.
     *  \param dataPtr is the buffer containing the data to write.
     *  \param numStorageBytes Number of bytes of data
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write(UINT16 dataLen, UINT8* dataPtr, unsigned numStorageBytes) = 0;

    /*! \brief  Read the SPI bus, a complete atomic sequence
     *
     *  Do the read from the bus.
     *  It will perform the complete access in a single atomic sequence.
     *  The sequence must include:\n
     *  - lock the bus\n
     *  - access the device (read)\n
     *  - unlock the bus.
     *
     *  \param portInfo the SPI port configuration information
     *  \param dataLen is the number of words to read.
     *  \param dataPtr is the buffer to hold read data. How the data is
     *  placed in the buffer depends on the word size of the selected device.\n
     *  4-8 bits one read per byte.\n
     *  9-16 bits one read every two bytes\n
     *  32 bits one read every four bytes\n
     *  \param numStorageBytes Number of bytes available for storing the read data
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State read(UINT8* portInfo, UINT16 dataLen, UINT8* dataPtr, unsigned numStorageBytes) =0;

    /*! \brief  Write to the SPI bus, a complete atomic sequence
     *
     *  Do the write to the bus.
     *  It will perform the complete access in a single atomic sequence.
     *  The sequence must include:\n
     *  - lock the bus\n
     *  - access the device (write)\n
     *  - unlock the bus.
     *
     *  \param portInfo the SPI port configuration information
     *  \param dataLen is the number of words to write.
     *  \param dataPtr is the buffer containing the data to write.
     *  \param numStorageBytes Number of bytes of data
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write(UINT8* portInfo, UINT16 dataLen, UINT8* dataPtr, unsigned numStorageBytes) = 0;

    /**
     * Read a single register from the SPI device. The register can be from 1 to 32 bits. The specified "write data" is used
     * to set up the device to perform the read operation.
     *
     *  \param portInfo the SPI port configuration information
     * @param writeNumBits	Number of bits to use from the write data
     * @param writeData		Write data to perform read operation
     * @param regSize		Size of register (1-32 bits)
     * @param regValue		Register value
     * @return
     */
    virtual ReturnType::State readReg(UINT8* portInfo, UINT16 writeNumBits, UINT8* writeData, UINT8 regSize, UINT32& regValue) =0;


    /*! \brief Get the SPI index
     *
     * Get the zero based index that can be used to reference the SPI from
     * a list of SPIs.
     *
     * \return zero-based index of the SPI
     */
    virtual int getIndex() = 0;

    /*! \brief Get the SPI bus number
     *
     * A one-based number that usually refers to the associated SPI number.
     *
     * \return one-based DAC number
     */
    virtual int getNumber() = 0;

    /*! \brief Get the SPI bus name string
     *
     * A string name associated with the SPI bus used in logging and debugging.
     *
     * \return SPI name string
     */
    virtual const char* getName() = 0;

    /*! \brief Destructor
     *
     */
    virtual ~ISpi() { };


protected:

    /*! \brief Constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     *  Needed due to the class Lock inclusion, for RAII.
     */
    ISpi() {}

};



/*! \brief  Generic SPI factory interface
 *
 * The ISpiFactory is a polymorphic SPI bus interface factory that allows a
 * specific radio implementation to set the number of SPI buses supported by
 * that particular hardware implementation, create the actual SPI bus implementation,
 * again specific to the radio implementation and return the SPI requested.
 *
 * The interface contains a static getMaxNumSpis() method, which when implemented
 * will get the maximum SPI buses available on the radio hardware.
 *
 * The implementation will change for each board variant, and the factory
 * knows implicitly the make-up of the SPI buses for each particular board.
 *
 * The interface contains a static getSpi() method, which when implemented
 * will create all SPIs available on the particular hardware implementation on
 * it's first invocation, and then return get the SPI actually requested.
 */
class ISpiFactory
{
public:
    static int getMaxNumSpis();
    static std::shared_ptr<ISpi> getSpi( int spiIndex ) /* throw (std::invalid_argument) */;
};

} /* namespace Mplane */

#endif /* _VRH_ISPI_H_ */
