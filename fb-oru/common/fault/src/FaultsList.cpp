/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FaultsList.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <stdexcept>
#include "FaultsList.h"

using namespace Mplane;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

class FaultsListInst : public FaultsList
{
public:
	FaultsListInst() : FaultsList() {}
	virtual ~FaultsListInst() {}
};
//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFaultsList> IFaultsList::getInstance()
{
	static std::shared_ptr<IFaultsList> instance(std::make_shared<FaultsListInst>()) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FaultsList::~FaultsList()
{
}

//-------------------------------------------------------------------------------------------------------------
void FaultsList::updateFaults()
{
	Mutex::Lock lock(mFaultsOwnersListMutex);
	for (auto entry : mFaultsOwnersList)
	{
		entry.second->updateFaults() ;
	}
}


//-------------------------------------------------------------------------------------------------------------
void FaultsList::addFault(std::shared_ptr<IFault> fault)
{
	Mutex::Lock lock(mFaultsListMutex);

	// check there's not already an entry
	auto entry(mFaultsList.find(fault->getName())) ;
	if (entry != mFaultsList.end())
		throw std::invalid_argument("FaultsList adding Fault '" + fault->getName() + "' already registered") ;

	// Add the fault
	mFaultsList[fault->getName()] = fault ;
}

//-------------------------------------------------------------------------------------------------------------
void FaultsList::addOwner(std::shared_ptr<IFaultOwner> owner)
{
	Mutex::Lock lock(mFaultsOwnersListMutex);

	// check there's not already an entry
	auto entry(mFaultsOwnersList.find(owner->getName())) ;
	if (entry != mFaultsOwnersList.end())
		return ;

	// Add the owner
	mFaultsOwnersList[owner->getName()] = owner ;
}

////-------------------------------------------------------------------------------------------------------------
void FaultsList::resetFaults()
{
	Mutex::Lock lock(mFaultsListMutex);
	for (auto entry : mFaultsList)
	{
		entry.second->reset() ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void FaultsList::show(std::ostream& os) const
{
	Mutex::Lock lock(mFaultsListMutex);
	for (auto entry : mFaultsList)
	{
		entry.second->show(os) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void FaultsList::showNamesAndIds(std::ostream& os) const
{
	Mutex::Lock lock(mFaultsListMutex);

	os << "Available fault Id's and Names -" << std::endl ;
	os << "    Id Name" << std::endl ;

	for (auto entry : mFaultsList)
	{
		entry.second->showNameAndId(os) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
bool FaultsList::allHaveOwners()
{
	Mutex::Lock lock(mFaultsListMutex);
	for (auto entry : mFaultsList)
	{
		if (!entry.second->getOwner().get())
			return false ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
int FaultsList::getSize() const
{
	Mutex::Lock lock(mFaultsListMutex);
	return mFaultsList.size() ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFault> FaultsList::getFault(const std::string& name) const
{
	Mutex::Lock lock(mFaultsListMutex);

	// Find the entry with the corresponding name
	auto entry(mFaultsList.find(name)) ;
	if (entry == mFaultsList.end())
		return std::shared_ptr<IFault>() ;

	// return the fault
	return std::shared_ptr<IFault>(mFaultsList.at(name).get(), [](IFault*){}) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFault> FaultsList::getFault(const unsigned int ident) const
{
	Mutex::Lock lock(mFaultsListMutex);

	std::string name;


	// Find the entry with the corresponding ident
	for (auto findEntryById : mFaultsList)
	{
		if( ident == findEntryById.second->getId() )
		{
			/* Retrieve the name to use */
			name = findEntryById.second->getName();

			/* Break out of the loop early */
			break;
		}
	}

	/* Using the name we just found, check that there is an entry and we didn't just get to the end */
	auto entry(mFaultsList.find(name)) ;
	if (entry == mFaultsList.end())
		return std::shared_ptr<IFault>() ;

	// return the fault
	return std::shared_ptr<IFault>(mFaultsList.at(name).get(), [](IFault*){}) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFaultOwner> FaultsList::getFaultOwner(const std::string& name) const
{
	Mutex::Lock lock(mFaultsOwnersListMutex);

	auto entry(mFaultsOwnersList.find(name)) ;
	if (entry == mFaultsOwnersList.end())
		return std::shared_ptr<IFaultOwner>() ;

	// return fault owner
	return std::shared_ptr<IFaultOwner>(mFaultsOwnersList.at(name).get(), [](IFaultOwner*){}) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FaultsList::FaultsList() :
	Loggable("FaultsList", "FL"),
	mFaultsList(),
	mFaultsOwnersList(),
	mFaultsListMutex(),
	mFaultsOwnersListMutex()
{
}

//=============================================================================================================
// TEST
//=============================================================================================================
#ifdef OFF_TARGET
//-------------------------------------------------------------------------------------------------------------
bool FaultsList::removeFault(const std::string& name)
{
	Mutex::Lock lock(mFaultsListMutex);

	// check there's an entry
	auto entry(mFaultsList.find(name)) ;
	if (entry == mFaultsList.end())
		return false ;

	// remove the fault
	mFaultsList.erase(entry) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FaultsList::removeFaultOwner(const std::string& name)
{
	Mutex::Lock lock(mFaultsOwnersListMutex);

	// check there's an entry
	auto entry(mFaultsOwnersList.find(name)) ;
	if (entry == mFaultsOwnersList.end())
		return false ;

	// remove the fault owner
	mFaultsOwnersList.erase(entry) ;
	return true ;
}


#endif
