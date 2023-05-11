/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PlaybackWave.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "ByteTransfer.hpp"
#include "Crypt.h"
#include "IFeature.h"
#include "IKey.h"
#include "Lzo.h"
#include "Sha1.h"

#include "PlaybackWave.h"
#include "PlaybackWaveHeader.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
static const unsigned BLOCK_SIZE{8192};

// Uncomment this to allow files to also use compression along with encryption
// At present using compression takes a while!
#define USE_COMPRESSION

//=============================================================================================================
// TYPES
//=============================================================================================================
namespace Mplane {

//-------------------------------------------------------------------------------------------------------------
// RAII for encapsulated/encrypted file. Automatically closes file when object
// is destroyed
class EncapFile {
 public:
  EncapFile()
      : mEncapsulatedFilepath(""), mInFile(), mFileSize(0), mBytesLeft(0) {}

  ~EncapFile() {
    if (!mEncapsulatedFilepath.empty()) {
      mInFile.close();
    }
  }

  bool
  load(const std::string& path) {
    // open file in binary mode and get it's size
    mInFile.open(path, std::ios::binary | std::ios::ate);
    if (!mInFile) {
      return false;
    }

    mFileSize = mInFile.tellg();
    mBytesLeft = mFileSize;
    mInFile.seekg(0, std::ios::beg);
    mEncapsulatedFilepath = path;
    return true;
  }

  bool
  readFile(std::vector<uint8_t>& data, unsigned numBytes) {
    if (mEncapsulatedFilepath.empty())
      return false;

    if (numBytes > static_cast<unsigned>(mBytesLeft))
      return false;

    mBytesLeft -= numBytes;
    data.resize(numBytes);
    if (!mInFile.read((char*)data.data(), numBytes))
      return false;

    return true;
  }

  bool
  eof() const {
    if (mEncapsulatedFilepath.empty())
      return true;

    if (mBytesLeft > 0)
      return false;

    return true;
  }

 private:
  std::string mEncapsulatedFilepath;
  std::ifstream mInFile;
  std::streamsize mFileSize;
  std::streamsize mBytesLeft;
};

//-------------------------------------------------------------------------------------------------------------
// Playback file name information. Test model files have a fixed format
// filename. This class uses that formatting to extract information.
//
class PlaybackFileInfo {
 public:
  explicit PlaybackFileInfo(const std::string& filepath)
      : mFilepath(filepath),
        mPath(""),
        mSep(""),
        mFile(""),
        mBase(""),
        mExtension(""),
        mAirStd(""),
        mDuplex(""),
        mDuplexPrefix(""),
        mBw(""),
        mTm(""),
        mTmPrefix(""),
        mRate(""),
        mCellId("") {
    removePath(mFilepath, mPath, mSep, mFile);
    removeExtension(mFile, mBase, mExtension);

    // Handle filenames of the type:
    //    LTE_FDD-1_10M_TM31_15.36MSPS.art    LTE_TDD38_10M_RXTM11_15.36MSPS.art
    //    LTE_TDD38-1_10M_TM31_15.36MSPS.art  LTE_TDD38_20M_RXTM11_30.72MSPS.art
    //    LTE_TDD38-1_20M_TM31_30.72MSPS.art  LTE_TDD38_5M_RXTM11_7.68MSPS.art
    //    LTE_TDD38-1_5M_TM31_7.68MSPS.art    QMC_cal_tone_1.92MHz_15.36MSPS.art
    //  LTE_FDD-1_5M_FRCA3-4_7.68MSPS.art
    //
    // <AIRSTD>_<DUPLEX>_<BW>_<TM>_<RATE>
    //
    // And DUPLEX can be <DUPLEX>-<CELL ID>
    //
    std::vector<std::string> fields(split(mBase, '_'));
    if (fields.size() != 5)
      return;

    mAirStd = fields[0];
    mDuplex = fields[1];
    mBw = fields[2];
    mTm = fields[3];
    mRate = fields[4];

    mTmPrefix = mTm;
    mDuplexPrefix = mDuplex;

    // Strip any numbers from tm & duplex
    std::size_t pos;

    pos = mTmPrefix.find_first_of("0123456789-");
    if (pos != std::string::npos)
      mTmPrefix = mTmPrefix.substr(0, pos);
    pos = mDuplexPrefix.find_first_of("0123456789-");
    if (pos != std::string::npos)
      mDuplexPrefix = mDuplexPrefix.substr(0, pos);

    // Now see if DUPLEX is of the form: <DUPLEX>-<CELL ID>
    std::vector<std::string> duplexFields(split(mDuplex, '-'));
    if (duplexFields.size() != 2)
      return;

    mDuplex = duplexFields[0];
    mCellId = duplexFields[1];
  }

