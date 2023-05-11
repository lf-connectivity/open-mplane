/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      minilzo_unittest.cpp
 * \brief     Google Test of minilzo
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the minilzo class.
 *
 */

#include <gtest/gtest.h>

#include <string>
#include <iostream>

#include <memory>

#if 0
#ifdef OFF_TARGET
#include "Path.h"
#endif
#endif

#include "minilzo.h"

#include "Lzo.h"

using namespace Mplane ;

/* We want to compress the data block at 'in' with length 'IN_LEN' to
 * the block at 'out'. Because the input block may be incompressible,
 * we must provide a little more output space in case that compression
 * is not possible.
 */

#define IN_LEN      (128*1024ul)
#define OUT_LEN     (IN_LEN + IN_LEN / 16 + 64 + 3)

static unsigned char __LZO_MMODEL in  [ IN_LEN ];
static unsigned char __LZO_MMODEL out [ OUT_LEN ];

unsigned char __LZO_MMODEL in2  [ 2 * 614400 ];
unsigned char __LZO_MMODEL out2 [ 2 * 614400 ];


/* Work-memory needed for compression. Allocate memory in units
 * of 'lzo_align_t' (instead of 'char') to make sure it is properly aligned.
 */

#define HEAP_ALLOC(var,size) \
    lzo_align_t __LZO_MMODEL var [ ((size) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t) ]

static HEAP_ALLOC(wrkmem, LZO1X_1_MEM_COMPRESS);




//-------------------------------------------------------------------------------------------------------------
TEST(minilzo, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    int r;
    lzo_uint in_len;
    lzo_uint out_len;
    lzo_uint new_len;

    printf("\nLZO real-time data compression library (v%s, %s).\n",
           lzo_version_string(), lzo_version_date());
    printf("Copyright (C) 1996-2015 Markus Franz Xaver Johannes Oberhumer\nAll Rights Reserved.\n\n");


/*
 * Step 1: initialize the LZO library
 */
    r = lzo_init() ;
    EXPECT_EQ(LZO_E_OK, r) ;

    if (r != LZO_E_OK)
    {
        printf("internal error - lzo_init() failed !!!\n");
        printf("(this usually indicates a compiler bug - try recompiling\nwithout optimizations, and enable '-DLZO_DEBUG' for diagnostics)\n");
        return ;
    }

/*
 * Step 2: prepare the input block that will get compressed.
 *         We just fill it with zeros in this example program,
 *         but you would use your real-world data here.
 */
    in_len = IN_LEN;
    lzo_memset(in,0,in_len);

/*
 * Step 3: compress from 'in' to 'out' with LZO1X-1
 */
    r = lzo1x_1_compress(in,in_len,out,&out_len,wrkmem);
    EXPECT_EQ(LZO_E_OK, r) ;
    if (r == LZO_E_OK)
        printf("compressed %lu bytes into %lu bytes\n",
            (unsigned long) in_len, (unsigned long) out_len);
    else
    {
        /* this should NEVER happen */
        printf("internal error - compression failed: %d\n", r);
        return ;
    }

    EXPECT_TRUE(out_len < in_len) ;

    /* check for an incompressible block */
    if (out_len >= in_len)
    {
        printf("This block contains incompressible data.\n");
        return ;
    }

/*
 * Step 4: decompress again, now going from 'out' to 'in'
 */
    new_len = in_len;
    r = lzo1x_decompress(out,out_len,in,&new_len,NULL);
    EXPECT_EQ(LZO_E_OK, r) ;
    if (r == LZO_E_OK && new_len == in_len)
        printf("decompressed %lu bytes back into %lu bytes\n",
            (unsigned long) out_len, (unsigned long) in_len);
    else
    {
        /* this should NEVER happen */
        printf("internal error - decompression failed: %d\n", r);
        return ;
    }

    printf("\nminiLZO simple compression test passed.\n");

}




