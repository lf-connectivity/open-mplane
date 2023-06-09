/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SystemConfigTestHelper.cpp
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
#include "SystemConfigTestHelper.h"

// Add any specific includes here %%-->
#include <iomanip>
#include <sstream>
#include "IRadioConfig.h"
// <--%%


using namespace Mplane ;

// Add any statics, types, prototypes etc here %%-->
using namespace std;


// <--%%



//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<SystemConfigTestHelper> SystemConfigTestHelper::getInstance()
{
	static std::shared_ptr<SystemConfigTestHelper> instance(std::make_shared<SystemConfigTestHelper>()) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SystemConfigTestHelper::SystemConfigTestHelper()
// Insert additional inheritance constructors here : %%-->

// <--%%
{
	// Insert your code here : %%-->


	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
SystemConfigTestHelper::~SystemConfigTestHelper()
{
	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void SystemConfigTestHelper::save( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//

	// Insert your code here : %%-->
	std::shared_ptr<IRadioConfigSetter> config(IRadioConfigSetter::singleton()) ;
	(void)config->error() ;
	if (!config->save())
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Unable to save settings: " + config->error()) ;
	}

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void SystemConfigTestHelper::set( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * STRING setting
	// * STRING value
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//

	// Insert your code here : %%-->
	std::shared_ptr<IRadioConfigSetter> config(IRadioConfigSetter::singleton()) ;

	std::string setting(callList->find("setting")->toString()) ;
	std::string value(callList->find("value")->toString()) ;

	(void)config->error() ;
	if (!config->setValue(setting, value))
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Unable to set setting: " + config->error()) ;
	}

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void SystemConfigTestHelper::show( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//

	// Insert your code here : %%-->
	std::shared_ptr<IRadioConfig> config(IRadioConfig::singleton()) ;

	std::vector<std::pair<std::string, std::string>> values(config->values()) ;
	unsigned width(20) ;
	for (auto pair : values)
	{
		if (pair.first.size() > width)
			width = pair.first.size() ;
	}

	std::stringstream ss ;
	ss << std::endl ;
	for (auto pair : values)
	{
		ss << std::setw(width) << std::left << std::setfill('.') << pair.first << " : " << pair.second << std::endl ;
	}

	std::string error(config->error()) ;
	if (!error.empty())
	{
		ss << std::endl << "Previous error(s): " << error << std::endl ;
	}

	returnList->find(RtiKeyword::INFO_VAR)->set(ss.str()) ;

	// <--%%
}










// Add any statics, private methods etc here %%-->


// <--%%
