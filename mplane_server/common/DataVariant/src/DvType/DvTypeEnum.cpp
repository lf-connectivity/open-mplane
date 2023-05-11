/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DvTypeEnum.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DvTypeEnum.h"
#include "stringfunc.hpp"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const std::string TYPE_STR{"ENUM"};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DvTypeEnum::DvTypeEnum(const std::string& typeStr)
    : DvTypeBase(typeStr), mEnumIdx(0), mEnum() {
  //    std::cerr << "new DvTypeEnum '" << typeStr << "'" << std::endl ;

  if (typeStr.size() > TYPE_STR.size())
    mEnum = strToEnum(typeStr.substr(TYPE_STR.size(), std::string::npos));
}

//-------------------------------------------------------------------------------------------------------------
DvTypeEnum::~DvTypeEnum() {}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeEnum::canSetValue(const std::string& value) const {
  if (mEnum.empty())
    return false;

  // See if this is a valid value
  std::vector<std::string>::const_iterator iter = findEnum(value);
  if (iter == mEnum.end())
    return false;

  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeEnum::canSetType(const std::string& typeStr) const {
  if (typeStr.find(TYPE_STR) == 0) {
    std::vector<std::string> enumList =
        strToEnum(typeStr.substr(TYPE_STR.size(), std::string::npos));
    return enumList.size() > 0;
  }
  return false;
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeEnum::getTypeStr() const {
  std::string typeStr(TYPE_STR + getEnumStr());
  return typeStr;
}

//-------------------------------------------------------------------------------------------------------------
const DataVariantType::Type
DvTypeEnum::getType() const {
  return DataVariantType::Enum;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeEnum::set(const std::string& value) {
  return setEnumValue(value);
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterInt
DvTypeEnum::toInterInt() const {
  return static_cast<IDvAccess::InterInt>(mEnumIdx);
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterFloat
DvTypeEnum::toInterFloat() const {
  return static_cast<IDvAccess::InterFloat>(mEnumIdx);
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeEnum::fromInterInt(const IDvAccess::InterInt& value) {
  return setEnumValue(static_cast<unsigned>(value));
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeEnum::fromInterFloat(const IDvAccess::InterFloat& value) {
  return setEnumValue(static_cast<unsigned>(value));
}

//-------------------------------------------------------------------------------------------------------------
void
DvTypeEnum::clear() {
  mEnumIdx = 0;
  this->DvTypeBase::clear();
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
DvTypeEnum::setEnum(const std::vector<std::string>& enumList) {
  mEnum = enumList;

  //    std::cerr << "DvTypeEnum::setEnum '"  ;
  //    for (auto e : enumList)
  //    {
  //        std::cerr << e << ":" << std::endl ;
  //    }
  //    std::cerr << "'" << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeEnum::setEnumValue(const std::string& valueStr) {
  //    setStr("") ;
  mEnumIdx = 0;
  std::vector<std::string>::const_iterator iter = findEnum(valueStr);
  if (iter == mEnum.end()) {
    clear();
    return false;
  }

  setStr(*iter);
  mEnumIdx = std::distance(mEnum.cbegin(), iter);
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeEnum::setEnumValue(unsigned value) {
  if (value >= mEnum.size())
    return false;

  mEnumIdx = value;
  setStr(mEnum[mEnumIdx]);
  return true;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string>::const_iterator
DvTypeEnum::findEnum(const std::string& value) const {
  std::string lower(toLower(value));
  for (std::vector<std::string>::const_iterator iter = mEnum.begin();
       iter != mEnum.end();
       ++iter) {
    if (toLower(*iter) == lower) {
      return iter;
    }
  }

  return mEnum.end();
}

//-------------------------------------------------------------------------------------------------------------
std::string
DvTypeEnum::getEnumStr() const {
  if (mEnum.empty())
    return "";

  std::string enumStr("(");
  for (std::vector<std::string>::const_iterator iter(mEnum.begin());
       iter != mEnum.end();
       ++iter) {
    if (iter != mEnum.begin())
      enumStr += ":";
    enumStr += *iter;
  }
  enumStr += ")";
  return enumStr;
}

//-------------------------------------------------------------------------------------------------------------
unsigned
DvTypeEnum::getEnumValue() const {
  return mEnumIdx;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string>
DvTypeEnum::getEnum() const {
  return mEnum;
}
