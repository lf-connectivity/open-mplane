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
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stringfunc.hpp"

#include "DataVariant/DataVariantList.h"
#include "IDataVariantSettings.h"
#include "Tokeniser.h"

using namespace Mplane;

//=============================================================================================================
// DataVariantList PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataVariantList::DataVariantList() : errorVar("") {}

//-------------------------------------------------------------------------------------------------------------
DataVariantList::DataVariantList(const char* fieldList) : errorVar("") {
  addFields(fieldList);
}

//-------------------------------------------------------------------------------------------------------------
DataVariantList::~DataVariantList() {
  std::vector<DataVariant*>::iterator iter;

  for (iter = list.begin(); iter != list.end(); ++iter) {
    delete (*iter);
  }
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariantList::addFields(const char* fieldList) {
  std::string fields(fieldList);
  Tokeniser varTokens(fields, ",");

  // Expect a specification string of the form:
  //
  //      INT Status,INT Version=1,ENUM(LTE5:LTE10) airstd,[STRING Msg]
  //
  // Optional values are enclosed in []
  //
  // Can also optionally specify value units in () after the name/value:
  //
  //      INT Freq (kHz),INT Power=10 (W),ENUM(LTE5:LTE10) airstd,[STRING Msg]
  //
  // For INT and FLOAT can now specify min/max/step values as:
  //
  //    INT{min..max/step}
  //
  // Note any of the above can be omitted:
  //
  //    INT{..max/step}
  //    INT{min../step}
  //    INT{/step}
  //    INT{..max}
  //    INT{min..}
  //
  while (varTokens.nextToken()) {
    std::string varSpec(varTokens.getToken());

    std::shared_ptr<IDataVariantSettings> settings(
        IDataVariantSettings::getInstance());
    std::string errorStr;

    // This needs to be in the form:
    //
    // TYPE NAME[=VALUE][ (UNITS)]
    //
    Tokeniser t(varSpec, " \t\n\r");
    std::vector<std::string> tokens(t.getTokens());

    // need at least a type and var
    if (tokens.size() < 2)
      continue;

    std::string type(tokens[0]);
    std::string name(tokens[1]);
    std::string units;

    // Check for optional variable: [STRING Msg]
    bool optional = false;
    if (tokens.size() >= 3) {
      // units specified
      units = tokens[2];
      if ((type[0] == '[') && (units.back() == ']')) {
        type = type.substr(1, std::string::npos);
        units = units.substr(0, units.size() - 1);
        optional = true;
      }

      // strip () from units
      if ((units[0] == '(') && (units.back() == ')'))
        units = units.substr(1, units.size() - 2);
    } else {
      if ((type[0] == '[') && (name.back() == ']')) {
        type = type.substr(1, std::string::npos);
        name = name.substr(0, name.size() - 1);
        optional = true;
      }
    }

    // Expand the type (allows for ENUM defined using a variable as the list)
    type = settings->expandString(type, errorStr);

    // See if default value has been specified
    std::string value;
    std::size_t equal = name.find("=");
    if (equal != std::string::npos) {
      // split variable/value
      value = name.substr(equal + 1, std::string::npos);
      name = name.substr(0, equal);
    }

    // Check the type for limits "{..}"
    std::string limitsStr;
    std::size_t limStart = type.find("{");
    std::size_t limEnd = type.find_last_of("}");
    if ((limStart != std::string::npos) && (limEnd != std::string::npos) &&
        (limEnd > limStart)) {
      limitsStr = type.substr(limStart + 1, limEnd - limStart - 1);
      type = type.substr(0, limStart);
    }

    // see if variable has already been set
    DataVariant* dv(find(name));
    if (dv == 0) {
      dv = new DataVariant(name, type);
      if (!add(dv))
        dv = 0;
    } else {
      // if it's the same type then silently ignore
      if ((dv->getTypeStr() != type) || (dv->isOptional() != optional))
        std::cerr << "Rti error, duplicate field name: " << name << std::endl;
    }

    // set default
    if (!value.empty()) {
      dv->set(value);
      dv->setDefault(value);
    }

    // set optional flag
    dv->setOptional(optional);

    // add units
    if (!units.empty())
      dv->setUnits(units);

    // Add limits
    if (!limitsStr.empty()) {
      // Expand any limits variables where possible
      limitsStr = settings->expandString(limitsStr, errorStr);
      dv->setLimits(limitsStr);

      // handle any errors
      if (!errorStr.empty())
        throw std::invalid_argument("Error in limits string : " + errorStr);
    }
  }
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantList::add(DataVariant* variant) {
  if (find(variant->getName()) == 0) {
    list.push_back(variant);
    return true;
  }

  // cannot add to list so destroy object and fail
  delete variant;
  return false;
}

//-------------------------------------------------------------------------------------------------------------
DataVariant*
DataVariantList::find(const std::string& name) {
  std::vector<DataVariant*>::iterator iter = findIter(name);
  if (iter != list.end()) {
    return *iter;
  }
  return nullptr;
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariantList::show() {
  std::vector<DataVariant*>::iterator iter;

  for (iter = list.begin(); iter != list.end(); ++iter) {
    DataVariant* varPtr = *iter;
    std::cout << varPtr->getNameValuePair() << " ";
  }
  std::cout << std::endl;
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantList::add(
    const std::string& name, const DataVariantType::Type& type) {
  DataVariant* variant = new DataVariant(type, name);
  return add(variant);
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantList::set(std::string valuePairs) {
  Tokeniser t(valuePairs, " \t\n\r");

  errorVar = "";

  // Clear all vars first
  clearValues();

  // process the set string
  std::vector<DataVariant*>::iterator iter(list.begin());
  while (t.nextToken()) {
    // Need to cope with strings of the format:
    //   var=val var=val ..
    //   val  var=val ...
    //   var[n]=val var=val ...
    //
    std::string token(t.getToken());

    // see if this a lone value or var=value pair
    if (token.find("=") == std::string::npos) {
      // if we've got too many arguments then stop now
      if (iter == list.end()) {
        errorVar = std::string("Surplus command line args at ") + token;
        return false;
      }

      // this is a single value - Try setting the current argument variable
      // using this token as the value
      (*iter)->set(token);

      // check setting
      if (!(*iter)->isSet()) {
        errorVar =
            "Invalid value '" + token + "' for '" + (*iter)->getName() + "'";
        return false;
      }

      ++iter;
      continue;
    }

    // This is a var=value pair
    Tokeniser tpair(token, "=");
    std::vector<std::string> fields(tpair.getTokens());
    if (fields.size() != 2) {
      errorVar = "Invalid argument '" + token + "'";
      return false;
    }
    std::string name(fields[0]);
    std::string value(fields[1]);
    if (name.empty() || value.empty()) {
      errorVar = "Invalid argument '" + token + "'";
      return false;
    }

    // check for indexed variable
    bool isVector = false;
    unsigned index;
    std::string baseName;
    if (DataVariant::getIndex(name, index, baseName)) {
      isVector = true;
      name = baseName;
    }

    // see if the first token matches an expected variable name
    DataVariant* variant = find(name);
    if (variant == 0) {
      errorVar = "Invalid argument '" + name + "'";
      return false;
    }

    // check that, if it's a vector variable, we're treating it properly
    if (isVector != variant->isVector()) {
      errorVar = name;
      if (isVector)
        errorVar =
            std::string("Specified vector assignment for non-vector ") + name;
      else
        errorVar =
            std::string("Specified non-vector assignment for vector ") + name;

      return false;
    }

    // handle vector
    if (variant->isVector())
      variant->set(index, value);
    else
      variant->set(value);

    // check setting
    if (!variant->isSet()) {
      errorVar = "Invalid value '" + value + "' for '" + name + "'";
      return false;
    }

    // Set the iterator to this variable, then step 1 past it ready for next
    // time round
    iter = findIter(name);
    if (iter != list.end())
      ++iter;
  }
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantList::allSet() {
  errorVar = "";
  bool ok = true;

  std::vector<DataVariant*>::const_iterator iter;
  for (iter = list.begin(); iter != list.end(); ++iter) {
    // if it's not set AND not optional then fail
    if (!(*iter)->isSet() && !(*iter)->isOptional()) {
      ok = false;
      if (!errorVar.empty())
        errorVar += ", ";
      errorVar += (*iter)->getName();
    }
  }

  return ok;
}

//-------------------------------------------------------------------------------------------------------------
std::string
DataVariantList::toString(const std::string& separator) {
  std::string result = "";

  std::vector<std::string> strings(toStrings());
  for (std::vector<std::string>::const_iterator iter(strings.begin());
       iter != strings.end();
       ++iter) {
    if (!result.empty())
      result += separator;
    result += *iter;
  }
  return result;
}

//-------------------------------------------------------------------------------------------------------------
std::string
DataVariantList::toStringFull(const std::string& separator) {
  std::string result = "";

  std::vector<std::string> strings(toStringsFull());
  for (std::vector<std::string>::const_iterator iter(strings.begin());
       iter != strings.end();
       ++iter) {
    if (!result.empty())
      result += separator;
    result += *iter;
  }
  return result;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string>
DataVariantList::toStrings() {
  std::vector<std::string> result;

  std::vector<DataVariant*>::iterator iter;
  for (iter = list.begin(); iter != list.end(); ++iter) {
    DataVariant* varPtr = *iter;

    std::vector<std::string> strings(varPtr->toStrings());
    result.insert(result.end(), strings.begin(), strings.end());
  }
  return result;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string>
DataVariantList::toStringsFull() {
  std::vector<std::string> result;

  std::vector<DataVariant*>::iterator iter;
  for (iter = list.begin(); iter != list.end(); ++iter) {
    DataVariant* varPtr = *iter;

    std::vector<std::string> strings(varPtr->toStringsFull());
    result.insert(result.end(), strings.begin(), strings.end());
  }
  return result;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::pair<std::string, std::string>>
DataVariantList::toVarVals() {
  std::vector<std::pair<std::string, std::string>> result;

  std::vector<DataVariant*>::iterator iter;
  for (iter = list.begin(); iter != list.end(); ++iter) {
    DataVariant* varPtr = *iter;

    // handle vector
    if (varPtr->isVector()) {
      std::vector<std::pair<std::string, DataVariant>> vectorVars(
          varPtr->getList());
      std::vector<std::pair<std::string, DataVariant>>::iterator vecIter;
      for (vecIter = vectorVars.begin(); vecIter != vectorVars.end();
           ++vecIter) {
        std::string valueStr(vecIter->second.getValueOptional());

        if (valueStr.empty())
          continue;

        result.push_back(make_pair(vecIter->first, valueStr));
      }

      continue;
    }

    // Single value
    std::string valueStr(varPtr->getValueOptional());

    if (valueStr.empty())
      continue;

    result.push_back(make_pair(varPtr->getName(), valueStr));
  }
  return result;
}

//-------------------------------------------------------------------------------------------------------------
std::string
DataVariantList::getError() {
  return errorVar;
}

//-------------------------------------------------------------------------------------------------------------
std::string
DataVariantList::varlist(const std::string& separator, bool showValue) {
  std::string result = "";

  std::vector<DataVariant*>::iterator iter;
  for (iter = list.begin(); iter != list.end(); ++iter) {
    DataVariant* varPtr = *iter;
    if (!result.empty())
      result += separator;

    if (varPtr->isOptional())
      result += "[";

    // TYPE
    result += varPtr->getTypeStr();

    // Limits
    result += varPtr->getLimitsStr();

    result += " ";

    // VAR[=VALUE]
    if (showValue && !varPtr->toString().empty())
      result += varPtr->getNameValuePairOptional();
    else
      result += varPtr->getName();

    // [ (UNITS)]
    if (!varPtr->getUnits().empty())
      result += " (" + varPtr->getUnits() + ")";

    if (varPtr->isOptional())
      result += "]";
  }

  return result;
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantList::empty() const {
  return list.empty();
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantList::superset(const std::string& fieldList) const {
  DataVariantList other(fieldList.c_str());

  return superset(other);
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantList::superset(const DataVariantList& other) const {
  // see if all fields in the fieldList are contained in this list
  std::vector<DataVariant*>::const_iterator iter;
  for (iter = other.list.begin(); iter != other.list.end(); ++iter) {
    DataVariant* varPtr = *iter;

    std::vector<DataVariant*>::const_iterator thisIter(
        findIter(varPtr->getName()));
    if (thisIter == list.end())
      return false;

    DataVariant* thisVarPtr = *thisIter;
    if (thisVarPtr->getTypeStr() != varPtr->getTypeStr())
      return false;
  }

  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantList::subset(const std::string& fieldList) const {
  DataVariantList other(fieldList.c_str());

  return subset(other);
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantList::subset(const DataVariantList& other) const {
  // see if all fields in this list are a subset of those in the fieldList
  std::vector<DataVariant*>::const_iterator iter;
  for (iter = list.begin(); iter != list.end(); ++iter) {
    DataVariant* varPtr = *iter;

    // ignore if this variable is optional
    if (varPtr->isOptional())
      continue;

    // ignore of this var has a default
    if (varPtr->isSet())
      continue;

    // if no variable in other list matching this variable name then fail
    std::vector<DataVariant*>::const_iterator otherIter(
        other.findIter(varPtr->getName()));
    if (otherIter == other.list.end())
      return false;

    DataVariant* otherVarPtr = *otherIter;

    // if types don't match then also fail
    if (otherVarPtr->getTypeStr() != varPtr->getTypeStr())
      return false;
  }

  return true;
}

//-------------------------------------------------------------------------------------------------------------
void
DataVariantList::clearValues() {
  std::vector<DataVariant*>::iterator iter;
  for (iter = list.begin(); iter != list.end(); ++iter) {
    DataVariant* varPtr = *iter;
    varPtr->clear();

    // Set with default if default is specified
    std::string defaultVal(varPtr->getDefault());
    if (!defaultVal.empty())
      varPtr->set(defaultVal);
  }
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantList::checkLimits(std::string& error) {
  bool ok(true);
  error = "";
  for (auto var : list) {
    std::string varError;
    if (!var->checkLimits(varError)) {
      ok = false;
      if (!error.empty())
        error.append(", ");
      error.append(varError);
    }
  }
  return ok;
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantList::checkLimits() {
  return checkLimits(errorVar);
}

//-------------------------------------------------------------------------------------------------------------
std::vector<DataVariant>
Mplane::DataVariantList::getList() const {
  std::vector<DataVariant> vec;
  for (auto dvp : list) {
    vec.push_back(*dvp);
  }
  return vec;
}

//=============================================================================================================
// DataVariantList PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::vector<DataVariant*>::iterator
DataVariantList::findIter(const std::string& name) {
  std::string lowerName(toLower(name));
  std::vector<DataVariant*>::iterator iter;

  for (iter = list.begin(); iter != list.end(); ++iter) {
    DataVariant* varPtr = *iter;
    if (varPtr->getLowerName() == lowerName) {
      return iter;
    }
  }
  return iter;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<DataVariant*>::const_iterator
DataVariantList::findIter(const std::string& name) const {
  std::string lowerName(toLower(name));
  std::vector<DataVariant*>::const_iterator iter;

  for (iter = list.begin(); iter != list.end(); ++iter) {
    DataVariant* varPtr = *iter;
    if (varPtr->getLowerName() == lowerName) {
      return iter;
    }
  }
  return iter;
}
