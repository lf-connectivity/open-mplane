/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FaultOwner.cpp
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
#include "IFault.h"
#include "FaultOwner.h"

using namespace Mplane;


//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Mplane::FaultOwner::makeFaultOwner(std::shared_ptr<IFaultOwner> faultOwner)
{
	// become the owner of the named faults
	std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;
	for (auto name : faultOwner->getFaultNames())
	{
		std::shared_ptr<IFault> fault(faultsList->getFault(name)) ;
		if (!fault.get())
			throw std::invalid_argument("Invalid fault name " + name) ;

		if (fault->addOwner(faultOwner) != ReturnType::RT_OK)
			throw std::invalid_argument("Unable to become owner of fault " + name) ;
	}
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FaultOwner::FaultOwner(const std::string& name, const std::set<std::string>& faultNames) :
	mName(name),
	mFaultNames(faultNames)
{
}

Mplane::FaultOwner::FaultOwner(const std::string& name) :
	mName(name)
{
}

//-------------------------------------------------------------------------------------------------------------
FaultOwner::~FaultOwner()
{
}

//-------------------------------------------------------------------------------------------------------------
void FaultOwner::updateFaults()
{
	// override in derived object
}

//-------------------------------------------------------------------------------------------------------------
void FaultOwner::faultCallback(IFault& fault)
{
	// override in derived object
}

//-------------------------------------------------------------------------------------------------------------
void FaultOwner::resetFaults()
{
	// Call the hook first to allow derived objects to clear the hardware
	clearFaults() ;

	// Now clear the faults we own
	std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;
	for (auto name : mFaultNames)
	{
		std::shared_ptr<IFault> fault(faultsList->getFault(name)) ;
		if (!fault.get())
			continue ;

		fault->reset() ;
	}
}

//-------------------------------------------------------------------------------------------------------------
std::string FaultOwner::getName() const
{
	return mName ;
}

//-------------------------------------------------------------------------------------------------------------
std::set<std::string> FaultOwner::getFaultNames() const
{
	return mFaultNames ;
}


//-------------------------------------------------------------------------------------------------------------
void FaultOwner::show(std::ostream& os) const
{
	os << "Name....................: " << mName << std::endl ;
	os << "Faults Owned:" << std::endl ;

	std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;
	for (auto name : mFaultNames)
	{
		std::shared_ptr<IFault> fault(faultsList->getFault(name)) ;
		if (!fault.get())
			continue ;

		fault->show(os) ;
	}
}


//-------------------------------------------------------------------------------------------------------------
void FaultOwner::addFault(const std::string &name)
{
	addFault(std::set<std::string>{name}) ;
}

//-------------------------------------------------------------------------------------------------------------
void FaultOwner::addFault(const std::set<std::string> &names)
{
	mFaultNames.insert(names.begin(), names.end()) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void FaultOwner::clearFaults()
{
	// override in derived object
}
