/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TroubleshootRxFile.cpp
 * \brief     Troubleshooting file Rx ports
 *
 *
 * \details   Troubleshooting file Rx ports
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sstream>
#include <iomanip>

#include "IRxPort.h"
#include "TroubleshootRxFile.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TroubleshootRxFile::TroubleshootRxFile() :
	TroubleshootFile("rxport.txt")
{
}

//-------------------------------------------------------------------------------------------------------------
TroubleshootRxFile::~TroubleshootRxFile()
{
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string TroubleshootRxFile::dataGather()
{
	std::stringstream ss ;
	for (auto rx : IRxPortFactory::getPorts())
	{
		ss << "Rx" << rx->getIndex() << std::endl ;
		ss << "Frequency.............: " << rx->getFrequency() << std::endl ;
		ss << "IF Atten,.............: " << rx->getIfAttenuation() << std::endl ;
		ss << "RF Atten,.............: " << rx->getRfAttenuation() << std::endl ;
		ss << std::endl ;
	}

	return ss.str() ;

}
