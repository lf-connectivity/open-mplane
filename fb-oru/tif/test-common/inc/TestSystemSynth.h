#ifndef _TEST_SYSTEMSYNTH_H_
#define _TEST_SYSTEMSYNTH_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestSystemSynth.h
 * \brief     Defines a interface class for the main system clock chip synth/PLL
 *            specifically for the FTU. Originally SystemSynth.h
 *
 *
 * \details   Defines a interface class for the main system clock chip synth/PLL.
 *            specifically for the FTU. Originally SystemSynth.h
 *
 */

#include "ISystemSynth.h"
#include "Device.h"

namespace Mplane
{

/**
 * The class defines the interface to the radios main system clock. The LMK04806
 * device creates a number of time base reference clocks derived from the
 * main CPRI from clock timing.
 */
class TestSystemSynth: public virtual ISystemSynth, public Device
{
public:
    /**
     * Constructor sets the index in the device list.
     *
     * @param index
     */
    TestSystemSynth(int index);

    virtual ~TestSystemSynth();

    /**
     * Implementation of the pure virtual method to initialise the FTU device.
     *
     * \param data buffer containing the data to write
     * \param the data length
     *
     * \return RT_OK if successful, RT_other otherwise
     */
    virtual ReturnType::State initialise();

    virtual void show(void) override {}

};
} /* namespace Mplane */

#endif /* _TEST_SYSTEMSYNTH_H_ */
