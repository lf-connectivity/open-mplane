/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariant.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <cctype>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stringfunc.hpp"

#include "DataVariant/DataVariantClass.h"
#include "DvTypeBase.h"
#include "Tokeniser.h"

using namespace Mplane;

//=============================================================================================================
// DataVariant PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataVariant::DataVariant()
    : DataVariantBase(), mSet(false), mIsVector(false), mValues(), mNames() {}

//-------------------------------------------------------------------------------------------------------------
DataVariant::DataVariant(const std::string& name)
    : DataVariantBase(name),
      mSet(false),
      mIsVector(false),
      mValues(),
      mNames() {}

//-------------------------------------------------------------------------------------------------------------
DataVariant::DataVariant(const std::string& name, const std::string& type)
    : DataVariantBase(name),
      mSet(false),
      mIsVector(false),
      mValues(),
      mNames() {
  unsigned index;
  std::string typeStr(type);
  if (getIndex(type, index, typeStr))
    mIsVector = true;

  // Set the type of this
  setType(typeStr);

  // now add to vector if necessary
  if (mIsVector) {
    // Add to vector
    getIndexedValue(index);
  }
}

//-------------------------------------------------------------------------------------------------------------
DataVariant::DataVariant(
    const DataVariantType::Type& type,
    const std::string& name,
    const std::string& value)
    : DataVariantBase(type, name, value),
      mSet(false),
      mIsVector(false),
      mValues(),
      mNames() {
  mSet = this->super::isSet();
}

//-------------------------------------------------------------------------------------------------------------
DataVariant::DataVariant(const DataVariant& value)
    : DataVariantBase(value),
      mSet(false),
      mIsVector(false),
      mValues(),
      mNames() {}

//-------------------------------------------------------------------------------------------------------------
DataVariant::DataVariant(const DataVariantBase& value)
    : DataVariantBase(value),
      mSet(false),
      mIsVector(false),
      mValues(),
      mNames() {}

//-------------------------------------------------------------------------------------------------------------
DataVariant::~DataVariant() { clearVector(); }

//-------------------------------------------------------------------------------------------------------------
bool
DataVariant::isSet() const {
  return mSet || this->super::isSet();
}

