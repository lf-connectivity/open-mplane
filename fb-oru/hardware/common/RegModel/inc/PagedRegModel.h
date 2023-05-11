/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PagedRegModel.h
 * \brief     Model of a register set in a paged device
 *
 *
 * \details   Models the register set of any generic device with a paged register set
 *
 */


#ifndef INC_PAGED_REGMODEL_H_
#define INC_PAGED_REGMODEL_H_

#include <map>
#include <vector>
#include "RegModel.h"

namespace Mplane {

/*!
 * \class  PagedRegModel
 * \brief
 * \details   Model can be can be updated as an IBus monitor
 *
 */
class PagedRegModel : public RegModel
{
public:
	/**
	 * Create the model with a fixed number of address bits (i.e. fixed known number of registers) and each register
	 * having a fixed data width
	 */
	PagedRegModel(const std::string& name, unsigned numAddressBits, unsigned numDataBits,
			unsigned addressLSB, unsigned numPageBits, unsigned pageRegOffset) ;
	virtual ~PagedRegModel() ;

	// IRegModel interface

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

protected:
	virtual void updateModel(uint32_t offset, uint32_t data) override;

private:
	unsigned mNumPages ;
	unsigned mReadPage ;
	unsigned mWritePage ;
	unsigned mPagedRegOffset;
	std::map< uint32_t, std::vector< SetVal<uint32_t> >> mRegs ;
} ;

}

#endif /* INC_PAGED_REGMODEL_H_ */