#if 0
#ifdef OFF_TARGET

//-------------------------------------------------------------------------------------------------------------
TEST(minilzo, Wave1)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    int r;

    printf("\nLZO real-time data compression library (v%s, %s).\n",
           lzo_version_string(), lzo_version_date());
    printf("Copyright (C) 1996-2015 Markus Franz Xaver Johannes Oberhumer\nAll Rights Reserved.\n\n");


/*
 * Step 1: initialize the LZO library
 */
    r = lzo_init() ;
    EXPECT_EQ(LZO_E_OK, r) ;

    if (r != LZO_E_OK)
    {
        printf("internal error - lzo_init() failed !!!\n");
        printf("(this usually indicates a compiler bug - try recompiling\nwithout optimizations, and enable '-DLZO_DEBUG' for diagnostics)\n");
        return ;
    }

/*
 * Step 2: prepare the input block that will get compressed.
 *         We just fill it with zeros in this example program,
 *         but you would use your real-world data here.
 */
    std::string filename("../../../lzo/gtest/test/LTE_TDD38-1_10M_TM31_15.36MSPS.art") ;

    lzo_uint new_len;
    unsigned long in2_len = Path::fileSize(filename);
    unsigned long out2_len = (2*in2_len / 16) + 64 + 3 ;

//    unsigned char __LZO_MMODEL in2  [ 2 * in2_len ];
//    unsigned char __LZO_MMODEL out2 [ out2_len ];

std::cerr << "File " << filename << " size=" << in2_len << " buffer size=" << sizeof(in2) << std::endl ;

    std::ifstream file(filename, std::ios::binary);
    EXPECT_TRUE(file.read( (char *)in2, in2_len)) ;

/*
 * Step 3: compress from 'in2' to 'out2' with LZO1X-1
 */
    std::cerr << "Compressing..." << std::endl ;
    r = lzo1x_1_compress(in2,in2_len,out2,&out2_len,wrkmem);
    EXPECT_EQ(LZO_E_OK, r) ;
    if (r == LZO_E_OK)
        printf("compressed %lu bytes into %lu bytes\n",
            (unsigned long) in2_len, (unsigned long) out2_len);
    else
    {
        /* this should NEVER happen */
        printf("internal error - compression failed: %d\n", r);
        return ;
    }

    EXPECT_TRUE(out2_len < in2_len) ;

    /* check for an incompressible block */
    if (out2_len >= in2_len)
    {
        printf("This block contains incompressible data.\n");
        return ;
    }

/*
 * Step 4: decompress again, now going from 'out2' to 'in2'
 */
    std::cerr << "Decompressing..." << std::endl ;
    new_len = in2_len;
    r = lzo1x_decompress(out2,out2_len,in2,&new_len,NULL);
    EXPECT_EQ(LZO_E_OK, r) ;
    EXPECT_EQ(new_len, in2_len);
    if (r == LZO_E_OK && new_len == in2_len)
        printf("decompressed %lu bytes back into %lu bytes\n",
            (unsigned long) out2_len, (unsigned long) in2_len);
    else
    {
        /* this should NEVER happen */
        printf("internal error - decompression failed: %d\n", r);
        return ;
    }

    printf("\nminiLZO simple compression test passed.\n");

}


//-------------------------------------------------------------------------------------------------------------
TEST(minilzo, ClassWave1)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	// Create LZO on the heap
	std::shared_ptr<Lzo> lzo(std::make_shared<Lzo>()) ;

    std::string filename("../../../lzo/gtest/test/LTE_TDD38-1_10M_TM31_15.36MSPS.art") ;


    unsigned long in2_len = Path::fileSize(filename);
    std::vector<uint8_t> inData(in2_len) ;

std::cerr << "File " << filename << " size=" << in2_len << " buffer size=" << inData.size() << std::endl ;

    std::ifstream file(filename, std::ios::binary);
    EXPECT_TRUE(file.read( (char *)inData.data(), in2_len)) ;

