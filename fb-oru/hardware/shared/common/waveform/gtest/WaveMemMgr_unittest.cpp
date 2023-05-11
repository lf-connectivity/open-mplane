/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveMemMgr_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "model_fixture.h"

#include "Waveform.h"
#include "WaveformMem.h"
#include "WaveformHardware.h"
#include "WaveMemMgr.h"

using namespace Mplane;

//===================================================================================================================
class WaveMemMgrTest : public ModelFixture {
};

//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
TEST_F(WaveMemMgrTest, Basic)
{
	WaveMemMgr memMgr ;
	memMgr.show() ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(WaveMemMgrTest, Singleton)
{
	std::shared_ptr<WaveMemMgr> memMgr(WaveMemMgr::getInstance()) ;
	memMgr->show() ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(WaveMemMgrTest, Alloc)
{
	WaveMemMgr memMgr ;

	std::shared_ptr<IWaveformMem> waveMem( memMgr.allocate(1024) ) ;
	EXPECT_TRUE(waveMem.get() != 0) ;

	if (waveMem.get() != 0)
		std::cerr << std::hex << "Allocated: 0x" << waveMem->start() << " .. 0x" << waveMem->end() << std::dec << std::endl ;

	memMgr.show() ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(WaveMemMgrTest, AllocSize)
{
	// size, start, align
	WaveMemMgr memMgr(72, 8, 8) ;

	std::shared_ptr<IWaveformMem> waveMem ;

	// no alloc
	waveMem = memMgr.allocate(0) ;
	EXPECT_TRUE(waveMem.get() == 0) ;

	std::cout << "after no alloc" << std::endl ;
	memMgr.show() ;

	// align to multiple of 8
	waveMem = memMgr.allocate(1) ;
	EXPECT_TRUE(waveMem->size() == 8) ;
	std::cout << "after alloc 1" << std::endl ;
	memMgr.show() ;

	waveMem = memMgr.allocate(2) ;
	EXPECT_TRUE(waveMem->size() == 8) ;
	std::cout << "after alloc 2" << std::endl ;
	memMgr.show() ;

	waveMem = memMgr.allocate(3) ;
	EXPECT_TRUE(waveMem->size() == 8) ;
	std::cout << "after alloc 3" << std::endl ;
	memMgr.show() ;

	waveMem = memMgr.allocate(4) ;
	EXPECT_TRUE(waveMem->size() == 8) ;
	std::cout << "after alloc 4" << std::endl ;
	memMgr.show() ;

	waveMem = memMgr.allocate(5) ;
	EXPECT_TRUE(waveMem->size() == 8) ;
	std::cout << "after alloc 5" << std::endl ;
	memMgr.show() ;

	waveMem = memMgr.allocate(6) ;
	EXPECT_TRUE(waveMem->size() == 8) ;
	std::cout << "after alloc 6" << std::endl ;
	memMgr.show() ;

	waveMem = memMgr.allocate(7) ;
	EXPECT_TRUE(waveMem->size() == 8) ;
	std::cout << "after alloc 7" << std::endl ;
	memMgr.show() ;

	waveMem = memMgr.allocate(8) ;
	EXPECT_TRUE(waveMem->size() == 8) ;
	std::cout << "after alloc 8" << std::endl ;
	memMgr.show() ;


	// Should now be full
	waveMem = memMgr.allocate(8) ;
	EXPECT_TRUE(waveMem.get() == 0) ;
	std::cout << "full" << std::endl ;
	memMgr.show() ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(WaveMemMgrTest, Dealloc)
{
	// size, start, align
	WaveMemMgr memMgr(72, 8, 8) ;

	std::cout << std::endl << "empty" << std::endl ;
	memMgr.show() ;

	std::shared_ptr<IWaveformMem> waveMem ;

	// Try to dealloc invalid
	std::shared_ptr<IWaveformMem> dummyMem ;
	EXPECT_FALSE(memMgr.deallocate(dummyMem));


	// Use some mem
	std::shared_ptr<IWaveformMem> waveMem0(memMgr.allocate(8)) ;
	std::shared_ptr<IWaveformMem> waveMem1(memMgr.allocate(8)) ;
	std::shared_ptr<IWaveformMem> waveMem2(memMgr.allocate(8)) ;
	std::shared_ptr<IWaveformMem> waveMem3(memMgr.allocate(8)) ;
	std::shared_ptr<IWaveformMem> waveMem4(memMgr.allocate(8)) ;
	std::shared_ptr<IWaveformMem> waveMem5(memMgr.allocate(8)) ;
	std::shared_ptr<IWaveformMem> waveMem6(memMgr.allocate(8)) ;
	std::shared_ptr<IWaveformMem> waveMem7(memMgr.allocate(8)) ;

	// Should now be full
	std::cout << std::endl << "full" << std::endl ;
	memMgr.show() ;

	// case1: new free between (begin) and (end)
	EXPECT_TRUE(memMgr.deallocate(waveMem1));
	std::cout << std::endl << "free block1" << std::endl ;
	memMgr.show() ;

	// case2a: new free between [block] and (end) - no merge
	EXPECT_TRUE(memMgr.deallocate(waveMem5));
	std::cout << std::endl << "free block5" << std::endl ;
	memMgr.show() ;

	// case2b: new free between [block] and (end) - merge
	EXPECT_TRUE(memMgr.deallocate(waveMem6));
	std::cout << std::endl << "free block6" << std::endl ;
	memMgr.show() ;

	// case3a: new free between [block] and [block] - no merge
	EXPECT_TRUE(memMgr.deallocate(waveMem3));
	std::cout << std::endl << "free block3" << std::endl ;
	memMgr.show() ;

	// case3b: new free between [block] and [block] - merge
	EXPECT_TRUE(memMgr.deallocate(waveMem2));
	std::cout << std::endl << "free block2" << std::endl ;
	memMgr.show() ;

	// Merge in 4
	EXPECT_TRUE(memMgr.deallocate(waveMem4));
	std::cout << std::endl << "free block4" << std::endl ;
	memMgr.show() ;

	// Merge in 0
	EXPECT_TRUE(memMgr.deallocate(waveMem0));
	std::cout << std::endl << "free block0" << std::endl ;
	memMgr.show() ;

	// Merge in 7
	EXPECT_TRUE(memMgr.deallocate(waveMem7));
	std::cout << std::endl << "free block7" << std::endl ;
	memMgr.show() ;
}
