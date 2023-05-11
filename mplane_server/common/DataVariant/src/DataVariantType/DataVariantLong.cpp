/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantLong.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DataVariantLong.h"
#include "DvTypeFactory.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataVariantLong::DataVariantLong(std::shared_ptr<IDvType>& dv)
    : DataVariantTypeBase(dv) {}

//-------------------------------------------------------------------------------------------------------------
DataVariantLong::~DataVariantLong() {}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantLong::setLong(long long value) {
  /* If currently no type, then create an instance of Long */
  updateType(DataVariantType::Long);

  /* Need to convert from specific type to intermediate value. use intermediate
   * value to set */
  return mDvRef->fromInterInt(static_cast<IDvAccess::InterInt>(value));
}

//-------------------------------------------------------------------------------------------------------------
long long
DataVariantLong::toLong() const {
  /* return the long long */
  return static_cast<long long>(mDvRef->toInterInt());
}
