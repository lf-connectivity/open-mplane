// (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

#include "Common.h"

#include <fstream>
#include <sstream>

std::string loadFile(const std::string &path) {
  std::ifstream inputStream(path);
  if (inputStream) {
    std::stringstream buffer;
    buffer << inputStream.rdbuf();
    return buffer.str();
  } else {
    throw std::runtime_error("File '" + path + "' does not exist");
  }
}
