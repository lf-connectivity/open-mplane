/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Fault.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "IFaultsList.h"
#include "Fault.h"

using namespace Mplane;



//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Mplane::Fault::makeFault(std::shared_ptr<IFault> fault)
{
    // Add the fault to the global fault list and save its index into the list
    IFaultsList::getInstance()->addFault(fault);
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Fault::Fault(int presentCtr, int notpresentCtr, const std::string& name) :
	IFault(),
	Loggable( name, "FT" ),

	mOwner(),
	mFaultPresent(false),
	mName (name),
	mRaisedCount (0),
	mClearedCount (0),
	mRaiseForTestingCount (0),
	mClearForTestingCount (0),
	mResetCount (0)
{
    mPresentCtr = 1; // Set to default minimum value
    mNotpresentCtr = 1; // Set to default minimum value

    // Validate the present and notpresent parameters
    if (presentCtr > 0)
        mPresentCtr = presentCtr; // Valid data, so set to parameter value

    if (notpresentCtr > 0)
        mNotpresentCtr = notpresentCtr; // Valid data, so set to parameter value

    /* Initialise fault integrator counter status:
     * - fault is not present, therefore set the status to the present counter
     */
    mIntegratorStatus = mPresentCtr;

    /* Increment the fault if on every fault construction, start from 1 so that we know if
     * an invalid id exists */
    static unsigned int faultId = 1;
    mId = faultId ++;

    // NOTE: Expects the helper function make_fault() to be used to create and register this fault with the IFaultsList
}

//-------------------------------------------------------------------------------------------------------------
Fault::~Fault()
{
}

//-------------------------------------------------------------------------------------------------------------
void Fault::faultStateHasChanged(bool newState)
{
	// Implement in derived object
}

//-------------------------------------------------------------------------------------------------------------
std::string Fault::getName() const
{
    return mName;
}

//-------------------------------------------------------------------------------------------------------------
unsigned int Fault::getId() const
{
    return mId;
}

//-------------------------------------------------------------------------------------------------------------
void Fault::reset()
{
    logDebugNormal(
            "Fault %s: RESET fault state=%s: %s",
            mName.c_str(), getFaultPresentString().c_str(), __func__);

    // Count the number of resets
    mResetCount++;

    /* Re-Initialise fault integrator counter status:
     * - set to not present, therefore set the status to the appear counter
     */
    mIntegratorStatus = mPresentCtr;

    mRaisedCount = 0;
    mClearedCount = 0;

    // Counters for when this fault is used for testing
    mRaiseForTestingCount = 0;
    mClearForTestingCount = 0;

    // handle the state change
    stateChange();
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Fault::addOwner(std::shared_ptr<IFaultOwner> owner)
{
	// Check that an owner doesn't already exist and then add this one
	if (mOwner.get())
		return ReturnType::RT_ALREADY_EXISTS;

	if (!owner.get())
		return ReturnType::RT_NOT_ALLOWED;

	mOwner = owner;

	// Add the owner to the global fault owners list
	IFaultsList::getInstance()->addOwner(owner);

	return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
void Fault::setStatus(bool condition)
{
//	if (condition)
//		std::cerr << "FAULT: " << mName << std::endl ;

    if (mIntegratorStatus < 0)
    {
        // current status is 'fault present'
        if (condition)
        {
            // Fault condition still present, reset the 'fault not present' count
            mIntegratorStatus = -mNotpresentCtr;
        }
        else
        {
            if( mRaiseForTestingCount > mClearForTestingCount )
            {
                // We have raised the fault manually for testing purposes.
                // Carry on until the fault is cleared manually.
            }
            else
            {
                /* Fault condition no longer present, increment the count
                 * and check if we transition from present to not present
                 */
                mIntegratorStatus++;

                if (mIntegratorStatus >= 0)
                {
                    // Transition to 'not present' condition, set the present count
                    mIntegratorStatus = mPresentCtr;

                    // Keep count of the number of times this fault is cleared
                    mClearedCount++;

                    // handle the state change
                    stateChange();
                }
                else
                {
                    // NotPresent count threshold not reached. No transition.
                    logDebugNormal(
                            "Fault %s: 'Not present' threshold not reached. Status count=%d: %s",
                             mName.c_str(), mIntegratorStatus, __func__);
                }
            }
        }
    }
    else
    {
        // current status is 'fault not present'
        if (condition)
        {
            /* fault condition present, decrement the count
            * and check if we transition from not present to present
            */
            mIntegratorStatus--;

            if (mIntegratorStatus <= 0)
            {
                // Transition to 'present' condition, set the 'fault not present' count
                mIntegratorStatus = -mNotpresentCtr;

                // Keep count of the number of times this fault is raised
                mRaisedCount++;

                // handle the state change
                stateChange();
            }
            else
            {
                // Present count threshold not reached. No transition.
                logDebugNormal(
                        "Fault %s: 'Present' threshold not reached. Status count=%d: %s",
                         mName.c_str(), mIntegratorStatus, __func__);
            }
        }
        else
        {
            // Fault condition still not present, reset the 'fault present' count
            mIntegratorStatus = mPresentCtr;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------
bool Fault::isFaultPresent() const
{
    return mFaultPresent;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFaultOwner> Fault::getOwner() const
{
	return mOwner ;
}

//-------------------------------------------------------------------------------------------------------------
int Fault::getIntegratorStatus() const
{
    return mIntegratorStatus;
}

//-------------------------------------------------------------------------------------------------------------
std::string Fault::getFaultPresentString() const
{
    return mFaultPresent ? "FAULT_PRESENT" : "FAULT_NOT_PRESENT";
}

//-------------------------------------------------------------------------------------------------------------
int Fault::getPresentCtr() const
{
    return mPresentCtr;
}

//-------------------------------------------------------------------------------------------------------------
int Fault::getNotpresentCtr() const
{
    return mNotpresentCtr;
}

//-------------------------------------------------------------------------------------------------------------
unsigned Fault::getResetCount() const
{
    return mResetCount;
}

//-------------------------------------------------------------------------------------------------------------
void Fault::show(std::ostream& os) const
{
	os << "FAULT...................: " << mName << std::endl ;
	os << "State...................: " << getFaultPresentString() << std::endl ;
	if ( mOwner )
		os << "Owner...................: " << mOwner->getName() << std::endl ;
	os << "Id......................: " << mId << std::endl ;
	os << "Present count...........: " << mPresentCtr << std::endl ;
	os << "Raised count............: " << mRaisedCount << std::endl ;
	os << "Integrator status.......: " << mIntegratorStatus << std::endl ;
	os << "Cleared count...........: " << mClearedCount << std::endl ;
	os << "Not present count.......: " << mNotpresentCtr << std::endl ;
	os << "Reset count.............: " << mResetCount << std::endl ;

	if (mRaiseForTestingCount != 0 || mClearForTestingCount != 0)
	{
		os << "Testing raised count....: " << mRaiseForTestingCount << std::endl ;
		os << "Testing cleared count...: " << mClearForTestingCount << std::endl ;
	}
	traceTest();
}
//-------------------------------------------------------------------------------------------------------------
void Mplane::Fault::showNameAndId(std::ostream& os) const
{

	os.width(6);
	os.setf(std::ios::right);
	os << mId;
	os << " ";
	os.width(42);
	os.unsetf(std::ios::right);
	os.setf(std::ios::left);
	os << mName << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
void Fault::traceTest() const
{
}

//-------------------------------------------------------------------------------------------------------------
void Fault::raiseFaultForTesting()
{
    if (!mOwner.get())
    {
        logDebugNormal("*** This fault (%s) has no owner. Fault not raised ***", mName.c_str());
        return ;
    }

	// Transition to 'present' condition, set the 'not present' count
	mIntegratorStatus = -mNotpresentCtr;

	// Keep count of how many times this has been raised for testing purposes
	mRaiseForTestingCount++;

	// handle the state change
	stateChange();
}

//-------------------------------------------------------------------------------------------------------------
void Fault::clearFaultForTesting()
{
    if (!mOwner.get())
    {
        logDebugNormal("*** This fault (%s) has no owner. Fault not cleared ***", mName.c_str());
        return ;
    }

    // Transition to 'not present' condition, set the present count
    mIntegratorStatus = mPresentCtr;

    // Keep count of how many times this has been cleared for testing purposes
    mClearForTestingCount++;

    // handle the state change
    stateChange();
}

//-------------------------------------------------------------------------------------------------------------
void Fault::stateChange()
{
    /*
     * Ensure we only notify the observers once, at the state transition.
     *
     * A negative integrator status value means the fault is present.
     * A positive integrator status value means the fault is not present.
     */
    if ( ((mIntegratorStatus < 0) && !mFaultPresent) ||
         ((mIntegratorStatus > 0) && mFaultPresent) )
    {
        /* New fault condition, either present or not present.
         * Report the fault condition to the attached observers.
         */

        // Set our new state
        mFaultPresent = !mFaultPresent;

        logDebugNormal(
                "Fault %s: State changed, fault state=%s: %s",
                mName.c_str(), getFaultPresentString().c_str(), __func__);

        // Notify the inheritors of the fault state change
        faultStateHasChanged(mFaultPresent);

        // Notify the fault owner of the fault state change
        if (mOwner.get())
        {
            logDebugNormal(
                    "Fault %s: Notify owner %s",
                    mName.c_str(), mOwner->getName().c_str());

            mOwner->faultCallback(*this);
        }

        // Notify any Observers
        notify() ;
    }
}
