/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioDatastore.cpp
 * \brief     Radio datastore base class
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

// *****************************************************************************
// Includes
// *****************************************************************************
#include <stdexcept>
#include <iostream>

#include "RadioDatastore.h"

using namespace Mplane;

// *****************************************************************************
// Type Definitions
// *****************************************************************************

// *****************************************************************************
// Radio Datastore
// *****************************************************************************

// -----------------------------------------------------------------------------
// Class:        RadDsEvtMgr
// Description:  Radio Datastore event manager class.
// -----------------------------------------------------------------------------

//=============================================================================================================
// PUBLIC
//=============================================================================================================
RadDsEvtMgr::RadDsEvtMgr()
{
}

RadDsEvtMgr::~RadDsEvtMgr()
{
}

bool RadDsEvtMgr::add(RadDsEvt_t event)
{
	mEvents.push(event);
	return true;
}

bool RadDsEvtMgr::getNext(RadDsEvt_t & event)
{
	if(mEvents.empty())
		return false;

	event = mEvents.front();
	mEvents.pop();
	return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//=============================================================================================================
// PRIVATE
//=============================================================================================================

// -----------------------------------------------------------------------------
// Class:        RadioDatastore
// Description:  Radio Datastore base class.
// -----------------------------------------------------------------------------

//=============================================================================================================
// PUBLIC
//=============================================================================================================
RadioDatastore::RadioDatastore()
	: Loggable("RadioDatastore","RDS"),
	  mEvtMgr(new RadDsEvtMgr()),
	  mState(State_E::UNINITIALISED)
{
}

RadioDatastore::~RadioDatastore()
{
}

IRadioDataStore::State_E RadioDatastore::getState(void) const
{
	return mState;
}

bool RadioDatastore::isState(IRadioDataStore::State_E state) const
{
	return(mState == state);
}

YangResult_E RadioDatastore::activate(void)
{
	return (setState(State_E::ACTIVE) ? YangResult_E::OK : YangResult_E::FAIL);
}

bool RadioDatastore::isModuleInstalled(const std::string & name) const
{
	bool installed = false;

	if (std::find(mModsInstalled.begin(), mModsInstalled.end(), name) != mModsInstalled.end())
	{
		installed = true;
	}

	return installed;
}

std::vector<std::string> RadioDatastore::getListOfInstalledModules(void) const
{
	return mModsInstalled;
}

/*
 * Get next event
 */
bool RadioDatastore::getNextEvent(RadDsEvt_t & event)
{
	return mEvtMgr->getNext(event);
}

YangResult_E RadioDatastore::dumpInstalledModules(void)
{
	YangResult_E result = YangResult_E::OK;

	eventInfo("=== Installed YANG modules in sysrepo ===");
	for(UINT32 moduleIdx = 0; moduleIdx < mModsInstalled.size(); moduleIdx++)
	{
		eventInfo("%s", mModsInstalled[moduleIdx].c_str());
	}

	return result;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

bool RadioDatastore::setState(IRadioDataStore::State_E state)
{
	bool validStateChange = true;

	if(state != mState)
	{
		switch(mState)
		{
			case State_E::UNINITIALISED:
				if(state != State_E::INITIALISED)
					validStateChange = false;
				break;
			case State_E::INITIALISED:
				if(state != State_E::CONFIGURING)
					validStateChange = false;
				break;
			case State_E::CONFIGURING:
				if(state != State_E::ACTIVE)
					validStateChange = false;
				break;
			case State_E::ACTIVE:
			case State_E::SETUP_FAILURE:
				break;
		}
		if(!validStateChange)
			throw std::runtime_error("Invalid radio datastore state change");

		mState = state;
	}

	return validStateChange;
}

bool RadioDatastore::addInstalledModule(const std::string & name)
{
	if(!isModuleInstalled(name))
	{
		mModsInstalled.push_back(name);
	}
	return true;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================
