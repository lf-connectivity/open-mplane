/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SI570.h
 * \brief     Programmable clock source
 *
 *
 * \details   Programmable clock source that is configured via the I2C bus
 *
 */


#ifndef COMMON_I2C_INC_SI570_H_
#define COMMON_I2C_INC_SI570_H_

#include "bus/II2cBus.h"
#include "IRefClockDriver.h"
#include "RegDriver.h"
#include "RegModel.h"

namespace Mplane {

/*!
 * \class  SI570 driver class
 * \brief
 * \details
 *
 */
class SI570 : public virtual IRefClockDriver, public RegDriver
{
public:
	SI570(std::shared_ptr<II2cBus> spi, const std::string& name) ;
	virtual ~SI570() ;

	static const std::vector< std::pair<uint32_t, uint32_t> > mPreamble;
	static const std::vector< std::pair<uint32_t, uint32_t> > mPostamble;

	/**
	 * Initialise the driver
	 */
	virtual ReturnType::State initialise( void ) ;

    /*! \brief  Determine whether the PLL is locked
     *
     *  Method used to check if the PLL is locked.
     *
     *  \return true if the PLL is locked
     */
    virtual bool isPllLocked(void) override;

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
	std::shared_ptr<II2cBus> mI2c ;                                    //!> Pointer to the bus class
} ;

}

#endif /* COMMON_I2C_INC_SI570_H_ */
