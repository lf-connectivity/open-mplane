/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Crypt.h
 * \brief     Class used for encryption/decryption
 *
 *
 * \details   Encrypt/decrypt data using a 128-bit key
 *
 */


#ifndef CRYPT_H_
#define CRYPT_H_

#include <cstdint>
#include <vector>

namespace Mplane {

class Crypt {
public:
	explicit Crypt(uint32_t key[4]) ;
	explicit Crypt( std::vector<uint32_t> key ) ;
	virtual ~Crypt() ;

	/**
	 * Encrypt the input data (two 32-bit words) in-place
	 * @param data
	 */
	bool encrypt(uint32_t data[2]) ;

	/**
	 * Decrypt the input data (two 32-bit words) in-place
	 * @param data
	 */
	bool decrypt(uint32_t data[2]) ;


	/**
	 * Encrypt the input data
	 * @param inData
	 * @param outData
	 */
	bool encrypt(const std::vector<uint8_t>& inData, std::vector<uint8_t>& outData) ;

	/**
	 * Decrypt the input data
	 * @param inData
	 * @param outData
	 */
	bool decrypt(const std::vector<uint8_t>& inData, std::vector<uint8_t>& outData) ;

	/**
	 * Encrypt the input data
	 * @param inData
	 * @param outData
	 */
	bool encrypt(std::vector<uint8_t>::const_iterator inDataStart, std::vector<uint8_t>::const_iterator inDataEnd,
			std::vector<uint8_t>& outData) ;

	/**
	 * Decrypt the input data
	 * @param inData
	 * @param outData
	 */
	bool decrypt(std::vector<uint8_t>::const_iterator inDataStart, std::vector<uint8_t>::const_iterator inDataEnd,
			std::vector<uint8_t>& outData) ;


//	/**
//	 * Encrypt the input data
//	 * @param headerLen Number of header bytes to skip. These bytes are copied as-is from input to output
//	 * @param inData
//	 * @param outData
//	 */
//	bool encrypt(unsigned headerLen, const std::vector<uint8_t>& inData, std::vector<uint8_t>& outData) ;
//
//	/**
//	 * Decrypt the input data
//	 * @param headerLen Number of header bytes to skip. These bytes are copied as-is from input to output
//	 * @param inData
//	 * @param outData
//	 */
//	bool decrypt(unsigned headerLen, const std::vector<uint8_t>& inData, std::vector<uint8_t>& outData) ;
//


private:
	void encipher(unsigned int num_rounds, uint32_t v[2], uint32_t const key[4]) const ;
	void decipher(unsigned int num_rounds, uint32_t v[2], uint32_t const key[4]) const ;

private:
	uint32_t mKey[4] ;
} ;

}

#endif /* CRYPT_H_ */
