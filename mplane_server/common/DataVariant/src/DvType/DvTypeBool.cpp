/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DvTypeBool.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DvTypeBool.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const std::string TYPE_STR{"BOOL"};
const std::string BOOL_ENUM_STR{"(false:true)"};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DvTypeBool::DvTypeBool(const std::string& typeStr)
    : DvTypeEnum(
          (typeStr.empty() || (typeStr == TYPE_STR))
              ? (TYPE_STR + BOOL_ENUM_STR)
              : typeStr) {
  //    std::cerr << "new DvTypeBool '" << typeStr << "'" << std::endl ;

  //    // see if it's just a generic BOOL
  //    if (typeStr.empty() || (typeStr == TYPE_STR))
  //        return ;
  //
  //    // Must have 2 and only 2 enumerations
  //    std::vector< std::string > enumList =
  // strToEnum(typeStr.substr(TYPE_STR.size(), std::string::npos)) ;     if
  //(enumList.size() != 2)         return ;
  //
  //    // ok to set the enumeration list
  //    setEnum(enumList) ;
}

//-------------------------------------------------------------------------------------------------------------
DvTypeBool::~DvTypeBool() {}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeBool::canSetValue(const std::string& value) const {
  if (strIsBool(value))
    return true;
  return false;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeBool::canSetType(const std::string& typeStr) const {
  if (typeStr.find(TYPE_STR) == 0) {
    // see if it's just a generic BOOL
    if (typeStr == TYPE_STR)
      return true;

    // Must have 2 and only 2 enumerations
    std::vector<std::string> enumList =
        strToEnum(typeStr.substr(TYPE_STR.size(), std::string::npos));
    return enumList.size() == 2;
  }
  return false;
}

//-------------------------------------------------------------------------------------------------------------
const std::string
DvTypeBool::getTypeStr() const {
  std::string typeStr(getInitialTypeStr());

  // If default string then just say we're a "BOOL"
  if (typeStr == TYPE_STR + BOOL_ENUM_STR)
    return TYPE_STR;

  // otherwise return actual type string used
  return typeStr;
}

//-------------------------------------------------------------------------------------------------------------
const DataVariantType::Type
DvTypeBool::getType() const {
  return DataVariantType::Bool;
}

//-------------------------------------------------------------------------------------------------------------
bool
DvTypeBool::set(const std::string& value) {
  // Try using ENUM
  if (this->super::set(value))
    return true;

  // Fallback to handling bool
  if (!strIsBool(value)) {
    clear();
    return false;
  }

  bool bval(strToBool(value));
  return setEnumValue(bval ? 1 : 0);
}

//-------------------------------------------------------------------------------------------------------------
bool
Mplane::DvTypeBool::setBool(bool value) {
  return setEnumValue(value ? 1 : 0);
}

//-------------------------------------------------------------------------------------------------------------
bool
Mplane::DvTypeBool::toBool() const {
  return (getEnumValue() > 0);
}
