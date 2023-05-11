/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SI5382aI2CWithIntr.h
 * \brief     SI5382a I2C driver with interrupt pin access
 *
 *
 * \details   SI5382a I2C driver with interrupt pin access
 *
 */


#ifndef COMMON_SYNTH_INC_SI5382AI2CWITHINTR_H_
#define COMMON_SYNTH_INC_SI5382AI2CWITHINTR_H_

#include "SI5382aI2C.h"
#include "IGpioExp.h"

namespace Mplane {

/*!
 * \class  SI5382a I2C with interrupt driver class
 * \brief
 * \details
 *
 */
class SI5382aI2CWithIntr : public SI5382aI2C
{
public:
	SI5382aI2CWithIntr(std::shared_ptr<IGpioExp> gpioExp,
			unsigned gpioExpPort, unsigned gpioExpBitIndex,
			std::shared_ptr<II2cBus> i2c, const std::string& name) ;
	virtual ~SI5382aI2CWithIntr() {};

    /*! \brief  Determine whether the PLL is locked
     *
     *  Method used to check if the PLL is locked.
     *
     *  \return true if the PLL is locked
     */
    virtual bool isPllLocked(void) override;

private:

	std::shared_ptr<IGpioExp> mGpioExp;
	unsigned mGpioExpPort;
	unsigned mGpioExpBitIndex;
} ;

}

#endif /* COMMON_SYNTH_INC_SI5382AI2CWITHINTR_H_ */
