/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISoftwareSlot.h
 * \brief     Represents a software slot
 *
 *
 * \details   A slot may be empty or assigned to a SoftwarePackage.
 * If the assigned software package is valid then this slot can then be activated.
 *
 */


#ifndef VCOMMONI_INC_ISOFTWARESLOT_H_
#define VCOMMONI_INC_ISOFTWARESLOT_H_

#include <string>
#include <iostream>
#include <memory>
#include <vector>

#include "ISoftwarePackage.h"

namespace Mplane {

/*!
 * \class  ISoftwareSlot
 * \brief
 * \details
 *
 */
class ISoftwareSlot {
public:
	ISoftwareSlot() {}
	virtual ~ISoftwareSlot() {}

	/**
	 * Get name
	 */
	virtual std::string name() const =0 ;

	/**
	 * is this slot allocated to a read-only package
	 */
	virtual bool isReadOnly() const =0 ;

	/**
	 * Change the read-only status of the allocated package
	 */
	virtual bool setReadOnly(bool readOnly) =0 ;

	/**
	 * Make this slot the active slot
	 */
	virtual bool activate() =0 ;

	/**
	 * Is this the running slot?
	 */
	virtual bool isRunning() const =0 ;

	/**
	 * is this the active slot
	 */
	virtual bool isActive() const =0 ;

	/**
	 * Assign a software package to this slot
	 */
	virtual bool allocatePackage(std::shared_ptr<ISoftwarePackage> package) =0 ;

	/**
	 * Get the allocated package
	 */
	virtual std::shared_ptr<ISoftwarePackage> package() const =0 ;

	/**
	 * Un-assign any software package
	 */
	virtual bool clearPackage() =0 ;

	/**
	 * Is slot allocated
	 */
	virtual bool isAllocated() const =0 ;

	/**
	 * Is this slot allocated with a valid package?
	 */
	virtual bool isValid() const =0 ;

	/*
	 * Debug - output the current slot information
	 */
	virtual void show(std::ostream& os = std::cout) =0 ;


} ;

}

#endif /* VCOMMONI_INC_ISOFTWARESLOT_H_ */
