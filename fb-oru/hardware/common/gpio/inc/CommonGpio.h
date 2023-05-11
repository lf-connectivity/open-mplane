#ifndef _RADIO_HARDWARE_COMMONGPIO_H_
#define _RADIO_HARDWARE_COMMONGPIO_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonGpio.h
 * \brief     A file to contain the common implementation of a generic gpio interface.
 *
 *
 * \details   This file defines the common implementation of a gpio interface
 *            and expands on it if necessary.
 *
 */

#include "IGpio.h"

// Combine in the register access
#include "CommonGpioRegs.h"


namespace Mplane
{

class CommonGpio : public IGpio,
                   public CommonGpioRegs
{
    /*
     * In an OFF_TARGET build we allow the Test harness to be our friend
     */
//    friend class CommonGpioTestCase;

public:

    /*! \brief  Get the singleton instance
     *
     *  Used to get a reference to the single instance of the common gpio
     *  object.
     */
    static std::shared_ptr<CommonGpio> getInstance(void);

    /*! \brief  The initialise method
     *
     *  Method called during system startup, to fully
     *  initialise the device and to override any initial settings with
     *  board-specific ones.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise(void);


    /*! \brief  Read a gpio register
     *
     *  Method used to return a gpio register value at the specified offset.
     *
     *  \return  UINT32 gpio register contents
     */
    virtual UINT32 readRegister(unsigned offset) ;

    /*! \brief  Write a gpio register
     *
     *  Method used to write a gpio register value at the specified offset.
     *
     */
    virtual void writeRegister(unsigned offset, UINT32 value) ;

    /*! \brief  Modify an gpio register
     *
     *  Method used to write a gpio register value at the specified offset.
     *
     */
    virtual void modifyRegister(unsigned offset, UINT32 value, UINT32 mask) ;

    /*
     * Method to set one of the GPIO pins of the power PC
     */
    virtual void setOutput(unsigned int pin);

    /*
     * Method to reset one of the GPIO pins of the power PC
     */
    virtual void resetOutput(unsigned int pin);

    /*
     * Protected methods to allow friend classes access to the FPGA
     */

    /*! Destructor
     *
     *  Destructor, should never be called.
     */
    virtual ~CommonGpio() { };

protected:

    /*! \brief  Constructor
     *
     */
    CommonGpio();


private:

     /*!
     * Flag used to indicate that module initialisation has completed.
     */
    bool mInitComplete;


};

typedef std::shared_ptr<CommonGpio> CommonGpioPtr ;


} /* namespace Mplane */

#endif /* _RADIO_HARDWARE_COMMONGPIO_H_ */
