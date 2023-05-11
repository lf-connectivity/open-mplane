/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantTypes.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DataVariantTypes.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataVariantTypes::DataVariantTypes(std::shared_ptr<IDvType>& dv)
    : DataVariantFloat(dv),
      DataVariantComplex(dv),
      DataVariantEnum(dv),
      DataVariantBool(dv),
      DataVariantFreq(dv),
      DataVariantPower(dv),
      DataVariantUint(dv),
      DataVariantLong(dv),
      DataVariantDouble(dv),

      DataVariantInt(dv) {}

//-------------------------------------------------------------------------------------------------------------
DataVariantTypes::~DataVariantTypes() {}
