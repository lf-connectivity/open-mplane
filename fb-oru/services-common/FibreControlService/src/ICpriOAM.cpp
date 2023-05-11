/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICpriOAM.cpp
 * \brief     Implementation of common radio services interface to the CPRI OAM interface
 *
 *
 * \details   Implementation of common radio services interface to the CPRI OAM interface
 *
 */

// Includes go here, before the namespace
#include "ICpriOAM.h"
#include "CpriController.h"

using namespace Mplane;

std::shared_ptr<ICpriOAM> Mplane::ICpriOAM::getInterface()
{
    return std::dynamic_pointer_cast<ICpriOAM>( ICpriController::getInterface() );
}

Mplane::ICpriOAM::~ICpriOAM()
{
}
