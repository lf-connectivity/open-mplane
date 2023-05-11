/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangTypes.h
 * \brief     YANG types
 *
 *
 * \details   Types used by the YANG Manager and associated classes.
 *
 */

#ifndef YANG_TYPES_H_
#define YANG_TYPES_H_

// *****************************************************************************
// Includes
// *****************************************************************************
#include <cstdint>

namespace Mplane {

// *****************************************************************************
// Definitions
// *****************************************************************************

// *****************************************************************************
// Type Definitions
// *****************************************************************************
enum
{
	ITEM_NULL=-1,
};

typedef int32_t itemId_t;

enum class YangResult_E : uint8_t
{
	OK,
	FAIL,
	INVALID_TYPE,
	EXISTS,
	NOT_FOUND,
};

enum class YangParamType_E : uint8_t
{
	UNKNOWN,
	BOOL,
	STRING,
	INT8,
	INT16,
	INT32,
	INT64,
	UINT8,
	UINT16,
	UINT32,
	UINT64,
	DECIMAL64,
	BINARY
};

} /* namespace Mplane */

#endif /* YANG_TYPES_H_ */
