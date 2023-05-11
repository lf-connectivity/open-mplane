#ifndef _COMM_IFAULT_H_
#define _COMM_IFAULT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFault.h
 * \brief     Interface to faults
 *
 *
 * \brief     This file defines a general purpose radio fault handling system
 *
 */

#include <iostream>
#include <memory>
#include <string>

#include "GlobalTypeDefs.h"

namespace Mplane
{

// forward
class IFaultOwner ;

/*! \brief A general purpose radio fault class.
 *
 * The Fault base class defines a single fault, its associated data and related
 * interfaces to its owner.
 *
 * It inherits from Loggable in order to make use of the general logging
 * and error services.
 *
 * Each Fault object in the system must inherit from this base class, and implement
 * the pure virtual methods.
 * The faults are instantiated during system bring up and before the application is started.
 *
 * The owner of a fault has to do the following:
 * - Inherit from IFaultOwner and implement the pure virtual methods
 * - take ownership of the Fault(s) it will generate by calling the addOwner()
 * method for each fault it owns,
 * - raise/clear faults as they arise, by calling setStatus()
 * - implement the mandatory IFaultOwner::faultCallback() method to handle the
 * fault when raised and cleared
 *
 * The Fault object has raise and clear integrator periods implemented as
 * a single integrator status counter.
 *
 * When the owner calls Fault::setStatus(this, true) to raise a fault
 * the 'integrator' counter is incremented. If the threshold is reached the fault
 * is deemed to be real and the pure virtual method faultStateHasChanged() is called so that the real
 * fault implementations can handle the change in state. In most cases they will notify their observers
 * of the fault state change.
 *
 * Vice-versa for clearing a fault.\n
 * When the owner calls Fault::setStatus(this, false) to clear a fault, the
 * 'integrator' counter is decremented. If the threshold is
 * reached the fault is deemed to be cleared and the pure virtual method faultStateHasChanged() is called.
 *
 */
class IFault
{
public:
    IFault() {}

    /**
     * Fault Constructor:@n
     *
     * Initialises the fault object data from the parameter list.
     * It validates the parameters values before use.
     *
     * The fault state is initialised to 'not present' and the
     * integrator status is set to the 'present' counter.
     *
     * The fault is added to the global fault list.
     *
     * @param presentCtr The integration count for confirming the fault is
     * present, must be > 0.
     *
     * @param notpresentCtr The integration count for confirming the fault is
     * not present, must be > 0.
     *
     * @param name The text string describing this fault
     *
     */
    IFault(int  presentCtr,
          int  notpresentCtr,
          const std::string& name) {}

    /**
     * Fault Destructor:@n
     *
     * This should never be called, and is an empty function
     */
    virtual ~IFault() {}

    /**
     * Pure virtual method that forces its implementation.
     * Indicates that the fault has changed state to the value in the parameter.
     *
     * \param The new fault state: true means fault is present
     */
    virtual void faultStateHasChanged(bool newState) =0;

    /**
     * Gets the fault name text string
     *
     * @return The fault name string
     */
    virtual std::string getName() const =0;

    /**
     * Gets the fault Id
     *
     * @return The fault Id
     */
    virtual unsigned int getId() const =0;

    /**
     * Resets the fault object to its initial state.
     * If the fault transitions state then it will inform the owner of the state change and
     * call the faultStateHasChanged() interface to the inheritors.
     */
    virtual void reset() =0 ;

    /**
     * Adds the Owner for the fault.
     *
     * This is how a user takes ownership of a fault. Only one owner is allowed
     * and so the first one to grab it gets it.
     *
     * An owner is a software module which is responsible for detecting
     * the occurrence of one or more hardware fault. It knows which fault(s) it
     * is responsible for and takes ownership of them during its initialisation
     * phase.
     *
     * @param owner The interface to the owner for this fault
     *
     * @return ReturnType RT_OK if successful,\n
     * RT_NOT_ALLOWED if the owner is invalid,\n
     * RT_ALREADY_EXISTS if the fault already has an owner
     */
    virtual ReturnType::State addOwner(std::shared_ptr<IFaultOwner> owner) =0 ;

