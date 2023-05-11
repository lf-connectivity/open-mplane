/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ByteTransfer.hpp
 * \brief     Inline class providing shared byte transfer utilities
 *
 *
 * \details   Provides static methods for reading and writing multi-byte values portably as big-endian values
 *
 */


#ifndef BYTETRANSFER_HPP_
#define BYTETRANSFER_HPP_

#include <cstdint>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ostream>
#include <vector>
#include <string>

namespace Mplane {

class ByteTransfer {
public:
 //----------------------------------------------------------------------------------------------
 // String access

 /**
  * Read a zero terminated sequence of chars into a string
  * @param idx    Starting index (updated for each byte used)
  * @param data
  * @return string or empty
  */
 static inline std::string
 readString(unsigned& idx, const std::vector<uint8_t>& data) {
   std::string str;

   uint8_t cc;
   while ((cc = readByte(idx, data)) != 0x00)
     str.push_back(cc);
   return str;
 }

 /**
  * Read a specified number of chars into a string
  * @param idx    Starting index (updated for each byte used)
  * @param data
  * @return string or empty
  */
 static inline std::string
 readString(unsigned& idx, unsigned num, const std::string& data) {
   std::string str;

   if (idx >= data.size())
     return 0;

   while ((num-- > 0) && (idx < data.size())) {
     str.push_back(readByte(idx, data));
   }
   return str;
 }

 /**
  * Write a string into data as a zero termiated sequence of chars
  * @param idx    Starting index (updated for each byte used)
  * @param data
  * @param str    String to write
  */
 static inline void
 writeString(
     unsigned& idx, std::vector<uint8_t>& data, const std::string& str) {
   for (char cc : str)
     writeByte(idx, data, (uint8_t)cc);
   writeByte(idx, data, 0x00);
 }

 /**
  * Read a byte value from the data starting at the index 'idx'
  * @param idx    Starting index (updated for each byte used)
  * @param data
  * @return byte
  */
 static inline uint8_t
 readByte(unsigned& idx, const std::string& data) {
   if (idx >= data.size())
     return 0;

   return data[idx++];
 }

 /**
  * Read a 64-bit word value from the data starting at the index 'idx'
  * @param idx    Starting index (updated for each byte used)
  * @param data
  * @return 64-bit word
  */
 static inline uint64_t
 read64bit(unsigned& idx, const std::vector<uint8_t>& data) {
   return readVal<uint64_t, 8>(idx, data);
 }

 /**
  * Write 64-bit word into data start at the index 'idx'
  * @param idx    Starting index (updated for each byte used)
  * @param data
  * @param word
  */
 static inline void
 write64bit(unsigned& idx, std::vector<uint8_t>& data, uint64_t word) {
   writeVal<uint64_t, 8>(idx, data, word);
 }

 /**
  * Write 64-bit word into data start at the index 'idx'
  * @param idx    Starting index (updated for each byte used)
  * @param data
  * @param word
  */
 static inline void
 write64bit(unsigned& idx, std::string& data, uint64_t word) {
   writeVal<uint64_t, 8>(idx, data, word);
 }

 /**
  * Read a 32-bit word value from the data starting at the index 'idx' (big
  * endian)
  * @param idx    Starting index (updated for each byte used)
  * @param data
  * @return 32-bit word
  */
 static inline uint32_t
 readWord(unsigned& idx, const std::vector<uint8_t>& data) {
   return readVal<uint32_t, 4>(idx, data);
 }

 /**
  * Read a 32-bit word value from the data starting at the index 'idx' (little
  * endian)
  * @param idx    Starting index (updated for each byte used)
  * @param data
  * @return 32-bit word
  */
 static inline uint32_t
 readWordLE(unsigned& idx, const std::vector<uint8_t>& data) {
   return readValLE<uint32_t, 4>(idx, data);
 }

 /**
  * Write 32-bit word into data start at the index 'idx' (big endian)
  * @param idx    Starting index (updated for each byte used)
  * @param data
  * @param word
  */
 static inline void
 writeWord(unsigned& idx, std::vector<uint8_t>& data, uint32_t word) {
   writeVal<uint32_t, 4>(idx, data, word);
 }

 /**
  * Write 32-bit word into data start at the index 'idx' (little endian)
  * @param idx    Starting index (updated for each byte used)
  * @param data
  * @param word
  */
 static inline void
 writeWordLE(unsigned& idx, std::vector<uint8_t>& data, uint32_t word) {
   writeValLE<uint32_t, 4>(idx, data, word);
 }

