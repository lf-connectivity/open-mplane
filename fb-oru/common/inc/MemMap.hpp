/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MemMap.hpp
 * \brief     Memory mapped access to hardware
 *
 *
 * \details   Wraps up mmap access to different bus sizes. Currently supports access to 8, 16, and 32 bit buses
 *
 */

#ifndef MEMMAP_HPP_
#define MEMMAP_HPP_

// Uncomment to add debug trace
//#define MEMMAP_DEBUG

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sys/mman.h>
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>   /* For open(), creat() */

#include <iostream>
#include <stdexcept>
#include <vector>

#include "Mutex.h"
#include "GlobalTypeDefs.h"

//=============================================================================================================
// CLASS
//=============================================================================================================
namespace Mplane {

//-------------------------------------------------------------------------------------------------------------
// Help class that sets the bus width code
template <typename T>
class MemMapBusWidth {
public:
	// Specifically do *NOT* define a code here so that we get a compiler error if we don't support the type
} ;

// specialise for know widths
template <>
class MemMapBusWidth<unsigned char> {
public:
	enum {code = 0} ;
} ;

template <>
class MemMapBusWidth<unsigned short> {
public:
	enum {code = 1} ;
} ;

template <>
class MemMapBusWidth<unsigned> {
public:
	enum {code = 2} ;
} ;


//-------------------------------------------------------------------------------------------------------------
/**
 * Basic template class - defaults to 8-bit bus width
 *
 * Does not have a mutex lock
 */

template <typename T>
class MemMapUnlock {
public:
	// BUG#845: Temp hack to enable debug
	enum MemCaptureType {
		MEM_NONE,
		MEM_READ,
		MEM_WRITE,
		MEM_RMW,
	};
	struct MemCapture {
		MemCapture() :
			mType(MEM_NONE),
			mOffset(0),
			mValue(0),
			mMask(0),
			mReadVal(0)
		{}

		MemCapture(MemCaptureType type, unsigned offset, unsigned value, unsigned mask, unsigned readVal=0) :
			mType(type),
			mOffset(offset),
			mValue(value),
			mMask(mask),
			mReadVal(readVal)
		{}

		MemCaptureType 	mType ;
		unsigned		mOffset ;
		unsigned		mValue ;
		unsigned		mMask ;
		unsigned		mReadVal ;
	};


	/**
	 * element_type	Template parameter (T), the type of the managed object
	 */
	typedef T element_type ;

	enum BusWidthCode {
		BUS_WIDTH_8		= 0,
		BUS_WIDTH_16	= 1,
		BUS_WIDTH_32	= 2,
	};

	/**
	 * Create the memory map
	 * @param address	Physical address to map
	 * @param size		Size of region to map (in bytes)
	 */
	MemMapUnlock(unsigned address, unsigned size, const std::string& device = "/dev/mem") :
		mDevice(device),
		mMap(0),
		mFd(-1),
		mAddr(address),
		mSize(size),
		mPAGESIZE(sysconf(_SC_PAGESIZE))
	{
		openMap() ;
	}

	/**
	 * Close down map - don't want to throw errors during destruction, just report them
	 */
	virtual ~MemMapUnlock()
	{
		if (mMap)
		{
			if (munmap(mMap, mSize) == -1)
				std::cerr << "Error un-mapping 0x" << std::hex << mAddr <<
					" of size 0x" << mSize << std::dec << std::endl ;
		}

		if (mFd > 0)
			close(mFd) ;
	}

	/**
	 * Read a value
	 * @param offset	Offset (from base address) in bytes
	 * @param mask		Mask value
	 * @return the read value masked
	 */
	virtual T readVal(unsigned offset, T mask = static_cast<T>(-1))
	{
		// divide the offset by the appropriate value for this bus width
		offset >>= MemMapBusWidth<T>::code ;

		// read the value
		T current = *(mMap + offset) ;

#ifdef MEMMAP_DEBUG
		// BUG#845: Temp hack to enable debug
		if (debug)
			trace.push_back( MemCapture(MEM_READ, offset, current, mask) ) ;
//			printf("MEM: READ 0x%05x => 0x%04x\n", offset<<MemMapBusWidth<T>::code, current&mask) ;
#endif

		// return value masked
		return(current & mask) ;
	}

