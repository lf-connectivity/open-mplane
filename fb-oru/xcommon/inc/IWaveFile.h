/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IWaveFile.h
 * \brief     Virtual interface to waveform files
 *
 *
 * \details
 *
 */


#ifndef IWAVEFILE_H_
#define IWAVEFILE_H_

#include <cstdint>
#include <vector>

namespace Mplane {

class IWaveFile {
public:
	IWaveFile() {}
	virtual ~IWaveFile() {}

	/**
	 * Magic value at start of wave file
	 */
	enum {
		WAVE_MAGIC = 0x57415645//!< WAVE_MAGIC
	};

	/**
	 * "File" contents type
	 */
	enum class WaveType {
		UNSET  		= 0,
		PLAYBACK	= (unsigned)'B',//!< playBack
		CAPTURE  	= (unsigned)'C', //!< Capture
	};

	/**
	 * Wave block data type. Raw IQ data or compressed/encrypted
	 */
	enum class WaveBlockType {
		RAW			= 0,        //!< RAW
		COMPRESSED	= 1<<0,//!< COMPRESSED
		ENCRYPTED	= 1<<1, //!< ENCRYPTED
	};




	/**
	 * Iterator type
	 */
	using WaveDataIter = std::vector<uint8_t>::const_iterator ;

} ;

inline IWaveFile::WaveBlockType
operator&(IWaveFile::WaveBlockType __a, IWaveFile::WaveBlockType __b)
{ return IWaveFile::WaveBlockType(static_cast<int>(__a) & static_cast<int>(__b)); }

inline IWaveFile::WaveBlockType
operator|(IWaveFile::WaveBlockType __a, IWaveFile::WaveBlockType __b)
{ return IWaveFile::WaveBlockType(static_cast<int>(__a) | static_cast<int>(__b)); }

inline IWaveFile::WaveBlockType
operator^(IWaveFile::WaveBlockType __a, IWaveFile::WaveBlockType __b)
{ return IWaveFile::WaveBlockType(static_cast<int>(__a) ^ static_cast<int>(__b)); }

inline IWaveFile::WaveBlockType&
operator|=(IWaveFile::WaveBlockType& __a, IWaveFile::WaveBlockType __b)
{ return __a = __a | __b; }

inline IWaveFile::WaveBlockType&
operator&=(IWaveFile::WaveBlockType& __a, IWaveFile::WaveBlockType __b)
{ return __a = __a & __b; }

inline IWaveFile::WaveBlockType&
operator^=(IWaveFile::WaveBlockType& __a, IWaveFile::WaveBlockType __b)
{ return __a = __a ^ __b; }

inline IWaveFile::WaveBlockType
operator~(IWaveFile::WaveBlockType __a)
{ return IWaveFile::WaveBlockType(~static_cast<int>(__a)); }

}

#endif /* IWAVEFILE_H_ */