//-------------------------------------------------------------------------------------------------------------
DataVariant&
DataVariant::operator=(const DataVariant& rhs) {
  // if we're a vector, clear out the contents first
  clearVector();

  // copy DataVariantBase parts
  this->super::operator=(rhs);

  // copy DataVariant parts
  mIsVector = rhs.mIsVector;

  // stop now if not a vector
  if (!mIsVector)
    return *this;

  // copy vector
  for (ValuesConstIter iter(rhs.mValues.begin()); iter != rhs.mValues.end();
       ++iter) {
    mValues.push_back(new DataVariantBase(**iter));
  }
  for (NamesConstIter iter(rhs.mNames.begin()); iter != rhs.mNames.end();
       ++iter) {
    mNames.push_back(*iter);
  }

  return *this;
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariant::isVector() const {
  return mIsVector;
}

//-------------------------------------------------------------------------------------------------------------
unsigned
DataVariant::size() const {
  return mValues.size();
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::pair<std::string, DataVariant>>
DataVariant::getList() const {
  std::vector<std::pair<std::string, DataVariant>> list;

  if (!mIsVector) {
    // non vector
    list.push_back(make_pair(mName, DataVariant(*this)));
    return list;
  }

  // vector
  for (unsigned idx = 0; idx < mValues.size(); ++idx) {
    list.push_back(make_pair(mNames[idx], DataVariant(*mValues[idx])));
  }

  return list;
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariant::set(const DataVariant& rhs) {
  operator=(rhs);
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariant::set(const DataVariant* rhs) {
  operator=(*rhs);
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariant::set(const std::shared_ptr<DataVariant>& rhs) {
  operator=(*rhs);
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariant::set(
    unsigned index, const std::string& value, const std::string& name) {
  // vector only
  if (!mIsVector)
    return;

  // set element
  DataVariantBase& dv(getIndexedValue(index));
  dv.set(value);

  // set name
  setName(index, name);

  // mark this wrapper as set if any elements are set
  if (dv.isSet())
    mSet = true;

  // mirror element [0] in this object
  if (index == 0)
    set(value);
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariant::set(unsigned index, int value, const std::string& name) {
  // vector only
  if (!mIsVector)
    return;

  // set element
  DataVariantBase& dv(getIndexedValue(index));
  dv.setInt(value);

  // set name
  setName(index, name);

  // mark this wrapper as set if any elements are set
  if (dv.isSet())
    mSet = true;

  // mirror element [0] in this object
  if (index == 0)
    set(value);
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariant::set(unsigned index, float value, const std::string& name) {
  // vector only
  if (!mIsVector)
    return;

  // set element
  DataVariantBase& dv(getIndexedValue(index));
  dv.setFloat(value);

  // set name
  setName(index, name);

  // mark this wrapper as set if any elements are set
  if (dv.isSet())
    mSet = true;

  // mirror element [0] in this object
  if (index == 0)
    set(value);
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariant::set(
    unsigned index, const std::complex<float>& value, const std::string& name) {
  // vector only
  if (!mIsVector)
    return;

  // set element
  DataVariantBase& dv(getIndexedValue(index));
  dv.setComplex(value);

  // set name
  setName(index, name);

  // mark this wrapper as set if any elements are set
  if (dv.isSet())
    mSet = true;

  // mirror element [0] in this object
  if (index == 0)
    set(value);
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariant::setName(unsigned index, const std::string& name) {
  // vector only
  if (!mIsVector)
    return;

  if (name.empty())
    return;

  if (index >= mNames.size())
    return;

  mNames[index] = name;
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariant::set(const std::string& value) {
  this->super::set(value);
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariant::set(int value) {
  this->super::setInt(value);
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariant::set(float value) {
  this->super::setFloat(value);
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariant::set(const std::complex<float>& value) {
  this->super::setComplex(value);
}

//-------------------------------------------------------------------------------------------------------------
std::string
DataVariant::getNameValuePair() const {
  std::vector<std::string> list(toStringsFull());

  std::string result;
  std::vector<std::string>::const_iterator iter;
  for (iter = list.begin(); iter != list.end(); ++iter) {
    if (!result.empty())
      result += " ";
    result += *iter;
  }

  return result;
}

//-------------------------------------------------------------------------------------------------------------
std::string
DataVariant::getNameValuePairOptional() const {
  std::vector<std::string> list(toStrings());

  std::string result;
  std::vector<std::string>::const_iterator iter;
  for (iter = list.begin(); iter != list.end(); ++iter) {
    if (!result.empty())
      result += " ";
    result += *iter;
  }

  return result;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string>
DataVariant::toStrings() const {
  std::vector<std::string> result;

  if (!mIsVector) {
    std::string valueStr(this->super::getNameValuePairOptional());

    if (!valueStr.empty())
      result.push_back(valueStr);

    return result;
  }

  // handle vector case
  for (unsigned idx = 0; idx < mValues.size(); ++idx) {
    std::string valueStr(mValues[idx]->getNameValuePairOptional(mNames[idx]));

    if (valueStr.empty())
      continue;

    result.push_back(valueStr);
  }

  return result;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string>
DataVariant::toStringsFull() const {
  std::vector<std::string> result;

  if (!mIsVector) {
    std::string valueStr(this->super::getNameValuePair());

    if (!valueStr.empty())
      result.push_back(valueStr);

    return result;
  }

  // handle vector case
  for (unsigned idx = 0; idx < mValues.size(); ++idx) {
    std::string valueStr(mValues[idx]->getNameValuePair(mNames[idx]));

    if (valueStr.empty())
      continue;

    result.push_back(valueStr);
  }

  return result;
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DataVariant::getTypeStr() const {
  std::string typeStr(this->super::getTypeStr());

  if (!mIsVector)
    return typeStr;

  // handle vector case
  return typeStr + "[]";
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariant::clear() {
  mSet = false;

  if (!mIsVector) {
    // scalar clear
    this->super::clear();
    return;
  }

  // vector clear
  clearVector();
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariant::clearVector() {
  if (!mIsVector)
    return;

  for (ValuesIter iter(mValues.begin()); iter != mValues.end(); ++iter) {
    delete *iter;
  }
  mValues.clear();
  mNames.clear();
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariant::setLimits(const std::string& limitsStr) {
  if (!mIsVector)
    // scalar set
    return this->super::setLimits(limitsStr);

  for (auto value : mValues) {
    if (!value->setLimits(limitsStr))
      return false;
  }
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariant::setLimits(
    const std::string& minStr,
    const std::string& maxStr,
    const std::string& stepStr) {
  if (!mIsVector)
    // scalar set
    return this->super::setLimits(minStr, maxStr, stepStr);

  for (auto value : mValues) {
    if (!value->setLimits(minStr, maxStr, stepStr))
      return false;
  }
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariant::checkLimits() {
  if (!mIsVector)
    // scalar check
    return this->super::checkLimits();

  for (auto value : mValues) {
    if (!value->checkLimits())
      return false;
  }
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariant::checkLimits(std::string& error) {
  if (!mIsVector)
    // scalar check
    return this->super::checkLimits(error);

  for (auto value : mValues) {
    if (!value->checkLimits(error))
      return false;
  }
  return true;
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariant::setUnits(const std::string& units) {
  // set units on this object
  this->super::setUnits(units);
  if (!mIsVector)
    return;

  // propagate units down to all vector elements
  for (auto value : mValues) {
    value->setUnits(units);
  }
}

//=============================================================================================================
// DataVariant PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool
DataVariant::getIndex(
    const std::string& indexedStr, unsigned& index, std::string& baseStr) {
  // minimum string is something like 'a[]'
  if (indexedStr.length() < 3)
    return false;

  // find '['
  std::size_t idxStart(indexedStr.find_first_of("["));

  // skip if at start or end of string
  if ((idxStart == std::string::npos) || (idxStart == 0) ||
      (idxStart == indexedStr.length() - 1))
    return false;

  // find matching ']'
  std::size_t idxEnd(indexedStr.find_first_of("]", idxStart + 1));
  if (idxEnd == std::string::npos)
    return false;

  // Extract index and base name
  baseStr = indexedStr.substr(0, idxStart);
  index = 0;
  std::string idxStr(indexedStr.substr(idxStart + 1, idxEnd - idxStart - 1));
  if (DvTypeBase::strIsNumber(idxStr))
    index = atoi(idxStr.c_str());

  return true;
}

//-------------------------------------------------------------------------------------------------------------
DataVariantBase&
DataVariant::getIndexedValue(unsigned index) {
  if (!mIsVector)
    return *this;

  // Ensure vectors are the correct size
  for (unsigned idx = mValues.size(); idx <= index; ++idx) {
    // fill with unset DataVariants of the same type
    DataVariantBase* dvb(new DataVariantBase(*this));
    dvb->clear();
    mValues.push_back(dvb);

    // copy units over
    std::string units(getUnits());
    if (!units.empty())
      dvb->setUnits(units);

    // auto-generate a name
    std::stringstream ss;
    ss << mName << "[" << idx << "]";
    mNames.push_back(ss.str());
  }

  return *mValues[index];
}

//-------------------------------------------------------------------------------------------------------------
std::string&
DataVariant::getIndexedName(unsigned index) {
  if (!mIsVector)
    return mName;

  // Use getIndexValue() to ensure the vectors are the correct size
  getIndexedValue(index);

  return mNames[index];
}