    /**
     * Updates the integrator status of a fault condition.
     *
     * This is how an owner provides a new sample to the integrator.
     *
     * Called by the fault owner for each new fault state sample.
     *
     * If a contiguous series of samples indicates that the sampled object is
     * faulty, a 'fault present' alarm is generated. Likewise, if a contiguous
     * series of samples indicates that the sampled object is ok, a
     *  'fault not present' alarm is generated.
     *
     * The sample lengths for detecting the appearance
     * and disappearance of a fault condition are provided in the constructor.
     *
     * The numeric value of the integrator status indicates how many
     * consecutive samples are required in order for the fault threshold to
     * be reached.@n
     * eg. if 3 samples are required for a fault to be raised, integrator status
     * will have value +3, and is decremented on each sample.@n
     * If 2 samples are required for a fault to be cleared, integrator status
     * will have value -2, and is incremented on each sample.@n
     * The threshold is reached when the status count reaches 0.
     *
     * When the fault integration count threshold is reached the inheritors are informed
     * by calling the faultStateHasChanged() method, and the owner is notified  by calling its callback function.
     *
     * Note, if the samples continue to stay in the same condition past the
     * threshold, the status value is reset to the threshold value.@n
     * eg. if a fault transitions to active, the status is set to -n. If the
     * fault condition remains active then status is reset to -n each time.
     *
     * @param condition true = fault is active for this sample,
     * false = fault is not active for this sample.
     */
    virtual void setStatus(bool condition) =0 ;

    /**
     * Used to return the 'fault present' status for the fault object.
     *
     * @return true = The fault is present, false if not present
     */
    virtual bool isFaultPresent() const =0 ;

    /**
     * Gets the fault owner instance
     *
     * @return Pointer to the Owner instance who owns this fault
     */
    virtual std::shared_ptr<IFaultOwner> getOwner() const =0 ;

    /**
     * Gets the fault integration status, the signed value that indicates if the
     * fault is in the active state.
     *
     * @return The current value that represents the integration count for
     * both the up and down counter. A -ve value means fault is active, a
     * +ve value means the fault is inactive.
     */
    virtual int getIntegratorStatus() const =0 ;

    /**
     * gets the Fault state as a string.
     *
     * \return the Fault state as a string.
     */
    virtual std::string getFaultPresentString() const =0 ;

    /**
     * Gets the 'fault present' counter.\n
     *
     * The counter value is set at instantiation and never changed. The value
     * indicates the number of consecutive samples that are required to
     * transition the fault from inactive to active.
     *
     * @return The 'fault present' counter value
     */
    virtual int getPresentCtr() const =0 ;

    /**
     * Gets the 'fault not present' counter.\n
     *
     * The counter value is set at instantiation and never changed. The value
     * indicates the number of consecutive samples that are required to
     * transition the fault from active to inactive.
     *
     * @return The 'fault not present' counter value
     */
    virtual int getNotpresentCtr() const =0 ;

    /**
     * Gets the number of resets performed since power up.\n
     *
     * The reset scenarios are part of 'session resets' when sessions are
     * implemented by the application.
     *
     * @return the number of resets performed since power up
     */
    virtual unsigned getResetCount() const =0 ;

    /**
     * The show method required by Loggable.
     * Displays its current status.
     */
    virtual void show(std::ostream& os = std::cout) const =0 ;

    /**
     * The show name and id method.
     * Displays the fault name and id
     */
    virtual void showNameAndId(std::ostream& os) const =0;

    /**
     * Shows the active trace and debug levels for this class
     */
    virtual void traceTest() const =0 ;

    /**
     * This method is used for system and integration test purposes
     * and allows a tester to raise a fault without going through
     * the normal owner channels.
     */
    virtual void raiseFaultForTesting() =0 ;

    /**
     * This method is used for system and integration test purposes
     * and allows a tester to clear a fault without going through
     * the normal owner channels.
     */
    virtual void clearFaultForTesting() =0 ;



};  // end of class Fault

/*-?|fault|gdurban|c0|?*/

}

#endif /* _COMM_IFAULT_H_ */
