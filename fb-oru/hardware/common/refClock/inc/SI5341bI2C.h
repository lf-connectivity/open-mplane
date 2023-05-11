/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SI5341bI2C.h
 * \brief     Ultra Low Jitter, Any-Frequency, Any Output Clock Generator, Revision D
 *
 *
 * \details   Clock Generator that is configured via the I2C bus
 *
 */


#ifndef COMMON_REFCLOCK_INC_SI5341BI2C_H_
#define COMMON_REFCLOCK_INC_SI5341BI2C_H_

#include "bus/II2cBus.h"
#include "IRefClockDriver.h"
#include "RegDriver.h"
#include "PagedRegModel.h"

namespace Mplane {

/*!
 * \class  SI5341b I2C driver class
 * \brief
 * \details
 *
 */
class SI5341bI2C : public virtual IRefClockDriver, public RegDriver
{
public:
	SI5341bI2C(std::shared_ptr<II2cBus> i2c, const std::string& name) ;
	virtual ~SI5341bI2C() ;

	static const std::vector< std::pair<uint32_t, uint32_t> > mPreamble;
	static const std::vector< std::pair<uint32_t, uint32_t> > mPostamble;

	/**
	 * Initialise the driver
	 */
	virtual ReturnType::State initialise( void ) override;

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
	static const unsigned PAGE_BITS;
	static const unsigned PAGE_REG_OFFSET;

    virtual void appendWriteCommand(uint16_t address, uint8_t data,
    		std::vector<IBus::BusCommand>& commands);

private:
	std::shared_ptr<II2cBus> mI2c ;                                    //!> Pointer to the bus class
	uint8_t mCurrentPage;                                              //!> Current page number
} ;

}

#endif /* COMMON_REFCLOCK_INC_SI5341BI2C_H_ */
