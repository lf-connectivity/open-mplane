/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Lzo.h
 * \brief     Compression/decompression class using LZO
 *
 *
 * \details   C++ wrapper for minilzo (which implements LZO1X)
 *
 */


#ifndef LZO_H_
#define LZO_H_

#include <cstdint>
#include <vector>

namespace Mplane {

class Lzo {
public:
	Lzo() ;
	virtual ~Lzo() ;

	/**
	 * Use LZO to compress the input data
	 * @param inData	uncompressed data
	 * @param outData	compressed data
	 * @return true if compression succeeded
	 */
	bool compress(const std::vector<uint8_t> inData, std::vector<uint8_t>& outData) ;
	bool compress(std::vector<uint8_t>::const_iterator inDataStart, std::vector<uint8_t>::const_iterator inDataEnd,
			std::vector<uint8_t>& outData) ;

	/**
	 * Use LZO to decompress the input data
	 * @param inData	compressed data
	 * @param outData	uncompressed data
	 * @return true if compression succeeded
	 */
	bool decompress(const std::vector<uint8_t> inData, std::vector<uint8_t>& outData) ;
	bool decompress(std::vector<uint8_t>::const_iterator inDataStart, std::vector<uint8_t>::const_iterator inDataEnd,
			std::vector<uint8_t>& outData) ;

	/**
	 * Specify a minimum size to use when decompressing. This ensures that enough memory is allocated as a workspace
	 * @param size
	 */
	void setBlockSize(unsigned size) ;

private:
	// Used to initialise the LZO lib once
	static bool init() ;

	// calc compressed data size from uncompressed size
	unsigned compressedSize(unsigned uncompressedSize) const ;

	// calc uncompressed data size from compressed size
	unsigned uncompressedSize(unsigned compressedSize) const ;

private:
	// Used to initialise the LZO lib once
	static bool mInit ;

	// workspace
	std::vector<uint8_t> mWorkspace ;

	// Minimum decompression size - as specified by the user
	unsigned mDecompressionMinSize ;
} ;

}

#endif /* LZO_H_ */
