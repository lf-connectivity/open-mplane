/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveFileHeader.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "WaveFileHeader.h"
#include "ByteTransfer.hpp"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
// Version
static const uint8_t HEADER_VER{0x01};

// File header
static const unsigned MAGIC_SIZE{4};
static const unsigned DATA_TYPE_SIZE{1};
static const unsigned HEAD_VER_SIZE{1};
static const unsigned HEAD_LEN_SIZE{2};
static const unsigned HEAD_BYTES{
    MAGIC_SIZE + DATA_TYPE_SIZE + HEAD_VER_SIZE + HEAD_LEN_SIZE};

// Data block header
static const unsigned BLOCK_TYPE_SIZE{1};
static const unsigned BLOCK_UNUSED_SIZE{3};
static const unsigned BLOCK_SIZE{4};
static const unsigned BLOCK_HEAD_BYTES{
    BLOCK_TYPE_SIZE + BLOCK_UNUSED_SIZE + BLOCK_SIZE};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
WaveFileHeader::WaveFileHeader()
    : mError(""),
      mType(IWaveFile::WaveType::UNSET),
      mBlockStart(),

      mBlockType(IWaveFile::WaveBlockType::RAW),
      mBlockLength(0) {}

//-------------------------------------------------------------------------------------------------------------
WaveFileHeader::~WaveFileHeader() {}

//-------------------------------------------------------------------------------------------------------------
bool
WaveFileHeader::processHeader(
    IWaveFile::WaveDataIter& dataStart, IWaveFile::WaveDataIter dataEnd) {

  // Assumes that the header data will be complete in this vector. There may be
  // extra data after the header but the full header will be present
  unsigned minFileHeadBytes(HEAD_BYTES);

  unsigned numBytes(std::distance(dataStart, dataEnd));
  if (numBytes < minFileHeadBytes) {
    setError("Invalid header data");
    return true;
  }

  uint32_t magic(ByteTransfer::readWord(dataStart, dataEnd));
  if (magic != IWaveFile::WAVE_MAGIC) {
    setError("Invalid wave data (not valid magic)");
    return false;
  }
  uint8_t dataType(ByteTransfer::readByte(dataStart, dataEnd));
  uint8_t headVer(ByteTransfer::readByte(dataStart, dataEnd));
  uint16_t headLen(ByteTransfer::readShort(dataStart, dataEnd));

  (void)headVer;

  if (!checkType(dataType))
    return false;

  mType = static_cast<IWaveFile::WaveType>(dataType);

  // Create a pointer to the start of the block data
  mBlockStart = dataStart + headLen;

  //{
  //    printf("HEADER:\n") ;
  //    printf("Magic......: 0x%08x\n", magic) ;
  //    printf("Type.......: 0x%02x\n", dataType) ;
  //    printf("Ver........: 0x%02x\n", headVer) ;
  //    printf("Start......: 0x%04x\n", headLen) ;
  //}

  return true;
}

//-------------------------------------------------------------------------------------------------------------
IWaveFile::WaveType
WaveFileHeader::getType() const {
  return mType;
}

//-------------------------------------------------------------------------------------------------------------
bool
WaveFileHeader::processBlockHeader(
    IWaveFile::WaveDataIter& dataStart, IWaveFile::WaveDataIter dataEnd) {
  unsigned minHeadBytes(BLOCK_HEAD_BYTES);

  unsigned numBytes(std::distance(dataStart, dataEnd));
  if (numBytes < minHeadBytes) {
    setError("Invalid block header data");
    return true;
  }

  // first byte is the type
  uint8_t type(ByteTransfer::readByte(dataStart, dataEnd));
  if (!checkBlockType(type))
    return false;

  // next bytes are unused
  ByteTransfer::read24bit(dataStart, dataEnd);

  mBlockType = static_cast<IWaveFile::WaveBlockType>(type);

  // Get the block length
  mBlockLength = ByteTransfer::readWord(dataStart, dataEnd);

  //{
  //    printf("BLOCK HEADER:\n") ;
  //    printf("Type.......: 0x%02x\n", type) ;
  //    printf("Length.....: 0x%08x\n", mBlockLength) ;
  //}

  return true;
}

//-------------------------------------------------------------------------------------------------------------
IWaveFile::WaveBlockType
WaveFileHeader::getBlockType() const {
  return mBlockType;
}

//-------------------------------------------------------------------------------------------------------------
unsigned
WaveFileHeader::getBlockLength() const {
  return mBlockLength;
}

//-------------------------------------------------------------------------------------------------------------
std::string
WaveFileHeader::getError() {
  std::string error("");
  std::swap(mError, error);
  return error;
}

//-------------------------------------------------------------------------------------------------------------
unsigned
Mplane::WaveFileHeader::getHeaderSize() const {
  return HEAD_BYTES;
}

//-------------------------------------------------------------------------------------------------------------
unsigned
Mplane::WaveFileHeader::getBlockHeaderSize() const {
  return BLOCK_HEAD_BYTES;
}

//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool
WaveFileHeader::createHeader(
    std::vector<uint8_t>& data,
    IWaveFile::WaveType type,
    unsigned headerLenDelta) {
  ByteTransfer::appendWord(data, IWaveFile::WAVE_MAGIC);
  ByteTransfer::appendByte(data, (uint8_t)type);
  ByteTransfer::appendByte(data, HEADER_VER);
  ByteTransfer::appendShort(data, headerLenDelta);

  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
WaveFileHeader::createBlockHeader(
    std::vector<uint8_t>& data,
    IWaveFile::WaveBlockType type,
    unsigned blockLen) {
  ByteTransfer::appendByte(data, (uint8_t)type);
  ByteTransfer::append24bit(data, 0u);
  ByteTransfer::appendWord(data, blockLen);

  return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
WaveFileHeader::setError(const std::string& error) {
  if (!mError.empty())
    mError += "\n";
  mError += error;
}

//-------------------------------------------------------------------------------------------------------------
bool
WaveFileHeader::checkType(uint8_t type) {
  if (type == (uint8_t)IWaveFile::WaveType::CAPTURE)
    return true;

  if (type == (uint8_t)IWaveFile::WaveType::PLAYBACK)
    return true;

  return false;
}

//-------------------------------------------------------------------------------------------------------------
bool
WaveFileHeader::checkBlockType(uint8_t blockType) {
  // TODO
  return true;
}

//-------------------------------------------------------------------------------------------------------------
void
WaveFileHeader::skipHeader(IWaveFile::WaveDataIter& dataStart) const {
  // Point at the start of the block data
  dataStart = mBlockStart;
}
