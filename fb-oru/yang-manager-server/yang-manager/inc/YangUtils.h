/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangUtils.h
 * \brief     YANG Utilites
 *
 *
 * \details   Utilities used by the YANG Manager and associated classes.
 *
 */

#ifndef YANG_UTILS_H_
#define YANG_UTILS_H_

// *****************************************************************************
// Includes
// *****************************************************************************
#include <cstdint>
#include <string>
#include <memory>
#include <ctime>

namespace Mplane {

// *****************************************************************************
// Definitions
// *****************************************************************************

// *****************************************************************************
// Type Definitions
// *****************************************************************************

// *****************************************************************************
// Class Definitions
// *****************************************************************************
/*!
 * \class  YangUtils
 * \brief
 * \details
 *
 */
class YangUtils
{
public:
	YangUtils();
	virtual ~YangUtils();

	/*
	 * Get date time in YANG format
	 */
	static std::string getDateTime(time_t timestamp);
	static std::string getDateTime(struct tm * timeInfo);

};

} /* namespace Mplane */

#endif /* YANG_UTILS_H_ */
