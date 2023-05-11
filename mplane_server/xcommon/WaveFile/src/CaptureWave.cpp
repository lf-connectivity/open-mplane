/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CaptureWave.cpp
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

#include "CaptureWaveData.h"

#include "CaptureWave.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CaptureWave::CaptureWave()
    : mDataList(1, std::make_shared<CaptureWaveData>()), // list always needs at
                                                         // least one entry
      mData(mDataList.front()) // track the first element
{}

//-------------------------------------------------------------------------------------------------------------
CaptureWave::~CaptureWave() {}

//-------------------------------------------------------------------------------------------------------------
bool
CaptureWave::addData(const std::string& data) {
  return addData(std::vector<uint8_t>(data.begin(), data.end()));
}

//-------------------------------------------------------------------------------------------------------------
bool
CaptureWave::addData(const std::vector<uint8_t>& data) {
  IWaveFile::WaveDataIter dataStart(data.begin());
  IWaveFile::WaveDataIter dataEnd(data.end());

  std::shared_ptr<CaptureWaveData> current(mDataList.back());

  // keep iterating over the data until there's none left
  while (dataStart != dataEnd) {
    if (!current->addData(dataStart, dataEnd))
      return false;

    // Got to end of file?
    if (current->endOfFile()) {
      // add another wave file to the pile
      current = std::make_shared<CaptureWaveData>();
      mDataList.push_back(current);
    }
  }

  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
CaptureWave::endOfFile() const {
  return mData->endOfFile();
}

//-------------------------------------------------------------------------------------------------------------
void
CaptureWave::next() {
  if (mDataList.size() > 1) {
    // delete top of the pile
    mDataList.pop_front();
    mData = mDataList.front();
  } else {
    // At the last entry so just clear it
    mData->reset();
  }
}

//-------------------------------------------------------------------------------------------------------------
const std::vector<uint8_t>&
CaptureWave::getData() const {
  return mData->getData();
}

//-------------------------------------------------------------------------------------------------------------
std::string
CaptureWave::getError() {
  return mData->getError();
}

//-------------------------------------------------------------------------------------------------------------
unsigned
CaptureWave::getWaveIndex() const {
  return mData->getWaveIndex();
}

//-------------------------------------------------------------------------------------------------------------
unsigned
Mplane::CaptureWave::getDataLength() const {
  return mData->getDataLength();
}

//-------------------------------------------------------------------------------------------------------------
unsigned
Mplane::CaptureWave::getSampleRateKsps() const {
  return mData->getSampleRateKsps();
}
