/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SoftwareSlot.h
 * \brief     Represents a software slot
 *
 *
 * \details   A slot may be empty or assigned to a SoftwarePackage.
 * If the assigned software package is valid then this slot can then be activated.
 *
 */


#ifndef SOFTWARESLOTS_INC_SOFTWARESLOT_H_
#define SOFTWARESLOTS_INC_SOFTWARESLOT_H_

#include "ISoftwareSlot.h"

namespace Mplane {


/*!
 * \class  SoftwareSlot
 * \brief
 * \details
 *
 */
class SoftwareSlot : public virtual ISoftwareSlot {
public:
	SoftwareSlot(const std::string& name, const std::string& mgmtPath) ;
	virtual ~SoftwareSlot() ;

	/**
	 * Initialise the slot using the list of available packages
	 */
	bool initialise(std::vector<std::shared_ptr<ISoftwarePackage>> packages) ;


	/**
	 * Get name
	 */
	virtual std::string name() const override ;

	/**
	 * is this slot allocated to a read-only package
	 */
	virtual bool isReadOnly() const override ;

	/**
	 * Change the read-only status of the allocated package
	 */
	virtual bool setReadOnly(bool readOnly) override ;

	/**
	 * Make this slot the active slot
	 */
	virtual bool activate() override ;

	/**
	 * Is this the running slot?
	 */
	virtual bool isRunning() const override ;

	/**
	 * is this the active slot
	 */
	virtual bool isActive() const override ;

	/**
	 * Assign a software package to this slot
	 */
	virtual bool allocatePackage(std::shared_ptr<ISoftwarePackage> package) override ;

	/**
	 * Get the allocated package
	 */
	virtual std::shared_ptr<ISoftwarePackage> package() const override ;

	/**
	 * Un-assign any software package
	 */
	virtual bool clearPackage() override ;

	/**
	 * Is slot allocated
	 */
	virtual bool isAllocated() const override ;

	/**
	 * Is this slot allocated with a valid package?
	 */
	virtual bool isValid() const override ;

	/*
	 * Debug - output the current slot information
	 */
	virtual void show(std::ostream& os = std::cout) override ;

private:
	std::string mSlotName ;
	std::string mMgrPath ;
	std::string mSlotLink ;

	std::shared_ptr<ISoftwarePackage> mPackage ;

} ;

}

#endif /* SOFTWARESLOTS_INC_SOFTWARESLOT_H_ */
