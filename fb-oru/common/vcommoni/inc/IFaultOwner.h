#ifndef _COMM_IFAULTOWNER_H_
#define _COMM_IFAULTOWNER_H_

#include <set>
#include <string>
#include <memory>
#include <iostream>

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFaultOwner.h
 * \brief     A file to contain general purpose radio fault owner interface
 *
 *
 * \brief     This file defines a general purpose radio fault owner interface
 *
 */

// Includes go here, before the namespace

namespace Mplane
{

// forward class definitions
class IFault;

/*! \brief A general purpose interface class for being a fault owner
 *
 * This is the base class that all software modules that raise faults
 * must inherit from.
 *
 * It contains two pure virtual methods that forces the fault owners to
 * provide their own handlers for the fault notification callbacks.
 *
 * The owner is notified by callback when there is a change in the fault state,
 * to either raised or cleared, and the owner takes remedial actions if
 * required.
 *
 * The IFaultOwner::faultCallback() method is called when the fault integration
 * threshold is reached and therefore the fault condition is either raised
 * or cleared.
 * The faultCallback() method allows the owner to take any remedial
 * actions, if any at all.
 *
 * The IFaultOwner::resetFaults() method is called as part of the fault handling
 * restart procedure. This method is called ONCE per fault owner
 * and the fault owner must handle this such that it resets all of its faults
 * and restarts its own fault or error handling strategy.
 */
class IFaultOwner
{
public:

	/**
	 * Called by a service or any other regular task. Causes the IFaultOwner to update it's owned faults
	 */
	virtual void updateFaults() =0 ;

    /**
     * The pure virtual method that all owners must implement.
     *
     * It is called when the fault integrator reaches the raise or clear
     * threshold.
     *
     * If the owner has no use of this callback then their implementation
     * will just leave the method implementation empty.
     *
     * @param fault The fault object instance
     */
    virtual void faultCallback(IFault& fault) = 0;

    /**
     * The pure virtual method that all users must implement.
     *
     * It is called as part of the fault handling restart sequence.
     *
     * All fault owners will need to implement this callback and to handle
     * the restarting of their faults.
     */
    virtual void resetFaults() = 0;

    /**
     * Hook provided for derived objects. They can use this to support clearing out things like hardware sticky registers
     * from which the fault is derived.
     */
    virtual void clearFaults() =0 ;


    /**
     * Gets the fault owner name text string
     *
     * @return The fault owner name string
     */
    virtual std::string getName() const = 0;

    /**
     * Get the list of fault names that this IFaultOwner owns
     * @return list of names
     */
    virtual std::set<std::string> getFaultNames() const =0 ;

    /**
     * Add a single fault to the set
     */
    virtual void addFault(const std::string& name) =0 ;

    /**
     * Add a set of faults to the set
     */
    virtual void addFault(const std::set<std::string>& names) =0 ;

    /**
     * The show method, displays its current status.
     */
    virtual void show(std::ostream& os = std::cout) const = 0;


protected:
    /**
     * virtual destructor
     *
     * This should never be called, and is an empty function
     */
    virtual ~IFaultOwner() { }
};


} /* namespace Mplane */

#endif /* _COMM_IFAULTOWNER_H_ */
