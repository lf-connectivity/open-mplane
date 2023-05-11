/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangParam.h
 * \brief     YANG parameters for datastores
 *
 *
 * \details   YANG parameter wrappers
 *
 */

// *****************************************************************************
// Includes
// *****************************************************************************
#include <cstring>

#include "Base64.h"
#include "YangParam.h"

using namespace Mplane;

// *****************************************************************************
// Definitions
// *****************************************************************************
//#define TEST_DBG(test_debug)  test_debug
#define TEST_DBG(test_debug)

// *****************************************************************************
// Type Definitions
// *****************************************************************************

// *****************************************************************************
// YANG Parameter Classes
// *****************************************************************************

// -----------------------------------------------------------------------------
// Class:        YangParam
// Description:  YANG parameter container class.
// -----------------------------------------------------------------------------

//=============================================================================================================
// PUBLIC
//=============================================================================================================
YangParam::YangParam(bool param, const std::string& name) : YangParam() {
  setBool(param);
  setName(name);
}

YangParam::YangParam(int8_t param, const std::string& name) : YangParam() {
  setInt8(param);
  setName(name);
}

YangParam::YangParam(int16_t param, const std::string& name) : YangParam() {
  setInt16(param);
  setName(name);
}

YangParam::YangParam(int32_t param, const std::string& name) : YangParam() {
  setInt32(param);
  setName(name);
}

YangParam::YangParam(int64_t param, const std::string& name) : YangParam() {
  setInt64(param);
  setName(name);
}

YangParam::YangParam(uint8_t param, const std::string& name) : YangParam() {
  setUInt8(param);
  setName(name);
}

YangParam::YangParam(uint16_t param, const std::string& name) : YangParam() {
  setUInt16(param);
  setName(name);
}

YangParam::YangParam(uint32_t param, const std::string& name) : YangParam() {
  setUInt32(param);
  setName(name);
}

YangParam::YangParam(uint64_t param, const std::string& name) : YangParam() {
  setUInt64(param);
  setName(name);
}

YangParam::YangParam(const std::string& param, const std::string& name)
    : YangParam() {
  setString(param);
  setName(name);
}

YangParam::YangParam(double param, const std::string& name) : YangParam() {
  setDecimal64(param);
  setName(name);
}

YangParam::YangParam(const char* param, const std::string& name) : YangParam() {
  setString(std::string(param));
  setName(name);
}

YangParam::YangParam(
    const std::vector<uint8_t>& param, const std::string& name, bool encoded)
    : YangParam() {
  setBinary(param, encoded);
  setName(name);
}

YangParamType_E
YangParam::getType(void) const {
  return mType;
}

std::string
YangParam::name() const {
  return mName;
}

bool
YangParam::getBool(void) const {
  return mData.valBool;
}

int8_t
YangParam::getInt8(void) const {
  return mData.valInt8;
}

int16_t
YangParam::getInt16(void) const {
  return mData.valInt16;
}

int32_t
YangParam::getInt32(void) const {
  return mData.valInt32;
}

int64_t
YangParam::getInt64(void) const {
  return mData.valInt64;
}

uint8_t
YangParam::getUInt8(void) const {
  return mData.valUInt8;
}

uint16_t
YangParam::getUInt16(void) const {
  return mData.valUInt16;
}

uint32_t
YangParam::getUInt32(void) const {
  return mData.valUInt32;
}

uint64_t
YangParam::getUInt64(void) const {
  return mData.valUInt64;
}

std::string
YangParam::getString(void) const {
  return mData.valString;
}

double
YangParam::getDecimal64(void) const {
  return mData.valDecimal64;
}

std::vector<uint8_t>
YangParam::getBinaryEncoded(void) const {
  return mData.valBinary;
}

std::vector<uint8_t>
YangParam::getBinaryDecoded(void) const {
  std::string decodedStr = Base64::decode(mData.valBinary);
  std::vector<uint8_t> decodedVal(decodedStr.begin(), decodedStr.end());

  return decodedVal;
}

