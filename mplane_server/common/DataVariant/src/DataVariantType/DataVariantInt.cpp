/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantInt.cpp
 * \brief     Provides access methods for INT type
 *
 *
 * \details   Provides the methods used to access the DataVariant as an INT
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DataVariantInt.h"
#include "DvTypeFactory.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataVariantInt::DataVariantInt(std::shared_ptr<IDvType>& dv)
    : DataVariantTypeBase(dv) {}

//-------------------------------------------------------------------------------------------------------------
DataVariantInt::~DataVariantInt() {}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantInt::setInt(int value) {
  /* If currently no type, then create an instance of X */
  updateType(DataVariantType::Int);

  /* Need to convert from specific type to intermediate value. use intermediate
   * value to set */
  return mDvRef->fromInterInt(static_cast<IDvAccess::InterInt>(value));
}

//-------------------------------------------------------------------------------------------------------------
int
DataVariantInt::toInt() const {
  /* return the Int */
  return static_cast<int>(mDvRef->toInterInt());
}
