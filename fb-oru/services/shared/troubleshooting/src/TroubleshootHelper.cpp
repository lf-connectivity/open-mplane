/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TroubleshootHelper.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "ITroubleshootMgr.h"

#include "TroubleshootLoghistoryFile.h"
#include "TroubleshootCarrierFile.h"
#include "TroubleshootCarrierhwFile.h"
#include "TroubleshootTxFile.h"
#include "TroubleshootRxFile.h"

#include "TroubleshootHelper.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void TroubleshootHelper::commonSetup()
{
	// add troubleshooting for the logs
	ITroubleshootMgr::singleton()->addFile( std::make_shared<TroubleshootLoghistoryFile>() ) ;

	// carrier troubleshooting
	ITroubleshootMgr::singleton()->addFile( std::make_shared<TroubleshootCarrierFile>() ) ;

	// carrier hardware troubleshooting
	ITroubleshootMgr::singleton()->addFile( std::make_shared<TroubleshootCarrierhwFile>() ) ;

	// TX ports troubleshooting
	ITroubleshootMgr::singleton()->addFile( std::make_shared<TroubleshootTxFile>() ) ;

	// RX ports troubleshooting
	ITroubleshootMgr::singleton()->addFile( std::make_shared<TroubleshootRxFile>() ) ;

}