std::string
YangParam::getText(void) {
  std::string paramStr;

  switch (getType()) {
    case YangParamType_E::BOOL:
      paramStr = getBool() ? "true" : "false";
      break;
    case YangParamType_E::STRING:
      paramStr = getString();
      break;
    case YangParamType_E::INT8:
      paramStr = std::to_string(getInt8());
      break;
    case YangParamType_E::INT16:
      paramStr = std::to_string(getInt16());
      break;
    case YangParamType_E::INT32:
      paramStr = std::to_string(getInt32());
      break;
    case YangParamType_E::INT64:
      paramStr = std::to_string(getInt64());
      break;
    case YangParamType_E::UINT8:
      paramStr = std::to_string(getUInt8());
      break;
    case YangParamType_E::UINT16:
      paramStr = std::to_string(getUInt16());
      break;
    case YangParamType_E::UINT32:
      paramStr = std::to_string(getUInt32());
      break;
    case YangParamType_E::UINT64:
      paramStr = std::to_string(getUInt64());
      break;
    case YangParamType_E::DECIMAL64:
      paramStr = std::to_string(getDecimal64());
      break;
    case YangParamType_E::BINARY: {
      std::vector<uint8_t> data = getBinaryEncoded();
      paramStr = std::string(data.begin(), data.end());
    } break;

    case YangParamType_E::UNKNOWN:
    default:
      break;
  }
  return paramStr;
}

