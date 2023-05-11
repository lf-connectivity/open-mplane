/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonFpgadev.cpp
 * \brief     Implementation of the CommonFpgaDev class
 *
 *
 * \details   This file contains the implementation of the hardware radio
 *            CommonFpgaDev class.
 *
 */

// Includes go here, before the namespace
#include "CommonFpgaDev.h"

using namespace Mplane;

//////// CommonFpgaDev implementation //////////

Mplane::CommonFpgaDev::CommonFpgaDev(int index, const std::string& name):
        Device( Device::FPGA, index, name )

{

}

Mplane::CommonFpgaDev::~CommonFpgaDev()
{

}


void CommonFpgaDev::show(std::ostream& os)
{
}

void Mplane::CommonFpgaDev::show(void)
{
}
