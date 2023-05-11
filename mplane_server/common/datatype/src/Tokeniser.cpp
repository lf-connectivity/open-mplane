/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Tokenizer.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "Tokeniser.h"
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

const std::string Tokeniser::DELIMITERS(" \t\n\r");

// cppcheck-suppress warningId
// cppcheck-suppress performanceId
Tokeniser::Tokeniser(const std::string& s)
    : mString(s), mOffset(0), mDelimiters(DELIMITERS), mDelimiter(0) {}

// cppcheck-suppress warningId
// cppcheck-suppress performanceId
Tokeniser::Tokeniser(const std::string& s, const std::string& delimiters)
    : mString(s), mOffset(0), mDelimiters(delimiters), mDelimiter(0) {}

bool
Tokeniser::nextToken() {
  return nextToken(mDelimiters);
}

bool
Tokeniser::nextToken(const std::string& delimiters) {
  size_t index = mString.find_first_not_of(delimiters, mOffset);
  if (std::string::npos == index) {
    mOffset = mString.length();
    return false;
  }

  if (index > 0) {
    mDelimiter = mString[index - 1];
  } else {
    mDelimiter = 0;
  }

  size_t subindex = mString.find_first_of(delimiters, index);
  if (std::string::npos == subindex) {
    mToken = mString.substr(index);
    mOffset = mString.length();
    return true;
  }

  mToken = mString.substr(index, subindex - index);
  mOffset = subindex;
  return true;
}

bool
Tokeniser::hasNextToken() const {
  return hasNextToken(mDelimiters);
}

bool
Tokeniser::hasNextToken(const std::string& delimiters) const {
  size_t index = mString.find_first_not_of(delimiters, mOffset);
  if (std::string::npos == index) {
    return false;
  }
  return true;
}

const std::string
Tokeniser::getToken() const {
  return mToken;
}

void
Tokeniser::reset() {
  mOffset = 0;
  mToken = "";
  mDelimiter = 0;
}

char
Tokeniser::getDelimiter() const {
  return mDelimiter;
}

std::vector<std::string>
Tokeniser::getTokens() {
  std::vector<std::string> tokens;
  while (nextToken()) {
    tokens.push_back(getToken());
  }

  return tokens;
}
