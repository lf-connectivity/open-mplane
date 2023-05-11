/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Mcp23S17Spi.h
 * \brief     GPIO expander
 *
 *
 * \details   GPIO expander that is configured via the SPI bus
 *
 */


#ifndef COMMON_MCP23S17SPI_H_
#define COMMON_MCP23S17SPI_H_

#include <mutex>
#include "bus/ISpiBus.h"
#include "IGpioExpDriver.h"
#include "RegDriver.h"
#include "RegModel.h"

namespace Mplane {

/*!
 * \class  Mcp23S17Spi driver class
 * \brief
 * \details
 *
 */
class Mcp23S17Spi : public virtual IGpioExpDriver, public RegDriver
{
public:
	Mcp23S17Spi(std::shared_ptr<ISpiBus> spi, const std::string& name) ;
	virtual ~Mcp23S17Spi() ;

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

protected:

	static const unsigned ADDR_WIDTH;
	static const unsigned DATA_WIDTH;
	static const unsigned ADDR_LSB; //The address is not part of the register data, hence setting it to max value

private:

	std::shared_ptr<ISpiBus> mSpi ;                                    //!> Pointer to the bus class
	std::mutex mMutex;                                                 //!> Mutex to protect the read and write operations
	std::vector<uint8_t> mPortValues;                                  //!> Cached port values
	std::vector<uint8_t> mPortDir;                                     //!> Cached port dir
} ;

}

#endif /* COMMON_MCP23S17SPI_H_ */
