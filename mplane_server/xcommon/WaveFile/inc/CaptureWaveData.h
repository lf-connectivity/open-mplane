/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CaptureWaveData.h
 * \brief     Stores the data for a capture file
 *
 *
 * \details
 *
 */

#ifndef CAPTUREWAVEDATA_H_
#define CAPTUREWAVEDATA_H_

#include "IWaveFile.h"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace Mplane {

class CaptureWaveHeader;

class CaptureWaveData {
 public:
  CaptureWaveData();
  virtual ~CaptureWaveData();

  /**
   * Add more data bytes to the file
   * @param dataStart    Iterator to start of data. Updated by this method as
   * data is used
   * @return false on error
   */
  bool addData(
      IWaveFile::WaveDataIter& dataStart, IWaveFile::WaveDataIter dataEnd);

  /**
   * Get the amount of IQ data in the capture waveform. Can be read back any
   * time after the header has been read (before the complete data has been
   * transferred)
   */
  unsigned getDataLength() const;

  /**
   * Have we completed loading the file data?
   */
  bool endOfFile() const;

  /**
   * Reset the file ready for new data
   */
  void reset();

  /**
   * Get the file data - will just be IQ data
   */
  const std::vector<uint8_t>& getData() const;

  /**
   * Get the wave index from the header
   */
  unsigned getWaveIndex() const;

  /**
   * Get the sample rate from the header
   */
  unsigned getSampleRateKsps() const;

  /**
   * Get error string
   */
  std::string getError();

 protected:
  void setError(const std::string& error);

 private:
  std::string mError;
  unsigned mDataLen;
  bool mEof;
  std::shared_ptr<CaptureWaveHeader> mHeader;
  std::vector<uint8_t> mData;
};

} // namespace Mplane

#endif /* CAPTUREWAVEDATA_H_ */
