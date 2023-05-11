/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantFreq.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DataVariantFreq.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataVariantFreq::DataVariantFreq(std::shared_ptr<IDvType>& dv)
    : DataVariantTypeBase(dv) {}

//-------------------------------------------------------------------------------------------------------------
DataVariantFreq::~DataVariantFreq() {}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantFreq::setFreq(const Frequency& value) {
  /* If currently no type, then create an instance of Float */
  updateType(DataVariantType::Freq);

  /* If current type is already FREQ, then set it directly */
  if (mDvRef->getType() == DataVariantType::Freq) {
    std::shared_ptr<IDvFreq> dv(std::dynamic_pointer_cast<IDvFreq>(mDvRef));
    return dv->setFreq(value);
  }

  /* Need to convert from specific type to intermediate value. use intermediate
   * value to set */
  return mDvRef->fromInterFloat(
      static_cast<IDvAccess::InterFloat>(value.getDbl()));
}

//-------------------------------------------------------------------------------------------------------------
Frequency
DataVariantFreq::toFreq() const {
  /* If current type is already FREQ, then use it directly */
  if (mDvRef->getType() == DataVariantType::Freq) {
    std::shared_ptr<IDvFreq> dv(std::dynamic_pointer_cast<IDvFreq>(mDvRef));
    return dv->toFreq();
  }

  /* return the Frequency */
  return Frequency(static_cast<double>(mDvRef->toInterFloat()));
}
