/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      XpathUtils.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "XpathUtils.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string
XpathUtils::leafName(const std::string& xpath) {
  std::string leaf(xpath);
  std::size_t pos(leaf.find_last_of('/'));
  if (pos == std::string::npos)
    return leaf;

  return leaf.substr(pos + 1);
}

//-------------------------------------------------------------------------------------------------------------
std::string
XpathUtils::leafPath(const std::string& xpath) {
  std::string path(xpath);
  std::size_t pos(path.find_last_of('/'));
  if (pos == std::string::npos)
    return path;

  return path.substr(0, pos);
}

//-------------------------------------------------------------------------------------------------------------
bool
XpathUtils::listIndex(
    const std::string& xpath,
    std::string& listName,
    std::string& key,
    std::string& value) {
  listName.clear();
  key.clear();
  value.clear();

  std::size_t start(xpath.find_first_of('['));
  if (start == std::string::npos)
    return false;

  std::size_t sep(xpath.find_last_of('/', start));
  if (sep == std::string::npos)
    return false;

  std::size_t stop(xpath.find_first_of(']', start + 1));
  if (stop == std::string::npos)
    return false;

  // set the list name
  listName = xpath.substr(sep + 1, start - sep - 1);

  // index string is now of the form:
  //  name='rxcc0'
  // or
  //  'rxcco'
  //
  std::string index(xpath.substr(start + 1, stop - start - 1));
  std::size_t eqpos(index.find_first_of('='));
  if (eqpos != std::string::npos) {
    key = index.substr(0, eqpos);
    index = index.substr(eqpos + 1);
  }

  // index should now be the key value with possible quotes
  if (index.empty())
    return false;

  std::size_t spos(0);
  std::size_t epos(index.size() - 1);
  if (index[spos] == '\'')
    ++spos;
  if (index[epos] == '\'')
    --epos;

  value = index.substr(spos, epos - spos + 1);
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
XpathUtils::listIndex(
    const std::string& xpath,
    std::string& listName,
    std::string& key,
    int& value) {
  std::string valstr;
  if (!listIndex(xpath, listName, key, valstr))
    return false;

  value = std::stoi(valstr);
  return true;
}

//-----------------------------------------------------------------------------
bool
XpathUtils::listIndexN(
    const std::string& xpath,
    std::string& listName,
    std::string& key,
    std::string& value,
    int n) {
  std::size_t start = 0;
  std::size_t prevBracket = 0;
  int i;
  for (i = 0; i < n; i++) {
    start = prevBracket;
    prevBracket = xpath.find_first_of(']', prevBracket + 1);
    if (prevBracket == std::string::npos) {
      break;
    }
  }
  if (i != n) {
    return false;
  }
  std::string subXpath = xpath.substr(start + 1);
  return listIndex(subXpath, listName, key, value);
}
