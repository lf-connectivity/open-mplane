/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LinuxPtpServiceSingleton.cpp
 * \brief     LinuxPTP service singleton
 *
 *
 * \details
 *
 */
#include "LinuxPtpService.h"

using namespace Mplane;

std::shared_ptr<ILinuxPtp> Mplane::ILinuxPtp::singleton()
{
	static std::shared_ptr<LinuxPtp> instance(std::make_shared<LinuxPtp>()) ;
	return instance ;
}
