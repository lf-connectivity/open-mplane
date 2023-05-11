/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestImageManagementFactory.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TestImageManagement.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
// The interface to the singleton
std::shared_ptr<IImageManagement> IImageManagement::getInstance()
{
    static std::shared_ptr<IImageManagement> pImageManagement(new TestImageManagement());

    // auto start
    static int start = pImageManagement->start() ;

	// avoid compiler warning
	int rc = start ; start = rc ;

    return pImageManagement;
}
