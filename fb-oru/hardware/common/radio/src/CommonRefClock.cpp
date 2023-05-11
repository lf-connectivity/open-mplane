/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRefClock.cpp
 * \brief     Implementation of the CommonRefClock class
 *
 *
 * \details   This file contains the implementation of the hardware radio
 *            CommonRefClock class.
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

// Includes go here, before the namespace
#include "CommonRefClock.h"
#include <iostream>

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//---------------------------------------------------------------------------------------------------------------------------------------------------
Mplane::CommonRefClock::CommonRefClock(std::shared_ptr<IRefClockDriver> driver, int index, const std::string& name):
	Device( Device::REFCLOCK, index, name ),
	mDriver( driver )
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
Mplane::CommonRefClock::~CommonRefClock()
{

}

//---------------------------------------------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::CommonRefClock::doInit()
{
	ReturnType::State rc = mDriver->initialise();

    setInitResult(rc);
    std::string str = getName() + " Init" + ReturnType::getState(rc);
    setInitResultString(str);
    return rc;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
bool Mplane::CommonRefClock::isPllLocked(void)
{
	return mDriver->isPllLocked();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
void Mplane::CommonRefClock::forceOutOfLock(void)
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
void CommonRefClock::show(std::ostream& os)
{
	os << "Reference clock device : " << getName() << std::endl;
	mDriver->show(os);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
void Mplane::CommonRefClock::show(void)
{
	show(std::cout);
}