 /**
  * Read a 24-bit word value from the data starting at the index 'idx' (big
  * endian)
  * @param idx    Starting index (updated for each byte used)
  * @param data
  * @return 24-bit word
  */
 static inline uint32_t
 read24bit(unsigned& idx, const std::vector<uint8_t>& data) {
   return readVal<uint32_t, 3>(idx, data);
 }

 /**
  * Read a 24-bit word value from the data starting at the index 'idx' (litlle
  * endian)
  * @param idx    Starting index (updated for each byte used)
  * @param data
  * @return 24-bit word
  */
 static inline uint32_t
 read24bitLE(unsigned& idx, const std::vector<uint8_t>& data) {
   return readValLE<uint32_t, 3>(idx, data);
 }

 /**
  * Write 24-bit word into data start at the index 'idx' (big endian)
  * @param idx    Starting index (updated for each byte used)
  * @param data
  * @param word
  */
 static inline void
 write24bit(unsigned& idx, std::vector<uint8_t>& data, uint32_t word) {
   writeVal<uint32_t, 3>(idx, data, word);
 }

 /**
  * Write 24-bit word into data start at the index 'idx' (little endian)
  * @param idx    Starting index (updated for each byte used)
  * @param data
  * @param word
  */
 static inline void
 write24bitLE(unsigned& idx, std::vector<uint8_t>& data, uint32_t word) {
   writeValLE<uint32_t, 3>(idx, data, word);
 }

 /**
  * Read a 16-bit short value from the data starting at the index 'idx' (big
  * endian)
  * @param idx    Starting index (updated for each byte used)
  * @param data
  * @return 16-bit short
  */
 static inline uint16_t
 readShort(unsigned& idx, const std::vector<uint8_t>& data) {
   return readVal<uint16_t, 2>(idx, data);
 }

 /**
  * Read a 16-bit short value from the data starting at the index 'idx' (little
  * endian)
  * @param idx    Starting index (updated for each byte used)
  * @param data
  * @return 16-bit short
  */
 static inline uint16_t
 readShortLE(unsigned& idx, const std::vector<uint8_t>& data) {
   return readValLE<uint16_t, 2>(idx, data);
 }

 /**
  * Write 16-bit short into data start at the index 'idx' (big endian)
  * @param idx    Starting index (updated for each byte used)
  * @param data
  * @param shortval
  */
 static inline void
 writeShort(unsigned& idx, std::vector<uint8_t>& data, uint16_t shortval) {
   writeVal<uint16_t, 2>(idx, data, shortval);
 }

 /**
  * Write 16-bit short into data start at the index 'idx' (little endian)
  * @param idx    Starting index (updated for each byte used)
  * @param data
  * @param shortval
  */
 static inline void
 writeShortLE(unsigned& idx, std::vector<uint8_t>& data, uint16_t shortval) {
   writeValLE<uint16_t, 2>(idx, data, shortval);
 }

 /**
  * Read a byte value from the data starting at the index 'idx'
  * @param idx    Starting index (updated for each byte used)
  * @param data
  * @return byte
  */
 static inline uint8_t
 readByte(unsigned& idx, const std::vector<uint8_t>& data) {
   if (idx >= data.size())
     return 0;

   return data[idx++];
 }

 /**
  * Write byte into data start at the index 'idx'
  * @param idx    Starting index (updated for each byte used)
  * @param data
  * @param byte
  */
 static inline void
 writeByte(unsigned& idx, std::vector<uint8_t>& data, uint8_t byteval) {
   if (idx >= data.size())
     return;

   data[idx++] = byteval;
 }

 //----------------------------------------------------------------------------------------------
 // Vector Append data

 /**
  * Append a byte (provided to make interface consistent)
  * @param data
  * @param val
  */
 static inline void
 appendByte(std::vector<uint8_t>& data, uint8_t val) {
   data.push_back(val);
 }

 /**
  * Append a 16-bit short in big endian mode
  * @param data
  * @param val
  */
 static inline void
 appendShort(std::vector<uint8_t>& data, uint16_t val) {
   unsigned idx((unsigned)data.size());
   data.push_back(0);
   data.push_back(0);
   writeShort(idx, data, val);
 }

 /**
  * Append a 16-bit short in little endian mode
  * @param data
  * @param val
  */
 static inline void
 appendShortLE(std::vector<uint8_t>& data, uint16_t val) {
   unsigned idx(data.size());
   data.push_back(0);
   data.push_back(0);
   writeShortLE(idx, data, val);
 }

