/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonTxEqualiser.cpp
 * \brief     A file to define the interface to a common tx equaliser
 *
 *
 * \details   A file to define the interface to a common tx equaliser
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "CommonTxEqualiser.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

const unsigned CommonTxEqualiser::MAX_NUM_TAPS(32);

//=============================================================================================================
// CommonTxEqualiser
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonTxEqualiser::CommonTxEqualiser(int index, const char* name, FrequencyOffset minFreq,
		FrequencyOffset maxFreq, unsigned int numPoints) :
	CommonEqualiser(index, name, minFreq, maxFreq, numPoints)
{
	attachToFreqChange();
}

//-------------------------------------------------------------------------------------------------------------
CommonTxEqualiser::~CommonTxEqualiser()
{
}

//-------------------------------------------------------------------------------------------------------------
void CommonTxEqualiser::attachToFreqChange(void)
{
    // To allow us to be an observer of any frequency changes on Rx Port 0 we much attach our selves
    std::vector< std::shared_ptr<ITxPort> > myTxPorts = ITxPortFactory::getPorts();

    // Attach to port number of the instance
    std::dynamic_pointer_cast<Subject<IFrequencyChange>>(myTxPorts[getIndex()])->attach(*this);
}
