/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantBool.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DataVariantBool.h"
#include "DvTypeFactory.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataVariantBool::DataVariantBool(std::shared_ptr<IDvType>& dv)
    : DataVariantTypeBase(dv) {}

//-------------------------------------------------------------------------------------------------------------
DataVariantBool::~DataVariantBool() {}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantBool::setBool(bool value) {
  /* If currently no type, then create an instance of X */
  updateType(DataVariantType::Bool);

  /* Need to convert from specific type to intermediate value. use intermediate
   * value to set */
  return mDvRef->fromInterInt(value ? 1 : 0);
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantBool::toBool() const {
  /* return the bool */
  return (mDvRef->toInterInt() > 0);
}
