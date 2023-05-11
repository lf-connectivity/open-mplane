#ifndef _VRH_IGPIOEXP_H_
#define _VRH_IGPIOEXP_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IGpioExp.h
 * \brief     Pure virtual interface that defines methods need to access the GPIO Expander device.
 *
 *
 * \details   Pure virtual interface that defines methods need to access the GPIO Expander device.
 *
 */

#include <stdexcept>
#include <memory>

#include "IDevice.h"

namespace Mplane
{

class IGpioExp: public virtual IDevice
{
public:

    /**
     * This pure virtual method is used to write a value to the selected port. By using
     * the mask, only the required bits in the port can be written
     *
     * @param port 0 base port selector
     * @param value raw value to be written
     * @return true if write successful
     */
    virtual ReturnType::State write8BitPort( int port, UINT8 value, UINT8 mask = 0xFF ) = 0;

    /**
     * This pure virtual method is used to read the selected port.
     *
     * @param port 0 base port selector
     * @param value Port value read
     * @return true if write successful
     */
    virtual ReturnType::State read8BitPort( int port, UINT8& value ) = 0;

    /**
     * This pure virtual method is used to set direction of the pins on the selected port.
     *
     * @param port - 0 base port selector
     * @param dir - 8 bits for 8 pins on the port (1 = input, 0 = output)
     * @param mask - If it is possible to set direction of individual pins,
     * then the mask shall be used to decide which pin directions to set
     * @return true if set direction successful
     */
    virtual ReturnType::State setDirection( int port, UINT8 dir, UINT8 mask ) = 0;

    /*! \brief  Dump the GPIO expander status
     *
     *  Dump the state of the GPIO expander to the console or log file
     */
    virtual void show(std::ostream& os) = 0;
    virtual void show(void) = 0;

protected:
    // Must be defined in hardware/<BOARD>/radio/src/<Board>GpioExp.cpp
    static const char* mDevName;

    IGpioExp() {};

    virtual ~IGpioExp(){};
};

}

#endif /* _VRH_ICAM_H_ */
