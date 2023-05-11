/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Tca6416aGpio.h
 * \brief     GPIO expander
 *
 *
 * \details   GPIO expander that is configured via the Gpio control interface
 *
 */


#ifndef COMMON_TC6416AI2C_H_
#define COMMON_TC6416AI2C_H_

#include <mutex>
#include <map>
#include "bus/II2cBus.h"
#include "IGpioExpDriver.h"
#include "IGpioControl.h"
#include "Driver.h"

namespace Mplane {

/*!
 * \class  Tca6416aGpio driver class
 * \brief
 * \details
 *
 */
class Tca6416aGpio : public virtual IGpioExpDriver, public Driver
{
public:
	Tca6416aGpio(std::shared_ptr<IGpioControl> gpio, const std::string& name) ;
	virtual ~Tca6416aGpio() ;

    /**
     * This pure virtual method is used to write a value to the selected port. By using
     * the mask, only the required bits in the port can be written
     *
     * @param port 0 base port selector
     * @param value raw value to be written
     * @return true if write successful
     */
    virtual ReturnType::State write8BitPort( int port, UINT8 value, UINT8 mask = 0xFF ) override;

    /**
     * This pure virtual method is used to write a value to the selected D/A channel.
     *
     * @param channelIndex 0 base channel selector
     * @param value raw value to be written
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

	/**
	 * Initialise the driver
	 */
	virtual ReturnType::State initialise( void ) ;

    /*! \brief  Dump the reference clock status
     *
     *  Dump the state of the reference clock driver to the log file
     */
    virtual void show(std::ostream& os) override;

    /*! \brief  Dump the reference clock status
     *
     *  Dump the state of the reference clock driver to the console
     */
    virtual void show(void) override;

private:

    std::shared_ptr<IGpioControl> mGpio ;               //!> Pointer to the Gpio control class
	std::mutex mMutex;                                  //!> Mutex to protect the read and write operations
} ;

}

#endif /* COMMON_TC6416AI2C_H_ */
