/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FaultTest.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef FAULTTEST_H_
#define FAULTTEST_H_

#include "IFault.h"
#include "IFaultOwner.h"
#include "IFaultsList.h"

#include "Fault.h"
#include "FaultsList.h"
#include "FaultOwner.h"
#include "IFaultPackage.h"
#include "FaultBuilder.h"

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

}

#endif /* FAULTTEST_H_ */
