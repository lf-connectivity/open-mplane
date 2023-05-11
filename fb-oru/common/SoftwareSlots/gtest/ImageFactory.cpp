/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ImageFactory.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TestConstants.h"
#include "TestImageManagement.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IImageManagement> IImageManagement::getInstance()
{
    static std::shared_ptr<IImageManagement> pImageManagement(new TestImageManagement(TestConstants::TESTDIR));

    // auto start
    static int start = pImageManagement->start() ;

	// avoid compiler warning
	int rc = start ; start = rc ;

    return pImageManagement;
}
