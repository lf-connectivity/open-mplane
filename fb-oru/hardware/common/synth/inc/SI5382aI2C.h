/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SI5382aI2C.h
 * \brief     Multi-DSPLL Wireless Jitter Attenuator / Clock Multiplier with Ultra-Low Noise
 *
 *
 * \details   Multi-PLL that is configured via the I2C bus
 *
 */


#ifndef COMMON_SYNTH_INC_SI5382AI2C_H_
#define COMMON_SYNTH_INC_SI5382AI2C_H_

#include "bus/II2cBus.h"
#include "ISynthDriver.h"
#include "RegDriver.h"
#include "PagedRegModel.h"

namespace Mplane {

/*!
 * \class  SI5382a I2C driver class
 * \brief
 * \details
 *
 */
class SI5382aI2C : public virtual ISynthDriver, public RegDriver
{
public:
	SI5382aI2C(std::shared_ptr<II2cBus> i2c, const std::string& name) ;
	virtual ~SI5382aI2C() ;

	/**
	 * Initialise the driver
	 */
	virtual ReturnType::State initialise( void ) override;

    /*! \brief  Set the synthesiser frequency
     *
     *  Program the given frequency
     *
     *  \param the synthesiser frequency
     */
    virtual ReturnType::State program(Frequency frequency ) override;

    /*! \brief  Post Program steps if any
     *
     *  Called after ISynthDriver::program to perform any steps after frequency is changed
     *
     *  \return None
     */
    virtual void postProgram(void) override;

    /*! \brief  Determine whether the PLL is locked
     *
     *  Method used to check if the PLL is locked.
     *
     *  \return true if the PLL is locked
     */
    virtual bool isPllLocked(void) override;

    /*! \brief  Determine whether the synthesiser is locked
     *
     *  Method used to check if the synthesiser is out of lock.
     *
     *  \return true if the synthesiser is out of lock.
     */
    virtual bool isOutOfLock(void) override;

    /*! \brief  Force the synthesiser out of lock
     *
     *  Used for synthesiser testing by forcing the synth to go out lock.
     */
    virtual void forceOutOfLock(void) override;

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

	static const std::vector< std::pair<uint32_t, uint32_t> > mPreamble;
	static const std::vector< std::pair<uint32_t, uint32_t> > mPostamble;
	static const unsigned ADDR_WIDTH;
	static const unsigned DATA_WIDTH;
	static const unsigned ADDR_LSB; //The address is not part of the register data, hence setting it to max value
	static const unsigned PAGE_BITS;
	static const unsigned PAGE_REG_OFFSET;
	static const unsigned STATUS_REG_START_ADDR;
	static const unsigned NUM_STATUS_REGS;

    virtual void appendWriteCommand(uint16_t address, uint8_t data,
    		std::vector<IBus::BusCommand>& commands);
	std::shared_ptr<II2cBus> mI2c ;                                    //!> Pointer to the bus class

private:
	uint8_t mCurrentPage;                                              //!> Current page number
} ;

}

#endif /* COMMON_SYNTH_INC_SI5382AI2C_H_ */
