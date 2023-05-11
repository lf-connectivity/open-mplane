/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantComplex.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DataVariantComplex.h"
#include "DvTypeFactory.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataVariantComplex::DataVariantComplex(std::shared_ptr<IDvType>& dv)
    : DataVariantTypeBase(dv) {}

//-------------------------------------------------------------------------------------------------------------
DataVariantComplex::~DataVariantComplex() {}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantComplex::setComplex(const std::complex<float>& value) {
  /* If currently no type, the create an instance of X */
  updateType(DataVariantType::Complex);

  /* If current type is already COMPLEX, then set it directly */
  if (mDvRef->getType() == DataVariantType::Complex) {
    std::shared_ptr<IDvComplex> dv(
        std::dynamic_pointer_cast<IDvComplex>(mDvRef));
    return dv->setComplex(value);
  }

  /* Need to convert from specific type to intermediate value. use intermediate
   * value to set */
  return mDvRef->fromInterFloat(
      static_cast<IDvAccess::InterFloat>(value.real()));
}

//-------------------------------------------------------------------------------------------------------------
std::complex<float>
DataVariantComplex::toComplex() const {
  /* If current type is already Complex, then use it directly */
  if (mDvRef->getType() == DataVariantType::Complex) {
    std::shared_ptr<IDvComplex> dvComplex(
        std::dynamic_pointer_cast<IDvComplex>(mDvRef));
    return dvComplex->toComplex();
  }

  /* return the Complex */
  return std::complex<float>(static_cast<float>(mDvRef->toInterFloat()), 0.0);
}
