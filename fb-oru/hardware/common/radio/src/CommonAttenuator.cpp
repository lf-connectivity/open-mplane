/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonAttenuator.cpp
 * \brief     Implementation of the CommonAttenuator class
 *
 *
 * \details   This file contains the implementation of the hardware radio
 *            CommonAttenuator class.
 *
 */

// Includes go here, before the namespace
#include "CommonAttenuator.h"

using namespace Mplane;

Mplane::CommonAttenuator::CommonAttenuator(std::shared_ptr<IAttenuatorDriver> driver,
		int index, const char* name):
        AttnBase( driver, index, name )
{
}

Mplane::CommonAttenuator::~CommonAttenuator()
{
}
