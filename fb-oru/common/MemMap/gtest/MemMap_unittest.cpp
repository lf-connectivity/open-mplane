/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MemMap_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include <typeinfo>
#include <string>
#include <iostream>
#include <vector>

#include <numeric>
#include <functional>
#include <algorithm>

#include "MemMap.hpp"

using namespace std;
using namespace Mplane;


//------------------------------------------------------------------------------------------------------------------------
// Test fixture
class MemMapTests : public ::testing::Test
{
public:

    /*! @brief Setup the test
     */
    virtual void SetUp()
    {
        const ::testing::TestInfo* const test_info =
          ::testing::UnitTest::GetInstance()->current_test_info();

        cout << endl << "*** " << test_info->test_case_name() << " Tests ***" <<  endl;
        cout << test_info->name() << " - START" <<  endl;

    }

    /*! @brief Tear down the test
     */
    virtual void TearDown()
    {

    }

};



//========================================================================================================================
// TESTS
//========================================================================================================================


//------------------------------------------------------------------------------------------------------------------------
TEST_F(MemMapTests, bus8)
{
	MemMap<unsigned char> memmap(0, 4, "../../../MemMap/gtest/test/mapfile.bin") ;

	// write
	memmap.writeVal(0x0, 0xde) ;
	memmap.writeVal(0x1, 0xad) ;
	memmap.writeVal(0x2, 0xfe) ;
	memmap.writeVal(0x3, 0xed) ;

	// read
	EXPECT_EQ(0xfe, memmap.readVal(0x2)) ;
	EXPECT_EQ(0xed, memmap.readVal(0x3)) ;
	EXPECT_EQ(0xde, memmap.readVal(0x0)) ;
	EXPECT_EQ(0xad, memmap.readVal(0x1)) ;

	// rmw
	memmap.modifyVal(0x0, 0x01, 0x0f) ;
	memmap.modifyVal(0x1, 0x23, 0xf0) ;
	memmap.modifyVal(0x2, 0x45, 0x3c) ;
	memmap.modifyVal(0x3, 0x67, 0xc3) ;

	EXPECT_EQ(0xd1, memmap.readVal(0x0)) ;
	EXPECT_EQ(0x2d, memmap.readVal(0x1)) ;
	EXPECT_EQ(0xc6, memmap.readVal(0x2)) ;
	EXPECT_EQ(0x6f, memmap.readVal(0x3)) ;

	// clean up
	memmap.writeVal(0x0, 0x20) ;
	memmap.writeVal(0x1, 0x20) ;
	memmap.writeVal(0x2, 0x20) ;
	memmap.writeVal(0x3, 0x20) ;
}

//------------------------------------------------------------------------------------------------------------------------
TEST_F(MemMapTests, bus16)
{
	MemMap<unsigned short> memmap(0, 16, "../../../MemMap/gtest/test/mapfile.bin") ;

#ifdef MEMMAP_DEBUG
	MemMap<unsigned short>::debug = true ;
#endif

	// write
	memmap.writeVal(0x0, 0xdead) ;
	memmap.writeVal(0x2, 0xfeed) ;
	memmap.writeVal(0x4, 0xc0ff) ;
	memmap.writeVal(0x6, 0xbeef) ;

	// read
	EXPECT_EQ(0xc0ff, memmap.readVal(0x4)) ;
	EXPECT_EQ(0xbeef, memmap.readVal(0x6)) ;
	EXPECT_EQ(0xdead, memmap.readVal(0x0)) ;
	EXPECT_EQ(0xfeed, memmap.readVal(0x2)) ;

	// rmw
	memmap.modifyVal(0x0, 0x0123, 0x000f) ;
	memmap.modifyVal(0x2, 0x4567, 0x00f0) ;
	memmap.modifyVal(0x4, 0x89ab, 0x0f00) ;
	memmap.modifyVal(0x6, 0xcdef, 0xf000) ;

	EXPECT_EQ(0xdea3, memmap.readVal(0x0)) ;
	EXPECT_EQ(0xfe6d, memmap.readVal(0x2)) ;
	EXPECT_EQ(0xc9ff, memmap.readVal(0x4)) ;
	EXPECT_EQ(0xceef, memmap.readVal(0x6)) ;

	// rmw
	memmap.modifyVal(0x0, 0x0000, 0xffff) ;
	memmap.modifyVal(0x2, 0xffff, 0xffff) ;
	memmap.modifyVal(0x4, 0x0000, 0xffff) ;
	memmap.modifyVal(0x6, 0xffff, 0xffff) ;

	EXPECT_EQ(0x0000, memmap.readVal(0x0)) ;
	EXPECT_EQ(0xffff, memmap.readVal(0x2)) ;
	EXPECT_EQ(0x0000, memmap.readVal(0x4)) ;
	EXPECT_EQ(0xffff, memmap.readVal(0x6)) ;

	// clean up
	memmap.writeVal(0x0, 0x2020) ;
	memmap.writeVal(0x2, 0x2020) ;
	memmap.writeVal(0x4, 0x2020) ;
	memmap.writeVal(0x6, 0x2020) ;

	EXPECT_EQ(0x2020, memmap.readVal(0x0)) ;
	EXPECT_EQ(0x2020, memmap.readVal(0x2)) ;
	EXPECT_EQ(0x2020, memmap.readVal(0x4)) ;
	EXPECT_EQ(0x2020, memmap.readVal(0x6)) ;

#ifdef MEMMAP_DEBUG
	MemMap<unsigned short>::dumpTrace() ;
#endif
}

//------------------------------------------------------------------------------------------------------------------------
TEST_F(MemMapTests, bus32)
{
	MemMap<unsigned> memmap(0, 32, "../../../MemMap/gtest/test/mapfile.bin") ;

	// write
	memmap.writeVal(0x0, 0xdeadbeef) ;
	memmap.writeVal(0x4, 0xfeedface) ;
	memmap.writeVal(0x8, 0xc0ffee11) ;
	memmap.writeVal(0xc, 0xf00d1ace) ;

	// read
	EXPECT_EQ(0xdeadbeef, memmap.readVal(0x0)) ;
	EXPECT_EQ(0xfeedface, memmap.readVal(0x4)) ;
	EXPECT_EQ(0xc0ffee11, memmap.readVal(0x8)) ;
	EXPECT_EQ(0xf00d1ace, memmap.readVal(0xc)) ;

	// rmw
	memmap.modifyVal(0x0, 0x12345678, 0x0f0f0f0f) ;
	memmap.modifyVal(0x4, 0x9abcdef0, 0xf0f0f0f0) ;
	memmap.modifyVal(0x8, 0x87654321, 0xff0f0fff) ;
	memmap.modifyVal(0xc, 0x0fedcba9, 0x00ffff00) ;

	EXPECT_EQ(0xd2a4b6e8, memmap.readVal(0x0)) ;
	EXPECT_EQ(0x9ebddafe, memmap.readVal(0x4)) ;
	EXPECT_EQ(0x87f5e321, memmap.readVal(0x8)) ;
	EXPECT_EQ(0xf0edcbce, memmap.readVal(0xc)) ;

	// clean up
	memmap.writeVal(0x0, 0x20202020) ;
	memmap.writeVal(0x4, 0x20202020) ;
	memmap.writeVal(0x8, 0x20202020) ;
	memmap.writeVal(0xc, 0x20202020) ;
}