 /**
  * Append a 24-bit word in big endian mode
  * @param data
  * @param val
  */
 static inline void
 append24bit(std::vector<uint8_t>& data, uint32_t val) {
   unsigned idx(data.size());
   data.push_back(0);
   data.push_back(0);
   data.push_back(0);
   write24bit(idx, data, val);
 }

 /**
  * Append a 24-bit word in little endian mode
  * @param data
  * @param val
  */
 static inline void
 append24bitLE(std::vector<uint8_t>& data, uint32_t val) {
   unsigned idx(data.size());
   data.push_back(0);
   data.push_back(0);
   data.push_back(0);
   write24bitLE(idx, data, val);
 }

 /**
  * Append a 32-bit word in big endian mode
  * @param data
  * @param val
  */
 static inline void
 appendWord(std::vector<uint8_t>& data, uint32_t val) {
   unsigned idx(data.size());
   data.push_back(0);
   data.push_back(0);
   data.push_back(0);
   data.push_back(0);
   writeWord(idx, data, val);
 }

 /**
  * Append a 32-bit word in little endian mode
  * @param data
  * @param val
  */
 static inline void
 appendWordLE(std::vector<uint8_t>& data, uint32_t val) {
   unsigned idx(data.size());
   data.push_back(0);
   data.push_back(0);
   data.push_back(0);
   data.push_back(0);
   writeWordLE(idx, data, val);
 }

 /**
  * Append a 64-bit word in big endian mode
  * @param data
  * @param val
  */
 static inline void
 append64bit(std::vector<uint8_t>& data, uint64_t val) {
   unsigned idx((unsigned)data.size());
   for (unsigned i = 0; i < 8; ++i)
     data.push_back(0);
   write64bit(idx, data, val);
 }

 /**
  * Append a 64-bit word in big endian mode
  * @param data
  * @param val
  */
 static inline void
 append64bit(std::string& data, uint64_t val) {
   unsigned idx((unsigned)data.size());
   for (unsigned i = 0; i < 8; ++i)
     data.push_back(0);
   write64bit(idx, data, val);
 }

 //----------------------------------------------------------------------------------------------
 // Iterator access

 using ByteIter = std::vector<uint8_t>::iterator;
 using ByteConstIter = std::vector<uint8_t>::const_iterator;

 /**
  * Read a zero terminated sequence of chars into a string
  * @param dataStart    Start of data buffer
  * @param dataEnd    End of data buffer
  * @return string or empty
  */
 static inline std::string
 readString(ByteConstIter& dataStart, ByteConstIter dataEnd) {
   std::string str;

   uint8_t cc;
   while ((cc = readByte(dataStart, dataEnd)) != 0x00)
     str.push_back(cc);
   return str;
 }

 /**
  * Write a string into data as a zero termiated sequence of chars
  * @param dataStart    Start of data buffer
  * @param dataEnd    End of data buffer
  * @param str    String to write
  */
 static inline void
 writeString(
     ByteTransfer::ByteIter& dataStart,
     ByteTransfer::ByteIter dataEnd,
     const std::string& str) {
   for (char cc : str)
     writeByte(dataStart, dataEnd, (uint8_t)cc);
   writeByte(dataStart, dataEnd, 0x00);
 }

 /**
  * Read a 64-bit word value from the data starting at the index 'idx'
  * @param dataStart    Start of data buffer
  * @param dataEnd    End of data buffer
  * @return 64-bit word
  */
 static inline uint64_t
 read64bit(ByteConstIter& dataStart, ByteConstIter dataEnd) {
   return readVal<uint64_t, 8>(dataStart, dataEnd);
 }

 /**
  * Read a 32-bit word value from the data starting at the index 'idx' (big
  * endian)
  * @param dataStart    Start of data buffer
  * @param dataEnd    End of data buffer
  * @return 32-bit word
  */
 static inline uint32_t
 readWord(ByteConstIter& dataStart, ByteConstIter dataEnd) {
   return readVal<uint32_t, 4>(dataStart, dataEnd);
 }

 /**
  * Read a 32-bit word value from the data starting at the index 'idx' (little
  * endian)
  * @param dataStart    Start of data buffer
  * @param dataEnd    End of data buffer
  * @return 32-bit word
  */
 static inline uint32_t
 readWordLE(ByteConstIter& dataStart, ByteConstIter dataEnd) {
   return readValLE<uint32_t, 4>(dataStart, dataEnd);
 }

