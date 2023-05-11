/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonFem.cpp
 * \brief     Implementation of the CommonFem class
 *
 *
 * \details   This file contains the implementation of the hardware radio
 *            CommonFem class.
 *
 */

// Includes go here, before the namespace
#include "CommonFem.h"

using namespace Mplane;


Mplane::CommonFem::CommonFem(int index, int number, const char* name):
        Mplane::IFem::IFem( index, number, name )
{
}

bool Mplane::CommonFem::shutdown(void)
{
    // do the Fem shutdown - TBD

    return true;
}

UINT32 Mplane::CommonFem::getNumAntennaPorts()
{
    return CommonFem::numAntennaPorts;
}

Mplane::CommonFem::~CommonFem()
{
}

void Mplane::CommonFem::show(void)
{
}
