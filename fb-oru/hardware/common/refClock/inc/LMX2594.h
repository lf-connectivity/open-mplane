/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LMX2594.h
 * \brief     15GHz Wideband PLL
 *
 *
 * \details   A PLL that is configured via the SPI bus
 *
 */


#ifndef COMMON_SPI_INC_LMX2594_H_
#define COMMON_SPI_INC_LMX2594_H_

#include "bus/ISpiBus.h"
#include "IRefClockDriver.h"
#include "RegDriver.h"
#include "RegModel.h"

namespace Mplane {

/*!
 * \class  LMX2594 driver class
 * \brief
 * \details
 *
 */
class LMX2594 : public virtual IRefClockDriver, public RegDriver
{
public:
	LMX2594(std::shared_ptr<ISpiBus> spi, const std::string& name) ;
	virtual ~LMX2594() ;

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
    static const unsigned ADDR_LSB;
    static const bool USE_RW ;
    static const unsigned RW_BIT;

    static const unsigned ADDR_MSB;
    static const unsigned SR_SIZE ;
    static const unsigned PLL_LOCK_REGISTER;
    static const unsigned RB_LD_VTUNE_MASK;
    static const unsigned RB_LD_VTUNE_SHIFT;
    static const unsigned RB_LD_VTUNE_LOCKED;

private:
	std::shared_ptr<ISpiBus> mSpi ;                                    //!> Pointer to the bus class
} ;

}

#endif /* COMMON_SPI_INC_LMX2594_H_ */
