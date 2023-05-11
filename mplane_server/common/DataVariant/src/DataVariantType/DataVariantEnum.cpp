/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantEnum.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DataVariantType/DataVariantEnum.h"
#include "DvTypeFactory.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataVariantEnum::DataVariantEnum(std::shared_ptr<IDvType>& dv)
    : DataVariantTypeBase(dv) {}

//-------------------------------------------------------------------------------------------------------------
DataVariantEnum::~DataVariantEnum() {}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantEnum::setEnum(int value) {
  // If currently no type, then we can't set the ENUM
  if (mDvRef->getType() != DataVariantType::Enum)
    return false;

  /* Need to convert from specific type to intermediate value. use intermediate
   * value to set */
  return mDvRef->fromInterInt(static_cast<IDvAccess::InterInt>(value));
}

//-------------------------------------------------------------------------------------------------------------
int
DataVariantEnum::toEnum() const {
  /* return the Int */
  return static_cast<int>(mDvRef->toInterInt());
}
