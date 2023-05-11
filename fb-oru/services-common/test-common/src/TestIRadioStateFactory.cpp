/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestIRadioStateFactory.cpp
 * \brief     Test implementation of the IRadioStateFactory
 *
 *
 * \details   This file defines the stub implementation of the RadioState
 *            interface IRadioState class.
 *
 */

#include <memory>
#include "TestIRadioState.h"


using namespace Mplane;


/******* Base class interface implementation ***********/


std::shared_ptr<IRadioState> Mplane::IRadioState::getInstance( void )
{

    static std::shared_ptr<IRadioState> _pInstance(new TestRadioState());

    return _pInstance;
}
