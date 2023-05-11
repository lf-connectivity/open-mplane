/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PlaybackWaveHeader.h
 * \brief     Handles the capture waveform header data
 *
 *
 * \details   Encapsulated waveform data has a header that this class manages
 * (either adding a header at the SCPI end or reading it out at the embedded
 * end)
 *
 */

#ifndef PLAYBACKWAVEFILEHEADER_H_
#define PLAYBACKWAVEFILEHEADER_H_

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "WaveFileHeader.h"

namespace Mplane {

class PlaybackWaveHeader : public WaveFileHeader {
 public:
  using super = WaveFileHeader;

  PlaybackWaveHeader();
  virtual ~PlaybackWaveHeader();

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
   * Get the SHA1 from the header
   */
  std::string getSha1String() const;

  /**
   * Get the SHA1 from the header
   */
  std::vector<uint8_t> getSha1() const;

  //    /**
  //     * Get the sample rate from the header
  //     */
  //    unsigned getSampleRateKsps() const ;

  /**
   * Create a capture file header
   * @param data
   * @param sha1    Authentication SHA-1
   * @return false on error
   */
  bool createHeader(
      std::vector<uint8_t>& data, const std::vector<uint8_t>& sha1);

 private:
  // "File" header information
  std::vector<uint8_t> mSha1;
  //    unsigned mSampleRateKsps ;
};

} // namespace Mplane

#endif /* PLAYBACKWAVEFILEHEADER_H_ */