/*
 * Step 3: compress from 'in2' to 'out2' with LZO1X-1
 */
    std::vector<uint8_t> outData ;

    std::cerr << "Compressing..." << std::endl ;

    bool ok = lzo->compress(inData, outData) ;
    EXPECT_TRUE(ok) ;

    if (ok)
        printf("compressed %lu bytes into %lu bytes\n",
            (unsigned long)inData.size(), (unsigned long)outData.size());
    else
    {
        /* this should NEVER happen */
        printf("internal error - compression failed\n");
        return ;
    }

    unsigned long out2_len = outData.size();
    EXPECT_TRUE(out2_len < in2_len) ;

    /* check for an incompressible block */
    if (out2_len >= in2_len)
    {
        printf("This block contains incompressible data.\n");
        return ;
    }

/*
 * Step 4: decompress again, now going from 'out2' to 'in2'
 */
    std::cerr << "Decompressing..." << std::endl ;

    std::vector<uint8_t> newData ;
    ok = lzo->decompress(outData, newData) ;
    EXPECT_TRUE(ok) ;
    lzo_uint new_len = newData.size();
    EXPECT_EQ(new_len, in2_len);

    if (ok && new_len == in2_len)
        printf("decompressed %lu bytes back into %lu bytes\n",
            (unsigned long) out2_len, (unsigned long) in2_len);
    else
    {
        /* this should NEVER happen */
        printf("internal error - decompression failed\n");
        return ;
    }

    printf("\nminiLZO simple compression test passed.\n");

}


//-------------------------------------------------------------------------------------------------------------
TEST(minilzo, ClassWaveIter)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	// Create LZO on the heap
	std::shared_ptr<Lzo> lzo(std::make_shared<Lzo>()) ;

    std::string filename("../../../lzo/gtest/test/LTE_TDD38-1_10M_TM31_15.36MSPS.art") ;


    unsigned long in2_len = Path::fileSize(filename);
    std::vector<uint8_t> inData(in2_len) ;

std::cerr << "File " << filename << " size=" << in2_len << " buffer size=" << inData.size() << std::endl ;

    std::ifstream file(filename, std::ios::binary);
    EXPECT_TRUE(file.read( (char *)inData.data(), in2_len)) ;

/*
 * Step 3: compress from 'in2' to 'out2' with LZO1X-1
 */
    std::vector<uint8_t> outData ;

    std::cerr << "Compressing..." << std::endl ;

    bool ok = lzo->compress(inData.begin(), inData.end(), outData) ;
    EXPECT_TRUE(ok) ;

    if (ok)
        printf("compressed %lu bytes into %lu bytes\n",
            (unsigned long)inData.size(), (unsigned long)outData.size());
    else
    {
        /* this should NEVER happen */
        printf("internal error - compression failed\n");
        return ;
    }

    unsigned long out2_len = outData.size();
    EXPECT_TRUE(out2_len < in2_len) ;

    /* check for an incompressible block */
    if (out2_len >= in2_len)
    {
        printf("This block contains incompressible data.\n");
        return ;
    }

/*
 * Step 4: decompress again, now going from 'out2' to 'in2'
 */
    std::cerr << "Decompressing..." << std::endl ;

    std::vector<uint8_t> newData ;
    ok = lzo->decompress(outData.begin(), outData.end(), newData) ;
    EXPECT_TRUE(ok) ;
    lzo_uint new_len = newData.size();
    EXPECT_EQ(new_len, in2_len);

    if (ok && new_len == in2_len)
        printf("decompressed %lu bytes back into %lu bytes\n",
            (unsigned long) out2_len, (unsigned long) in2_len);
    else
    {
        /* this should NEVER happen */
        printf("internal error - decompression failed\n");
        return ;
    }

    printf("\nminiLZO simple compression test passed.\n");

}



#endif
#endif
