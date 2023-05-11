/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SystemReboot.cpp
 * \brief     Reboots the system
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>

#include "SystemReboot.h"

using namespace Mplane;

//=============================================================================================================
// STATIC
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SystemReboot::SystemReboot()
{
}

//-------------------------------------------------------------------------------------------------------------
SystemReboot::~SystemReboot()
{
}

//-------------------------------------------------------------------------------------------------------------
int SystemReboot::now()
{
	Mutex::Lock lock(mMutex);

#ifdef OFF_TARGET // ONLY REBOOT IF ON TARGET
	throw std::runtime_error("System reboot request");
#else
	std::cerr << "System reboot request" << std::endl;
	return system("reboot");
#endif
}
