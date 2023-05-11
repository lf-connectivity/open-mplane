/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantTypeBase.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "DvTypeFactory.h"

#include "DataVariantTypeBase.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataVariantTypeBase::DataVariantTypeBase(std::shared_ptr<IDvType>& dv)
    : mDvRef(dv) {}

//-------------------------------------------------------------------------------------------------------------
DataVariantTypeBase::~DataVariantTypeBase() {}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
DataVariantTypeBase::updateType(DataVariantType::Type type) {
  // If currently no type, the create an INT
  if (mDvRef->getType() == DataVariantType::None) {
    mDvRef = DvTypeFactory::factory(type);
  }
}
