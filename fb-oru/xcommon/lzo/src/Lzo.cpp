/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Lzo.cpp
 * \brief     Compression/decompression class using LZO
 *
 *
 * \details   C++ wrapper for minilzo (which implements LZO1X)
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>

#include "minilzo.h"

#include "Lzo.h"

using namespace Mplane;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Lzo::Lzo() :
	mWorkspace(LZO1X_1_MEM_COMPRESS),
	mDecompressionMinSize(0)
{
	init() ;
}

//-------------------------------------------------------------------------------------------------------------
Lzo::~Lzo()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Lzo::compress(const std::vector<uint8_t> inData, std::vector<uint8_t>& outData)
{
	return compress(inData.cbegin(), inData.cend(), outData) ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::Lzo::compress(std::vector<uint8_t>::const_iterator inDataStart,
		std::vector<uint8_t>::const_iterator inDataEnd,
		std::vector<uint8_t>& outData)
{
	unsigned inDataSize(std::distance(inDataStart, inDataEnd)) ;

	// Size the output
	lzo_uint outSize( compressedSize(inDataSize) ) ;
	uint8_t *buffer = (uint8_t *)malloc(outSize) ;
	if (!buffer)
		return false ;

//	std::cerr << "Lzo::compress : insize=" << inDataSize << " estimated outsize=" << outSize << std::endl ;

	// compress
    int rc = lzo1x_1_compress( &(*inDataStart), inDataSize, buffer, &outSize, mWorkspace.data());

    // Copy data
    outData.resize(outSize) ;
    uint8_t* outPtr(outData.data()) ;
    uint8_t* bptr(buffer) ;
    for (unsigned byte=0; byte < outSize; ++byte)
    {
    	*outPtr++ = *bptr++ ;
    }
    free(buffer) ;

//    if (rc != LZO_E_OK)
//    	std::cerr << "compress() error=" << rc << std::endl ;

    if (rc != LZO_E_OK)
    	return false ;

    return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Lzo::decompress(const std::vector<uint8_t> inData, std::vector<uint8_t>& outData)
{
	return decompress(inData.cbegin(), inData.cend(), outData) ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::Lzo::decompress(std::vector<uint8_t>::const_iterator inDataStart,
		std::vector<uint8_t>::const_iterator inDataEnd,
		std::vector<uint8_t>& outData)
{
	unsigned inDataSize(std::distance(inDataStart, inDataEnd)) ;

	// Size the output
	lzo_uint outSize( uncompressedSize(inDataSize) ) ;
	uint8_t *buffer = (uint8_t *)malloc(outSize) ;
	if (!buffer)
		return false ;

//	std::cerr << "Lzo::decompress : insize=" << inDataSize << " estimated outsize=" << outSize << std::endl ;

	// decompress
    int rc = lzo1x_decompress( &(*inDataStart), inDataSize, buffer, &outSize, mWorkspace.data());

    // Copy data
    outData.resize(outSize) ;
    uint8_t* outPtr(outData.data()) ;
    uint8_t* bptr(buffer) ;
    for (unsigned byte=0; byte < outSize; ++byte)
    {
    	*outPtr++ = *bptr++ ;
    }
    free(buffer) ;

//    if (rc != LZO_E_OK)
//    	std::cerr << "decompress() error=" << rc << std::endl ;

    if (rc != LZO_E_OK)
    	return false ;

    return true ;
}

//-------------------------------------------------------------------------------------------------------------
void Lzo::setBlockSize(unsigned size)
{
	mDecompressionMinSize = size ;
}


//=============================================================================================================
// PRIVATE STATIC
//=============================================================================================================

bool Lzo::mInit{false} ;

//-------------------------------------------------------------------------------------------------------------
bool Lzo::init()
{
	if (!mInit)
	{
		if (lzo_init() != LZO_E_OK)
		    return false ;

		mInit = true ;
	}

	return true ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
unsigned Lzo::compressedSize(unsigned uncompressedSize) const
{
	return ( uncompressedSize + (uncompressedSize/16) + 64 +3 ) ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned Lzo::uncompressedSize(unsigned compressedSize) const
{
	if (compressedSize > 67)
		compressedSize -= (64 + 3);

	// This is a rubbish estimate (even though it is based on the LZO documentation!)
	// They suggest ( (compressedSize -64 - 3) * 16 / 17 ) but that can give much too low a figure
	// Even doubling the number has lead to me seeing where we've been 30% out. If the size ends up too low then
	// we don't allocate enough work space in the output buffer and end up overflowing the buffer
	// with a fault.
	//
	// So for safety I'm multiplying this estimate by 8
	//
	unsigned decompressSize = ( 8 * ( compressedSize * 16 / 17 ) ) ;

	// Ensure we've calculated at least the minimum
	if (decompressSize < mDecompressionMinSize)
		decompressSize = mDecompressionMinSize ;

	return decompressSize ;
}
