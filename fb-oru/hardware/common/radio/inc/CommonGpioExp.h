#ifndef _RADIO_HARDWARE_COMMONGPIOEXP_H_
#define _RADIO_HARDWARE_COMMONGPIOEXP_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonGpioExp.h
 * \brief     A file to contain the common implementation of a generic GPIO Expnder.
 *
 *
 * \details   This file defines the common implementation of a generic GPIO Expander
 *            and expands on it if necessary.
 *
 */

#include <string>
#include "IGpioExp.h"
#include "IGpioExpDriver.h"
#include "Device.h"

namespace Mplane
{

class CommonGpioExp:  public virtual IGpioExp, public Device
{

public:


    /*! \brief  The doInit method
     *
     *  Method called by the initialise() method in Initialise.
     *  This is pure virtual and MUST be implemented by inheritors.
     *
     *  Means that this CommonGpioExp class does not provide any type specific
     *  initialisation. That is left to the inheritors who know what
     *  device they are.
     *
     *  The implementation is expected to set the following before returning:
     *  mInitResult - eg. to ReturnType::RT_OK if all is ok
     *  mInitResultString - eg. to "DAC INITIALISED OK" if all is ok
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State doInit();

    /**
     * This virtual method is used to write a value to the selected port. By using
     * the mask, only the required bits in the port can be written
     *
     * @param port 0 base port selector
     * @param value raw value to be written
     * @return true if write successful
     */
    virtual ReturnType::State write8BitPort( int port, UINT8 value, UINT8 mask = 0xFF ) override;

    /**
     * This virtual method is used to read the selected port.
     *
     * @param port 0 base port selector
     * @param value Port value read
     * @return true if write successful
     */
    virtual ReturnType::State read8BitPort( int port, UINT8& value ) override;

    /**
     * This pure virtual method is used to set direction of the pins on the selected port.
     *
     * @param port - 0 base port selector
     * @param dir - 8 bits for 8 pins on the port (1 = input, 0 = output)
     * @param mask - If it is possible to set direction of individual pins,
     * then the mask shall be used to decide which pin directions to set
     * @return true if set direction successful
     */
    virtual ReturnType::State setDirection( int port, UINT8 dir, UINT8 mask ) override;

    /*! \brief  Dump the GPIO expander status
     *
     *  Dump the state of the GPIO expander to the console or log file
     */
    virtual void show(std::ostream& os);
    virtual void show(void);

    /*! @brief  Default constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     *
     *  \param index  zero-based index
     *  \param number one-based number
     *  \param name   name string for the device
     */
    CommonGpioExp( std::shared_ptr<IGpioExpDriver> driver, int index, const char* name);

    /*! \brief Destructor
     *
     */
    virtual ~CommonGpioExp();

private:

    std::shared_ptr<IGpioExpDriver> mDriver;

};

} /* namespace Mplane */

#endif /* _RADIO_HARDWARE_COMMONGPIOEXP_H_ */