 /**
  * Write 64-bit word into data start at the index 'idx'
  * @param dataStart    Start of data buffer
  * @param dataEnd    End of data buffer
  * @param word
  */
 static inline void
 write64bit(ByteIter& dataStart, ByteIter dataEnd, uint64_t word) {
   writeVal<uint64_t, 8>(dataStart, dataEnd, word);
 }

 /**
  * Write 32-bit word into data start at the index 'idx' (big endian)
  * @param dataStart    Start of data buffer
  * @param dataEnd    End of data buffer
  * @param word
  */
 static inline void
 writeWord(ByteIter& dataStart, ByteIter dataEnd, uint32_t word) {
   writeVal<uint32_t, 4>(dataStart, dataEnd, word);
 }

 /**
  * Write 32-bit word into data start at the index 'idx' (little endian)
  * @param dataStart    Start of data buffer
  * @param dataEnd    End of data buffer
  * @param word
  */
 static inline void
 writeWordLE(ByteIter& dataStart, ByteIter dataEnd, uint32_t word) {
   writeValLE<uint32_t, 4>(dataStart, dataEnd, word);
 }

 /**
  * Read a 24-bit word value from the data starting at the index 'idx' (big
  * endian)
  * @param dataStart    Start of data buffer
  * @param dataEnd    End of data buffer
  * @return 24-bit word
  */
 static inline uint32_t
 read24bit(ByteConstIter& dataStart, ByteConstIter dataEnd) {
   return readVal<uint32_t, 3>(dataStart, dataEnd);
 }

 /**
  * Read a 24-bit word value from the data starting at the index 'idx' (little
  * endian)
  * @param dataStart    Start of data buffer
  * @param dataEnd    End of data buffer
  * @return 24-bit word
  */
 static inline uint32_t
 read24bitLE(ByteConstIter& dataStart, ByteConstIter dataEnd) {
   return readValLE<uint32_t, 3>(dataStart, dataEnd);
 }

 /**
  * Write 24-bit word into data start at the index 'idx' (big endian)
  * @param dataStart    Start of data buffer
  * @param dataEnd    End of data buffer
  * @param word
  */
 static inline void
 write24bit(ByteIter& dataStart, ByteIter dataEnd, uint32_t word) {
   writeVal<uint32_t, 3>(dataStart, dataEnd, word);
 }

 /**
  * Write 24-bit word into data start at the index 'idx' (little endian)
  * @param dataStart    Start of data buffer
  * @param dataEnd    End of data buffer
  * @param word
  */
 static inline void
 write24bitLE(ByteIter& dataStart, ByteIter dataEnd, uint32_t word) {
   writeValLE<uint32_t, 3>(dataStart, dataEnd, word);
 }

 /**
  * Read a 16-bit short value from the data starting at the index 'idx' (big
  * endian)
  * @param dataStart    Start of data buffer
  * @param dataEnd    End of data buffer
  * @return 16-bit short
  */
 static inline uint16_t
 readShort(ByteConstIter& dataStart, ByteConstIter dataEnd) {
   return readVal<uint16_t, 2>(dataStart, dataEnd);
 }

 /**
  * Read a 16-bit short value from the data starting at the index 'idx' (little
  * endian)
  * @param dataStart    Start of data buffer
  * @param dataEnd    End of data buffer
  * @return 16-bit short
  */
 static inline uint16_t
 readShortLE(ByteConstIter& dataStart, ByteConstIter dataEnd) {
   return readValLE<uint16_t, 2>(dataStart, dataEnd);
 }

 /**
  * Write 16-bit short into data start at the index 'idx' (big endian)
  * @param dataStart    Start of data buffer
  * @param dataEnd    End of data buffer
  * @param shortval
  */
 static inline void
 writeShort(ByteIter& dataStart, ByteIter dataEnd, uint16_t shortval) {
   writeVal<uint16_t, 2>(dataStart, dataEnd, shortval);
 }

 /**
  * Write 16-bit short into data start at the index 'idx' (little endian)
  * @param dataStart    Start of data buffer
  * @param dataEnd    End of data buffer
  * @param shortval
  */
 static inline void
 writeShortLE(ByteIter& dataStart, ByteIter dataEnd, uint16_t shortval) {
   writeValLE<uint16_t, 2>(dataStart, dataEnd, shortval);
 }

 /**
  * Read a byte value from the data starting at the index 'idx'
  * @param dataStart    Start of data buffer
  * @param dataEnd    End of data buffer
  * @return byte
  */
 static inline uint8_t
 readByte(ByteConstIter& dataStart, ByteConstIter dataEnd) {
   if (dataStart == dataEnd)
     return 0;

   return *dataStart++;
 }

