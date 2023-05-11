/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestIFibreControl.cpp
 * \brief     Implementation of the Fibre control interface IFibreControl class
 *
 *
 * \details   This file defines the stub implementation of the Fibre control
 *            interface IFibreControl class.
 *
 */

#include <memory>
#include "TestIFibreControl.h"

using namespace Mplane;


/******* Base class interface implementation ***********/

std::shared_ptr<IFibreControl> Mplane::IFibreControl::getInterface()
{
    static std::shared_ptr<IFibreControl> _pInstance(new TestIFibreControl());

    return _pInstance;
}
