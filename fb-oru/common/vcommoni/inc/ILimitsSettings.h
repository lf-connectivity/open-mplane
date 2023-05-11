/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ILimitsSettings.h
 * \brief     TIF command arguments limits variables
 *
 *
 * \details
 *
 */


#ifndef ILIMITSSETTINGS_H_
#define ILIMITSSETTINGS_H_

#include <memory>

namespace Mplane {

class ILimitsSettings {
public:
	ILimitsSettings() {}
	virtual ~ILimitsSettings() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<ILimitsSettings> getInstance() ;

	/**
	 * Perform registration of any settings
	 */
	virtual void registerSettings() =0 ;

} ;

}

#endif /* ILIMITSSETTINGS_H_ */
