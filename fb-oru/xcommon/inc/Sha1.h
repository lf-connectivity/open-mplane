/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Sha1.h
 * \brief     Calculate SHA1
 *
 *
 * \details   Calculate the SHA1 hash on the given data
 *
 */


#ifndef SHA1_H_
#define SHA1_H_

#include <cstdint>
#include <vector>
#include <string>

namespace Mplane {

class Sha1 {
public:
	/**
	 * Number of bytes used to store SHA1
	 */
	static unsigned SHA1_SIZE ;

	/**
	 * Calculate the SHA1 hash value over the given data
	 * @param data
	 * @return vector containing the calculated hash
	 */
	static std::vector<uint8_t> getHash(const std::vector<uint8_t>& data) ;

	/**
	 * Calculate the SHA1 hash value over the given data
	 * @param data
	 * @return vector containing the calculated hash
	 */
	static std::vector<uint8_t> getHash(const std::string& data) ;

	/**
	 * Calculate the SHA1 hash value over the given data and return the result as a HEX string
	 * @param data
	 * @return string containing the calculated hash in hex
	 */
	static std::string getHashString(const std::vector<uint8_t>& data) ;

	/**
	 * Calculate the SHA1 hash value over the given data and return the result as a HEX string
	 * @param data
	 * @return string containing the calculated hash in hex
	 */
	static std::string getHashString(const std::string& data) ;

	/**
	 * Convert to 20 byte SHA1 vector into a hex string
	 * @param data
	 * @return hex string
	 */
	static std::string hashToString(const std::vector<uint8_t>& data) ;

private:
	// Calculate the hash (inner loop of algorithm)
	// h = 5 word result
	// w = 80 word buffer
	static void calcHash(uint32_t h[], uint32_t w[]) ;

	// zero the first 16 locations of the buffer
	static void clearW(uint32_t w[]) ;

} ;

}

#endif /* SHA1_H_ */
