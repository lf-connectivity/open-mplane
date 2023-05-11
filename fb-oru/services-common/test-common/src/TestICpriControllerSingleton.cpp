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

#include "TestICpriController.h"

using namespace Mplane;


/******* Base class interface implementation ***********/

std::shared_ptr<ICpriController> Mplane::ICpriController::getInterface()
{
    static std::shared_ptr<ICpriController> _pInstance(new TestICpriController());

    return _pInstance;
}
