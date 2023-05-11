/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Crypt.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>

#include "ByteTransfer.hpp"
#include "Crypt.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
static const uint32_t DELTA{0x9E3779B9} ;
static const unsigned NUM_ROUNDS{32} ;	// recommended
static const uint32_t CRYPT_MAGIC{0x43727970} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Crypt::Crypt(uint32_t key[4]) :
	mKey{key[0], key[1], key[2], key[3]}
{
}

//-------------------------------------------------------------------------------------------------------------
Crypt::Crypt(std::vector<uint32_t> key) :
	mKey{key[0], key[1], key[2], key[3]}
{

}

//-------------------------------------------------------------------------------------------------------------
Crypt::~Crypt()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::Crypt::encrypt(uint32_t data[2])
{
	encipher(NUM_ROUNDS, data, mKey) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::Crypt::decrypt(uint32_t data[2])
{
	decipher(NUM_ROUNDS, data, mKey) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Crypt::encrypt(const std::vector<uint8_t>& inData, std::vector<uint8_t>& outData)
{
	return encrypt(inData.begin(), inData.end(), outData) ;
}

//-------------------------------------------------------------------------------------------------------------
bool Crypt::decrypt(const std::vector<uint8_t>& inData, std::vector<uint8_t>& outData)
{
	return decrypt(inData.begin(), inData.end(), outData) ;
}


//-------------------------------------------------------------------------------------------------------------
bool Mplane::Crypt::encrypt(std::vector<uint8_t>::const_iterator inDataStart,
		std::vector<uint8_t>::const_iterator inDataEnd,
		std::vector<uint8_t>& outData)
{
//printf("encrypt: key 0x%08x 0x%08x 0x%08x 0x%08x \n", mKey[0], mKey[1], mKey[2], mKey[3]) ;

	// Need to 1. Add a header to the data (with magic & original length), 2. pad to next 64 bit
	uint32_t inSize( std::distance(inDataStart, inDataEnd) ) ;
	unsigned outSize( outData.size() + ((inSize+8 +7) / 8 * 8) ) ;
	unsigned outIdx=outData.size() ;

	outData.resize( outSize ) ;

	// Start by encrypting the MAGIC and length words
	{
		uint32_t v[2] = { CRYPT_MAGIC, inSize } ;

		encipher(NUM_ROUNDS, v, mKey) ;

		ByteTransfer::writeWord(outIdx, outData, v[0]) ;
		ByteTransfer::writeWord(outIdx, outData, v[1]) ;
	}

	// works on 64 bits at a time - pad with zeroes
	while (inDataStart != inDataEnd)
	{
		uint32_t v[2] = { ByteTransfer::readWord(inDataStart, inDataEnd), ByteTransfer::readWord(inDataStart, inDataEnd) } ;

		encipher(NUM_ROUNDS, v, mKey) ;

		ByteTransfer::writeWord(outIdx, outData, v[0]) ;
		ByteTransfer::writeWord(outIdx, outData, v[1]) ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::Crypt::decrypt(std::vector<uint8_t>::const_iterator inDataStart,
		std::vector<uint8_t>::const_iterator inDataEnd,
		std::vector<uint8_t>& outData)
{
//printf("decrypt: key 0x%08x 0x%08x 0x%08x 0x%08x \n", mKey[0], mKey[1], mKey[2], mKey[3]) ;

	// Ensure the data contains:
	// 1. any header
	// 2. the magic number + original data size
	// 3. Some data
	unsigned outIdx=outData.size() ;

	// Need to extract the MAGIC & original size
	unsigned dataSize ;
	{
		uint32_t v[2] = { ByteTransfer::readWord(inDataStart, inDataEnd), ByteTransfer::readWord(inDataStart, inDataEnd) } ;

//		printf(" * v[0] = 0x%08x v[1] = 0x%08x\n", v[0], v[1]) ;

		decipher(NUM_ROUNDS, v, mKey) ;

//		printf(" * decrypted: v[0] = 0x%08x v[1] = 0x%08x\n", v[0], v[1]) ;

		uint32_t inSize( std::distance(inDataStart, inDataEnd) ) ;

		if (v[0] != CRYPT_MAGIC)
		{
			std::cerr << "Invalid magic = 0x" << std::hex << v[0] << std::dec << std::endl ;
			return false ;
		}
		if (v[1] > inSize)
		{
			std::cerr << "Invalid size = 0x" << std::hex << v[1] << std::dec << " In size=" << inSize << std::endl ;
			return false ;
		}

		dataSize = v[1] ;
	}

	// Resize based on original size
	unsigned outSize(dataSize + outData.size()) ;
	outData.resize( outSize ) ;

	// works on 64 bits at a time
	while (inDataStart != inDataEnd && outIdx < outSize)
	{
		uint32_t v[2] = { ByteTransfer::readWord(inDataStart, inDataEnd), ByteTransfer::readWord(inDataStart, inDataEnd) } ;

		decipher(NUM_ROUNDS, v, mKey) ;

		ByteTransfer::writeWord(outIdx, outData, v[0]) ;
		ByteTransfer::writeWord(outIdx, outData, v[1]) ;
	}

	return true ;
}




//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Crypt::encipher(unsigned int num_rounds, uint32_t v[2], uint32_t const key[4]) const
{
    unsigned int i;
    uint32_t v0=v[0], v1=v[1], sum=0, delta=DELTA;
    for (i=0; i < num_rounds; i++) {
        v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
        sum += delta;
        v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum>>11) & 3]);
    }
    v[0]=v0; v[1]=v1;
}

//-------------------------------------------------------------------------------------------------------------
void Crypt::decipher(unsigned int num_rounds, uint32_t v[2], uint32_t const key[4]) const
{
    unsigned int i;
    uint32_t v0=v[0], v1=v[1], delta=DELTA, sum=delta*num_rounds;
    for (i=0; i < num_rounds; i++) {
        v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum>>11) & 3]);
        sum -= delta;
        v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
    }
    v[0]=v0; v[1]=v1;
}
