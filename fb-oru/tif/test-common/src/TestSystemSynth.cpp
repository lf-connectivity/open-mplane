/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestSystemSynth.cpp
 * \brief     Implement the interface to the main system clock synth/PLL.
 *
 *
 * \details   Implement the interface to the main system clock synth/PLL.
 *
 */

#include "GlobalTypeDefs.h"
#include "TestSystemSynth.h"

using namespace Mplane;

Mplane::TestSystemSynth::TestSystemSynth(int index) :
	Device(Device::SYNTH, index, 0, "TestSystemSynth")
{
/*
 * Nothing to do here?
 */
}

Mplane::TestSystemSynth::~TestSystemSynth()
{
}

ReturnType::State Mplane::TestSystemSynth::initialise()
{
    return ReturnType::RT_OK;
}
