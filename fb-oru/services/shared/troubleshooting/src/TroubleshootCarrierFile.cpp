/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TroubleshootCarrierFile.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "ICarrier.h"
#include "ICarrierServer.h"

#include "TroubleshootCarrierFile.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TroubleshootCarrierFile::TroubleshootCarrierFile() :
	TroubleshootFile("carrier.txt")
{
}

//-------------------------------------------------------------------------------------------------------------
TroubleshootCarrierFile::~TroubleshootCarrierFile()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string TroubleshootCarrierFile::dataGather()
{
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance()) ;

	std::stringstream ss ;
	unsigned numCarriers(carrierServer->getMaxCarriers()) ;
	for (unsigned idx=0; idx < numCarriers; ++idx)
	{
		const ICarrier& carrier( carrierServer->getCarrier(idx) ) ;
		carrier.showCarrier(ss) ;
	}

	return ss.str() ;
}
