/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestLimitsSettings.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "IDataVariantSettings.h"
#include "TestLimitsSettings.h"

// Add any specific includes here %%-->
#include "xstringfunc.hpp"
#include "ICarrier.h"
// <--%%


using namespace Mplane ;

// Add any statics, types, prototypes etc here %%-->

// <--%%


//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ILimitsSettings> ILimitsSettings::getInstance()
{
	static std::shared_ptr<ILimitsSettings> instance(std::make_shared<TestLimitsSettings>()) ;
	return instance ;
}



//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TestLimitsSettings::TestLimitsSettings()
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
TestLimitsSettings::~TestLimitsSettings()
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
void TestLimitsSettings::registerSettings()
{
	std::shared_ptr<IDataVariantSettings> settings(IDataVariantSettings::getInstance()) ;

	settings->registerSettings(std::map<std::string, std::string>{
		{ "MAX_FIBRE",		"1" },
		{ "NUM_FIBRES",		"2" },
		{ "NUM_TX_PORTS",	"2" },
		{ "NUM_RX_PORTS",	"2" },
		{ "NUM_SRX_PORTS",	"2" },
		{ "CAL_FILE_TYPES",	"" },
		{ "CARRIER_TYPES",	"" },
		{ "CARRIER_SIGNALS",	"" },
		{ "CARRIER_STATES",	"" },
	}) ;

	// Insert your code here : %%-->

	settings->setSetting("MAX_FIBRE", std::to_string(1)) ;
	settings->setSetting("NUM_FIBRES", std::to_string(2)) ;
	settings->setSetting("NUM_TX_PORTS", std::to_string(2)) ;
	settings->setSetting("NUM_RX_PORTS", std::to_string(2)) ;
	settings->setSetting("NUM_SRX_PORTS", std::to_string(1)) ;
	settings->setSetting("CAL_FILE_TYPES", "Tx:Rx") ;
	settings->setSetting("CARRIER_TYPES", join(ICarrier::getAllTypes(), ':')) ;
	settings->setSetting("CARRIER_SIGNALS", join(ICarrier::getAllSignals(), ':')) ;
	settings->setSetting("CARRIER_STATES", join(ICarrier::getAllStates(), ':')) ;
	// <--%%
}

// Add any statics, private methods etc here %%-->

// <--%%
