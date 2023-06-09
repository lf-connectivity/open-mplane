/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioStateTestHelper.cpp
 * \brief     Test helper for ZCU111
 *
 *
 * \details   Auto-generated by gentool. Contains test interface definitions. Please add your own
 * code between the %%--> and <--%% comment lines (any code outside these comments will be discarded
 * next time the generate tool is run)
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "RtiKeyword.h"
#include "RadioStateTestHelper.h"

// Add any specific includes here %%-->
#include "IRadioState.h"
// <--%%


using namespace Mplane ;

// Add any statics, types, prototypes etc here %%-->
//=============================================================================================================
// CONSTANTS
//=============================================================================================================



// <--%%



//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<RadioStateTestHelper> RadioStateTestHelper::getInstance()
{
	static std::shared_ptr<RadioStateTestHelper> instance(std::make_shared<RadioStateTestHelper>()) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RadioStateTestHelper::RadioStateTestHelper()
// Insert additional inheritance constructors here : %%-->

// <--%%
{
	// Insert your code here : %%-->


	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
RadioStateTestHelper::~RadioStateTestHelper()
{
	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void RadioStateTestHelper::getState( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//

	// Insert your code here : %%-->
	std::stringstream     returnString;

	std::shared_ptr<IRadioState> radioState(IRadioState::getInstance());

	IRadioState::RadioStatesType state = radioState->getState();

	returnString << "Current state of radio - ";

	switch( state )
	{
	case IRadioState::RADIO_STATE_INITIAL:
		returnString << "Initial";
		break;
	case IRadioState::RADIO_STATE_NORMAL:
		returnString << "Normal";
		break;
	case IRadioState::RADIO_STATE_NORMAL_STANDBY:
		returnString << "Standby";
		break;
	case IRadioState::RADIO_STATE_NORMAL_SW_DOWNLOAD:
		returnString << "Downloading Software";
		break;
	case IRadioState::RADIO_STATE_FAILED_CPRI_LINK_FAIL:
		returnString << "CPRI link failure";
		break;
	case IRadioState::RADIO_STATE_DEGRADED:
		returnString << "Degraded";
		break;
	case IRadioState::RADIO_STATE_FAILED:
		returnString << "Failed";
		break;
	default:
		returnString << "Unknown!";
		break;
	}

	returnList->find(RtiKeyword::INFO_VAR)->set(returnString.str());
	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void RadioStateTestHelper::showAll( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//

	// Insert your code here : %%-->
	std::shared_ptr<IRadioState> radioState(IRadioState::getInstance());

	radioState->showRadioState();
	// <--%%
}










// Add any statics, private methods etc here %%-->

// <--%%
