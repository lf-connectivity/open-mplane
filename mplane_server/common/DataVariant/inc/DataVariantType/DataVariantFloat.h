/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantFloat.h
 * \brief     Provides access methods for FLOAT type
 *
 *
 * \details   Provides the methods used to access the DataVariant as an FLOAT
 *
 */

#ifndef DATAVARIANTFLOAT_H_
#define DATAVARIANTFLOAT_H_

#include "DataVariantTypeBase.h"
#include "IDvFloat.h"

namespace Mplane {

class DataVariantFloat : public DataVariantTypeBase, public virtual IDvFloat {
 public:
  explicit DataVariantFloat(std::shared_ptr<IDvType>& dv);
  virtual ~DataVariantFloat();

  /**
   * Set the value of the the variant to the float value. If the variant
   * is type Float, the value is cast to a float internally.
   *
   *
   * @param value
   */
  virtual bool setFloat(float value) override;

  /**
   * Method returns the current variant value as an float
   *
   * @return variant value as an float
   */
  virtual float toFloat() const override;
};

} // namespace Mplane

#endif /* DATAVARIANTFLOAT_H_ */
