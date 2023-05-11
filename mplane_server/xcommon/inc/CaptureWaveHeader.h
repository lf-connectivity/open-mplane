/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CaptureWaveHeader.h
 * \brief     Handles the capture waveform header data
 *
 *
 * \details   Encapsulated waveform data has a header that this class manages
 * (either adding a header at the SCPI end or reading it out at the embedded
 * end)
 *
 */

#ifndef CAPTUREWAVEFILEHEADER_H_
#define CAPTUREWAVEFILEHEADER_H_

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "WaveFileHeader.h"

namespace Mplane {

class CaptureWaveHeader : public WaveFileHeader {
 public:
  using super = WaveFileHeader;

  CaptureWaveHeader();
  virtual ~CaptureWaveHeader();

  /**
   * Returns the size of the file header
   */
  virtual unsigned getHeaderSize() const override;

  /**
   * Process the start data (at the "file" head using iterators that point at
   * the byte vector
   * @param dataStart    Iterator to start of data. Is moved by this method to
   * end up pointing just past the header
   * @param dataEnd
   * @return false on error
   */
  virtual bool processHeader(
      IWaveFile::WaveDataIter& dataStart,
      IWaveFile::WaveDataIter dataEnd) override;

  /**
   * Get the wave index from the header
   */
  unsigned getWaveIndex() const;

  /**
   * Get the sample rate from the header
   */
  unsigned getSampleRateKsps() const;

  /**
   * Create a capture file header
   * @param data
   * @param waveIndex
   * @return false on error
   */
  bool createHeader(
      std::vector<uint8_t>& data, unsigned waveIndex, unsigned sampleRateKsps);

 private:
  // "File" header information
  unsigned mWaveIndex;
  unsigned mSampleRateKsps;
};

} // namespace Mplane

#endif /* CAPTUREWAVEFILEHEADER_H_ */