void
YangParam::dump() {
  std::cerr << "YANG Param: " << name() << "='" << getText() << "'"
            << std::endl;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================
YangParam::YangParam() : mType(YangParamType_E::UNKNOWN), mData(), mName() {}

YangParam::~YangParam() {}

void
YangParam::setBool(bool param) {
  mData.valBool = param;
  mType = YangParamType_E::BOOL;
}

void
YangParam::setInt8(int8_t param) {
  mData.valInt8 = param;
  mType = YangParamType_E::INT8;
}

void
YangParam::setInt16(int16_t param) {
  mData.valInt16 = param;
  mType = YangParamType_E::INT16;
}

void
YangParam::setInt32(int32_t param) {
  mData.valInt32 = param;
  mType = YangParamType_E::INT32;
}

void
YangParam::setInt64(int64_t param) {
  mData.valInt64 = param;
  mType = YangParamType_E::INT64;
}

void
YangParam::setUInt8(uint8_t param) {
  mData.valUInt8 = param;
  mType = YangParamType_E::UINT8;
}

void
YangParam::setUInt16(uint16_t param) {
  mData.valUInt16 = param;
  mType = YangParamType_E::UINT16;
}

void
YangParam::setUInt32(uint32_t param) {
  mData.valUInt32 = param;
  mType = YangParamType_E::UINT32;
}

void
YangParam::setUInt64(uint64_t param) {
  mData.valUInt64 = param;
  mType = YangParamType_E::UINT64;
}

void
YangParam::setString(const std::string param) {
  mData.valString = param;
  mType = YangParamType_E::STRING;
}

void
YangParam::setDecimal64(double param) {
  mData.valDecimal64 = param;
  mType = YangParamType_E::DECIMAL64;
}

void
YangParam::setBinary(std::vector<uint8_t> param, bool encoded) {
  if (encoded) {
    mData.valBinary = param;
  } else {
    std::string encodedStr = Base64::encode(param);
    mData.valBinary.assign(encodedStr.begin(), encodedStr.end());
  }
  mType = YangParamType_E::BINARY;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================
YangParam::uYangData_t::uYangData_t() : valDecimal64(0.0) {}

YangParam::uYangData_t::~uYangData_t() {}

// -----------------------------------------------------------------------------
// Class:        YangParams
// Description:  Group of YANG parameters container class.
// -----------------------------------------------------------------------------

//=============================================================================================================
// PUBLIC
//=============================================================================================================
YangParams::YangParams() : mParams() {}

YangParams::YangParams(std::vector<std::shared_ptr<YangParam>> params) {
  mParams = params;
}

YangResult_E
YangParams::addParam(std::shared_ptr<YangParams> params) {
  YangResult_E result = YangResult_E::OK;

  for (uint32_t idx = 0; idx < params->getNumParams(); idx++) {
    if (addParam(params->getParam(idx)) != YangResult_E::OK) {
      result = YangResult_E::FAIL;
    }
  }

  return result;
}

YangResult_E
YangParams::addParam(std::shared_ptr<YangParam> param) {
  YangResult_E result = YangResult_E::OK;

  mParams.push_back(param);
  TEST_DBG(param->dump());

  return result;
}

#define DEFINE_ADD_PARAM(type)                                             \
  YangResult_E YangParams::addParam(type param, const std::string& name) { \
    std::shared_ptr<YangParam> paramPtr(                                   \
        std::make_shared<YangParam>(param, name));                         \
    if (paramPtr == nullptr) {                                             \
      return YangResult_E::FAIL;                                           \
    }                                                                      \
                                                                           \
    mParams.push_back(paramPtr);                                           \
    TEST_DBG(paramPtr->dump());                                            \
                                                                           \
    return YangResult_E::OK;                                               \
  }

DEFINE_ADD_PARAM(bool)
DEFINE_ADD_PARAM(int8_t)
DEFINE_ADD_PARAM(int16_t)
DEFINE_ADD_PARAM(int32_t)
DEFINE_ADD_PARAM(int64_t)
DEFINE_ADD_PARAM(uint8_t)
DEFINE_ADD_PARAM(uint16_t)
DEFINE_ADD_PARAM(uint32_t)
DEFINE_ADD_PARAM(uint64_t)
DEFINE_ADD_PARAM(double)
DEFINE_ADD_PARAM(const std::string&)

YangResult_E
YangParams::addParam(const char* param, const std::string& name) {
  return addParam(std::string(param), name);
}

YangResult_E
YangParams::addParam(
    const std::vector<uint8_t>& param, const std::string& name, bool encoded) {
  std::shared_ptr<YangParam> paramPtr(
      std::make_shared<YangParam>(param, name, encoded));
  if (paramPtr == nullptr) {
    return YangResult_E::FAIL;
  }

  mParams.push_back(paramPtr);
  TEST_DBG(paramPtr->dump());

  return YangResult_E::OK;
}

uint32_t
YangParams::getNumParams(void) const {
  return mParams.size();
}

std::shared_ptr<YangParam>
YangParams::getParam(uint32_t index) const {
  return mParams[index];
}

std::vector<std::shared_ptr<YangParam>>
YangParams::getParamList(void) {
  return mParams;
}

YangParamType_E
YangParams::getType(uint32_t index) const {
  return mParams[index]->getType();
}

bool
YangParams::getBool(uint32_t index) const {
  return mParams[index]->getBool();
}

int8_t
YangParams::getInt8(uint32_t index) const {
  return mParams[index]->getInt8();
}

int16_t
YangParams::getInt16(uint32_t index) const {
  return mParams[index]->getInt16();
}

int32_t
YangParams::getInt32(uint32_t index) const {
  return mParams[index]->getInt32();
}

int64_t
YangParams::getInt64(uint32_t index) const {
  return mParams[index]->getInt64();
}

uint8_t
YangParams::getUInt8(uint32_t index) const {
  return mParams[index]->getUInt8();
}

uint16_t
YangParams::getUInt16(uint32_t index) const {
  return mParams[index]->getUInt16();
}

uint32_t
YangParams::getUInt32(uint32_t index) const {
  return mParams[index]->getUInt32();
}

uint64_t
YangParams::getUInt64(uint32_t index) const {
  return mParams[index]->getUInt64();
}

std::string
YangParams::getString(uint32_t index) const {
  return mParams[index]->getString();
}

double
YangParams::getDecimal64(uint32_t index) const {
  return mParams[index]->getDecimal64();
}

std::vector<uint8_t>
YangParams::getBinaryEncoded(uint32_t index) const {
  return mParams[index]->getBinaryEncoded();
}

std::vector<uint8_t>
YangParams::getBinaryDecoded(uint32_t index) const {
  return mParams[index]->getBinaryDecoded();
}

std::string
YangParams::getText(uint32_t index) {
  return mParams[index]->getText();
}

void
YangParams::dump() {
  for (auto param : mParams)
    param->dump();
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================
YangParams::~YangParams() {}

void
YangParam::setName(const std::string& name) {
  mName = name;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================
