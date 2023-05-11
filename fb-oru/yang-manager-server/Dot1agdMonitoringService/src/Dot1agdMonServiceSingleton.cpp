/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Dot1agdMonServiceSingleton.cpp
 * \brief     Dot1agd monitoring service singleton
 *
 *
 * \details   Dot1agd (IEEE 802.1ag Daemon) monitoring service singleton
 *
 */
#include <memory>

#include "Dot1agdMonService.h"

using namespace Mplane;

std::shared_ptr<Dot1agdMonService> Dot1agdMonService::singleton(void)
{
	static std::shared_ptr<Dot1agdMonService> instance(std::make_shared<Dot1agdMonService>());
	return instance;
}
