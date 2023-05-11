#ifndef _VHI_INC_IPSU_H_
#define _VHI_INC_IPSU_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IPSU.h
 * \brief     A file to define generic interface to an IPsu (Power Supply Unit) Module
 *
 *
 * \details   A file to define generic interface to an IPsu (Power Supply Unit) Module
 *
 */

#include <memory>

#include "GlobalTypeDefs.h"

namespace Mplane
{

class IPsu
{
public:

    enum PsuState
    {
        DISABLED,
        ENABLED,
        UNKNOWN
    };

    virtual ~IPsu() { };

    // Get the state of the PSU (ON or OFF)
    virtual PsuState getState() = 0;

    // Get the voltage of the PSU
    virtual double getVoltage() = 0;

    // Enable the PSU
    virtual ReturnType::State psuEnable() = 0;

    // Disable the PSU
    virtual ReturnType::State psuDisable() = 0;

    // Set the voltage of the PSU
    virtual ReturnType::State setVoltage(double voltage) = 0;

    // Get an instance of the PSU interface
    static std::shared_ptr<IPsu> getInterface();

protected:

    IPsu() {};
};
}


#endif /* _VHI_INC_IPSU_H_ */
