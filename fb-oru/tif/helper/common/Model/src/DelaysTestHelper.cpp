/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DelaysTestHelper.cpp
 * \brief     Test helper for common
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
#include "DelaysTestHelper.h"

// Add any specific includes here %%-->

// <--%%


using namespace Mplane ;

// Add any statics, types, prototypes etc here %%-->


// <--%%



//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<DelaysTestHelper> DelaysTestHelper::getInstance()
{
	static std::shared_ptr<DelaysTestHelper> instance(std::make_shared<DelaysTestHelper>()) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DelaysTestHelper::DelaysTestHelper()
// Insert additional inheritance constructors here : %%-->
: mDelayInterface( IDelaysMgr::getInterface() )

// <--%%
{
	// Insert your code here : %%-->


	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
DelaysTestHelper::~DelaysTestHelper()
{
	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void DelaysTestHelper::getAdjDelayDown( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * UINT carrier
	// * UINT{1..${NUM_TX_PORTS}} tx
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * UINT delay (ns)
	//

	// Insert your code here : %%-->
	unsigned delay = mDelayInterface->getCarrierDelay(IDelaysMgr::ADJDELAY_DOWN,
		callList->find("carrier")->toUint(),
		callList->find("tx")->toUint()-1
	) ;
	returnList->find("delay")->setUint(delay) ;

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void DelaysTestHelper::getAdjDelayUp( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * UINT carrier
	// * UINT{1..${NUM_RX_PORTS}} rx
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * UINT delay (ns)
	//

	// Insert your code here : %%-->
	unsigned delay = mDelayInterface->getCarrierDelay(IDelaysMgr::ADJDELAY_UP,
		callList->find("carrier")->toUint(),
		callList->find("rx")->toUint()-1
	) ;
	returnList->find("delay")->setUint(delay) ;

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void DelaysTestHelper::getAdjLimits( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * UINT dlLimit (ns)
	// * UINT dlStep (ns)
	// * UINT ulLimit (ns)
	// * UINT ulStep (ns)
	//

	// Insert your code here : %%-->
	unsigned dlLimit ;
	unsigned dlStep ;
	unsigned ulLimit ;
	unsigned ulStep ;

	mDelayInterface->getAdjDelayLimit(dlLimit, dlStep, ulLimit, ulStep) ;
	returnList->find("dlLimit")->setUint(dlLimit) ;
	returnList->find("dlStep")->setUint(dlStep) ;
	returnList->find("ulLimit")->setUint(ulLimit) ;
	returnList->find("ulStep")->setUint(ulStep) ;

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void DelaysTestHelper::getExtDelayDown( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * UINT{1..${NUM_TX_PORTS}} tx
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * UINT delay (ns)
	//

	// Insert your code here : %%-->
	unsigned delay = mDelayInterface->getPathDelay(IDelaysMgr::EXTDELAY_DOWN,
		callList->find("tx")->toUint()-1
	) ;
	returnList->find("delay")->setUint(delay) ;

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void DelaysTestHelper::getExtDelayUp( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * UINT{1..${NUM_RX_PORTS}} rx
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * UINT delay (ns)
	//

	// Insert your code here : %%-->
	unsigned delay = mDelayInterface->getPathDelay(IDelaysMgr::EXTDELAY_UP,
		callList->find("rx")->toUint()-1
	) ;
	returnList->find("delay")->setUint(delay) ;

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void DelaysTestHelper::getFrameOffsetDown( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * UINT carrier
	// * UINT{1..${NUM_TX_PORTS}} tx
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * UINT delay (BF)
	//

	// Insert your code here : %%-->
	unsigned delay = mDelayInterface->getCarrierDelay(IDelaysMgr::FRAMEOFF_UP,
		callList->find("carrier")->toUint(),
		callList->find("tx")->toUint()-1
	) ;
	returnList->find("delay")->setUint(delay) ;

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void DelaysTestHelper::setAdjDelayDown( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * UINT carrier
	// * UINT{1..${NUM_TX_PORTS}} tx
	// * UINT delay (ns)
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//

	// Insert your code here : %%-->
	bool ok = mDelayInterface->appSetCarrierDelay(IDelaysMgr::ADJDELAY_DOWN,
		callList->find("carrier")->toUint(),
		callList->find("tx")->toUint()-1,
		callList->find("delay")->toUint()
	) ;
	if (!ok)
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Error settings delay: "+mDelayInterface->getError()) ;
	}
	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void DelaysTestHelper::setAdjDelayUp( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * UINT carrier
	// * UINT{1..${NUM_RX_PORTS}} rx
	// * UINT delay (ns)
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//

	// Insert your code here : %%-->
	bool ok = mDelayInterface->appSetCarrierDelay(IDelaysMgr::ADJDELAY_UP,
		callList->find("carrier")->toUint(),
		callList->find("rx")->toUint()-1,
		callList->find("delay")->toUint()
	) ;
	if (!ok)
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Error settings delay: "+mDelayInterface->getError()) ;
	}
	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void DelaysTestHelper::setExtDelayDown( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * UINT{1..${NUM_TX_PORTS}} tx
	// * UINT delay (ns)
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//

	// Insert your code here : %%-->
	bool ok = mDelayInterface->appSetPathDelay(IDelaysMgr::EXTDELAY_DOWN,
		callList->find("tx")->toUint()-1,
		callList->find("delay")->toUint()
	) ;
	if (!ok)
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Error settings delay: "+mDelayInterface->getError()) ;
	}

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void DelaysTestHelper::setExtDelayUp( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * UINT{1..${NUM_RX_PORTS}} rx
	// * UINT delay (ns)
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//

	// Insert your code here : %%-->
	bool ok = mDelayInterface->appSetPathDelay(IDelaysMgr::EXTDELAY_UP,
		callList->find("rx")->toUint()-1,
		callList->find("delay")->toUint()
	) ;
	if (!ok)
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Error settings delay: "+mDelayInterface->getError()) ;
	}

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void DelaysTestHelper::setFrameOffsetDown( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * UINT carrier
	// * UINT{1..${NUM_TX_PORTS}} tx
	// * UINT delay (BF)
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//

	// Insert your code here : %%-->
	bool ok = mDelayInterface->appSetCarrierDelay(IDelaysMgr::FRAMEOFF_DOWN,
		callList->find("carrier")->toUint(),
		callList->find("tx")->toUint()-1,
		callList->find("delay")->toUint()
	) ;
	if (!ok)
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Error settings delay: "+mDelayInterface->getError()) ;
	}
	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void DelaysTestHelper::show( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//

	// Insert your code here : %%-->
	std::stringstream ss ;
	ss << std::endl ;
	mDelayInterface->show(ss) ;
	returnList->find(RtiKeyword::INFO_VAR)->set(ss.str()) ;
	// <--%%
}










// Add any statics, private methods etc here %%-->



// <--%%
