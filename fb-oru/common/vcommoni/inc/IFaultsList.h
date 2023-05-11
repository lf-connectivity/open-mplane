#ifndef _COMM_IFAULTSLIST_H_
#define _COMM_IFAULTSLIST_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFaultsList.h
 * \brief     Interface to faults list
 *
 *
 * \brief     This file defines a general purpose radio fault handling system
 *
 */

#include <iostream>
#include <memory>
#include <string>

namespace Mplane
{

// Forward
class IFault ;
class IFaultOwner ;

/*! \brief The FaultsList class that keeps a list of all the faults that are
 * created.
 *
 * The FaultsList class maintains a list of all the faults that are
 * created. The list starts empty and Faults are added to the list by the
 * Fault objects during their construction.
 *
 */
class IFaultsList
{
public:

	/**
	 * Singleton method for getting the application instance
	 * @return shared pointer to singleton
	 */
	static std::shared_ptr<IFaultsList> getInstance() ;

    /**
     * Should never get called unless the system is shutting down
     */
    virtual ~IFaultsList() {}

    /**
     * Called by regular service to cause all IFaulOwner objects to update their faults
     */
    virtual void updateFaults() =0 ;

    /**
     * Add a fault to the faults list.
     * Will be called by the Fault constructor.
     *
     * \param A Fault instance
     *
     */
    virtual void addFault(std::shared_ptr<IFault> fault) =0 ;

    /**
     * Add a fault owner to the faults owners list.
     * Called by the Fault when the owner takes ownership.
     *
     *@TODO Don'r understand why this is required. Fault owners are responsible for updating faults, they shouldn't need to be proded to do so. REMOVE?
     *
     * \param A IFaultOwner instance
     */
    virtual void addOwner(std::shared_ptr<IFaultOwner> owner) =0 ;

//    /**
//     * This method resets all faults in the faults list.
//     *
//     * All faults are cleared and their owners informed, so they can handle
//     * the reset.
//     *
//     * This reset is likely to be called during a session reset, which
//     * can be caused by external OAM request or as a recovery action from
//     * certain alarm conditions.
//     */
//    virtual void reset() =0 ;

    /**
     * This method resets all faults in the faults list.
     *
     * This is used to ensure that all fault are in a reset condition, usually
     * after the alarms have been cleared. This ensures that faults are re-evaluated
     * and re-asserted, as normally once a fault has been raised it wont notify the observer.
     */
    virtual void resetFaults() =0;

    /**
     * The show method required by Loggable.
     * Displays its current status.
     */
    virtual void show(std::ostream& os = std::cout) const =0 ;

    /**
     * The show names and id's method.
     */
    virtual void showNamesAndIds(std::ostream& os = std::cout) const =0 ;

    /**
     * Check that all faults have an owner.
     *
     * \return true if all OK, false otherwise
     */
    virtual bool allHaveOwners() =0 ;

    /**
     * Return the fault list size.
     *
     * @return  the size of the fault list
     */
    virtual int getSize() const =0 ;

    /**
     * Get the named fault
     * @param name fault name
     * @return shared pointer to named fault, or null pointer if invalid name
     */
    virtual std::shared_ptr<IFault> getFault(const std::string& name) const  =0 ;

    /**
     * Get the identified fault
     * @param ident fault identification
     * @return shared pointer to named fault, or null pointer if invalid name
     */
    virtual std::shared_ptr<IFault> getFault(const unsigned int ident) const  =0 ;

    /**
     * Get the named fault owner
     * @param name fault owner name
     * @return shared pointer to named fault owner, or null pointer if invalid name
     */
    virtual std::shared_ptr<IFaultOwner> getFaultOwner(const std::string& name) const  =0 ;



protected:
    IFaultsList() {}

};  // end of class IFaultsList

} /* namespace Mplane */


#endif /* _COMM_IFAULTSLIST_H_ */
