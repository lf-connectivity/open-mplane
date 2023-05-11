/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangParamUtils.h
 * \brief     Conversion utilities for YangParam
 *
 *
 * \details   Convert YangParam from whatever value it is stored as into the required type
 *
 */


#ifndef YANG_MANAGER_INC_YANGPARAMUTILS_H_
#define YANG_MANAGER_INC_YANGPARAMUTILS_H_

#include <cstdint>
#include <memory>

#include "YangParam.h"

namespace Mplane {

/*!
 * \class  YangParamUtils
 * \brief
 * \details
 *
 */
class YangParamUtils {
public:
	/**
	 * Convert to unsigned
	 */
	static unsigned toUnsigned(std::shared_ptr<YangParam> param, std::string& error) ;

	/**
	 * Convert to int
	 */
	static int toInt(std::shared_ptr<YangParam> param, std::string& error) ;

	static uint64_t toUint64(std::shared_ptr<YangParam> param, std::string& error) ;
	static int64_t toInt64(std::shared_ptr<YangParam> param, std::string& error) ;
	static uint32_t toUint32(std::shared_ptr<YangParam> param, std::string& error) ;
	static int32_t toInt32(std::shared_ptr<YangParam> param, std::string& error) ;
	static uint16_t toUint16(std::shared_ptr<YangParam> param, std::string& error) ;
	static int16_t toInt16(std::shared_ptr<YangParam> param, std::string& error) ;
	static uint8_t toUint8(std::shared_ptr<YangParam> param, std::string& error) ;
	static int8_t toInt8(std::shared_ptr<YangParam> param, std::string& error) ;

	/**
	 * Convert to bool
	 */
	static bool toBool(std::shared_ptr<YangParam> param, std::string& error) ;

	/*
	 * Convert to string
	 */
	static std::string toString(std::shared_ptr<YangParam> param, std::string& error) ;

	/**
	 * Find a YangParam in a YangParams list using the param xpath. Returns the param or null if not found
	 */
	static std::shared_ptr<YangParam> find(std::shared_ptr<YangParams> params, const std::string& xpath) ;

	/**
	 * DEBUG - show the parameters
	 */
	static void show(std::shared_ptr<YangParams> params) ;

} ;

}

#endif /* YANG_MANAGER_INC_YANGPARAMUTILS_H_ */
