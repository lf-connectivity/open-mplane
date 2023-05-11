/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      EtnaRrhStaicSystemSynth.c
 * \brief     Factory use to create and return and instance of the ETNA RRH System Synth
 *
 *
 * \details   Factory use to create and return and instance of the ETNA RRH System Synth
 *
 */


#include "TestSystemSynth.h"

using namespace Mplane ;

/**
 * Implement static SystemSynth get instance using the ETNA specific radio implementation.
 *
 * @return a pointer to a EtnaFpga that is a SystemSynth implementation
 */
std::shared_ptr<SystemSynth> SystemSynth::getInstance(int index)
{
    static std::shared_ptr<SystemSynth> SystemSynth( std::make_shared<TestSystemSynth>(index) );

    return SystemSynth;
}
