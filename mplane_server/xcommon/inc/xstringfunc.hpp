#ifndef _COMMON_XSTRINGFUNC_HPP_
#define _COMMON_XSTRINGFUNC_HPP_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      xstringfunc.hpp
 * \brief     A collection of string helper functions used to manipulate the contents of std::string
 *
 *
 * \details   A collection of string helper functions used to manipulate the contents of std::string
 *
 */

#include <cctype>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>

namespace Mplane {

/**
 * Split string on 'delim' char
 * @param str        Input string
 * @param delim        Delimiter
 * @return vector of strings extracted from input string
 */
inline std::vector<std::string> split(const std::string& str, char delim)
{
  std::vector<std::string> result;
  std::stringstream ss(str);
  while (ss.good()) {
    std::string splitStr;
    getline(ss, splitStr, delim);
    result.push_back(splitStr);
  }
  return result;
}

/**
 * Join vector of strings using 'delim' char
 * @param strs        Input strings
 * @param delim        Delimiter
 * @return string of the individual strings combined with the delim char
 */
inline std::string join(const std::vector<std::string>& strs, char delim)
{
  std::string result;
  for (auto str : strs) {
    if (!result.empty())
      result += delim;
    result += str;
  }
  return result;
}

/**
 * Join set of strings using 'delim' char
 * @param strs        Input strings
 * @param delim        Delimiter
 * @return string of the individual strings combined with the delim char
 */
inline std::string join(const std::set<std::string>& strs, char delim)
{
  std::string result;
  for (auto str : strs) {
    if (!result.empty())
      result += delim;
    result += str;
  }
  return result;
}

}

#endif /* _XSTRINGFUNC_HPP_ */
