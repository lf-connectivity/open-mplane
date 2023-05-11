#ifndef _COMM_FAULTSLIST_H_
#define _COMM_FAULTSLIST_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Fault.h
 * \brief     Interface to faults
 *
 *
 * \brief     This file defines a general purpose radio fault handling system
 *
 */

#include <memory>
#include <vector>
#include <map>
#include <string>

#include "IFault.h"
#include "IFaultOwner.h"
#include "IFaultsList.h"
#include "Loggable.h"
#include "Mutex.h"

namespace Mplane
{

/*! \brief The FaultsList class that keeps a list of all the faults that are
 * created.
 *
 * The FaultsList class maintains a list of all the faults that are
 * created. The list starts empty and Faults are added to the list by the
 * Fault objects during their construction.
 *
 */
class FaultsList: public IFaultsList, public Loggable
{
public:

    /**
     * Should never get called unless the system is shutting down
     */
    virtual ~FaultsList();

    /**
     * Called by regular service to cause all IFaulOwner objects to update their faults
     */
    virtual void updateFaults() override ;

    /**
     * Add a fault to the faults list.
     * Will be called by the Fault constructor.
     *
     * \param A Fault instance
     *
     */
    virtual void addFault(std::shared_ptr<IFault> fault) override ;

    /**
     * Add a fault owner to the faults owners list.
     * Called by the Fault when the owner takes ownership.
     *
     * \param A IFaultOwner instance
     */
    virtual void addOwner(std::shared_ptr<IFaultOwner> owner) override ;

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
//    virtual void reset() override ;

    /**
     * This method resets all faults in the faults list.
     *
     * This is used to ensure that all fault are in a reset condition, usually
     * after the alarms have been cleared. This ensures that faults are re-evaluated
     * and re-asserted, as normally once a fault has been raised it wont notify the observer.
     */
    virtual void resetFaults() override;

    /**
     * The show method required by Loggable.
     * Displays its current status.
     */
    virtual void show(std::ostream& os) const override ;

    /**
     * The show name and id method.
     */
    virtual void showNamesAndIds(std::ostream& os) const override;

    /**
     * Check that all faults have an owner.
     *
     * \return true if all OK, false otherwise
     */
    virtual bool allHaveOwners() override ;

    /**
     * Return the fault list size.
     *
     * @return  the size of the fault list
     */
    virtual int getSize() const override ;

    /**
     * Get the named fault
     * @param name fault name
     * @return shared pointer to named fault, or null pointer if invalid name
     */
    virtual std::shared_ptr<IFault> getFault(const std::string& name) const  override ;

    /**
     * Get the identified fault
     * @param ident fault identifier
     * @return shared pointer to named fault, or null pointer if invalid name
     */
    virtual std::shared_ptr<IFault> getFault(const unsigned int ident) const override;

    /**
     * Get the named fault owner
     * @param name fault owner name
     * @return shared pointer to named fault owner, or null pointer if invalid name
     */
    virtual std::shared_ptr<IFaultOwner> getFaultOwner(const std::string& name) const  override ;

    // Test interface
#ifdef OFF_TARGET
    bool removeFault(const std::string& name) ;
    bool removeFaultOwner(const std::string& name) ;
#endif

protected:
    /**
     * Faults list constructor
     */
    FaultsList();


    /**
     * \note: Standard copy constructors defined but not implemented as a
     * FaultsList cannot be copied.
     */
    FaultsList& operator=(const FaultsList&);

private:
    /**
     * These lists are maintained in this class:\n
     * - a list of faults\n
     * - a list of the owners of faults\n
     */
    std::map< std::string, std::shared_ptr<IFault> > mFaultsList;  /*! a list of faults */
    std::map< std::string, std::shared_ptr<IFaultOwner> > mFaultsOwnersList;   /*! a list of faults owners */

    mutable Mutex mFaultsListMutex;
    mutable Mutex mFaultsOwnersListMutex;

};  // end of class FaultsList

} /* namespace Mplane */


#endif /* _COMM_FAULTSLIST_H_ */
