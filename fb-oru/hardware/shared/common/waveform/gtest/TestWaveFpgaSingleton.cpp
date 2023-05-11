/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestWaveFpgaSingleton.cpp
 * \brief     Factory for creating the ETNA FTU FPGA
 *
 *
 * \details   Factory for creating the ETNA FTU FPGA
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "TestWaveformFpga.h"

using namespace Mplane;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpga> IFpga::getInstance(void)
{
    static std::shared_ptr<IFpga> instance(new TestWaveformFpga() ) ;
    return instance;
}
