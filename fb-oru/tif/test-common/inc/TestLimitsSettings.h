/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestLimitsSettings.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef TestLimitsSettings_H_
#define TestLimitsSettings_H_

#include "ILimitsSettings.h"

// Add any specific includes here %%-->

// <--%%

//=============================================================================================================
// CLASS
//=============================================================================================================

namespace Mplane {

class TestLimitsSettings : public ILimitsSettings
{
public:
	TestLimitsSettings() ;
	virtual ~TestLimitsSettings() ;

	/**
	 * Perform registration of any settings
	 */
	virtual void registerSettings() override ;

// Add any extra methods %%-->

// <--%%

} ;

}

#endif /* TestLimitsSettings_H_ */
