/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRegModel.h
 * \brief     Model of a register set in any device
 *
 *
 * \details   Models the register set of any generic device with a paged/non-paged register set
 *
 */


#ifndef VHI_INC_IREGMODEL_H_
#define VHI_INC_IREGMODEL_H_

#include <cstdint>
#include <vector>
#include <memory>
#include <string>

#include "SetVal.hpp"

namespace Mplane {

/*!
 * \class  IRegModel
 * \brief
 * \details
 *
 */
class IRegModel {
public:
	IRegModel() {}
	virtual ~IRegModel() {}

	/**
	 * Get the name of the model
	 */
	virtual std::string name() const =0 ;

	/**
	 * Get the number of bits used for address (register index)
	 */
	virtual unsigned addressWidth() const =0 ;

	/**
	 * Get the number of bits used for data
	 */
	virtual unsigned dataWidth() const =0 ;

	/**
	 * Returns TRUE if the register set is paged
	 */
	virtual bool isPaged() const =0 ;

	/**
	 * Set the page number to be used to display register values
	 */
	virtual void setReadPage(unsigned page) =0 ;

	/**
	 *
	 * Get the actual value of a register. Returns 0 if not set
	 */
	virtual uint32_t regValue(uint32_t regNumber) const =0 ;

	/**
	 * Returns TRUE if the register has been set; FALSE otherwise
	 */
	virtual bool regIsSet(uint32_t regNumber) const =0 ;

	/**
	 * Get the full vector of registers
	 */
	virtual std::vector< SetVal<uint32_t> > regs() const =0 ;

	/**
	 * Get the full vector of registers as actual values (0 if not set)
	 */
	virtual std::vector< uint32_t > regValues() const =0 ;

	/**
	 * Get the full vector of registers as actual values, with the register number and data aligned to the appropriate bits
	 * as if reading directly from the device (0 if not set)
	 */
	virtual std::vector< uint32_t > deviceValues() const =0 ;

} ;


/*!
 * \class  IRegModelMgr
 * \brief  Singleton that manages IRegModels
 * \details
 *
 */
class IRegModelMgr {
public:
	IRegModelMgr() {}
	virtual ~IRegModelMgr() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IRegModelMgr> singleton() ;

	/**
	 * Add a new IRegModel to the list
	 */
	virtual void addModel(IRegModel* regModel) =0 ;

	/**
	 * Remove a IRegModel from the list
	 */
	virtual void delModel(IRegModel* regModel) =0 ;

	/**
	 * Get the list of names of the models
	 */
	virtual std::vector<std::string> names() const =0 ;

	/**
	 * Get the named IRegModel
	 */
	virtual IRegModel* regModel(const std::string& name) const =0 ;

} ;

}

#endif /* VHI_INC_IREGMODEL_H_ */