	/**
	 * Read-Modify-Write a value
	 * @param offset	Offset (from base address) in bytes
	 * @param value		Value to write
	 * @param mask		Mask value
	 * @return the modified value
	 */
	virtual T modifyVal(unsigned offset, T value, T mask = static_cast<T>(-1))
	{
		// divide the offset by the appropriate value for this bus width
		offset >>= MemMapBusWidth<T>::code ;

		// If mask covers all bits, then just write
		T newVal(value & mask) ;
		if (mask == static_cast<T>(-1))
		{
			// write the new value
			*(mMap + offset) = newVal ;
		}
		else
		{
			// read the value
			T current = *(mMap + offset) ;

			// modify / write the new value
			newVal |= (current & ~mask) ;
			*(mMap + offset) = newVal ;
		}

#ifdef MEMMAP_DEBUG
		// BUG#845: Temp hack to enable debug
		if (debug)
			trace.push_back( MemCapture(MEM_RMW, offset, value, mask, newVal) ) ;
//			printf("MEM: WRITE 0x%05x <= 0x%04x / 0x%04x (MODIFY 0x%04x)\n",
//					offset<<MemMapBusWidth<T>::code, value, mask, newVal) ;
#endif

		// return new value
		return (newVal) ;
	}

	/**
	 * Write a value
	 * @param offset	Offset (from base address) in bytes
	 * @param value		Value to write
	 * @param mask		Mask value
	 */
	virtual void writeVal(unsigned offset, T value, T mask = static_cast<T>(-1))
	{
		// divide the offset by the appropriate value for this bus width
		offset >>= MemMapBusWidth<T>::code ;

		// modify / write the new value
		*(mMap + offset) = (value & mask) ;

#ifdef MEMMAP_DEBUG
		// BUG#845: Temp hack to enable debug
		if (debug)
			trace.push_back( MemCapture(MEM_WRITE, offset, value, mask) ) ;
//			printf("MEM: WRITE 0x%05x <= 0x%04x / 0x%04x\n", offset, value, mask) ;
#endif
	}

#ifdef MEMMAP_DEBUG
	// BUG#845: Temp hack to enable debug
	static bool debug ;
	static std::vector< typename MemMapUnlock<T>::MemCapture > trace ;

	static void dumpTrace(void)
	{
		std::cout << std::endl << "==============================" << std::endl ;
		std::cout << "Memory Access Trace : " << trace.size() << " accesses" << std::endl ;
		unsigned numAccesses = 0 ;
		typename std::vector< MemMapUnlock<T>::MemCapture >::iterator iter ;
		for (iter = trace.begin(); iter != trace.end(); ++iter)
		{
			if (iter->mType == MEM_NONE)
			{
				break ;
			}
			else if (iter->mType == MEM_WRITE)
			{
				printf("[%3u] MEM: WRITE 0x%05x <= 0x%04x / 0x%04x\n", numAccesses,
						iter->mOffset<<MemMapBusWidth<T>::code, iter->mValue, iter->mMask);
			}
			else if (iter->mType == MEM_RMW)
			{
				printf("[%3u] MEM: WRITE 0x%05x <= 0x%04x / 0x%04x (MODIFY 0x%04x)\n", numAccesses,
						iter->mOffset<<MemMapBusWidth<T>::code, iter->mValue, iter->mMask,
						iter->mReadVal);
			}
			else // READ
			{
				printf("[%3u] MEM: READ 0x%05x => 0x%04x / 0x%04x\n", numAccesses,
						iter->mOffset<<MemMapBusWidth<T>::code, iter->mValue, iter->mMask) ;
			}
			++numAccesses ;
		}
		std::cout << std::endl << "==============================" << std::endl ;
	}
#endif

private:
	/**
	 * Private method for actually opening the devices - used to make specialisation easier
	 */
	void openMap(void)
	{
		/* open /dev/mem and error checking */
		mFd = open( mDevice.c_str(), O_RDWR | O_SYNC );

		if (mFd < 0)
		{
			throw std::runtime_error("Unable to open memory device") ;
		}

		// Ensure address is page aligned
		mAddr = (mAddr / mPAGESIZE) * mPAGESIZE ;

		/* mmap() the opened /dev/mem */
		mMap = static_cast<T *>( mmap(0, mSize, PROT_READ|PROT_WRITE, MAP_SHARED, mFd, mAddr) );
		if (!mMap)
		{
			close(mFd) ;
			throw std::runtime_error("Unable to map memory region") ;
		}
	}

private:
    // Name of device file to open
	const std::string mDevice ;