 /**
  * Write byte into data start at the index 'idx'
  * @param dataStart    Start of data buffer
  * @param dataEnd    End of data buffer
  * @param byte
  */
 static inline void
 writeByte(ByteIter& dataStart, ByteIter dataEnd, uint8_t byteval) {
   if (dataStart == dataEnd)
     return;

   *dataStart++ = byteval;
 }

 //----------------------------------------------------------------------------------------------
 // Debug

 /**
  * Debug utility to dump out data as hex and ascii
  * @param dataStart
  * @param dataEnd
  * @param os
  */
 static inline void
 dump(
     ByteConstIter dataStart,
     ByteConstIter dataEnd,
     std::ostream& os = std::cout) {
   unsigned dataSize((unsigned)std::distance(dataStart, dataEnd));
   std::stringstream addSs;
   std::stringstream dataSs;
   std::string prevData;
   std::string prevAscii;
   bool abbrev{false};

   for (unsigned idx = 0; idx < dataSize;) {
     addSs.str("");
     addSs << "0x" << std::setfill('0') << std::setw(4) << std::hex << idx
           << std::dec << "  ";

     std::string ascii(16, ' ');
     unsigned byte(0);
     for (; byte < 16 && idx < dataSize; ++byte, ++idx, ++dataStart) {
       dataSs << "0x" << std::setfill('0') << std::setw(2) << std::hex
              << (unsigned)*dataStart << std::dec << " ";

       if (byte == 7)
         dataSs << " ";

       if (isprint(*dataStart))
         ascii[byte] = (char)*dataStart;
       else
         ascii[byte] = '.';
     }

     if (byte <= 7)
       dataSs << " ";

     for (; byte < 16; ++byte) {
       dataSs << "     ";
     }

     // check to see if this data is same as previous
     bool newAbbrev(false);
     if (dataSs.str() == prevData)
       newAbbrev = true;

     // show we've been abbreviating if coming out of abbreviation
     if (abbrev && !newAbbrev)
       os << "***                                                              "
             "                          ***"
          << std::endl;

     // Don't output if currently abbreviating
     if (!newAbbrev)
       os << addSs.str() << dataSs.str() << "  |" << ascii << "|" << std::endl;

     // std::cerr << "abbrev=" << abbrev << " newAbbrev=" << newAbbrev <<
     //        " : " << addSs.str() <<
     //        " : data='" << dataSs.str() << "' prev='" << prevData << "'" <<
     //        std::endl ;

     prevData = dataSs.str();
     prevAscii = ascii;
     abbrev = newAbbrev;
     dataSs.str("");
   }

   // show we've been abbreviating if we still are
   if (abbrev) {
     os << "***                                                                "
           "                        ***"
        << std::endl;
     os << addSs.str() << prevData << "  |" << prevAscii << "|" << std::endl;
   }

   os << std::endl;
 }

 /**
  * Debug utility to dump out data as hex and ascii
  * @param dataStart
  * @param dataEnd
  * @param os
  */
 static inline void
 dump(const std::vector<uint8_t>& data, std::ostream& os = std::cout) {
   dump(data.cbegin(), data.cend(), os);
 }

 /**
  * Debug utility to dump out data as hex and ascii
  * @param dataStart
  * @param dataEnd
  * @param os
  */
 static inline void
 dump(const std::string& str, std::ostream& os = std::cout) {
   std::vector<uint8_t> data(str.begin(), str.end());
   dump(data.cbegin(), data.cend(), os);
 }

 //----------------------------------------------------------------------------------------------
 // Debug

 /**
  * Debug utility to dump out data as a std::vector<uint8_t> suitable for
  * including in C++
  * @param dataStart
  * @param dataEnd
  * @param os
  */
 static inline void
 dumpVector(
     ByteConstIter dataStart,
     ByteConstIter dataEnd,
     std::ostream& os = std::cout) {
   unsigned dataSize((unsigned)std::distance(dataStart, dataEnd));
   std::stringstream dataSs;

   os << "std::vector<uint8_t> DATA{" << std::endl;

   for (unsigned idx = 0; idx < dataSize;) {
     unsigned byte(0);
     for (; byte < 16 && idx < dataSize; ++byte, ++idx, ++dataStart) {
       if (!dataSs.str().empty())
         dataSs << ", ";

       dataSs << "0x" << std::setfill('0') << std::setw(2) << std::hex
              << (unsigned)*dataStart << std::dec;
     }

     if (idx < dataSize)
       dataSs << ",";

     os << dataSs.str() << std::endl;
     dataSs.str("");
   }

   os << "};" << std::endl;
 }

