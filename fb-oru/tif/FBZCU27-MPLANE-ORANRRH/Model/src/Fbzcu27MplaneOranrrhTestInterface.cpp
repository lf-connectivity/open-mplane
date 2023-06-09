/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Fbzcu27MplaneOranrrhTestInterface.cpp
 * \brief     Test interface for FBZCU27-MPLANE-ORANRRH
 *
 *
 * \details   Auto-generated by gentool. Contains test interface definitions.
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "Fbzcu27MplaneOranrrhTestInterface.h"

#include "Fbzcu27MplaneOranrrhAgcTestHandler.h"
#include "Fbzcu27MplaneOranrrhCarrierTestHandler.h"
#include "Fbzcu27MplaneOranrrhCarrierHwTestHandler.h"
#include "Fbzcu27MplaneOranrrhDot1agdMonTestHandler.h"
#include "Fbzcu27MplaneOranrrhEmbeddedTestHandler.h"
#include "Fbzcu27MplaneOranrrhEqualiserTestHandler.h"
#include "Fbzcu27MplaneOranrrhFibreTestHandler.h"
#include "Fbzcu27MplaneOranrrhFpgaTestHandler.h"
#include "Fbzcu27MplaneOranrrhGpioTestHandler.h"
#include "Fbzcu27MplaneOranrrhHeartbeatTestHandler.h"
#include "Fbzcu27MplaneOranrrhI2cTestHandler.h"
#include "Fbzcu27MplaneOranrrhIpTestHandler.h"
#include "Fbzcu27MplaneOranrrhIpListTestHandler.h"
#include "Fbzcu27MplaneOranrrhNetopeerMonTestHandler.h"
#include "Fbzcu27MplaneOranrrhOranFpgaTestHandler.h"
#include "Fbzcu27MplaneOranrrhRadioStateTestHandler.h"
#include "Fbzcu27MplaneOranrrhRegDevicesTestHandler.h"
#include "Fbzcu27MplaneOranrrhRxPortTestHandler.h"
#include "Fbzcu27MplaneOranrrhSrxPortTestHandler.h"
#include "Fbzcu27MplaneOranrrhSystemTestHandler.h"
#include "Fbzcu27MplaneOranrrhSystemConfigTestHandler.h"
#include "Fbzcu27MplaneOranrrhTxPortTestHandler.h"
#include "Fbzcu27MplaneOranrrhYangConfigTestHandler.h"
#include "Fbzcu27MplaneOranrrhYangManagerTestHandler.h"
#include "Fbzcu27MplaneOranrrhYangTestTestHandler.h"


using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Fbzcu27MplaneOranrrhTestInterface::Fbzcu27MplaneOranrrhTestInterface()
{
	Fbzcu27MplaneOranrrhAgcTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhCarrierTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhCarrierHwTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhDot1agdMonTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhEmbeddedTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhEqualiserTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhFibreTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhFpgaTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhGpioTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhHeartbeatTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhI2cTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhIpTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhIpListTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhNetopeerMonTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhOranFpgaTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhRadioStateTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhRegDevicesTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhRxPortTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhSrxPortTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhSystemTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhSystemConfigTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhTxPortTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhYangConfigTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhYangManagerTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	Fbzcu27MplaneOranrrhYangTestTestHandler::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;


}

//-------------------------------------------------------------------------------------------------------------
Fbzcu27MplaneOranrrhTestInterface::~Fbzcu27MplaneOranrrhTestInterface()
{
}
