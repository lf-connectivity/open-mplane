/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveMemMgr.h
 * \brief     Manages waveform memory
 *
 *
 * \details   Manages allocation and deallocation of waveform memory
 *
 */


#ifndef WAVEMEMMGR_H_
#define WAVEMEMMGR_H_

#include <list>

#include <memory>
#include "IWaveformMem.h"

namespace Mplane {

class WaveMemMgr {
public:
	enum {
		DEFAULT_MEMSIZE		= 32 * 1024 * 1024,
		DEFAULT_MEMSTART	= 8,
		DEFAULT_MEMALIGN	= 8,
	};
	WaveMemMgr(unsigned memorySize = DEFAULT_MEMSIZE, unsigned memoryStart = DEFAULT_MEMSTART,
			unsigned memoryAlignment = DEFAULT_MEMALIGN) ;
	virtual ~WaveMemMgr() ;

	/**
	 * Factory for creating/getting the singleton
	 * @param memorySize
	 * @param memoryStart
	 * @param memoryAlignment
	 * @return shared pointer to the singleton
	 */
	static std::shared_ptr<WaveMemMgr> getInstance(unsigned memorySize = DEFAULT_MEMSIZE,
			unsigned memoryStart = DEFAULT_MEMSTART,
			unsigned memoryAlignment = DEFAULT_MEMALIGN) ;

	/**
	 * Allocate a memory block of the specified size
	 * @param size	Memory size to allocate
	 * @return shared pointer to an allocated memory block (details in WaveformMem class). If unable to allocate then
	 * the shared pointer will point to NULL
	 */
	std::shared_ptr<IWaveformMem> allocate(unsigned size) ;

	/**
	 * Deallocate the allocated block
	 * @param waveMem	An allocated WaveformMem object
	 * @return true if successfully deallocated; false otherwise (e.g. if block already deallocated or is invalid)
	 */
	bool deallocate(const std::shared_ptr<IWaveformMem>& waveMem) ;

	/**
	 * Display the memory blocks
	 * @param os	Output stream
	 */
	void show(std::ostream& os = std::cout) const ;

	const unsigned getMemAlign() const {
		return mMemAlign;
	}

	const unsigned getMemSize() const {
		return mMemSize;
	}

	const unsigned getMemStart() const {
		return mMemStart;
	}

private:
	// Add a new WaveformMem object into the used list preserving the address order
	void addUsed(std::shared_ptr<IWaveformMem> waveMem) ;

	// Return a WaveformMem object into the free list preserving the address order
	// Also merge any adjacent free blocks
	void addFree(std::shared_ptr<IWaveformMem> waveMem) ;

private:
	// Total size of memory
	const unsigned mMemSize ;

	// First block starts at this offset
	const unsigned mMemStart ;

	// Must align all memory blocks to this size (for hardware reasons)
	const unsigned mMemAlign ;

	// List of free memory blocks
	std::list< std::shared_ptr<IWaveformMem> > mFreeList ;

	// List of allocated memory blocks
	std::list< std::shared_ptr<IWaveformMem> > mUsedList ;

} ;

}

#endif /* WAVEMEMMGR_H_ */