  ~PlaybackFileInfo() {}

  const std::string&
  getPath() const {
    return mPath;
  }

  const std::string&
  getSeparator() const {
    return mSep;
  }

  const std::string&
  getFile() const {
    return mFile;
  }

  const std::string&
  getFilepath() const {
    return mFilepath;
  }

  const std::string&
  getAirStd() const {
    return mAirStd;
  }

  const std::string&
  getBase() const {
    return mBase;
  }

  const std::string&
  getBw() const {
    return mBw;
  }

  const std::string&
  getCellId() const {
    return mCellId;
  }

  const std::string&
  getDuplex() const {
    return mDuplex;
  }

  const std::string&
  getExtension() const {
    return mExtension;
  }

  const std::string&
  getRate() const {
    return mRate;
  }

  const std::string&
  getTm() const {
    return mTm;
  }

  std::string
  getFeatureString() const {

    if (mAirStd.empty())
      return "";
    if (mTmPrefix.empty())
      return "";
    if (mDuplexPrefix.empty())
      return "";

    return mAirStd + "_" + mDuplexPrefix + "_" + mTmPrefix;
  }

 private:
  static void
  removePath(
      const std::string& filepath,
      std::string& path,
      std::string& sep,
      std::string& file) {
    std::size_t pos(filepath.find_last_of("/\\"));
    if (pos == std::string::npos) {
      file = filepath;
      path = "";
      sep = "";
      return;
    }

    path = filepath.substr(0, pos);
    file = filepath.substr(pos + 1);
    sep = filepath.substr(pos, 1);
  }

  static void
  removeExtension(
      const std::string& name, std::string& base, std::string& ext) {
    std::size_t pos(name.find_last_of('.'));
    if (pos == std::string::npos) {
      base = name;
      ext = "";
      return;
    }

    base = name.substr(0, pos);
    ext = name.substr(pos);
  }

  static std::vector<std::string>
  split(const std::string& str, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    while (ss.good()) {
      std::string splitStr;
      getline(ss, splitStr, delim);
      result.push_back(splitStr);
    }
    return result;
  }

 private:
  std::string mFilepath;
  std::string mPath;
  std::string mSep;
  std::string mFile;
  std::string mBase;
  std::string mExtension;
  std::string mAirStd;
  std::string mDuplex;
  std::string mDuplexPrefix;
  std::string mBw;
  std::string mTm;
  std::string mTmPrefix;
  std::string mRate;
  std::string mCellId;
};

} // namespace Mplane

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
PlaybackWave::PlaybackWave(std::shared_ptr<IKey> key)
    : mKey(key),
      mHeader(std::make_shared<PlaybackWaveHeader>()),
      mLzo(std::make_shared<Lzo>()),
      mCrypt(std::make_shared<Crypt>(mKey->licenseKey())),
      mError(""),

      mEncapFile(),
      mFileInfo() {
  // Give the LZO algorithm a hint about the minimum block size
  mLzo->setBlockSize(BLOCK_SIZE);
}

//-------------------------------------------------------------------------------------------------------------
PlaybackWave::~PlaybackWave() {}