 /**
  * Debug utility to dump out data as hex and ascii
  * @param dataStart
  * @param dataEnd
  * @param os
  */
 static inline void
 dumpVector(const std::vector<uint8_t>& data, std::ostream& os = std::cout) {
   dumpVector(data.cbegin(), data.cend(), os);
 }

 /**
  * Debug utility to dump out data as hex and ascii
  * @param dataStart
  * @param dataEnd
  * @param os
  */
 static inline void
 dumpVector(const std::string& str, std::ostream& os = std::cout) {
   std::vector<uint8_t> data(str.begin(), str.end());
   dumpVector(data.cbegin(), data.cend(), os);
 }

private:
 template <typename T, int N>
 static inline T
 readVal(unsigned& idx, const std::string& data) {
   T val{0};
   for (unsigned byte = 0, shift = (N - 1) * 8; byte < N && idx < data.size();
        ++byte, ++idx, shift -= 8) {
     val |= (T)((uint8_t)(data[idx])) << shift;
   }
   return val;
 }

 template <typename T, int N>
 static inline void
 writeVal(unsigned& idx, std::string& data, T val) {
   for (unsigned byte = 0, shift = (N - 1) * 8; byte < N && idx < data.size();
        ++byte, ++idx, shift -= 8) {
     data[idx] = (uint8_t)(((val) >> shift) & 0xff);
   }
 }

 template <typename T, int N>
 static inline T
 readVal(unsigned& idx, const std::vector<uint8_t>& data) {
   T val{0};
   for (unsigned byte = 0, shift = (N - 1) * 8; byte < N && idx < data.size();
        ++byte, ++idx, shift -= 8) {
     val |= (T)(data[idx]) << shift;
   }
   return val;
 }

 template <typename T, int N>
 static inline void
 writeVal(unsigned& idx, std::vector<uint8_t>& data, T val) {
   for (unsigned byte = 0, shift = (N - 1) * 8; byte < N && idx < data.size();
        ++byte, ++idx, shift -= 8) {
     data[idx] = (uint8_t)(((val) >> shift) & 0xff);
   }
 }

 template <typename T, int N>
 static inline T
 readVal(ByteConstIter& dataStart, ByteConstIter dataEnd) {
   T val{0};
   for (unsigned byte = 0, shift = (N - 1) * 8;
        byte < N && dataStart != dataEnd;
        ++byte, shift -= 8) {
     val |= (T)(*dataStart++) << shift;
   }
   return val;
 }

 template <typename T, int N>
 static inline void
 writeVal(ByteIter& dataStart, ByteIter dataEnd, T val) {
   for (unsigned byte = 0, shift = (N - 1) * 8;
        byte < N && dataStart != dataEnd;
        ++byte, shift -= 8) {
     *dataStart++ = (uint8_t)(((val) >> shift) & 0xff);
   }
 }

 template <typename T, int N>
 static inline T
 readValLE(unsigned& idx, const std::vector<uint8_t>& data) {
   T val{0};
   for (unsigned byte = 0, shift = 0; byte < N && idx < data.size();
        ++byte, ++idx, shift += 8) {
     val |= (T)(data[idx] << shift);
   }
   return val;
 }

 template <typename T, int N>
 static inline void
 writeValLE(unsigned& idx, std::vector<uint8_t>& data, T val) {
   for (unsigned byte = 0, shift = 0; byte < N && idx < data.size();
        ++byte, ++idx, shift += 8) {
     data[idx] = (T)(((val) >> shift) & 0xff);
   }
 }

 template <typename T, int N>
 static inline T
 readValLE(ByteConstIter& dataStart, ByteConstIter dataEnd) {
   T val{0};
   for (unsigned byte = 0, shift = 0; byte < N && dataStart != dataEnd;
        ++byte, shift += 8) {
     val |= (T)(*dataStart++ << shift);
   }
   return val;
 }

 template <typename T, int N>
 static inline void
 writeValLE(ByteIter& dataStart, ByteIter dataEnd, T val) {
   for (unsigned byte = 0, shift = 0; byte < N && dataStart != dataEnd;
        ++byte, shift += 8) {
     *dataStart++ = (uint8_t)(((val) >> shift) & 0xff);
   }
 }
} ;

}

#endif /* BYTETRANSFER_HPP_ */
