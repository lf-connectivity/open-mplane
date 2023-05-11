/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdPapr.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DpdPapr.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DpdPapr::DpdPapr() :
	TaskEvent(Task::PRIORITY_MEDIUM, Task::SMALL_STACK, "DpdPapr", "DpdService"),

	mPaprSubjects(),
	mMutex(),
	mData()
{

	// Register for PAPR updates
	std::vector< std::shared_ptr<IPaprSubject> > paprSubjects(IPaprFactory::getPaprSubjects()) ;
	for (auto paprSubject : paprSubjects)
	{
		std::dynamic_pointer_cast< Subject<IPaprSubject, const IPaprData&> >(paprSubject)->attach(*this) ;

		// keep a copy of this object so that it doesn't go out of scope before we get chance to deregister
		mPaprSubjects.push_back(paprSubject) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
DpdPapr::~DpdPapr()
{
	// UnRegister for PAPR updates
	for (auto paprSubject : mPaprSubjects)
	{
		std::shared_ptr<Subject<IPaprSubject, const IPaprData&>> subject(std::dynamic_pointer_cast< Subject<IPaprSubject, const IPaprData&> >(paprSubject)) ;
		if (!subject)
			continue ;
		subject->detach(*this) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void DpdPapr::update(IPaprSubject& subject, const IPaprData& data)
{
	{
	Mutex::Lock lock(mMutex) ;
	mData.push(PaprData(data.getTxPort(), data.getPapr())) ;
	}
	event() ;
}

//-------------------------------------------------------------------------------------------------------------
const char* DpdPapr::name() const
{
	return "DpdPapr" ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool DpdPapr::runEvent()
{
	unsigned numEntries(0) ;
	{
		Mutex::Lock lock(mMutex) ;
		numEntries = mData.size() ;
	}

	std::shared_ptr<IDpdControl> dpdControl(IDpdControl::getInterface()) ;

	PaprData data ;
	while (numEntries > 0)
	{
		{
			Mutex::Lock lock(mMutex) ;
			data = mData.front() ;
			mData.pop() ;
			numEntries = mData.size() ;
		}

		// Set the PAPR target for this TX
		dpdControl->setPapr(data.getTxPort(), data.getPapr()) ;
	}

	return true ;
}
