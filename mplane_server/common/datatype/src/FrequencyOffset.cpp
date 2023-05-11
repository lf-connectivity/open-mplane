/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FrequencyOffset.cpp
 * \brief     Implement frequency offsets (which may be negative)
 *
 *
 * \details   This file contains the implementation of the common datatype
 *            FrequencyOffset class.
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <math.h>

#include "FrequencyOffset.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FrequencyOffset::FrequencyOffset() : FrequencyBase<long long>() {}

//-------------------------------------------------------------------------------------------------------------
FrequencyOffset::FrequencyOffset(
    long long frequency, FrequencyOffset::Unit unit)
    : FrequencyBase<long long>(frequency, unit) {}

//-------------------------------------------------------------------------------------------------------------
FrequencyOffset::FrequencyOffset(const FrequencyBase<long long>& rhs)
    : FrequencyBase<long long>(rhs) {}

//-------------------------------------------------------------------------------------------------------------
FrequencyOffset::FrequencyOffset(const Frequency& rhs)
    : FrequencyBase<long long>(static_cast<long long>(rhs.getUint())) {}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
long long
FrequencyOffset::negativeValue(const long long val) const {
  return val;
}
