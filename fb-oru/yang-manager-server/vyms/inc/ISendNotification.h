/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IYangHandler.h
 * \brief     Handler layer between YANG models and application
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef VYMS_INC_ISENDNOTIFICATION_H_
#define VYMS_INC_ISENDNOTIFICATION_H_

#include <string>
#include "YangTypes.h"

namespace Mplane
{
class YangParams;
/*!
 * \class  IYangHandler
 * \brief
 * \details
 *
 */
class ISendNotification
{
public:
	virtual ~ISendNotification() {}

	/**
	 * Send out a notification with it's parameters
	 */
	virtual YangResult_E sendNotification(const std::string & xpath, std::shared_ptr<YangParams> params) = 0;
};

}

#endif /* VYMS_INC_ISENDNOTIFICATION_H_ */
