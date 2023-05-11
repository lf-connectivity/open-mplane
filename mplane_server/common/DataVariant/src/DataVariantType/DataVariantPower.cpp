/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantPower.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DataVariantPower.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataVariantPower::DataVariantPower(std::shared_ptr<IDvType>& dv)
    : DataVariantTypeBase(dv) {}

//-------------------------------------------------------------------------------------------------------------
DataVariantPower::~DataVariantPower() {}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantPower::setPower(const Power& value) {
  /* If currently no type, then create an instance of Float */
  updateType(DataVariantType::Power);

  /* If current type is already POWER, then set it directly */
  if (mDvRef->getType() == DataVariantType::Power) {
    std::shared_ptr<IDvPower> dv(std::dynamic_pointer_cast<IDvPower>(mDvRef));
    return dv->setPower(value);
  }

  /* Need to convert from specific type to intermediate value. use intermediate
   * value to set */
  return mDvRef->fromInterFloat(
      static_cast<IDvAccess::InterFloat>(value.get()));
}

//-------------------------------------------------------------------------------------------------------------
Power
DataVariantPower::toPower() const {
  /* If current type is already POWER, then use it directly */
  if (mDvRef->getType() == DataVariantType::Power) {
    std::shared_ptr<IDvPower> dv(std::dynamic_pointer_cast<IDvPower>(mDvRef));
    return dv->toPower();
  }

  /* return the Power */
  return Power(static_cast<double>(mDvRef->toInterFloat()));
}
