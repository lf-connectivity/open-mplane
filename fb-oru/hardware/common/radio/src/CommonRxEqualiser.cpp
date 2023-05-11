/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRxEqualiser.cpp
 * \brief     A file to define the interface to a common rx equaliser
 *
 *
 * \details   A file to define the interface to a common rx equaliser
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "CommonRxEqualiser.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

const unsigned CommonRxEqualiser::MAX_NUM_TAPS(32);

//=============================================================================================================
// CommonRxEqualiser
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonRxEqualiser::CommonRxEqualiser(int index, const char* name, FrequencyOffset minFreq,
		FrequencyOffset maxFreq, unsigned int numPoints) :
	CommonEqualiser(index, name, minFreq, maxFreq, numPoints)
{
	attachToFreqChange();
}

//-------------------------------------------------------------------------------------------------------------
CommonRxEqualiser::~CommonRxEqualiser()
{
}

//-------------------------------------------------------------------------------------------------------------
void CommonRxEqualiser::attachToFreqChange(void)
{
    // To allow us to be an observer of any frequency changes on Rx Port 0 we much attach our selves
    std::vector< std::shared_ptr<IRxPort> > myRxPorts = IRxPortFactory::getPorts();

    // Attach to port number of the instance
    std::dynamic_pointer_cast<Subject<IFrequencyChange>>(myRxPorts[getIndex()])->attach(*this);
}
