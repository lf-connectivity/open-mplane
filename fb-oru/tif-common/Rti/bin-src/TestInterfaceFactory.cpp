/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestInterfaceFactory.cpp
 * \brief     Factory for creating objects of test interface
 *
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "TestInterfaceFactory.h"
#include "TestInterface.h"
#include "CommonCpri.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<TestInterfaceBase> TestInterfaceFactory::createInstance()
{
	return std::shared_ptr<TestInterfaceBase>(new TestInterface()) ;
}


std::shared_ptr<ICpri> Mplane::ICpri::getInterface()
{
    static std::shared_ptr<ICpri> _pTestInstance(new CommonCpri());

    return _pTestInstance;
}
