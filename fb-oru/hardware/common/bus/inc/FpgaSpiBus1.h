/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaSpiBus1.h
 * \brief     FPGA SPI bus implementation for SPI1
 *
 *
 * \details   FPGA SPI bus implementation for SPI1
 *
 */


#ifndef COMMON_BUS_INC_FPGASPIBUS1_H_
#define COMMON_BUS_INC_FPGASPIBUS1_H_

#include "IFpgaMgr.h"
#include "FpgaSpiBus.h"
#include "ISpiBusSettings.h"
#include "GlobalTypeDefs.h"

namespace Mplane {

/*!
 * \class  FpgaSpiBus1
 * \brief
 * \details
 *
 */
class FpgaSpiBus1 : public FpgaSpiBus {
public:

	FpgaSpiBus1(const std::string& busName, const std::string& busDetails, std::shared_ptr<IBusLock> busLock,
			std::shared_ptr<ISpiBusReadonlySettings> busSettings) ;
	virtual ~FpgaSpiBus1() ;


protected:

	/// Implement the register access functions

	/**
	 * Set the control 1 register
	 */
	virtual void setControlReg1(uint8_t readLen, uint8_t writeLen, uint8_t polarity, bool rdOppEdge) override;

	/**
	 * Set the control 2 register
	 */
	virtual void setControlReg2(uint8_t div, uint8_t phase, bool enable) override;

	/**
	 * Start the SPI transaction
	 */
	virtual void startSpiTransaction() override;

	/**
	 * Write the data to be sent on the bus
	 */
	virtual void setupWriteData(uint16_t low, uint16_t high) override;

	/**
	 * Read the data received on the bus
	 */
	virtual void readData(uint32_t& data) override;

	/**
	 * Check if SPI transaction is complete
	 */
	virtual bool isTransactionComplete() override;

private:

	std::shared_ptr<IFpgaSystemRegs> mFpga;     //!> Pointer to FPGA system register space


} ;

}

#endif /* COMMON_BUS_INC_FPGASPIBUS1_H_ */
