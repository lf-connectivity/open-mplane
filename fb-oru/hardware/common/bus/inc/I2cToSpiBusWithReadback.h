/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      I2cToSpiBusWithReadback.h
 * \brief     An I2cToSpi bus with readout using GPIO expander
 *
 *
 * \details   An I2cToSpi bus with readout using GPIO expander
 *
 */


#ifndef COMMON_BUS_INC_I2CTOSPIBUSWITHREADOUT_H_
#define COMMON_BUS_INC_I2CTOSPIBUSWITHREADOUT_H_

#include "I2cToSpiBus.h"
#include "IGpioExp.h"

namespace Mplane {

/*!
 * \class  I2cToSpiBusWithReadout
 * \brief
 * \details
 *
 */
class I2cToSpiBusWithReadback : public I2cToSpiBus {
public:
	I2cToSpiBusWithReadback(std::shared_ptr<IGpioExp> gpioExp,
			unsigned gpioExpPort, unsigned gpioExpVal, unsigned gpioExpMask,
			std::shared_ptr<II2cBus> i2c,
			std::shared_ptr<IBusReadonlySettings> busSettings, unsigned spiSelect) ;
	virtual ~I2cToSpiBusWithReadback() ;

protected:

	/**
	 * Read a byte from a particular offset address / register in the device
	 */
	virtual bool doReadByte(uint32_t offset, uint8_t& byte) override ;

	/**
	 * Read a short from a particular offset address / register in the device
	 */
	virtual bool doReadShort(uint32_t offset, uint16_t& shortVal) override ;

	/**
	 * Read a word from a particular offset address / register in the device
	 */
	virtual bool doReadWord(uint32_t offset, uint32_t& word) override ;

private:

	std::shared_ptr<IGpioExp> mGpioExp;
	unsigned mGpioExpPort;
	unsigned mGpioExpValue;
	unsigned mGpioExpMask;

} ;

}

#endif /* COMMON_BUS_INC_I2CTOSPIBUSWITHREADOUT_H_ */
