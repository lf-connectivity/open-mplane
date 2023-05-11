/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AppSettingsSingleton.cpp
 * \brief     Factory for creating AppSettings singleton
 *
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "IAppSettingsFactory.h"
#include "AppSettings.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAppSettings> IAppSettingsFactory::getInterface()
{
	static std::shared_ptr<IAppSettings> appSettings(new AppSettings) ;
	return appSettings ;
}
