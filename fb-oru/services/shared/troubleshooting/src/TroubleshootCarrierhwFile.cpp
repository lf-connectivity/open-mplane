/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TroubleshootCarrierhwFile.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "ICarrierServer.h"
#include "ICarrierHardware.h"

#include "TroubleshootCarrierhwFile.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TroubleshootCarrierhwFile::TroubleshootCarrierhwFile() :
	TroubleshootFile("carrierhw.txt")
{
}

//-------------------------------------------------------------------------------------------------------------
TroubleshootCarrierhwFile::~TroubleshootCarrierhwFile()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string TroubleshootCarrierhwFile::dataGather()
{
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance()) ;
	std::shared_ptr<ICarrierHardwareList> carrierHardwareList( ICarrierHardwareList::getInstance() ) ;

	std::stringstream ss ;

	unsigned numCarriers(carrierServer->getMaxCarriers()) ;
	for (unsigned idx=0; idx < numCarriers; ++idx)
	{
		ICarrierHardware* ch = carrierHardwareList->getCarrierHardware( idx ) ;
		ch->showDiag(ss) ;
	}

	return ss.str() ;
}
