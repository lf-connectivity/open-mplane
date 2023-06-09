/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SystemBootTestHelper.cpp
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
#include "SystemBootTestHelper.h"

// Add any specific includes here %%-->
#include <sstream>
#include "IBootTimer.h"
// <--%%


using namespace Mplane ;

// Add any statics, types, prototypes etc here %%-->
using namespace std;


// <--%%



//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<SystemBootTestHelper> SystemBootTestHelper::getInstance()
{
	static std::shared_ptr<SystemBootTestHelper> instance(std::make_shared<SystemBootTestHelper>()) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SystemBootTestHelper::SystemBootTestHelper()
// Insert additional inheritance constructors here : %%-->

// <--%%
{
	// Insert your code here : %%-->


	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
SystemBootTestHelper::~SystemBootTestHelper()
{
	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void SystemBootTestHelper::get( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * FLOAT appStart (s)
	// * FLOAT tifTime (s)
	// * FLOAT tifElapsed (s)
	// * FLOAT appElapsed (s)
	// * FLOAT bootTime (s)
	//

	// Insert your code here : %%-->
	std::shared_ptr<IBootTimer> bootTimer(IBootTimer::getInstance()) ;

	returnList->find("appStart")->set( bootTimer->getStartTime() ) ;
	returnList->find("tifTime")->set( bootTimer->getTifTime() ) ;
	returnList->find("tifElapsed")->set( bootTimer->getTifElapsed() ) ;
	returnList->find("appElapsed")->set( bootTimer->getAppElapsed() ) ;
	returnList->find("bootTime")->set( bootTimer->getAppTime() ) ;

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void SystemBootTestHelper::show( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//

	// Insert your code here : %%-->
	std::shared_ptr<IBootTimer> bootTimer(IBootTimer::getInstance()) ;

	std::stringstream ss ;
	ss << std::endl ;
	bootTimer->show(ss) ;
	returnList->find(RtiKeyword::INFO_VAR)->set(ss.str()) ;
	// <--%%
}










// Add any statics, private methods etc here %%-->


// <--%%