	// The map pointer of correct bus width
	T*	mMap ;

	// file handle to memory device
	int mFd ;

	// Physical address
	unsigned mAddr ;

	// Mapped size
	unsigned mSize ;

	// (fixed) page size
	unsigned mPAGESIZE ;
} ;

#ifdef MEMMAP_DEBUG

// BUG#845: Temp hack to enable debug
template <typename T> bool MemMapUnlock<T>::debug = false ;
template <typename T> std::vector< typename MemMapUnlock<T>::MemCapture > MemMapUnlock<T>::trace ;

#endif

//-------------------------------------------------------------------------------------------------------------
/**
 * Template class - defaults to 8-bit bus width
 *
 * Derived from base class. Adds mutex locking on all methods to ensure each method is atomic
 */

template <typename T>
class MemMap : public MemMapUnlock<T> {
public:

	typedef MemMapUnlock<T> super ;

	/**
	 * element_type	Template parameter (T), the type of the managed object
	 */
	typedef T element_type ;



	/**
	 * Create the memory map
	 * @param address	Physical address to map
	 * @param size		Size of region to map (in bytes)
	 */
	MemMap(unsigned address, unsigned size, const std::string& device = "/dev/mem") :
		MemMapUnlock<T>(address, size, device),
		mAccessMutex()
	{
	}

	/**
	 * Close down map - don't want to throw errors during destruction, just report them
	 */
	~MemMap()
	{
	}

	/**
	 * Read a value
	 * @param offset	Offset (from base address) in bytes
	 * @param mask		Mask value
	 * @return the read value masked
	 */
	T readVal(unsigned offset, T mask = static_cast<T>(-1))
	{
		Mutex::Lock lock( mAccessMutex );  // use the Mutex lock guard here

		// forward method
		return this->super::readVal(offset, mask) ;
	}

	/**
	 * Read-Modify-Write a value
	 * @param offset	Offset (from base address) in bytes
	 * @param value		Value to write
	 * @param mask		Mask value
	 * @return the modified value
	 */
	T modifyVal(unsigned offset, T value, T mask = static_cast<T>(-1))
	{
		Mutex::Lock lock( mAccessMutex );  // use the Mutex lock guard here

		// forward method
		return this->super::modifyVal(offset, value, mask) ;
	}

	/**
	 * Write a value
	 * @param offset	Offset (from base address) in bytes
	 * @param value		Value to write
	 * @param mask		Mask value
	 */
	void writeVal(unsigned offset, T value, T mask = static_cast<T>(-1))
	{
		Mutex::Lock lock( mAccessMutex );  // use the Mutex lock guard here

		// forward method
		this->super::writeVal(offset, value, mask) ;
	}

private:
    /*!
     *  Mutex used to protect the memory map - ensures read-modify-write is stomic
     */
    Mutex mAccessMutex ;
} ;



}

#endif /* MEMMAP_HPP_ */
