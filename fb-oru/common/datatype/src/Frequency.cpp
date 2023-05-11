/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Frequency.cpp
 * \brief     Implementation of the Frequency class
 *
 *
 * \details   This file contains the implementation of the common datatype
 *            Frequency class.
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <math.h>

#include "Frequency.h"

using namespace Mplane;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Frequency::Frequency() :
	FrequencyBase<long long unsigned>()
{
}

//-------------------------------------------------------------------------------------------------------------
Frequency::Frequency(long long unsigned int frequency, Frequency::Unit unit ) :
	FrequencyBase<long long unsigned>(frequency, unit)
{
}

//-------------------------------------------------------------------------------------------------------------
Frequency::Frequency(double frequency, Frequency::Unit unit ) :
	FrequencyBase<long long unsigned>(frequency, unit)
{
}

//-------------------------------------------------------------------------------------------------------------
Frequency::Frequency(const FrequencyBase<long long unsigned>& rhs) :
	FrequencyBase<long long unsigned>(rhs)
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
long long unsigned Frequency::negativeValue(const long long unsigned val) const
{
	return val ;
}
