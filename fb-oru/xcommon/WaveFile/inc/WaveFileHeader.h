/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveFileHeader.h
 * \brief     Handles the waveform header data
 *
 *
 * \details   Encapsulated waveform data has a header that this class manages (either adding a header at the SCPI end or
 * 			reading it out at the embedded end)
 *
 */


#ifndef WAVEFILEHEADER_H_
#define WAVEFILEHEADER_H_

#include <cstdint>
#include <memory>
#include <vector>
#include <string>

#include "IWaveFile.h"

namespace Mplane {

class WaveFileHeader {
public:
	WaveFileHeader() ;
	virtual ~WaveFileHeader() ;

	/**
	 * Returns the size of the file header
	 */
	virtual unsigned getHeaderSize() const ;

	/**
	 * Process the start data (at the "file" head using iterators that point at the byte vector
	 * @param dataStart	Iterator to start of data. Is moved by this method to end up pointing just past the header
	 * @param dataEnd
	 * @return false on error
	 */
	virtual bool processHeader(IWaveFile::WaveDataIter& dataStart, IWaveFile::WaveDataIter dataEnd) ;

	/**
	 * Get the data type from the header
	 * @return data type
	 */
	virtual IWaveFile::WaveType getType() const ;

	/**
	 * Returns the size of the block header
	 */
	virtual unsigned getBlockHeaderSize() const ;

	/**
	 * Process the block header present before each block of data
	 * @param dataStart
	 * @param dataEnd
	 * @return false on error
	 */
	virtual bool processBlockHeader(IWaveFile::WaveDataIter& dataStart, IWaveFile::WaveDataIter dataEnd) ;

	/**
	 * Return the block data length from the block header
	 */
	unsigned getBlockLength() const ;

	/**
	 * Get the block type from the block header
	 * @return block type
	 */
	virtual IWaveFile::WaveBlockType getBlockType() const ;


	/**
	 * Get error string set if any method returns false
	 * @return error string containing all error messages
	 */
	virtual std::string getError() ;

	/**
	 * Create a data block header
	 * @param data
	 * @param type
	 * @param blockLen
	 * @param dataLen
	 * @return false on error
	 */
	virtual bool createBlockHeader(std::vector<uint8_t>& data, IWaveFile::WaveBlockType type,
			unsigned blockLen) ;

protected:
	/**
	 * Create a header filling in the common bytes
	 * @param data
	 * @param type
	 * @param headerLenDelta
	 * @return false on error
	 */
	bool createHeader(std::vector<uint8_t>& data, IWaveFile::WaveType type, unsigned headerLenDelta) ;

	void setError(const std::string& error) ;
	bool checkType(uint8_t dataType) ;
	bool checkBlockType(uint8_t type) ;
	void skipHeader(IWaveFile::WaveDataIter& dataStart) const ;

private:
	std::string mError ;

	// "File" header information
	IWaveFile::WaveType mType ;
	IWaveFile::WaveDataIter mBlockStart ;

	// Data block information
	IWaveFile::WaveBlockType mBlockType ;
	unsigned mBlockLength ;
} ;

}

#endif /* WAVEFILEHEADER_H_ */
