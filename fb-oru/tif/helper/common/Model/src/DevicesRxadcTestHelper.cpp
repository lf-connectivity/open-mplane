/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DevicesRxadcTestHelper.cpp
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
#include "DevicesRxadcTestHelper.h"

// Add any specific includes here %%-->
#include <sstream>
#include "IRadio.h"
#include "IDevices.h"
#include "IAdc.h"

// <--%%


using namespace Mplane ;

// Add any statics, types, prototypes etc here %%-->

// <--%%



//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<DevicesRxadcTestHelper> DevicesRxadcTestHelper::getInstance()
{
	static std::shared_ptr<DevicesRxadcTestHelper> instance(std::make_shared<DevicesRxadcTestHelper>()) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DevicesRxadcTestHelper::DevicesRxadcTestHelper()
// Insert additional inheritance constructors here : %%-->

// <--%%
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
DevicesRxadcTestHelper::~DevicesRxadcTestHelper()
{
	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void DevicesRxadcTestHelper::show( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//

	// Insert your code here : %%-->
	std::shared_ptr<IRadio> radio( IRadioFactory::getInterface() ) ;
	IDevices& devices( radio->getDevices() ) ;
	std::shared_ptr<IAdc> rxadc( devices.getRxAdc( 0 ) ) ;

	std::stringstream ss ;
	rxadc->show(ss) ;
	returnList->find(RtiKeyword::INFO_VAR)->set(ss.str()) ;

	// <--%%
}










// Add any statics, private methods etc here %%-->

// <--%%
