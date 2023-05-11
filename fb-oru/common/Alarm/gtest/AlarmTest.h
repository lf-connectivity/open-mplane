/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AlarmTest.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef ALARMTEST_H_
#define ALARMTEST_H_

#include <string.h>
#include <iostream>
#include <memory>

#include "IFault.h"
#include "IFaultOwner.h"
#include "IFaultPackage.h"
#include "IFaultBuilder.h"
#include "IFaultsList.h"

#include "Fault.h"
#include "FaultsList.h"
#include "FaultBuilder.h"
#include "FaultOwner.h"

#include "IAlarm.h"
#include "IAlarmsList.h"

#include "Alarm.h"
#include "AlarmLatched.h"
#include "AlarmPackage.h"
#include "AlarmBuilder.h"
#include "AlarmsList.h"

namespace Mplane {

//-------------------------------------------------------------------------------------------------------------
// FAULTS
class FaultA : public Fault
{
public:
	FaultA() :
		Fault(3, 2, "FaultA")
	{
		std::cerr << "FaultA new" << std::endl;
	}
	virtual ~FaultA() {
		std::cerr << "FaultA destroy" << std::endl;
	}

	void testSetState(bool state)
	{
		setStatus(state) ;
	}
};

class FaultB : public Fault
{
public:
	FaultB() :
		Fault(4, 5, "FaultB")
	{
		std::cerr << "FaultB new" << std::endl;
	}
	virtual ~FaultB() {
		std::cerr << "FaultB destroy" << std::endl;
	}

	void testSetState(bool state)
	{
		setStatus(state) ;
	}
};

class FaultC : public Fault
{
public:
	FaultC() :
		Fault(3, 5, "FaultC")
	{
		std::cerr << "FaultC new" << std::endl;
	}
	virtual ~FaultC() {
		std::cerr << "FaultC destroy" << std::endl;
	}

	void testSetState(bool state)
	{
		setStatus(state) ;
	}
};


//-------------------------------------------------------------------------------------------------------------
// FAULT OWNERS
class FaultOwner1 : public FaultOwner
{
public:
	FaultOwner1() :
		FaultOwner("FaultOwner1", {"FaultA", "FaultB"} ) {
			std::cerr << "FaultOwner1 new" << std::endl ;
	}
	virtual ~FaultOwner1() {
		std::cerr << "FaultOwner1 destroy" << std::endl ;
	}

	virtual void updateFaults() {
		std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;
		std::set<std::string> faultNames(getFaultNames()) ;

		// become the owner of the named faults
		for (auto name : faultNames)
		{
			std::shared_ptr<IFault> fault(faultsList->getFault(name)) ;
			fault->setStatus(mState) ;
		}
	}
	bool mState{false} ;
};

class FaultOwner2 : public FaultOwner
{
public:
	FaultOwner2() :
		FaultOwner("FaultOwner2", {"FaultC"} ) {
			std::cerr << "FaultOwner2 new" << std::endl ;
	}
	virtual ~FaultOwner2() {
		std::cerr << "FaultOwner2 destroy" << std::endl ;
	}

	virtual void updateFaults() {
		std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;
		std::set<std::string> faultNames(getFaultNames()) ;

		// become the owner of the named faults
		for (auto name : faultNames)
		{
			std::shared_ptr<IFault> fault(faultsList->getFault(name)) ;
			fault->setStatus(mState) ;
		}
	}
	bool mState{false} ;
};

//-------------------------------------------------------------------------------------------------------------
// FAULT PACKAGES
class FaultPackage1 : public IFaultPackage
{
public:
	FaultPackage1()
	{
		// Create the faults
		std::shared_ptr<IFault> faultA(make_fault<FaultA>()) ;
		std::shared_ptr<IFault> faultB(make_fault<FaultB>()) ;

		// Create the owner
		std::shared_ptr<IFaultOwner> faultOwner1(make_faultOwner<FaultOwner1>()) ;
	}

	virtual ~FaultPackage1() {}

};

class FaultPackage2 : public IFaultPackage
{
public:
	FaultPackage2()
	{
		// Create the faults
		std::shared_ptr<IFault> faultA(make_fault<FaultC>()) ;

		// Create the owner
		std::shared_ptr<IFaultOwner> faultOwner1(make_faultOwner<FaultOwner2>()) ;
	}

	virtual ~FaultPackage2() {}

};


//-------------------------------------------------------------------------------------------------------------
// FAULT BUILDERS
class FaultBuilder1 : public FaultBuilder
{
public:
	FaultBuilder1() {

		addFaultPackage(std::make_shared<FaultPackage1>()) ;
	}

	virtual ~FaultBuilder1() {}
} ;

class FaultBuilder2 : public FaultBuilder
{
public:
	FaultBuilder2() {

		addFaultPackage(std::make_shared<FaultPackage2>()) ;
	}

	virtual ~FaultBuilder2() {}
} ;


//-------------------------------------------------------------------------------------------------------------
// ALARMS
class Alarm1 : public Alarm
{
public:
	Alarm1() :
		Alarm("Alarm1", "test") {
			std::cerr << "Alarm1 new" << std::endl ;
	}
	virtual ~Alarm1() {
		std::cerr << "Alarm1 destroy" << std::endl ;
	}

};

class Alarm2 : public AlarmLatched
{
public:
	Alarm2() :
		AlarmLatched("Alarm2", "test") {
			std::cerr << "Alarm2 new" << std::endl ;
	}
	virtual ~Alarm2() {
		std::cerr << "Alarm2 destroy" << std::endl ;
	}

};


//-------------------------------------------------------------------------------------------------------------
// ALARM PACKAGE
class AlarmPackage1 : public AlarmPackage
{
public:
	AlarmPackage1() {

		// Create the Alarm
		std::shared_ptr<IAlarm> alarm(make_alarm<Alarm1>()) ;

		// Register faults with it
		addAlarm(alarm, {"FaultA", "FaultB"}) ;

	}
	virtual ~AlarmPackage1() {}
} ;


class AlarmPackage2 : public AlarmPackage
{
public:
	AlarmPackage2() {

		// Create the Alarm
		std::shared_ptr<IAlarm> alarm(make_alarm<Alarm2>()) ;

		// Register faults with it
		addAlarm(alarm, {"FaultC"}) ;

	}
	virtual ~AlarmPackage2() {}
} ;



//-------------------------------------------------------------------------------------------------------------
// ALARM BUILDER
class AlarmBuilder1 : public AlarmBuilder
{
public:
	AlarmBuilder1() {

		addAlarmPackage(std::make_shared<AlarmPackage1>()) ;
	}
	virtual ~AlarmBuilder1() {}
} ;

class AlarmBuilder2 : public AlarmBuilder
{
public:
	AlarmBuilder2() {

		addAlarmPackage(std::make_shared<AlarmPackage2>()) ;
	}
	virtual ~AlarmBuilder2() {}
} ;


/////////
}

#endif /* ALARMTEST_H_ */
