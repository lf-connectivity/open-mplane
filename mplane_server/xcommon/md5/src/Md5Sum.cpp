/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Md5Sum.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <cstdint>
#include <iomanip>
#include <sstream>

#include "Md5Sum.h"
#include "PathUtils.h"
#include "md5.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Md5Sum::Md5Sum() : mFilename(""), mSum("") {}

//-------------------------------------------------------------------------------------------------------------
Md5Sum::Md5Sum(const std::string& filename) : Md5Sum() {
  setFilename(filename);
}

//-------------------------------------------------------------------------------------------------------------
Md5Sum::~Md5Sum() {}

//-------------------------------------------------------------------------------------------------------------
void
Md5Sum::setFilename(const std::string& filename) {
  mSum.clear();
  mFilename = filename;
}

//-------------------------------------------------------------------------------------------------------------
std::string
Md5Sum::sum() {
  if (!mSum.empty())
    return mSum;

  // Need to calculate the sum
  if (mFilename.empty())
    return "";

  if (!PathUtils::isFile(mFilename))
    return "";

  FILE* fp = fopen(mFilename.c_str(), "r");
  if (fp == nullptr)
    return "";

  unsigned char md5buffer[16];
  int rc = md5_stream(fp, md5buffer);
  fclose(fp);

  if (rc != 0)
    return "";

  std::stringstream ss;
  for (unsigned i = 0; i < 16; ++i) {
    ss << std::setw(2) << std::setfill('0') << std::hex
       << (unsigned)md5buffer[i];
  }
  return ss.str();
}
