/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RegModel.h
 * \brief     Model of a register set in any device
 *
 *
 * \details   Models the register set of any generic device with a flat (non-paged) register set
 *
 */


#ifndef INC_REGMODEL_H_
#define INC_REGMODEL_H_

#include "IRegModel.h"
#include "IBusMonitor.h"

namespace Mplane {

/*!
 * \class  RegModel
 * \brief
 * \details   Model can be can be updated as an IBus monitor
 *
 */
class RegModel : public virtual IRegModel, public virtual IBusMonitor {
public:
	/**
	 * Create the model with a fixed number of address bits (i.e. fixed known number of registers) and each register
	 * having a fixed data width
	 */
	RegModel(const std::string& name, unsigned numAddressBits, unsigned numDataBits, unsigned addressLSB) ;
	virtual ~RegModel() ;

	// IRegModel interface

	/**
	 * Get the name of the model
	 */
	virtual std::string name() const override ;

	/**
	 * Get the number of bits used for address (register index)
	 */
	virtual unsigned addressWidth() const override ;

	/**
	 * Get the number of bits used for data
	 */
	virtual unsigned dataWidth() const override ;

	/**
	 * Returns TRUE if the register set is paged
	 */
	virtual bool isPaged() const override ;

	/**
	 * Set the page number to be used to display register values
	 */
	virtual void setReadPage(unsigned page) override ;

	/**
	 * Get the actual value of a register. Returns 0 if not set
	 */
	virtual uint32_t regValue(uint32_t regNumber) const override ;

	/**
	 * Returns TRUE if the register has been set; FALSE otherwise
	 */
	virtual bool regIsSet(uint32_t regNumber) const override ;

	/**
	 * Get the full vector of registers
	 */
	virtual std::vector< SetVal<uint32_t> > regs() const override ;

	/**
	 * Get the full vector of registers as actual values (0 if not set)
	 */
	virtual std::vector< uint32_t > regValues() const override ;

	/**
	 * Get the full vector of registers as actual values, with the register number and data aligned to the appropriate bits
	 * as if reading directly from the device (0 if not set)
	 */
	virtual std::vector< uint32_t > deviceValues() const override ;


	// IBusMonitor interface

	/**
	 * Called by IBus for any register write
	 */
	virtual void updateWrite(uint32_t offset, uint32_t data) override ;

	/**
	 * Called by IBus for any bytes write
	 */
	virtual void updateWrite(uint32_t offset, const std::vector<uint8_t>& data) override ;

	/**
	 * Called by IBus for any bytes write
	 */
	virtual void updateWrite(const std::vector<uint8_t>& data) override ;

	/**
	 * Called by IBus for any register read
	 */
	virtual void updateRead(uint32_t offset, uint32_t data) override ;

	/**
	 * Called by IBus for any bytes read
	 */
	virtual void updateRead(uint32_t offset, const std::vector<uint8_t>& data) override ;

	/**
	 * Called by IBus for any bytes read
	 */
	virtual void updateRead(const std::vector<uint8_t>& data) override ;

protected:
	virtual void updateModel(uint32_t offset, uint32_t data) ;

	/**
	 * If the address is part of data, then get the number of bits from LSB where the address starts
	 */
	virtual unsigned addressLSB() const ;

	/**
	 * Get the data mask
	 */
	virtual unsigned dataMask() const ;

	/**
	 * Get the number of registers
	 */
	virtual unsigned numRegs() const;

private:
	std::string mName ;
	unsigned mAddrWidth ;
	unsigned mDataWidth ;
	unsigned mAddrLSB ;
	unsigned mNumRegs ;
	uint32_t mDataMask ;

protected:

	std::vector< SetVal<uint32_t> > mRegs ;
} ;

}

#endif /* INC_REGMODEL_H_ */
