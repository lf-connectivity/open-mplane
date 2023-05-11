/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangConfigSingleton.cpp
 * \brief     Yang config singleton
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "IYangConfig.h"
#include "YangConfig.h"

using namespace Mplane;

// ====================================================================================================
std::shared_ptr<IYangConfig> IYangConfig::getConfigSingleton(void)
{
	static std::shared_ptr<IYangConfig> instance(std::make_shared<YangConfig>()) ;
	return instance;
}
