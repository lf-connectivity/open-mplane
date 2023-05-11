/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveMemMgr.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <algorithm>
#include "WaveformMem.h"
#include "WaveMemMgr.h"

using namespace Mplane;


//=============================================================================================================
// SINGLETON
//=============================================================================================================
std::shared_ptr<WaveMemMgr> WaveMemMgr::getInstance(unsigned memorySize, unsigned memoryStart, unsigned memoryAlignment)
{
	static std::shared_ptr<WaveMemMgr> instance(new WaveMemMgr(memorySize, memoryStart, memoryAlignment)) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
WaveMemMgr::WaveMemMgr(unsigned memorySize, unsigned memoryStart, unsigned memoryAlignment) :
	mMemSize(memorySize),
	mMemStart(memoryStart),
	mMemAlign(memoryAlignment),
	mFreeList(),
	mUsedList()
{
	// Create a free block of the usable memory
	mFreeList.push_back( std::shared_ptr<IWaveformMem>(new WaveformMem(mMemStart, mMemSize-mMemStart)) ) ;

	// If we're not starting at 0, the "allocate" a block to use up that space so it never get's allocated
	if (mMemStart > 0)
	{
		mUsedList.push_back( std::shared_ptr<IWaveformMem>(new WaveformMem(0, mMemStart)) ) ;
	}

}

//-------------------------------------------------------------------------------------------------------------
WaveMemMgr::~WaveMemMgr()
{
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IWaveformMem> WaveMemMgr::allocate(unsigned size)
{
	// Skip 0 length
	if (size == 0)
		return std::shared_ptr<IWaveformMem>() ;

	// Adjust size to match alignment
	if (mMemAlign)
		size = ((size + mMemAlign - 1) / mMemAlign) * mMemAlign ;

	// Search free list for the smallest block that we can fit this request into
	std::list< std::shared_ptr<IWaveformMem> >::iterator freeIter(mFreeList.begin()) ;
	std::list< std::shared_ptr<IWaveformMem> >::iterator smallestIter(mFreeList.end()) ;
	for(; freeIter != mFreeList.end(); ++freeIter)
	{
		if (smallestIter == mFreeList.end())
		{
			// init
			smallestIter = freeIter ;
		}
		else if ((*freeIter)->size() >= size)
		{
			if ((*smallestIter)->size() > (*freeIter)->size())
			{
				// This block can contain request and it is the smallest found so far
				smallestIter = freeIter ;
			}
		}
	}

	// At this stage, if smallest block is not set then we can't allocate
	if (smallestIter == mFreeList.end())
		return std::shared_ptr<IWaveformMem>() ;

	// Get the free block from the free list
	std::shared_ptr<IWaveformMem> freeBlock(*smallestIter) ;
	freeIter = mFreeList.erase(smallestIter) ;

	// if requested size matches size of free block, then just transfer to the used list
	std::shared_ptr<IWaveformMem> usedBlock ;
	if (size == freeBlock->size())
	{
		usedBlock = freeBlock ;
		addUsed(usedBlock) ;
	}
	else
	{
		// need to split the free block, remove used portion from the start and return the rest as free
		usedBlock = std::shared_ptr<IWaveformMem>(new WaveformMem(freeBlock->start(), size)) ;
		std::shared_ptr<IWaveformMem> newFreeBlock(new WaveformMem(usedBlock->end()+1, freeBlock->size() - size)) ;

		// add used
		addUsed(usedBlock) ;

		// put remaining back
		mFreeList.insert(freeIter, newFreeBlock) ;
	}

	return usedBlock ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveMemMgr::deallocate(const std::shared_ptr<IWaveformMem>& waveMem)
{
	// Check memory block is valid
	if (waveMem.get() == 0)
		return false ;

	// See if we can find it in the used list
	std::list< std::shared_ptr<IWaveformMem> >::iterator usedIter(
		std::find_if(mUsedList.begin(), mUsedList.end(), WaveformMemPtrFind(waveMem) )
	) ;

	// if we can't find the entry then stop
	if (usedIter == mUsedList.end())
		return false ;

	// Return the used memory back to the free list
	mUsedList.erase(usedIter) ;
	addFree(waveMem) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void WaveMemMgr::show(std::ostream& os) const
{
	{
		os << "----------------------" << std::endl ;
		os << "Free list:" << std::endl ;
		for (std::list< std::shared_ptr<IWaveformMem> >::const_iterator freeIter(mFreeList.begin()); freeIter != mFreeList.end(); ++freeIter)
		{
			os  << std::hex << "0x" << (*freeIter)->start() << " .. 0x" << (*freeIter)->end() << std::dec << std::endl ;
		}

		os << "Used list:" << std::endl ;
		for (std::list< std::shared_ptr<IWaveformMem> >::const_iterator usedIter(mUsedList.begin()); usedIter != mUsedList.end(); ++usedIter)
		{
			os  << std::hex << "0x" << (*usedIter)->start() << " .. 0x" << (*usedIter)->end() << std::dec << std::endl ;
		}
		os << "----------------------" << std::endl ;
	}

	unsigned addr = 0 ;

	std::list< std::shared_ptr<IWaveformMem> >::const_iterator freeIter(mFreeList.begin()) ;
	std::list< std::shared_ptr<IWaveformMem> >::const_iterator usedIter(mUsedList.begin()) ;

	while (freeIter != mFreeList.end() || usedIter != mUsedList.end())
	{
		unsigned nextAddr = 0 ;

		if (freeIter != mFreeList.end())
		{
			if ((*freeIter)->start() == addr)
			{
				os  << std::hex << "FREE 0x" << (*freeIter)->start() << " .. 0x" << (*freeIter)->end() << std::dec << std::endl ;
				nextAddr = (*freeIter)->end() + 1 ;
				++freeIter ;
			}
		}


		if (usedIter != mUsedList.end())
		{
			if ((*usedIter)->start() == addr)
			{
				if (nextAddr != 0)
				{
					os  << std::hex << "!!ERROR: USED overlap at 0x" << addr << " .. 0x" << (*usedIter)->end() << std::dec << std::endl ;
				}
				else
				{
					if ((*usedIter)->start() >= mMemStart)
						os  << "*USED*" ;
					else
						os  << "(RESERVED)" ;

					os  << std::hex << " 0x" << (*usedIter)->start() << " .. 0x" << (*usedIter)->end() << std::dec << std::endl ;
				}
				nextAddr = (*usedIter)->end() + 1 ;
				++usedIter ;
			}
		}

		if (nextAddr == 0)
		{
			os  << std::hex << "!!ERROR: No block at 0x" << addr << std::dec << std::endl ;
			return ;
		}

		addr = nextAddr ;
	}
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void WaveMemMgr::addUsed(std::shared_ptr<IWaveformMem> waveMem)
{
	std::list< std::shared_ptr<IWaveformMem> >::iterator usedIter(mUsedList.begin()) ;
	std::list< std::shared_ptr<IWaveformMem> >::iterator insertIter(mUsedList.begin()) ;
	for(; usedIter != mUsedList.end(); ++usedIter)
	{
		if ( (*usedIter)->start() < waveMem->start() )
			insertIter = usedIter ;

		else
			// gone past insertion point so stop
			break ;
	}

	// insert after this element
	mUsedList.insert(++insertIter, waveMem) ;
}

//-------------------------------------------------------------------------------------------------------------
void WaveMemMgr::addFree(std::shared_ptr<IWaveformMem> waveMem)
{
	std::list< std::shared_ptr<IWaveformMem> >::iterator freeIter(mFreeList.begin()) ;
	std::list< std::shared_ptr<IWaveformMem> >::iterator insertIter(mFreeList.end()) ;
	std::list< std::shared_ptr<IWaveformMem> >::iterator prevIter(mFreeList.end()) ;
	for(; freeIter != mFreeList.end(); ++freeIter)
	{
		if ( (*freeIter)->start() < waveMem->start() )
		{
			prevIter = freeIter ;

			insertIter = prevIter ;
			++insertIter ;
		}
		else
		{
			// insertion point so stop
			insertIter = freeIter ;
			break ;
		}
	}

	// Check for merge of this newly free block with the previous block
	if (prevIter != mFreeList.end())
	{
		// Check to see if the end of the block aligns with the start of the new block
		if ( (*prevIter)->end()+1 == waveMem->start() )
		{
			// Merge the blocks and remove the old previous block from the list
			std::shared_ptr<IWaveformMem> prevMem(*prevIter) ;
			mFreeList.erase(prevIter) ;
			waveMem = std::shared_ptr<IWaveformMem>(new WaveformMem(prevMem->start(), prevMem->size() + waveMem->size())) ;
		}
	}

	// Check for merge of this newly free block with the block that follows it
	if (insertIter != mFreeList.end())
	{
		// Check to see if the end of the new block aligns with the start of the following block
		if ( waveMem->end()+1 == (*insertIter)->start() )
		{
			// Merge the blocks and remove the old previous block from the list
			std::shared_ptr<IWaveformMem> nextMem(*insertIter) ;
			insertIter = mFreeList.erase(insertIter) ;
			waveMem = std::shared_ptr<IWaveformMem>(new WaveformMem(waveMem->start(), waveMem->size() + nextMem->size())) ;
		}
	}

	// Can now insert the possibly merged new block into the insertion point
	mFreeList.insert(insertIter, waveMem) ;
}
