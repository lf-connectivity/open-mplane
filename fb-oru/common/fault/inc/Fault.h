#ifndef _COMM_FAULT_H_
#define _COMM_FAULT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Fault.h
 * \brief     Class for recording faults
 *
 *
 * \brief     This file defines a general purpose radio fault handling system
 *
 */

#include <memory>
#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "IFaultOwner.h"
#include "IFault.h"
#include "IFaultsList.h"
#include "Loggable.h"
#include "Mutex.h"
#include "Observer.hpp"

namespace Mplane
{


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
class Fault : public IFault, public Loggable, public Subject<IFault>
{
public:

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
    Fault(int  presentCtr,
          int  notpresentCtr,
          const std::string& name);

    /**
     * Fault Constructor:@n
     *
     * Protection against copy constructor so that the ID is cannot be duplicated.
     *
     */
    Fault(const Fault&) = delete;
    Fault& operator=(const Fault&) = delete;


    /**
     * Fault Destructor:@n
     *
     * This should never be called, and is an empty function
     */
    virtual ~Fault();

    /**
     * Pure virtual method that forces its implementation.
     * Indicates that the fault has changed state to the value in the parameter.
     *
     * \param The new fault state: true means fault is present
     */
    virtual void faultStateHasChanged(bool newState) override ;

    /**
     * Gets the fault name text string
     *
     * @return The fault name string
     */
    virtual std::string getName() const override ;

    /**
     * Gets the fault Id
     *
     * @return The fault Id numeric value
     */
    virtual unsigned int getId() const override ;

    /**
     * Resets the fault object to its initial state.
     * If the fault transitions state then it will inform the owner of the state change and
     * call the faultStateHasChanged() interface to the inheritors.
     */
    virtual void reset() override ;

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
    virtual ReturnType::State addOwner(std::shared_ptr<IFaultOwner> owner) override ;

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
    virtual void setStatus(bool condition) override ;

    /**
     * Used to return the 'fault present' status for the fault object.
     *
     * @return true = The fault is present, false if not present
     */
    virtual bool isFaultPresent() const override ;

    /**
     * Gets the fault owner instance
     *
     * @return Pointer to the Owner instance who owns this fault
     */
    virtual std::shared_ptr<IFaultOwner> getOwner() const override ;

    /**
     * Gets the fault integration status, the signed value that indicates if the
     * fault is in the active state.
     *
     * @return The current value that represents the integration count for
     * both the up and down counter. A -ve value means fault is active, a
     * +ve value means the fault is inactive.
     */
    virtual int getIntegratorStatus() const override ;

    /**
     * gets the Fault state as a string.
     *
     * \return the Fault state as a string.
     */
    virtual std::string getFaultPresentString() const override ;

    /**
     * Gets the 'fault present' counter.\n
     *
     * The counter value is set at instantiation and never changed. The value
     * indicates the number of consecutive samples that are required to
     * transition the fault from inactive to active.
     *
     * @return The 'fault present' counter value
     */
    virtual int getPresentCtr() const override ;

    /**
     * Gets the 'fault not present' counter.\n
     *
     * The counter value is set at instantiation and never changed. The value
     * indicates the number of consecutive samples that are required to
     * transition the fault from active to inactive.
     *
     * @return The 'fault not present' counter value
     */
    virtual int getNotpresentCtr() const override ;

    /**
     * Gets the number of resets performed since power up.\n
     *
     * The reset scenarios are part of 'session resets' when sessions are
     * implemented by the application.
     *
     * @return the number of resets performed since power up
     */
    virtual unsigned getResetCount() const override ;

    /**
     * The show method required by Loggable.
     * Displays its current status.
     */
    virtual void show(std::ostream & os = std::cout) const override ;

    /**
     * The show name and id method.
     * Displays the fault name and id
     */
    virtual void showNameAndId(std::ostream & os = std::cout) const override;

    /**
     * Shows the active trace and debug levels for this class
     */
    virtual void traceTest() const override ;

    /**
     * This method is used for system and integration test purposes
     * and allows a tester to raise a fault without going through
     * the normal owner channels.
     */
    virtual void raiseFaultForTesting() override ;

    /**
     * This method is used for system and integration test purposes
     * and allows a tester to clear a fault without going through
     * the normal owner channels.
     */
    virtual void clearFaultForTesting() override ;


    /**
     * Helper method used by make_fault(). Does the additional work after the fault shared pointer has been created
     */
    static void makeFault(std::shared_ptr<IFault> fault) ;


private:

    /**
     * Called when there is a condition change in the fault.
     *
     * If a contiguous series of samples indicates that the fault is genuinely
     * active or inactive, a "stateHasChanged" notification is provided to the inheritors of the
     * fault and the owner of the fault.
     */
    void stateChange() ;


private:

    /**
     * The owner for this fault. It is supplied by the owner when
     * it adds itself as the owner.
     *
     * Defaults to 0.
     */
    std::shared_ptr<IFaultOwner> mOwner;

    /**
     * Indicates the current state of the fault, present or not present.
     *
     * Defaults to false, meaning fault not present
     */
    bool mFaultPresent;

    /**
     * The number of consecutive fault samples required for this fault to be
     * deemed to be real, i.e. fault present.@n
     *
     * Its value must be > 0
     *
     * If the fault is to be raised on the first fault sample this value
     * should be set to 1.
     */
    int mPresentCtr;

    /**
     * The number of consecutive fault samples required for this fault to be
     * deemed to be real, i.e. fault not present.@n
     *
     * Its value must be > 0
     *
     * If the fault is to be cleared on the first fault sample this value
     * should be set to 1.
     */
    int mNotpresentCtr;

    /**
     * The fault integrator status for this object.
     *
     * This is a counter that is either incremented or decremented for each
     * occasion of a fault condition.
     *
     * The sign and value indicates the current fault status, as follows:-
     *
     * < 0: PRESENT status, means the fault is currently present.\n
     * > 0: NOTPRESENT status, means the fault is not or has never been present\n
     * = 0: change status, a temporary condition when the integration count is reached
     */
    int mIntegratorStatus;

    /**
     * The fault object name string. Descriptive text to identify this fault.
     */
    const std::string mName;

    /**
     * The fault object ID. Numeric value to identify this fault.
     */
    unsigned int mId;

    /**
     * Count the number of times this fault has been raised
     */
    unsigned mRaisedCount;

    /**
     * Count the number of times this fault has been cleared
     */
    unsigned mClearedCount;

    /************************************************************
     * Metric collection area
     ************************************************************/
    /**
     * Count the number of times this fault has been raised for testing
     */
    unsigned mRaiseForTestingCount;

    /**
     * Count the number of times this fault has been cleared for testing
     */
    unsigned mClearForTestingCount;

    /**
     * Count the number of resets.
     * Required as part of the system reset procedures.
     */
    unsigned mResetCount;

};  // end of class Fault


//-------------------------------------------------------------------------------------------------------------

/**
 * All faults *MUST* be created via this helper template function. This ensures the shared pointer is created
 * and registered to the IFaultsList. Expects T to be derived from IFault
 *
 * @return shared pointer to fault
 */
template <typename T>
inline std::shared_ptr<T> make_fault()
{
	// create a new fault instance (assumes T is derived from IFault)
	std::shared_ptr<T> fault(std::make_shared<T>()) ;

	// Finish off
	Fault::makeFault(fault) ;

	return fault ;
}



}
#endif /* _COMM_FAULT_H_ */
