/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CaptureWave.h
 * \brief     Manages storing data as one or more capture files
 *
 *
 * \details   Capture data (nominally sent via TCP packets) is split into one of
 *more capture "files" in a list. The data is stored in instances of the class
 *                 CaptureWaveData. This class implements the PROXY
 *pattern by providing access to the methods of the CaptureWaveData class
 *instance that is first in the list.
 *
 *                 Because multiple capture data can span packets
 *(and in the case of short captures there may be multiple captures in a single
 *packet) you need to call the endOfFile() method repeatedly until false to pull
 *out each complete capture.
 *
 *                 An example of the class use is:
 *
 *                 @code
 *                // some data handler
 *                void dataHandler(const std::string& data)
 *                {
 *                    // Throw data into the CaptureWave until
 *it's a file's worth mCaptureWave->addData(data) ;
 *
 *                    // Process all of the complete files so
 *far while (mCaptureWave->endOfFile())
 *                    {
 *                        std::string fname("w" +
 *std::to_string(mCaptureWave->getWaveIndex()) + ".bin") ; int fd =
 *::open(fname.c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR |
 *S_IRGRP | S_IROTH) ; if (fd < 0) perror("Error opening file") ;
 *
 *                        const std::vector<uint8_t>&
 *fileData( mCaptureWave->getData() ) ;
 *                        ::write(fd, &fileData[0],
 *fileData.size())
 *;
 *                        ::close(fd);
 *
 *                        // move to next file
 *                        mCaptureWave->next() ;
 *                    }
 *                }
 *                 @endcode
 *
 */

#ifndef CAPTUREWAVE_H_
#define CAPTUREWAVE_H_

#include <cstdint>
#include <list>
#include <memory>
#include <string>

namespace Mplane {

class CaptureWaveData;

class CaptureWave {
 public:
  CaptureWave();
  virtual ~CaptureWave();

  /**
   * Add more data bytes to the file
   * @param data
   * @return false on error
   */
  bool addData(const std::string& data);

  /**
   * Add more data bytes to the file
   * @param data
   * @return false on error
   */
  bool addData(const std::vector<uint8_t>& data);

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
  void next();

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

 private:
  std::list<std::shared_ptr<CaptureWaveData>> mDataList;
  std::shared_ptr<CaptureWaveData> mData;
};

} // namespace Mplane

#endif /* CAPTUREWAVE_H_ */
