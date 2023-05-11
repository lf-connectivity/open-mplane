/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangParamUtils.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "YangParamUtils.h"
#include <sstream>

using namespace Mplane;

//=============================================================================================================
// LOCAL
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
namespace {

template <class T>
T
typeConvert(std::shared_ptr<YangParam> param, std::string& error) {
  error.clear();
  uint64_t uint64(YangParamUtils::toUint64(param, error));
  if (!error.empty())
    return 0;

  if (uint64 > std::numeric_limits<T>::max()) {
    error = "Value out of range";
    return 0;
  }

  return static_cast<T>(uint64);
}

} // namespace

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
unsigned
YangParamUtils::toUnsigned(
    std::shared_ptr<YangParam> param, std::string& error) {
  return toUint32(param, error);
}

//-------------------------------------------------------------------------------------------------------------
int
YangParamUtils::toInt(std::shared_ptr<YangParam> param, std::string& error) {
  return toInt32(param, error);
}

//-------------------------------------------------------------------------------------------------------------
uint64_t
YangParamUtils::toUint64(std::shared_ptr<YangParam> param, std::string& error) {
  uint64_t val(0);

  switch (param->getType()) {
    case YangParamType_E::BOOL:
      val = param->getBool() ? 1 : 0;
      break;

    case YangParamType_E::STRING: {
      std::string str(param->getString());
      val = strtoull(str.c_str(), nullptr, 10);
    } break;

    case YangParamType_E::INT8:
      val = static_cast<uint32_t>(param->getInt8());
      break;

    case YangParamType_E::INT16:
      val = static_cast<uint32_t>(param->getInt16());
      break;

    case YangParamType_E::INT32:
      val = static_cast<uint32_t>(param->getInt32());
      break;

    case YangParamType_E::INT64:
      val = static_cast<uint32_t>(param->getInt64());
      break;

    case YangParamType_E::UINT8:
      val = static_cast<uint32_t>(param->getUInt8());
      break;

    case YangParamType_E::UINT16:
      val = static_cast<uint32_t>(param->getUInt16());
      break;

    case YangParamType_E::UINT32:
      val = static_cast<uint32_t>(param->getUInt32());
      break;

    case YangParamType_E::UINT64:
      val = param->getUInt64();
      break;

    case YangParamType_E::UNKNOWN:
    default:
      error = "Invalid parameter";
      return 0;
  }

  return val;
}

//-------------------------------------------------------------------------------------------------------------
int64_t
YangParamUtils::toInt64(std::shared_ptr<YangParam> param, std::string& error) {
  return typeConvert<int64_t>(param, error);
}

//-------------------------------------------------------------------------------------------------------------
uint32_t
YangParamUtils::toUint32(std::shared_ptr<YangParam> param, std::string& error) {
  return typeConvert<uint32_t>(param, error);
}

//-------------------------------------------------------------------------------------------------------------
int32_t
YangParamUtils::toInt32(std::shared_ptr<YangParam> param, std::string& error) {
  return typeConvert<int32_t>(param, error);
}

//-------------------------------------------------------------------------------------------------------------
uint16_t
YangParamUtils::toUint16(std::shared_ptr<YangParam> param, std::string& error) {
  return typeConvert<uint16_t>(param, error);
}

//-------------------------------------------------------------------------------------------------------------
int16_t
YangParamUtils::toInt16(std::shared_ptr<YangParam> param, std::string& error) {
  return typeConvert<int16_t>(param, error);
}

//-------------------------------------------------------------------------------------------------------------
uint8_t
YangParamUtils::toUint8(std::shared_ptr<YangParam> param, std::string& error) {
  return typeConvert<uint8_t>(param, error);
}

//-------------------------------------------------------------------------------------------------------------
int8_t
YangParamUtils::toInt8(std::shared_ptr<YangParam> param, std::string& error) {
  return typeConvert<int8_t>(param, error);
}

//-------------------------------------------------------------------------------------------------------------
bool
YangParamUtils::toBool(std::shared_ptr<YangParam> param, std::string& error) {
  error.clear();
  uint64_t uint64(toUint64(param, error));
  if (!error.empty())
    return 0;

  return (uint64 > 0);
}

//-------------------------------------------------------------------------------------------------------------
std::string
YangParamUtils::toString(std::shared_ptr<YangParam> param, std::string& error) {
  switch (param->getType()) {
    case YangParamType_E::BOOL:
      return param->getBool() ? "true" : "false";
      break;

    case YangParamType_E::STRING:
      return param->getString();
      break;

    case YangParamType_E::BINARY: {
      std::vector<uint8_t> data = param->getBinaryEncoded();
      return std::string(data.begin(), data.end());
    } break;

    case YangParamType_E::INT8:
    case YangParamType_E::INT16:
    case YangParamType_E::INT32:
    case YangParamType_E::INT64: {
      int64_t val = (int64_t)toUint64(param, error);
      std::stringstream ss;
      ss << val;
      return ss.str();
    } break;

    case YangParamType_E::UINT8:
    case YangParamType_E::UINT16:
    case YangParamType_E::UINT32:
    case YangParamType_E::UINT64: {
      uint64_t val = toUint64(param, error);
      std::stringstream ss;
      ss << val;
      return ss.str();
    } break;

    case YangParamType_E::DECIMAL64: {
      double val = param->getDecimal64();
      std::stringstream ss;
      ss << val;
      return ss.str();
    } break;

    case YangParamType_E::UNKNOWN:
    default:
      error = "Invalid parameter";
      return "";
  }

  error = "Invalid type";
  return "";
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<YangParam>
YangParamUtils::find(
    std::shared_ptr<YangParams> params, const std::string& xpath) {
  for (unsigned i = 0; i < params->getNumParams(); ++i) {
    std::shared_ptr<YangParam> p(params->getParam(i));
    if (p->name() != xpath)
      continue;

    return p;
  }

  return std::shared_ptr<YangParam>();
}

//-------------------------------------------------------------------------------------------------------------
void
YangParamUtils::show(std::shared_ptr<YangParams> params) {
  for (unsigned i = 0; i < params->getNumParams(); ++i) {
    std::shared_ptr<YangParam> p(params->getParam(i));
    std::string error;

    std::cout << p->name() << " = " << toString(p, error) << std::endl;
  }
}