//-------------------------------------------------------------------------------------------------------------
bool
PlaybackWave::encapsulate(
    const std::string& inFilename,
    const std::vector<uint8_t>& inData,
    std::vector<uint8_t>& outData) {
#ifdef USE_UNECRYPTED_PLAYBACK
  outData.insert(outData.end(), inData.begin(), inData.end());
  return true;
#endif

  std::vector<uint8_t>::const_iterator dataStart(inData.begin());
  std::vector<uint8_t>::const_iterator dataEnd(inData.end());
  unsigned bytesLeft(std::distance(dataStart, dataEnd));

  // std::cerr << "ecapsulate(" << inFilename << ") size=" << bytesLeft <<
  // std::endl ;

  // SHA1
  std::vector<uint8_t> sha1(Sha1::getHash(inFilename));

  // Create header
  mHeader->createHeader(outData, sha1);

  // Pack up each full block
  // unsigned block{0} ;
  while (bytesLeft >= BLOCK_SIZE) {
    //        std::cerr << "ecapsulate block " << block << ": bytes left=" <<
    // bytesLeft << std::endl ;
    if (!encapsulateBlock(dataStart, dataStart + BLOCK_SIZE, outData))
      return false;
    dataStart += BLOCK_SIZE;
    bytesLeft -= BLOCK_SIZE;
    //        std::cerr << "ecapsulated block " << block << " : bytes left=" <<
    // bytesLeft << std::endl ;
    //++block ;
  }

  // pack up what's left
  //    std::cerr << "ecapsulated blocks : bytes left=" << bytesLeft <<
  // std::endl ;
  if (bytesLeft > 0) {
    //        std::cerr << "ecapsulate final block : bytes left=" << bytesLeft
    //        <<
    // std::endl ;
    if (!encapsulateBlock(dataStart, dataEnd, outData))
      return false;
  }

  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
PlaybackWave::encapsulate(
    const std::string& inFilename,
    const std::vector<uint8_t>& inData,
    const std::string& outFilename) {
  std::vector<uint8_t> outData;
  if (!encapsulate(inFilename, inData, outData))
    return false;

  std::ofstream file;
  file.open(outFilename, std::ios::out | std::ios::binary);
  if (!file) {
    setError("Unable to open file '" + outFilename + "' for writing");
    return false;
  }

  file.write((const char*)&outData[0], outData.size());
  if (!file) {
    setError("Error writing to file '" + outFilename + "'");
    return false;
  }

  return true;
}

//-------------------------------------------------------------------------------------------------------------
std::string
PlaybackWave::getError() {
  std::string error("");
  std::swap(mError, error);
  return error;
}

//-------------------------------------------------------------------------------------------------------------
void
Mplane::PlaybackWave::setFilepath(const std::string& filepath) {
  mFileInfo = std::make_shared<PlaybackFileInfo>(filepath);
}

//-------------------------------------------------------------------------------------------------------------
bool
Mplane::PlaybackWave::loadEncapsulated() {
#ifdef USE_UNECRYPTED_PLAYBACK
  // Shouldn't ever be called when compiling to use unencrypted file
  setError(
      "Cannot open encrypted file '" + mFileInfo->getFilepath() +
      "' when compiled to use unencrypted files");
  return false;
#endif

  mEncapFile.reset();

  // open file in binary mode and get it's size
  std::shared_ptr<EncapFile> encapFile(std::make_shared<EncapFile>());
  if (!encapFile->load(mFileInfo->getFilepath())) {
    setError("Unable to open '" + mFileInfo->getFilepath() + "' for reading");
    return false;
  }

  // Read in the header
  std::vector<uint8_t> header;
  if (!encapFile->readFile(header, mHeader->getHeaderSize())) {
    setError("Unable to read header");
    return false;
  }
  IWaveFile::WaveDataIter headStart(header.cbegin());
  if (!mHeader->processHeader(headStart, header.cend())) {
    setError(mHeader->getError());
    return false;
  }

  // Check SHA1
  std::string filenameSha1(Sha1::getHashString(mFileInfo->getFile()));
  std::string headerSha1(mHeader->getSha1String());
  if (filenameSha1 != headerSha1) {
    setError("File SHA1 does not match expected value");
    return false;
  }

  // ok to keep file pointer for subsequent use
  mEncapFile = encapFile;
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
Mplane::PlaybackWave::loadEncapsulated(const std::string& filepath) {
  setFilepath(filepath);

  return loadEncapsulated();
}

//-------------------------------------------------------------------------------------------------------------
bool
Mplane::PlaybackWave::loadNextBlock(std::vector<uint8_t>& data, bool& eof) {
#ifdef USE_UNECRYPTED_PLAYBACK
  // Shouldn't ever be called when compiling to use unencrypted file
  setError(
      "Cannot load encrypted block when compiled to use unencrypted files");
  return false;
#endif

  if (!mEncapFile) {
    setError("Attempting to load data without specifying input filename");
    return false;
  }

  if (mEncapFile->eof()) {
    eof = true;
    return true;
  }

  // Read in the block header
  std::vector<uint8_t> header;
  if (!mEncapFile->readFile(header, mHeader->getBlockHeaderSize())) {
    setError("Unable to read block header");
    return false;
  }
  IWaveFile::WaveDataIter headStart(header.cbegin());
  if (!mHeader->processBlockHeader(headStart, header.cend())) {
    setError(mHeader->getError());
    return false;
  }

  // load the block data
  std::vector<uint8_t> block;
  if (!mEncapFile->readFile(block, mHeader->getBlockLength())) {
    setError("Unable to read block");
    return false;
  }
  std::vector<uint8_t>::const_iterator dataStart(block.cbegin());
  std::vector<uint8_t>::const_iterator dataEnd(block.cend());

  // Get the block type
  IWaveFile::WaveBlockType type(mHeader->getBlockType());

  //    std::cerr << "Block type 0x" << std::hex << (unsigned)type << std::dec
  //<< std::endl ;     std::cerr << "Wave data ( " << std::distance(dataStart,
  // dataEnd) << "bytes):" << std::endl ;     ByteTransfer::dump(dataStart,
  // dataEnd)
  //;

  // process data
  std::vector<uint8_t> decrypted;
  if ((type & IWaveFile::WaveBlockType::ENCRYPTED) ==
      IWaveFile::WaveBlockType::ENCRYPTED) {
    if (!mCrypt->decrypt(dataStart, dataEnd, decrypted)) {
      setError("Unable to decrypt block");
      return false;
    }

    dataStart = decrypted.cbegin();
    dataEnd = decrypted.cend();
  }

  //    std::cerr << "After decryption ( " << std::distance(dataStart, dataEnd)
  //<< "bytes):" << std::endl ;     ByteTransfer::dump(dataStart, dataEnd) ;

  std::vector<uint8_t> decompressed;
  if ((type & IWaveFile::WaveBlockType::COMPRESSED) ==
      IWaveFile::WaveBlockType::COMPRESSED) {
    //        std::cerr << "Decompress ( " << std::distance(dataStart, dataEnd)
    //        <<
    //"bytes):" << std::endl ;

    if (!mLzo->decompress(dataStart, dataEnd, decompressed)) {
      setError("Unable to decompress block");
      return false;
    }

    dataStart = decompressed.begin();
    dataEnd = decompressed.end();

    //        std::cerr << "After decompression ( " << std::distance(dataStart,
    // dataEnd) << "bytes):" << std::endl ; ByteTransfer::dump(dataStart,
    // dataEnd) ;
  }

  // Save data
  data.insert(data.end(), dataStart, dataEnd);

  if (mEncapFile->eof())
    eof = true;

  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
PlaybackWave::checkFeatures(std::shared_ptr<IFeature> features) {

  if (!mFileInfo) {
    setError("Attempting to check features without specifying input filename");
    return false;
  }

  // we only need to feature validate licensed files supplied with the E6610A,
  // they all
  // have the ewf, the encrypted waveform file extension
  if (mFileInfo->getExtension() == ".ewf") {

    // create the feature string of the form <AIRSTD>_<DUPLEX>_<TM> and see if
    // it's enabled
    std::string featureString(mFileInfo->getFeatureString());
    if (featureString.empty())
      return true;

    // check feature enabled
    if (!features->checkSupported(featureString)) {
      setError(
          "Feature " + featureString +
          " not licensed for use in this application");
      return false;
    }
  }
  return true;
}

//-------------------------------------------------------------------------------------------------------------
unsigned
PlaybackWave::dataSize() {
  unsigned numBytes{0};

  // Load in encrypted data in blocks
  bool endOfFile{false};
  while (!endOfFile) {
    // read from file
    std::vector<uint8_t> buffer;

    if (!loadNextBlock(buffer, endOfFile))
      return 0;

    numBytes += buffer.size();
  }

  std::cerr << "PlaybackWave::dataSize() " << getFilepath() << " " << numBytes
            << std::endl;
  return numBytes;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
PlaybackWave::setError(const std::string& error) {
  if (!mError.empty())
    mError += "\n";
  mError += error;
}

//-------------------------------------------------------------------------------------------------------------
bool
Mplane::PlaybackWave::encapsulateBlock(
    std::vector<uint8_t>::const_iterator dataStart,
    std::vector<uint8_t>::const_iterator dataEnd,
    std::vector<uint8_t>& outData) {
  IWaveFile::WaveBlockType type{IWaveFile::WaveBlockType::RAW};

  //    std::cerr << "ecapsulateBlock() block size=" << std::distance(dataStart,
  // dataEnd) << std::endl ;     std::cerr << "Output Data so far:" << std::endl
  // ;
  //    ByteTransfer::dump(outData) ;

  //    std::cerr << "Input ( " << std::distance(dataStart, dataEnd) <<
  //"bytes):" << std::endl ;     ByteTransfer::dump(dataStart, dataEnd) ;

#ifdef USE_COMPRESSION
  // Try compressing block
  std::vector<uint8_t> compressedData;
  if (mLzo->compress(dataStart, dataEnd, compressedData)) {
    //        std::cerr << " * compressed size=" << compressedData.size() <<
    // std::endl ;

    // compressed ok - see if we've reduced the size
    if (compressedData.size() < (unsigned)std::distance(dataStart, dataEnd)) {
      //            std::cerr << " * * Use compression" << std::endl
      //;

      // use this compressed data
      type |= IWaveFile::WaveBlockType::COMPRESSED;
      dataStart = compressedData.begin();
      dataEnd = compressedData.end();
    }
  }
#endif

  //    std::cerr << "Encrypt input ( " << std::distance(dataStart, dataEnd) <<
  //"bytes):" << std::endl ;     ByteTransfer::dump(dataStart, dataEnd) ;

  // Encrypt the data
  std::vector<uint8_t> encryptedData;
  if (!mCrypt->encrypt(dataStart, dataEnd, encryptedData)) {
    setError("Failed to encrypt input data block");
    return false;
  }

  //    std::cerr << "Encrypted ( " << encryptedData.size() << "bytes):" <<
  // std::endl ;     ByteTransfer::dump(encryptedData) ;

  // create the header
  type |= IWaveFile::WaveBlockType::ENCRYPTED;
  mHeader->createBlockHeader(outData, type, encryptedData.size());

  // Append the encrypted data
  outData.insert(outData.end(), encryptedData.begin(), encryptedData.end());

  //    std::cerr << "ecapsulateBlock() END" << std::endl ;
  //    std::cerr << "Output Data now:" << std::endl ;
  //    ByteTransfer::dump(outData) ;

  return true;
}

//=============================================================================================================
// PROTECTED ACCESS FOR TESTING
//=============================================================================================================

#define FILEINFO_TEST_ACCESS(method)         \
  std::string PlaybackWave::method() const { \
    if (!mFileInfo)                          \
      return "";                             \
    return mFileInfo->method();              \
  }

//-------------------------------------------------------------------------------------------------------------
FILEINFO_TEST_ACCESS(getFile)
FILEINFO_TEST_ACCESS(getFilepath)
FILEINFO_TEST_ACCESS(getPath)
FILEINFO_TEST_ACCESS(getSeparator)
FILEINFO_TEST_ACCESS(getAirStd)
FILEINFO_TEST_ACCESS(getBase)
FILEINFO_TEST_ACCESS(getBw)
FILEINFO_TEST_ACCESS(getCellId)
FILEINFO_TEST_ACCESS(getDuplex)
FILEINFO_TEST_ACCESS(getExtension)
FILEINFO_TEST_ACCESS(getRate)
FILEINFO_TEST_ACCESS(getTm)
