/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhTestInterfaceFactory.cpp
 * \brief     Factory for creating objects of test interface for ZCU111-FBC-ORANRRH
 *
 *
 * \details   Auto-generated by gentool. Contains test interface definitions.
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <memory>
#include "TestInterfaceFactory.h"
#include "Zcu111FbcOranrrhTestInterface.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<TestInterfaceBase> TestInterfaceFactory::createInstance()
{
	return std::shared_ptr<TestInterfaceBase>( new Zcu111FbcOranrrhTestInterface() ) ;
}
