/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TroubleshootTxFile.cpp
 * \brief     Troubleshooting file TX ports
 *
 *
 * \details   Troubleshooting file TX ports
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sstream>
#include <iomanip>

#include "ITxPort.h"
#include "TroubleshootTxFile.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TroubleshootTxFile::TroubleshootTxFile() :
	TroubleshootFile("txport.txt")
{
}

//-------------------------------------------------------------------------------------------------------------
TroubleshootTxFile::~TroubleshootTxFile()
{
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string TroubleshootTxFile::dataGather()
{
	std::stringstream ss ;
	for (auto tx : ITxPortFactory::getPorts())
	{
		ss << "TX" << tx->getIndex() << std::endl ;
		ss << "Frequency.............: " << tx->getFrequency() << std::endl ;
		ss << "Synth Frequency.......: " << tx->getFrequency() << std::endl ;
		ss << "Target Power..........: " << tx->getTargetPower() << std::endl ;
		ss << "Min Power.............: " << tx->getMinPower() << std::endl ;
		ss << "Max Power.............: " << tx->getMaxPower() << std::endl ;
		ss << "RF Power..............: " << tx->getRfPower() << std::endl ;
		ss << "Attenutation..........: " << tx->getAttenuation() << std::endl ;
		ss << "IF Atten,.............: " << tx->getIFAttenuation() << std::endl ;
		ss << "RF Atten,.............: " << tx->getRFAttenuation() << std::endl ;
		ss << std::endl ;
	}

	return ss.str() ;

}
