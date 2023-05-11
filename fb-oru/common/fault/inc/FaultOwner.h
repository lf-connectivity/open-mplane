/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FaultOwner.h
 * \brief     Base class for objects implementing the IFaultOwner interface
 *
 *
 * \details
 *
 */


#ifndef FAULTOWNER_H_
#define FAULTOWNER_H_

#include <stdexcept>
#include <memory>
#include <vector>
#include <set>

#include "Loggable.h"
#include "IFault.h"
#include "IFaultsList.h"
#include "IFaultOwner.h"

namespace Mplane {

class FaultOwner : public IFaultOwner
{
public:

	/**
	 * Create an IFaultOwner with a name and a list of the faults that this owner manages
	 * @param name
	 * @param faultNames
	 */
	FaultOwner(const std::string& name, const std::set<std::string>& faultNames) ;

    /**
     * Create a simple IFaultOwner with a name let it decide what it should own later
     * @param name
     * @param faultNames
     */
    explicit FaultOwner(const std::string& name) ;

	virtual ~FaultOwner() ;

	/**
	 * Called by a service or any other regular task. Causes the IFaultOwner to update it's owned faults
	 */
	virtual void updateFaults() override ;

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
    virtual void faultCallback(IFault& fault) override;

    /**
     * The pure virtual method that all users must implement.
     *
     * It is called as part of the fault handling restart sequence.
     *
     * All fault owners will need to implement this callback and to handle
     * the restarting of their faults.
     */
    virtual void resetFaults() override;

    /**
     * Gets the fault owner name text string
     *
     * @return The fault owner name string
     */
    virtual std::string getName() const override;

    /**
     * Get the list of fault names that this IFaultOwner owns
     * @return list of names
     */
    virtual std::set<std::string> getFaultNames() const override ;

    /**
     * The show method, displays its current status.
     */
    virtual void show(std::ostream& os) const override;

    /**
     * Hook provided for derived objects. They can use this to support clearing out things like hardware sticky registers
     * from which the fault is derived.
     */
    virtual void clearFaults() override ;

    /**
     * Add a single fault to the set
     */
    virtual void addFault(const std::string& name) override ;

    /**
     * Add a set of faults to the set
     */
    virtual void addFault(const std::set<std::string>& names) override ;


    /**
     * Helper method used by make_faultOwner(). Does the additional work after the alarm shared pointer has been created
     */
    static void makeFaultOwner(std::shared_ptr<IFaultOwner> owner) ;

private:
    const std::string mName ;
    std::set<std::string> mFaultNames ;
} ;

//-------------------------------------------------------------------------------------------------------------

/**
 * All fault owners *MUST* be created via this helper template function. This ensures the shared pointer is created
 * and registered to the IFaultsList. Expects T to be derived from IFaultOwner
 *
 * @return shared pointer to fault owner
 */
template <typename T>
inline std::shared_ptr<T> make_faultOwner()
{
	// create a new fault instance (assumes T is derived from IFault)
	std::shared_ptr<T> faultOwner(std::make_shared<T>()) ;

	// Finish off
	FaultOwner::makeFaultOwner(faultOwner) ;

    return faultOwner ;
}


}

#endif /* FAULTOWNER_H_ */
