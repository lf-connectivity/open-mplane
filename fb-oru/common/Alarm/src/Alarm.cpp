/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Alarm.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <fstream>
#include <map>

#include "IFaultsList.h"
#include "IFaultOwner.h"
#include "IFault.h"

#include "IAlarmsList.h"
#include "Alarm.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::map<IAlarm::AlarmSeverity, std::string> SEVERITY_STR{
	{ IAlarm::ALARM_WARNING, 	"WARNING"},
	{ IAlarm::ALARM_MINOR, 		"MINOR"},
	{ IAlarm::ALARM_MAJOR, 		"MAJOR"},
	{ IAlarm::ALARM_CRITICAL, 	"CRITICAL"},
} ;


//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Alarm::makeAlarm(std::shared_ptr<IAlarm> alarm)
{
    // Add the alarm to the global alarm list and save its index into the list
    IAlarmsList::getInstance()->addAlarm(alarm);
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Alarm::Alarm(const std::string& name, const std::string& description)
	: Alarm(name, "STANDARD", description, IAlarm::ALARM_MAJOR)
{
}

//-------------------------------------------------------------------------------------------------------------
Alarm::Alarm(const std::string& name, const std::string& type, const std::string& description)
	: Alarm(name, type, description, IAlarm::ALARM_MAJOR)
{
}

//-------------------------------------------------------------------------------------------------------------
Alarm::Alarm(const std::string& name, const std::string& description, IAlarm::AlarmSeverity severity)
	: Alarm(name, "STANDARD", description, severity)
{
}

//-------------------------------------------------------------------------------------------------------------
Alarm::Alarm(const std::string& name, const std::string& type, const std::string& description, IAlarm::AlarmSeverity severity) :
	Loggable(name, "AL"),

	mAlarmState(false),
	mName(name),
	mDescription(description),
	mTypeStr(type),
	mSeverity(severity),
	mRaisedCount(0),
	mClearedCount(0),
	mPortId(-1),
	mSectorId(-1),
	mAlarmStateHasChanged(false),
	mObservers(),
	mRootCause(""),
	mTimeStamp(""),
	mRaiseForTestingCount(0),
	mClearForTestingCount(0),
	mResetCount(0)
{
    /* Increment the alarm id on every fault construction, start from 1 so that we know if
     * an invalid id exists */
    static unsigned int alarmId = 1;
    mId = alarmId ++;
}

//-------------------------------------------------------------------------------------------------------------
Alarm::~Alarm()
{
	// Detach any observers
	for (auto obs : mObservers)
	{
		std::shared_ptr<Subject<IFault>> subject( std::dynamic_pointer_cast<Subject<IFault>>(obs->getSubject()) ) ;
		subject->detach(*obs) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void Alarm::alarmStateHasChanged(bool newState)
{
	// Should be overridden by derived objects
}

//-------------------------------------------------------------------------------------------------------------
void Alarm::reset()
{
	logDebugNormal("%s %s", mName.c_str(), __func__);

	// Clear the root cause before clearing the faults
	clearRootCause();

	//== Reset the underlying Fault(s)
	resetFaults() ;

	//== Now reset the Alarm

	// Count the number of resets
	mResetCount++;

	mRaisedCount = 0;
	mClearedCount = 0;

	// Counters for when this alarm is used for testing
	mRaiseForTestingCount = 0;
	mClearForTestingCount = 0;

	// set the state and handle if the state changes
	setStatus(false);

	// Now process the current state of all the faults by generating "events" from each of them
	for (auto obs : mObservers)
	{
		std::shared_ptr<IFault> subject( obs->getSubject() ) ;
		update(*subject) ;
	}

}

//-------------------------------------------------------------------------------------------------------------
bool Alarm::isAlarmActive() const
{
    return mAlarmState;
}

//-------------------------------------------------------------------------------------------------------------
std::string Alarm::getName() const
{
	return mName ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Alarm::getDescription() const
{
	return mDescription ;
}

//-------------------------------------------------------------------------------------------------------------
IAlarm::AlarmSeverity Alarm::getSeverity() const
{
	return mSeverity ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Alarm::getSeverityStr() const
{
	return SEVERITY_STR.at(mSeverity) ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned int Alarm::getId() const
{
    return mId;
}

//-------------------------------------------------------------------------------------------------------------
std::string Alarm::getAlarmStateString() const
{
    return mAlarmState? "ALARM_PRESENT" : "ALARM_NOT_PRESENT";
}

//-------------------------------------------------------------------------------------------------------------
unsigned Alarm::getResetCount() const
{
	return mResetCount ;
}

//-------------------------------------------------------------------------------------------------------------
int Alarm::getPortId() const
{
	return mPortId ;
}

//-------------------------------------------------------------------------------------------------------------
void Alarm::setPortId(int port)
{
    mPortId = port;
}

//-------------------------------------------------------------------------------------------------------------
int Alarm::getSectorId() const
{
	return mSectorId ;
}

//-------------------------------------------------------------------------------------------------------------
void Alarm::setSectorId(int sector)
{
    mSectorId = sector;
}

//-------------------------------------------------------------------------------------------------------------
void Alarm::show(std::ostream& os) const
{
	os << "ALARM...................: " << mName << std::endl ;
	os << "Description.............: " << mDescription << std::endl ;
	os << "Type....................: " << mTypeStr << std::endl ;
	os << "Severity................: " << getSeverityStr() << std::endl ;
	os << "State...................: " << getAlarmStateString() << std::endl ;
	os << "Id......................: " << mId << std::endl ;
	os << "Raised count............: " << mRaisedCount << std::endl ;
	os << "Cleared count...........: " << mClearedCount << std::endl ;
	os << "Reset count.............: " << mResetCount << std::endl ;

	if (mRaiseForTestingCount != 0 || mClearForTestingCount != 0)
	{
		os << "Testing raised count....: " << mRaiseForTestingCount << std::endl ;
		os << "Testing cleared count...: " << mClearForTestingCount << std::endl ;
	}

	if( "" != mRootCause )
	{
		os << "\e[1m" << "Root cause..............: " << mRootCause << "\e[0m" << std::endl ;
	}

	traceTest();
}

//-------------------------------------------------------------------------------------------------------------
void Alarm::showAlarmAndFault(std::ostream& os) const
{
	show(os);

	// Show the alarm's faults
	os << "Alarm " << mName << " faults list: " << std::endl ;
	for (auto obs : mObservers)
	{
		std::shared_ptr<IFault> fault(obs->getSubject()) ;
		fault->show(os) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void Alarm::showNameAndId(std::ostream& os) const
{
	os.width(6);
	os.setf(std::ios::right);
	os << mId;
	os << " ";
	os.width(50);
	os.unsetf(std::ios::right);
	os.setf(std::ios::left);
	os << mName << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
void Alarm::traceTest() const
{
}

//-------------------------------------------------------------------------------------------------------------
void Alarm::raiseAlarmForTesting()
{
    logDebugNormal("%s %s", mName.c_str(), __func__);

    // Keep count of how many times this has been raised for testing purposes
    mRaiseForTestingCount++;

    setStatus(true);
}

//-------------------------------------------------------------------------------------------------------------
void Alarm::clearAlarmForTesting()
{
    logDebugNormal("%s %s", mName.c_str(), __func__);

    // Keep count of how many times this has been cleared for testing purposes
    mClearForTestingCount++;

    setStatus(false);
}

//-------------------------------------------------------------------------------------------------------------
void Alarm::setStatus(bool condition)
{
    /*
     * Ensure we only accept a change in the current state.
     */
    if ( (condition && !mAlarmState) || (!condition && mAlarmState) )
    {
        /* New alarm condition, set the new state
         */
        mAlarmState = !mAlarmState;

        if (!mAlarmState)
        {
            // Transition to alarm cleared
            // Keep count of the number of times this alarm is cleared
            mClearedCount++;

            // Clear the root cause name.
            clearRootCause();

            // Clear the time stamp
            clrTimeStamp();
        }
        else
        {
            // Transition to alarm raised
            // Keep count of the number of times this alarm is raised
            mRaisedCount++;

            // set the time stamp
            setTimeStamp();
        }

        // handle the state change
        stateChange();

        // Set the alarm state changed flag
        mAlarmStateHasChanged = true;
    }
}

//-------------------------------------------------------------------------------------------------------------
bool Alarm::registerFault(const std::string& name)
{
	std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;
	std::shared_ptr<IFault> fault(faultsList->getFault(name)) ;
	if (!fault.get())
		return false ;

	// create an object to handle Observer updates
	std::shared_ptr<ObserverWrapper<IAlarm, IFault>> observer(
		new ObserverWrapper<IAlarm, IFault>(dynamic_cast<IAlarm*>(this), name, fault)
	) ;
	mObservers.push_back(observer) ;

	// Attach observer to the IFault
	std::shared_ptr<Subject<IFault>> subject( std::dynamic_pointer_cast<Subject<IFault>>(fault) ) ;
	subject->attach(*observer) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Alarm::registerFaults(const std::set<std::string>& names)
{
	for (auto name : names)
	{
		if (!registerFault(name))
			return false ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void Alarm::update(IFault& subject)
{
	logDebugNormal("%s %s: %s %s", mName.c_str(), __func__,
		subject.getName().c_str(), subject.getFaultPresentString().c_str()
	);

	// Default action is to update the Alarm state based on the Fault status
	bool faultPresent(false) ;
	for (auto obs : mObservers)
	{
		std::shared_ptr<IFault> fault( obs->getSubject() ) ;
		if (fault->isFaultPresent())
		{
			setRootCause( subject.getName() );
			faultPresent = true ;
			break ;
		}
	}
	setStatus(faultPresent);
}

//-------------------------------------------------------------------------------------------------------------

std::string Mplane::Alarm::getRootCause() const
{
    return mRootCause;
}

//-------------------------------------------------------------------------------------------------------------
void Alarm::setRootCause(std::string rootCause)
{
	// Only update the root cause if its not already been populated
	if( "" == mRootCause )
	{
		mRootCause = rootCause;
	}
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::Alarm::clearRootCause( void )
{
	mRootCause = "";
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::Alarm::hasAlarmChangedSinceLastRead(void)
{
	bool returnValue = mAlarmStateHasChanged;

	mAlarmStateHasChanged = false; // Reset the flag before returning from the method

	return returnValue;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
std::vector<std::shared_ptr<ObserverWrapper<IAlarm, IFault> > > Alarm::getObservers()
{
	return mObservers ;
}


//=============================================================================================================
// PRIVATE
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
void Alarm::stateChange()
{
    logDebugVerbose("Alarm %s: State changed, alarm state=%s",
            mName.c_str(), getAlarmStateString().c_str());

    // Notify the inheritors of the alarm state change
    alarmStateHasChanged(mAlarmState);

    // Notify any Observers
    notify() ;
}


//-------------------------------------------------------------------------------------------------------------
void Alarm::resetFaults()
{
	// get list of FaultOwners
	std::set<std::shared_ptr<IFaultOwner>> faultOwners ;
	for (auto obs : mObservers)
	{
		std::shared_ptr<IFault> fault(obs->getSubject()) ;
		faultOwners.insert(fault->getOwner()) ;
	}

	// Use the FaultOwner to clear any hardware related faults
	for (auto owner : faultOwners)
	{
		owner->clearFaults() ;
	}
}

//-------------------------------------------------------------------------------------------------------------

std::string Mplane::Alarm::getTimeStamp(void)
{
	return mTimeStamp;
}

//-------------------------------------------------------------------------------------------------------------

void Mplane::Alarm::setTimeStamp(void)
{
	// Get the time and date from the system in the correct format and write it out to a file
	std::string dateTimeCommand  = "date +\"%Y-%m-%dT%H:%M:%S\" > /tmp/date.txt";

	int dataTimeRet = system( dateTimeCommand.c_str() ) ;

	if(dataTimeRet == 0)
	{
		// Data time command was successful, read in the file we just wrote
		std::ifstream dateTimeFile("/tmp/date.txt");

		if(dateTimeFile.is_open())
		{
			std::getline(dateTimeFile, mTimeStamp);
		}
		else
		{
			eventError("Alarm::recordTimeStamp - could not open /tmp/date.txt");
		}
		dateTimeFile.close();
	}

	// Clean up after ourselves, delete the file we created.
	std::remove("/tmp/date.txt");
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::Alarm::clrTimeStamp(void)
{
	mTimeStamp = "";
}
